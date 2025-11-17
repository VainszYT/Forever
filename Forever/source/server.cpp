#include "server.h"

static std::string lastResponse;
static PROCESS_INFORMATION serverProcess = { 0 };

// Start the server using a .bat file
bool StartServerBat(const char* batFilePath)
{
    if (!batFilePath) return false;

    STARTUPINFOA si = { sizeof(si) };
    ZeroMemory(&serverProcess, sizeof(serverProcess));

    BOOL success = CreateProcessA(
        nullptr,
        (LPSTR)batFilePath,
        nullptr,
        nullptr,
        FALSE,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &si,
        &serverProcess
    );

    return success == TRUE;
}

// Stop the server process
void StopServer()
{
    if (serverProcess.hProcess)
    {
        TerminateProcess(serverProcess.hProcess, 0);
        CloseHandle(serverProcess.hProcess);
        CloseHandle(serverProcess.hThread);
        serverProcess = { 0 };
    }
}

// Connect to http://localhost:3551 and get response
const char* ConnectToLocalServer()
{
    const wchar_t* server = L"localhost";
    INTERNET_PORT port = 3551;

    HINTERNET hSession = WinHttpOpen(L"ForeverDLL/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (!hSession) return "ERROR: Could not open WinHTTP session";

    HINTERNET hConnect = WinHttpConnect(hSession, server, port, 0);
    if (!hConnect)
    {
        WinHttpCloseHandle(hSession);
        return "ERROR: Could not connect to server";
    }

    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/", nullptr, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (!hRequest)
    {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return "ERROR: Could not open request";
    }

    BOOL bResults = WinHttpSendRequest(hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        0,
        0);

    if (!bResults)
    {
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return "ERROR: Failed to send request";
    }

    bResults = WinHttpReceiveResponse(hRequest, nullptr);
    if (!bResults)
    {
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return "ERROR: Failed to receive response";
    }

    DWORD dwSize = 0;
    lastResponse.clear();

    do
    {
        DWORD dwDownloaded = 0;
        if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) break;
        if (dwSize == 0) break;

        char* buffer = new char[dwSize + 1];
        ZeroMemory(buffer, dwSize + 1);

        if (!WinHttpReadData(hRequest, buffer, dwSize, &dwDownloaded))
        {
            delete[] buffer;
            break;
        }

        lastResponse.append(buffer, dwDownloaded);
        delete[] buffer;

    } while (dwSize > 0);

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return lastResponse.c_str();
}
