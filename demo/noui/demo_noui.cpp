// This is free and unencumbered software released into the public domain.
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// For more information, please refer to <http://unlicense.org/>

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <thread>
#include <atomic>

#if defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#endif

//generate zipped results
#define MICROPROFILE_MINIZ 1
#if MICROPROFILE_MINIZ
#include "miniz.c"
#endif



#define MICROPROFILE_MAX_FRAME_HISTORY (2<<10)
#define MICROPROFILE_IMPL
#include "microprofile.h"

MICROPROFILE_DEFINE(MAIN, "MAIN", "Main", 0xff0000);

#ifdef _WIN32
void usleep(__int64);
#endif
uint32_t g_nQuit = 0;

void StartFakeWork();
void StopFakeWork();


int main(int argc, char* argv[])
{
	MicroProfileOnThreadCreate("Main");
	printf("press ctrl-c to quit\n");

	//turn on profiling
	MicroProfileSetForceEnable(true);
	MicroProfileSetEnableAllGroups(true);
	MicroProfileSetForceMetaCounters(true);

	MicroProfileStartContextSwitchTrace();


	MICROPROFILE_COUNTER_ADD("memory/main", 1000);
	MICROPROFILE_COUNTER_ADD("memory/gpu/vertexbuffers", 1000);
	MICROPROFILE_COUNTER_ADD("memory/gpu/indexbuffersxsxsxsxsxsxsxxsxsxsxs", 200);
	MICROPROFILE_COUNTER_ADD("memory//main", 1000);
	MICROPROFILE_COUNTER_ADD("memory//", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//mainx/\\//", 1000);
	MICROPROFILE_COUNTER_ADD("//memoryx//mainx/", 1000);
	MICROPROFILE_COUNTER_ADD("//memoryy//main/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main0/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main1/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main2/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main3/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main4/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main5/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main6/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main7/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main8/", 1000);
	MICROPROFILE_COUNTER_ADD("//memory//main9/", 1000);
	MICROPROFILE_COUNTER_ADD("//\\\\///lala////lelel", 1000);


	StartFakeWork();
	while(!g_nQuit)
	{
		MICROPROFILE_SCOPE(MAIN);
		{
			usleep(16000);
		}
		MicroProfileFlip();
		static bool once = false;
		if(!once)
		{
			once = 1;
			printf("open localhost:%d in chrome to capture profile data\n", MicroProfileWebServerPort());
		}

	}

	StopFakeWork();
	
	MicroProfileShutdown();

	return 0;
}
