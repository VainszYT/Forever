#pragma once

#ifdef KSI_DLL_EXPORTS
#define KSI_API __declspec(dllexport)
#else
#define KSI_API __declspec(dllimport)
#endif

#include <framework.h>

extern "C"
{
    // Call each frame to update input status
    KSI_API void UpdateKeyboardState();

    // Check if a specific key is pressed
    KSI_API bool IsKeyPressed(int vKey);

    // Save a key binding to file
    KSI_API bool SaveKeyBinding(const char* filename, const char* action, int vKey);

    // Load a key binding from file
    KSI_API int LoadKeyBinding(const char* filename, const char* action);
}
