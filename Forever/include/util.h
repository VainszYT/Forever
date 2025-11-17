#pragma once

#ifdef UTIL_DLL_EXPORTS
#define UTIL_API __declspec(dllexport)
#else
#define UTIL_API __declspec(dllimport)
#endif
#include <framework.h>
extern "C"
{
    // Prints developer info
    UTIL_API void PrintDeveloperInfo();

    // Initializes internal buffers and memory pools
    UTIL_API void InitializeUtilMemory();

    // Frees memory pools on DLL unload
    UTIL_API void ShutdownUtilMemory();

    // Returns time in milliseconds (used to avoid heavy timers)
    UTIL_API unsigned long GetTimeMS();
}
