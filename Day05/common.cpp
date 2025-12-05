#include <iostream>
#include <fstream>
#include <numeric>
#include <ranges>
#include <vector>
#include <stdexcept>


std::vector<std::string> split(std::string text, std::string sep)
{
    std::vector<std::string> list;
    int start = 0;
    auto end = text.find(sep, start + 1);
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

std::vector<char> splitToChar(std::string text, std::string sep)
{
    std::vector<char> list;
    int start = 0;
    auto end = text.find(sep, start + 1);
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

std::vector<int> splitToInt(std::string text, std::string sep)
{
    std::vector<int> list;
    int start = 0;
    auto end = text.find(sep, start + 1);
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

std::vector<long> split_to_long(std::string text, std::string sep)
{
    std::vector<long> list;
    int start = 0;
    auto end = text.find(sep, start + 1);
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

std::vector<std::string> read_lines_from_file(std::string filename)
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

inline int mod(int a, int b) {
    int ret = a % b;
    return ret >= 0 ? ret : ret + b;
}