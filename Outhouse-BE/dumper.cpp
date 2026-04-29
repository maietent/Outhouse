#include "dumper.h"
#include "utils.h"

#include <TlHelp32.h>

int dmpproc(unsigned int pid, const char* outputPath, DumpOptions* options)
{
    Logger::init_logging(true, false);

    if (!options)
        return -1;

    std::string outputPathStr(outputPath);
    Log("Params: {} {} {}", pid, outputPath, options->handle_hijack);

    Dumper dumper{};

    /* open process */
	if (!dumper.GetProcess(pid))
    {
        Log("Failed to get process handle for PID: {}. GetLastError:", pid, GetLastError());
        return -1;
    }

	/* get snapshot */
	if (!dumper.GetSnapshot(pid))
    {
        Log("Failed to get snapshot for PID: {}. GetLastError:", pid, GetLastError());
        return -1;
    }

    return 0;
}

Dumper::~Dumper()
{
	CloseHandle(hProcess);
    CloseHandle(hSnapshot);
}

bool Dumper::GetProcess(unsigned int pid)
{
    if (!pid)
        return false;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (hProcess == INVALID_HANDLE_VALUE)
    {
        return false;
	}

    return true;
}

bool Dumper::GetSnapshot(unsigned int pid)
{
    if (!pid)
        return false;

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    return true;
}
