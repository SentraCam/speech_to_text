#include "sapi.h"


HRESULT SAPI::InitializeSAPIObjs()
{
    HRESULT hr = S_OK;

     // If we're waiting for a recognition, give up on it.
 if ( m_pRecoEventMgr->IsProcessingPhrase()  && (m_dwFlags & DP_DICTATION_MODE) )
 {
     m_pRecoEventMgr->FalseRecognition();
     m_pRecoEventMgr->DoneProcessingPhrase();
 }

    return hr;
}