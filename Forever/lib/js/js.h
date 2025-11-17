#pragma once

#ifdef JS_DLL_EXPORTS
#define JS_API __declspec(dllexport)
#else
#define JS_API __declspec(dllimport)
#endif
#include <framework.h>
#include <nlohmann/json.hpp>
extern "C"
{
    // Runs a .js file using Node.js
    JS_API bool RunJsFile(const char* filename);

    // Reads a JavaScript file
    JS_API const char* ReadJsFile(const char* filename);

    // Writes a JavaScript file
    JS_API bool WriteJsFile(const char* filename, const char* text);
}
