#include "util.h"
// --------------------------
// Simple memory pool
// --------------------------

static const int UTIL_POOL_SIZE = 4096;   // Small optimized pool
static unsigned char utilPool[UTIL_POOL_SIZE];
static bool utilPoolUsed[UTIL_POOL_SIZE] = { false };

// Allocates small blocks from the pool (very fast)
static void* UtilAlloc(size_t size)
{
    if (size == 0 || size > UTIL_POOL_SIZE)
        return nullptr;

    for (int i = 0; i <= UTIL_POOL_SIZE - size; i++)
    {
        bool blockFree = true;

        for (size_t j = 0; j < size; j++)
        {
            if (utilPoolUsed[i + j])
            {
                blockFree = false;
                break;
            }
        }

        if (blockFree)
        {
            for (size_t j = 0; j < size; j++)
                utilPoolUsed[i + j] = true;

            return &utilPool[i];
        }
    }

    return nullptr;
}

// Frees a block back to the pool
static void UtilFree(void* ptr, size_t size)
{
    if (!ptr) return;

    unsigned char* start = (unsigned char*)ptr;
    unsigned char* base = utilPool;

    if (start < base || start >= base + UTIL_POOL_SIZE)
        return;

    size_t offset = start - base;

    for (size_t i = offset; i < offset + size && i < UTIL_POOL_SIZE; i++)
        utilPoolUsed[i] = false;
}

// --------------------------
// API FUNCTIONS
// --------------------------

void PrintDeveloperInfo()
{
    OutputDebugStringA("Forever DLL By Vainsz\n");
    std::cout << "Forever DLL By Vainsz" << std::endl;
}

// Initializes optimized memory
void InitializeUtilMemory()
{
    ZeroMemory(utilPool, UTIL_POOL_SIZE);
    ZeroMemory(utilPoolUsed, UTIL_POOL_SIZE);

    OutputDebugStringA("[UTIL] Memory pool initialized.\n");
}

// Frees everything safely
void ShutdownUtilMemory()
{
    ZeroMemory(utilPool, UTIL_POOL_SIZE);
    ZeroMemory(utilPoolUsed, UTIL_POOL_SIZE);

    OutputDebugStringA("[UTIL] Memory pool shutdown.\n");
}

// Lightweight timing (very fast)
unsigned long GetTimeMS()
{
    return GetTickCount();
}
