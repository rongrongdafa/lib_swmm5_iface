//-----------------------------------------------------------------------------
//   swmm5.h
//
//   Project: EPA SWMM5
//   Version: 5.1
//   Date:    03/24/14  (Build 5.1.001)
//            08/01/16  (Build 5.1.011)
//   Author:  L. Rossman
//
//   Prototypes for SWMM5 functions exported to swmm5.dll.
//
//-----------------------------------------------------------------------------
#ifndef SWMM5_H
#define SWMM5_H

// --- define WINDOWS

#undef WINDOWS
#ifdef _WIN32
  #define WINDOWS
#endif
#ifdef __WIN32__
  #define WINDOWS
#endif

// --- define DLLEXPORT

//#ifdef WINDOWS
//  #define DLLEXPORT __declspec(dllexport) __stdcall
//#else
//  #define DLLEXPORT
//#endif

// --- use "C" linkage for C++ programs

#ifdef __cplusplus
extern "C" { 
#endif 

int     swmm_run(char* f1, char* f2, char* f3);
int     swmm_open(char* f1, char* f2, char* f3);
int     swmm_start(int saveFlag);
int     swmm_step(double* elapsedTime);
int     swmm_end(void);
int     swmm_report(void);
int     swmm_getMassBalErr(float* runoffErr, float* flowErr,
        float* qualErr);
int     swmm_close(void);
int     swmm_getVersion(void);
int     swmm_getError(char* errMsg, int msgLen);                      //(5.1.011)
int     swmm_getWarnings(void);                                       //(5.1.011)

#ifdef __cplusplus 
}   // matches the linkage specification from above */ 
#endif

#endif
