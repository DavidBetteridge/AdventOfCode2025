#include "common.cpp"

struct range
{
    long from;
    long to;
    range(long f, long t) : from(f), to(t) {}
};

int main()
{
    auto lines = read_lines_from_file("input.txt");

    std::vector<range> ranges;
    std::vector<long> ingredients;

    for(auto const &line : lines)
    {
        auto parts = split(line, "-");
        if (parts.size() == 2)
            ranges.emplace_back(std::stol(parts[0]), std::stol(parts[1]));
        else if (line != "")
            ingredients.emplace_back(std::stol(line));
    }

    long total = 0;
    for(auto const &ingredient : ingredients)
    {
        auto matched = false;
        for(auto const &range : ranges)
        {
            if (ingredient >= range.from && ingredient <= range.to)
            {
                matched = true;
                break;
            }
        }
        if (matched)
            total++;
    }

    std::cout << total << std::endl;
}