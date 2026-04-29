// Outhouse-BE.cpp : Defines the exported functions for the DLL.
//

#include <windows.h>
#include "Outhouse-BE.h"

extern "C" OUTHOUSEBE_API int DumpProcess(
    unsigned int pid,
    const char* outputPath,
    DumpOptions* options
)
{
    return dmpproc(pid, outputPath, options);
}