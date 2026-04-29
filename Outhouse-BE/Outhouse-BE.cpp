// Outhouse-BE.cpp : Defines the exported functions for the DLL.
//

#include <windows.h>
#include "Outhouse-BE.h"

#include "utils.h"

int dmpproc(unsigned int pid, const char* outputPath, DumpOptions* options)
{
    Logger::init_logging(true, false);

    if (!options)
        return -1;

	std::string outputPathStr(outputPath);
    Log("Params: {} {} {}", pid, outputPath, options->handle_hijack);
    return 0;
}

extern "C" OUTHOUSEBE_API int DumpProcess(
    unsigned int pid,
    const char* outputPath,
    DumpOptions* options
)
{
    return dmpproc(pid, outputPath, options);
}