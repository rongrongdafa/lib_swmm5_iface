// Test of the SWMM5 C Interfacing functions

// This is a command line executable that takes the name
// of a SWMM input file as its only command line argument
// and produces a time series listing to the console of the
// following system output results: total rainfall, total
// runoff and total outfall flow.

// This file must be compiled along with swmm5_iface.c
// and swmm5.h, and linked with swmm5.dll and swmm5.lib.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
typedef int(*Func1)();
typedef void(*Func2)();

int main(int argc, char *argv[])
{
	Func1 RunSwmmDll = NULL;
	Func1 OpenSwmmOutFile = NULL;
	Func1 GetSwmmResult = NULL;
	Func1 getSWMM_Nperiods = NULL;
	Func2 CloseSwmmOutFile = NULL;

	HINSTANCE h = LoadLibraryA("swmm5_iface.dll");

	if (!h)
	{
		printf("load dll faild\n");
		getchar();
	}
	RunSwmmDll = (Func1)GetProcAddress(h, "RunSwmmDll");
	OpenSwmmOutFile = (Func1)GetProcAddress(h, "OpenSwmmOutFile");
	GetSwmmResult = (Func1)GetProcAddress(h, "GetSwmmResult");
	getSWMM_Nperiods = (Func1)GetProcAddress(h, "getSWMM_Nperiods");
	CloseSwmmOutFile = (Func2)GetProcAddress(h, "CloseSwmmOutFile");


	if (RunSwmmDll == NULL || OpenSwmmOutFile == NULL || GetSwmmResult == NULL || getSWMM_Nperiods == NULL || CloseSwmmOutFile == NULL)
	{
		printf("load fun faild\n");
		getchar();
	}
  
	int i, r;
	float x, y, z;
	char rptfile[] = "tmp.rpt";
	char outfile[] = "tmp.out";

	// Check if a SWMM input file name is provided
	if (argc < 2)
	{
		printf("\nNo file name was provided.\n");
		return 0;
	}

	// Run the SWMM analysis
	r = RunSwmmDll(argv[1], rptfile, outfile);
	if (r > 0)
	{
		printf("\nSWMM run was unsuccessful; error code = %d\n", r);
	}
	else
	{
		// Open outfile as a SWMM output file
		r = OpenSwmmOutFile(outfile);
		if (r == 1)
		{
			printf("\nInvalid results in SWMM output file.\n");
		}
		else if (r == 2)
		{
			printf("\nFile is not a SWMM output file.\n");
		}
		else
		{
			printf("\nTime       Total     Total     Total");
			printf("\nPeriod  Rainfall    Runoff   Outflow");
			printf("\n====================================");
			for (i = 1; i <= getSWMM_Nperiods(); i++)
			{
				GetSwmmResult(3, 0, 1, i, &x);
				GetSwmmResult(3, 0, 4, i, &y);
				GetSwmmResult(3, 0, 11, i, &z);
				printf("\n%6d  %8.2f  %8.2f  %8.2f", i, x, y, z);
			}
			CloseSwmmOutFile();
		}
	}
	/*remove(rptfile);
	remove(outfile);*/
	FreeLibrary(h);
	return 0;
}