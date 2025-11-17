#pragma once

#ifdef SMSI_DLL_EXPORTS
#define SMSI_API __declspec(dllexport)
#else
#define SMSI_API __declspec(dllimport)
#endif
#include <framework.h>
extern "C"
{
    // Updates mouse delta and button state each frame
    SMSI_API void UpdateMouseState();

    // Get mouse movement delta since last frame
    SMSI_API void GetMouseDelta(int* dx, int* dy);

    // Check if a mouse button is pressed
    // Example: VK_LBUTTON, VK_RBUTTON, VK_MBUTTON
    SMSI_API bool IsMouseButtonPressed(int vKey);

    // Set the sensitivity value
    SMSI_API void SetMouseSensitivity(float sens);

    // Get current sensitivity value
    SMSI_API float GetMouseSensitivity();

    // Save sensitivity + mouse config to a file
    SMSI_API bool SaveMouseSettings(const char* filename);

    // Load sensitivity + mouse config from a file
    SMSI_API bool LoadMouseSettings(const char* filename);
}
