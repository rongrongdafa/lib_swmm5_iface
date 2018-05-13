// swmm5_iface.h
//
// Header file for SWMM 5 interfacing functions
//
// #include this file in any C module that references the functions
// contained in swmm5_iface.c.
//
#ifndef SWMM5_IFCAE_H
#define SWMM5_IFCAE_H

// --- define WINDOWS

#undef WINDOWS
#ifdef _WIN32
#define WINDOWS
#endif
#ifdef __WIN32__
#define WINDOWS
#endif


#ifdef DLL_EXPORT

#define DECLDIR __declspec(dllexport)

#else

#define DECLDIR __declspec(dllimport)

#endif

// --- use "C" linkage for C++ programs

#ifdef __cplusplus
extern "C" {
#endif 

//extern int    SWMM_Nperiods;           // number of reporting periods
//extern int    SWMM_FlowUnits;          // flow units code
//extern int    SWMM_Nsubcatch;          // number of subcatchments
//extern int    SWMM_Nnodes;             // number of drainage system nodes
//extern int    SWMM_Nlinks;             // number of drainage system links
//extern int    SWMM_Npolluts;           // number of pollutants tracked
//extern double SWMM_StartDate;          // start date of simulation
//extern int    SWMM_ReportStep;         // reporting time step (seconds)

int  DECLDIR  getSWMM_Nperiods();
	 
int  DECLDIR  RunSwmmExe(char* cmdLine);
int  DECLDIR  RunSwmmDll(char* inpFile, char* rptFile, char* outFile);
int  DECLDIR  OpenSwmmOutFile(char* outFile);
int  DECLDIR  GetSwmmResult(int iType, int iIndex, int vIndex, int period, float* value);
void DECLDIR  CloseSwmmOutFile(void);

#ifdef __cplusplus 
}   // matches the linkage specification from above */ 
#endif

#endif