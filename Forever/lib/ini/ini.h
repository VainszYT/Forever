#pragma once

#ifdef INI_DLL_EXPORTS
#define INI_API __declspec(dllexport)
#else
#define INI_API __declspec(dllimport)
#endif
#include <framework.h>
extern "C"
{
    // Read entire INI file into memory
    INI_API const char* ReadIniFile(const char* filename);

    // Write entire INI text to a file
    INI_API bool WriteIniFile(const char* filename, const char* text);

    // Get a specific value from [Section] Key=Value
    INI_API const char* GetIniValue(const char* iniText, const char* section, const char* key);

    // Set a value inside [Section] by replacing Key=Value (returns updated text)
    INI_API const char* SetIniValue(const char* iniText,
        const char* section,
        const char* key,
        const char* value);
}
