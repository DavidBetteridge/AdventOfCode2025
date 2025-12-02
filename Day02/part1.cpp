#include "common.cpp"

static std::array<int, 8> powers = { 1,10,100,1000,10000,100000,1000000, 10000000 };

int main()
{
    auto lines = read_lines_from_file("input.txt");
    auto ranges = split(lines[0], ",");

    long total = 0;
    for(const auto &range : ranges)
    {
        auto bounds = split_to_long(range,"-");
        for(auto i=bounds[0];i<=bounds[1];i++)
        {
            auto num_length = (int)(log10(i)) + 1;

            auto a = powers[num_length / 2];
            auto repeat = i % a;
            auto times = a + 1;

            if (repeat * times == i )
                total+=i;
        }

    }

    //28146997880
    std::cout << total << std::endl;
}