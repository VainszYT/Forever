#include <js.h>

static std::string lastText; // Holds returned text safely

bool RunJsFile(const char* filename)
{
    std::string command = "node ";
    command += filename;

    int result = system(command.c_str());
    return (result == 0);
}

const char* ReadJsFile(const char* filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        lastText = "ERROR: Could not open JS file.";
        return lastText.c_str();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    lastText = buffer.str();
    return lastText.c_str();
}

bool WriteJsFile(const char* filename, const char* text)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << text;
    file.close();
    return true;
}
