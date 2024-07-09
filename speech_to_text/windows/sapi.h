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




class SAPI {
    
    private:

        // Initialization methods
        HRESULT InitializeSAPIObjs();   // Set up the SAPI objects
        HRESULT InitSAPICallback( HWND hWnd );   // Hook up the client for SAPI notifications
        // SAPI objects
        CComPtr<ISpRecognizer> m_cpRecoEngine;    // SR engine
        CComPtr<ISpRecoContext> m_cpDictRecoCtxt;   // Recognition context for dictation
};