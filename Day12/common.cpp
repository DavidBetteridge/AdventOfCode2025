#include <iostream>
#include <fstream>
#include <ranges>
#include <vector>


std::vector<std::string> split(const std::string& text, const std::string &sep)
{
    std::vector<std::string> list;
    size_t start = 0;
    size_t end = 0;
    while (start < text.length())
    {
        end = text.find(sep, start + 1);
        if (end == std::string::npos)
            end = text.length();

        list.push_back(text.substr(start, end - start));
        start = end + sep.size();
    }
    return list;
}

std::vector<char> splitToChar(const std::string& text, const std::string &sep)
{
    std::vector<char> list;
    size_t start = 0;
    size_t end = 0;
    while (start < text.length())
    {
        end = text.find(sep, start + 1);
        if (end == std::string::npos)
            end = text.length();

        list.push_back(text.substr(start, end - start)[0]);
        start = end + sep.size();
    }
    return list;
}

std::vector<int> splitToInt(const std::string& text, const std::string &sep)
{
    std::vector<int> list;
    size_t start = 0;
    size_t end = 0;
    while (start < text.length())
    {
        end = text.find(sep, start + 1);
        if (end == std::string::npos)
            end = text.length();

        auto value = text.substr(start, end - start);
        list.push_back(std::stoi(value));
        start = end + sep.size();
    }
    return list;
}

std::vector<long> split_to_long(const std::string& text, const std::string &sep)
{
    std::vector<long> list;
    size_t start = 0;
    size_t end = 0;
    while (start < text.length())
    {
        end = text.find(sep, start + 1);
        if (end == std::string::npos)
            end = text.length();

        auto value = text.substr(start, end - start);
        list.push_back(std::stol(value));
        start = end + sep.size();
    }
    return list;
}

std::vector<std::string> read_lines_from_file(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (!file.is_open())
    { 
        std::cerr << "Error: Could not open file. " << filename << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

inline int mod(const int a, const int b) {
    const int ret = a % b;
    return ret >= 0 ? ret : ret + b;
}