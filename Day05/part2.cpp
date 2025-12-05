#include "common.cpp"
#include <algorithm>

struct range
{
    long from;
    long to;
    range(long f, long t) : from(f), to(t) {}
};

struct compare_ranges
{
    inline bool operator() (const range& range1, const range& range2)
    {
        if (range1.from < range2.from) return true;
        if (range1.to < range2.to) return false;
        return (range1.to < range2.to);
    }
};

int main()
{
    auto lines = read_lines_from_file("input.txt");

    std::vector<range> ranges;

    for(auto const &line : lines)
    {
        if (line == "") break;
        auto parts = split(line, "-");
        ranges.emplace_back(std::stol(parts[0]), std::stol(parts[1]));
    }

    std::sort(ranges.begin(), ranges.end(), compare_ranges());

    auto from = ranges[0].from;
    auto to = ranges[0].to;
    long total = 0;
    for(auto r=1;r<ranges.size();r++)
    {
        if (ranges[r].from > to)
        {
            // The previous range is complete
            total += (to - from + 1);
            from = ranges[r].from;
            to = ranges[r].to;
        }
        else if (ranges[r].to > to)
        {
            // Extend the previous range
            to = ranges[r].to;
        }
    }

    total += (to - from + 1);
    std::cout << total << std::endl;
}
