#include <SaveMouseSensAndInputs.h>

static int lastMouseX = 0;
static int lastMouseY = 0;
static int deltaX = 0;
static int deltaY = 0;

static float mouseSensitivity = 1.0f;

// Updates mouse movement and buttons (call once per frame)
void UpdateMouseState()
{
    POINT p;
    GetCursorPos(&p);

    deltaX = (p.x - lastMouseX);
    deltaY = (p.y - lastMouseY);

    lastMouseX = p.x;
    lastMouseY = p.y;
}

void GetMouseDelta(int* dx, int* dy)
{
    if (dx) *dx = (int)(deltaX * mouseSensitivity);
    if (dy) *dy = (int)(deltaY * mouseSensitivity);
}

bool IsMouseButtonPressed(int vKey)
{
    return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}

void SetMouseSensitivity(float sens)
{
    if (sens < 0.1f) sens = 0.1f;
    if (sens > 20.0f) sens = 20.0f;
    mouseSensitivity = sens;
}

float GetMouseSensitivity()
{
    return mouseSensitivity;
}

// Saves mouse sensitivity to a config file
bool SaveMouseSettings(const char* filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << "sensitivity=" << mouseSensitivity << "\n";
    file.close();
    return true;
}

// Loads mouse sensitivity from config file
bool LoadMouseSettings(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.rfind("sensitivity=", 0) == 0)
        {
            float value = std::stof(line.substr(13));
            SetMouseSensitivity(value);
        }
    }

    return true;
}
