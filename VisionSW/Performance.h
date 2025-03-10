#pragma once

#include <windows.h>
#include <psapi.h>
#include <ctime>

class Performance
{
private : 
	bool isRun = false;
	size_t memory_before;
	size_t memory_after;
	clock_t time_before;
	clock_t tiem_after;
public : 
	void start() {
		PROCESS_MEMORY_COUNTERS memInfo;
		GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));

		memory_before = memInfo.WorkingSetSize;
		time_before = clock();
		isRun = true;
	}
	void stop() {
		if (!isRun)
			return;
		PROCESS_MEMORY_COUNTERS memInfo;
		GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));

		memory_after = memInfo.WorkingSetSize;
		tiem_after = clock();
		isRun = false;
	}

	size_t getMemoryUsage() {
		return (memory_after - memory_before) / 1024;
	}
	double getProcessingTime() {
		return double(tiem_after - time_before) / CLOCKS_PER_SEC;
	}
};