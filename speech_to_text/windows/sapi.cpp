#include "sapi.h"
#include <iostream>


HRESULT SAPI::InitializeSAPIObjs()
{
    HRESULT hr = S_OK;

     // If we're waiting for a recognition, give up on it.
 if ( m_pRecoEventMgr->IsProcessingPhrase()  && (m_dwFlags & DP_DICTATION_MODE) )
 {
     m_pRecoEventMgr->FalseRecognition();
     m_pRecoEventMgr->DoneProcessingPhrase();
 }

    // Before releasing the dictation reco context, serialize all of the current
    // reco results that depend on this reco context.
    // All of the active reco results live in the text-run list.
    CComPtr<IStream> cpTextRunListStream;
    if ( m_cpDictRecoCtxt )
    {
        if ( !m_pTextRunList )
        {
            _ASSERTE( false );
            return E_UNEXPECTED;
        }

        // Create an IStream for the text-run list and write the serialized
        // text-run list to that stream
        hr = ::CreateStreamOnHGlobal( NULL, TRUE, &cpTextRunListStream );
        if ( SUCCEEDED( hr ) )
        {
            hr = m_pTextRunList->Serialize( 
                cpTextRunListStream, m_cpDictRecoCtxt );
        }

        // Commit the changes to the stream so that we can read them later
        if ( SUCCEEDED( hr ) )
        {
            hr = cpTextRunListStream->Commit( STGC_DEFAULT );
        }

        if ( FAILED( hr ) )
        {
            #ifdef _DEBUG
                std::cerr << "Error serializing the text run list." << std::endl;
            #endif
            return hr;
        }
    }


    // Release the SAPI object in the reverse order in which they
    // were created.  This will ensure that everything really does 
    // get released
    if ( m_cpCCRecoCtxt )
    {
        m_cpCCRecoCtxt.Release();
    }
    if ( m_cpDictRecoCtxt )
    {
        m_cpDictRecoCtxt.Release();
    }
    if ( m_cpRecoEngine )
    {
        m_cpRecoEngine.Release();
    }

     // Inproc reco engine.
    hr = m_cpRecoEngine.CoCreateInstance( CLSID_SpInprocRecognizer );
        
    // For an inproc reco engine, we need to call ISpRecognizer::SetInput() 
    // ourselves.
    CComPtr<ISpObjectToken> cpAudioToken;
    if (SUCCEEDED(hr))
    {
        // Get a token for the default audio input
        hr = SpGetDefaultTokenFromCategoryId(SPCAT_AUDIOIN, &cpAudioToken);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_cpRecoEngine->SetInput(cpAudioToken, TRUE);
    }

    if ( FAILED( hr ) )
    {
        #ifdef _DEBUG
            std::cerr << "Error creating reco engine" << std::endl;
        #endif
        return hr;
    }

    hr = m_cpRecoEngine->CreateRecoContext( &m_cpDictRecoCtxt );
    if ( FAILED( hr ) )
    {
        #ifdef _DEBUG
                std::cerr << "Error creating dictation reco context" << std::endl;
        #endif
        return hr;
    }

        // Now that there is a recognition context, deserialize the text-run list 
    // (serialized before any pre-existing recognition context was released)
    // using the new reco context
    if ( cpTextRunListStream )
    {
        // Move the seek pointer in the stream to the beginning, since
        // that is where we want to start reading from
        LARGE_INTEGER li0;
        ::memset( (void *) &li0, 0, sizeof( li0 ) );
        hr = cpTextRunListStream->Seek( li0, STREAM_SEEK_SET, NULL );

        // Deserialize the text-run list using the new reco context
        if ( SUCCEEDED( hr ) )
        {
            hr = m_pTextRunList->Deserialize( cpTextRunListStream, m_cpDictRecoCtxt );
        }

        if ( FAILED( hr ) )
        {
            #ifdef _DEBUG
                std::cerr << "Error deserializing the text run list" << std::endl;
            #endif
            return hr;
        }
    }


    // Set up the reco context for retaining audio in the dictation reco context.
    // Get the stream format for 8kHz, 8-bit mono
    GUID guidFormatId = GUID_NULL;
    WAVEFORMATEX *pWaveFormatEx = NULL;
    hr = SpConvertStreamFormatEnum(SPSF_8kHz8BitMono, &guidFormatId, &pWaveFormatEx);
    if ( FAILED( hr ) )
    {
        #ifdef _DEBUG
            std::cerr << "Error converting stream format" << std::endl;
        #endif
    }
    else
    {
        // Tell the reco contexts to retain its audio in this format
        hr = m_cpDictRecoCtxt->SetAudioOptions( SPAO_RETAIN_AUDIO, &guidFormatId, pWaveFormatEx );
    }
    
    #ifdef _DEBUG
        if ( FAILED( hr ) )
        {
            std::cerr << "Error setting retained audio data option for dictation reco context" << std::endl;
        }
    #endif

    ::CoTaskMemFree(pWaveFormatEx);
    if ( FAILED( hr ) )
    {
        return hr;
    }

    return hr;
}