#pragma once

#include <windows.h>

struct DumpOptions
{
    bool handle_hijack;
    // bool kernel_mode;
};

int dmpproc(unsigned int pid, const char* outputPath, DumpOptions* options);

class Dumper
{
public:
	~Dumper();

	bool GetProcess(unsigned int pid);
    bool GetSnapshot(unsigned int pid);
private:
    HANDLE hProcess{};
	HANDLE hSnapshot{};
};