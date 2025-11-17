#pragma once

#ifdef JSON_DLL_EXPORTS
#define JSON_API __declspec(dllexport)
#else
#define JSON_API __declspec(dllimport)
#endif

#include <framework.h>

extern "C"
{
    // Writes JSON text into a file
    JSON_API bool WriteJsonFile(const char* filename, const char* jsonText);

    // Reads JSON file content
    JSON_API const char* ReadJsonFile(const char* filename);

    // Extracts value of a key from a JSON object like { "key": "value" }
    JSON_API const char* GetJsonValue(const char* jsonText, const char* key);

    // Creates a simple JSON object: { "key": "value" }
    JSON_API const char* CreateJsonObject(const char* key, const char* value);
}
