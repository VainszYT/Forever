#pragma once
#ifdef PYTHON_DLL_EXPORTS
#define PY_API __declspec(dllexport)
#else
#define PY_API __declspec(dllimport)
#endif

#include <framework.h>

extern "C"
{
	PY_API bool RunPythonFile(const char* filename);

	PY_API const char* ReadPythonFile(const char* filename);

	PY_API bool WritePythonFile(const char* filename, const char* text);
}