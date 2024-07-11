#pragma once

// Disable the false warnings caused by the wrong definitions of SetWindowLongPtr
// and GetWindowLongPtr macros.
#pragma warning ( disable : 4244 )
#pragma warning(disable : 4996)

// Windows Header Files:
#include <atlbase.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <sapi.h>
#include <sphelper.h>
#include <stdio.h>
#include "tom.h"
#include "recomgr.h"
#include "textrunlist.h"
#include <flutter/plugin_registrar_windows.h>
#include <flutter/method_channel.h>

// Flags that determine the state of the app
typedef enum DPFLAGS
{
    DP_DICTATION_MODE     = ( 1L << 0 ),    // Toggles between dictation and command mode
    DP_WHOLE_WORD_SEL     = ( 1L << 1 ),    // Indicates that whole words should be selected
    DP_MICROPHONE_ON      = ( 1L << 2 ),    // Indicates that the "mic" is on (really that 
                                            // the appropriate grammars are active
    DP_SHARED_RECOGNIZER  = ( 1L << 3 ),    // Shared reco engine (false if engine is inproc)
    DP_IS_SPEAKING        = ( 1L << 4 ),    // Indicates that we are in the midst of a playback
    DP_GRAMMARS_ACTIVE    = ( 1L << 5 ),    // Indicates the the "mic" is on
    DP_JUST_PASTED_TEXT   = ( 1L << 6 ),    // Indicates that text has just been pasted
    DP_SKIP_UPDATE        = ( 1L << 7 )     // Indicates that selection changes should not be processed
} DPFLAGS;


// There are three grammars loaded
 enum GRAMMARIDS
{
    GID_DICTATION,      // ID for the dictation grammar
    GID_DICTATIONCC,    // ID for the C&C grammar that's active during dictation
    GID_CC              // ID for the C&C grammar that's active when dictation is not
};

typedef std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> FlutterResult;

// Constants
#define WM_DICTRECOEVENT    WM_USER + 1

class SAPI {

    public:

        static SAPI& getInstance()
        {
            static SAPI instance;
            return instance;
        }
        // Initialization method
        HRESULT InitializeSAPIObjs();   // Set up the SAPI objects
        SAPI(SAPI const&) = delete;
        void operator=(SAPI const&) = delete;
    
    private:
        SAPI() {
        }

        // Win32-related handles
        HACCEL m_hAccelTable;               // handle to the accelerators
        HINSTANCE m_hInst;                  // handle to the current instance
        HWND  m_hClient;                  // handle to the app's client window

        // Application state
        DWORD m_dwFlags;                  // DPFLAGS (see above)
        TCHAR *m_pszFile;                   // Name of the current file

        HRESULT InitSAPICallback( HWND hWnd );   // Hook up the client for SAPI notifications
        HRESULT LoadGrammars();           // Load the various grammars

        
        // SAPI objects
        CComPtr<ISpRecognizer> m_cpRecoEngine;    // SR engine
        CComPtr<ISpRecoContext> m_cpDictRecoCtxt; // Recognition context for dictation
        CRecoEventMgr *m_pRecoEventMgr;           // Handles placement of recognized text (recomgr.cpp)
        CComPtr<ISpRecoGrammar> m_cpDictGrammar;    // Dictation grammar 
        ULONGLONG m_ullDictInterest;          // Events in which DictationPad will be interested in
        CTextRunList *m_pTextRunList;               // List of dictated and non-dictated runs (textrunlist.cpp)


};