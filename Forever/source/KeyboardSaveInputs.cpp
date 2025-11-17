#include <KeyboardSaveInputs.h>

static BYTE currentKeys[256];        // Current key state
static BYTE previousKeys[256] = { 0 }; // Previous frame state

// Updates the state of the keyboard (call this once per frame)
void UpdateKeyboardState()
{
    for (int i = 0; i < 256; i++)
    {
        previousKeys[i] = currentKeys[i];
        currentKeys[i] = (GetAsyncKeyState(i) & 0x8000) ? 1 : 0;
    }
}

// Returns true if key is currently pressed
bool IsKeyPressed(int vKey)
{
    if (vKey < 0 || vKey > 255)
        return false;

    return currentKeys[vKey] == 1;
}

// Saves a key binding to a simple text format: action=vkey
bool SaveKeyBinding(const char* filename, const char* action, int vKey)
{
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
        return false;

    file << action << "=" << vKey << "\n";
    file.close();
    return true;
}

// Loads a key binding by reading "action=vKey" from file
int LoadKeyBinding(const char* filename, const char* action)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return -1;

    std::string line;
    std::string target = std::string(action) + "=";

    while (std::getline(file, line))
    {
        if (line.rfind(target, 0) == 0) // starts with target
        {
            int vKey = std::stoi(line.substr(target.length()));
            return vKey;
        }
    }

    return -1; // Not found
}
