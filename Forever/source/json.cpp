#include <json.h>

static std::string lastResult; // Used to hold returned strings

bool WriteJsonFile(const char* filename, const char* jsonText)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    file << jsonText;
    file.close();
    return true;
}

const char* ReadJsonFile(const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        lastResult = "ERROR: Could not open JSON file.";
        return lastResult.c_str();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    lastResult = buffer.str();
    return lastResult.c_str();
}

const char* CreateJsonObject(const char* key, const char* value)
{
    lastResult = "{ \"" + std::string(key) + "\": \"" + std::string(value) + "\" }";
    return lastResult.c_str();
}

static void trim(std::string& s)
{
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

const char* GetJsonValue(const char* jsonText, const char* key)
{
    std::string text = jsonText;
    trim(text); // remove whitespace

    std::string searchKey = "\"" + std::string(key) + "\":";

    size_t pos = text.find(searchKey);
    if (pos == std::string::npos)
    {
        lastResult = "ERROR: Key not found";
        return lastResult.c_str();
    }

    pos += searchKey.length();

    // Find first quote after key:
    size_t firstQuote = text.find("\"", pos);
    size_t secondQuote = text.find("\"", firstQuote + 1);

    if (firstQuote == std::string::npos || secondQuote == std::string::npos)
    {
        lastResult = "ERROR: Invalid JSON format";
        return lastResult.c_str();
    }

    lastResult = text.substr(firstQuote + 1, secondQuote - firstQuote - 1);
    return lastResult.c_str();
}
