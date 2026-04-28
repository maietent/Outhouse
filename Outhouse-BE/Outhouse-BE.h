// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the OUTHOUSEBE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// OUTHOUSEBE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef OUTHOUSEBE_EXPORTS
#define OUTHOUSEBE_API __declspec(dllexport)
#else
#define OUTHOUSEBE_API __declspec(dllimport)
#endif

// This class is exported from the dll
class OUTHOUSEBE_API COuthouseBE {
public:
	COuthouseBE(void);
	// TODO: add your methods here.
};

extern OUTHOUSEBE_API int nOuthouseBE;

OUTHOUSEBE_API int fnOuthouseBE(void);
