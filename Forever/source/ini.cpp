#include <ini.h>

static std::string lastResult;  // Holds returned strings
static std::string modifiedText;

const char* ReadIniFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        lastResult = "ERROR: Could not open INI file.";
        return lastResult.c_str();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    lastResult = buffer.str();
    return lastResult.c_str();
}

bool WriteIniFile(const char* filename, const char* text)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << text;
    file.close();
    return true;
}

static std::string trim(const std::string& s)
{
    std::string out = s;
    out.erase(0, out.find_first_not_of(" \t\r\n"));
    out.erase(out.find_last_not_of(" \t\r\n") + 1);
    return out;
}

const char* GetIniValue(const char* iniText, const char* section, const char* key)
{
    std::string text(iniText);
    std::string line;
    std::stringstream ss(text);

    bool inSection = false;
    std::string targetSection = "[" + std::string(section) + "]";

    while (std::getline(ss, line))
    {
        line = trim(line);

        if (line.empty() || line[0] == ';')
            continue;

        if (line == targetSection)
        {
            inSection = true;
            continue;
        }

        if (inSection)
        {
            if (line[0] == '[')  // next section reached
                break;

            size_t eqPos = line.find('=');
            if (eqPos == std::string::npos)
                continue;

            std::string foundKey = trim(line.substr(0, eqPos));
            std::string foundValue = trim(line.substr(eqPos + 1));

            if (foundKey == key)
            {
                lastResult = foundValue;
                return lastResult.c_str();
            }
        }
    }

    lastResult = "ERROR: Key not found";
    return lastResult.c_str();
}

const char* SetIniValue(const char* iniText,
    const char* section,
    const char* key,
    const char* value)
{
    std::string text(iniText);
    std::stringstream ss(text);
    std::string line;
    std::string output;
    bool inSection = false;
    bool changed = false;

    std::string targetSection = "[" + std::string(section) + "]";

    while (std::getline(ss, line))
    {
        std::string trimmed = trim(line);

        // Enter section
        if (trimmed == targetSection)
        {
            inSection = true;
            output += line + "\n";
            continue;
        }

        // Exit section
        if (inSection && trimmed.size() > 0 && trimmed[0] == '[')
            inSection = false;

        if (inSection)
        {
            size_t eqPos = trimmed.find('=');
            if (eqPos != std::string::npos)
            {
                std::string foundKey = trim(trimmed.substr(0, eqPos));

                if (foundKey == key)
                {
                    // Replace with new value
                    output += std::string(key) + "=" + value + "\n";
                    changed = true;
                    continue;
                }
            }
        }

        output += line + "\n";
    }

    // If key was not found inside the section, append it
    if (!changed)
    {
        // Append missing section if not present
        if (text.find(targetSection) == std::string::npos)
            output += targetSection + "\n";

        output += std::string(key) + "=" + value + "\n";
    }

    modifiedText = output;
    return modifiedText.c_str();
}
