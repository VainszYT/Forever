#include "server.h"

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        // Start the server using your bat file
        StartServerBat("start.bat");

        // Optional: connect immediately to check
        const char* response = ConnectToLocalServer();
        OutputDebugStringA(response);

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
    {
        StopServer(); // Safely terminate server
        break;
    }
    }
    return TRUE;
}
