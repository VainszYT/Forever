#pragma once

#ifdef SERVER_DLL_EXPORTS
#define SERVER_API __declspec(dllexport)
#else
#define SERVER_API __declspec(dllimport)
#endif
#include <framework.h>
extern "C"
{
    // Starts the server using a .bat file
    SERVER_API bool StartServerBat(const char* batFilePath);

    // Connects to the local server at http://localhost:3551 and returns the response as string
    SERVER_API const char* ConnectToLocalServer();

    // Stops the server process (optional)
    SERVER_API void StopServer();
}
