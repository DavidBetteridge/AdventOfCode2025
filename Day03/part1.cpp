#include "common.cpp"

// n1 n0
int main()
{
    auto batteries = read_lines_from_file("input.txt");

    long total = 0;
    for(auto const battery : batteries)
    {
        auto n1 = -1;
        auto n1_pos = 0;
        for (size_t i = 0; i < battery.size() - 1; i++)
        {
            if (battery[i] - '0' > n1)
            {
                n1 = battery[i] - '0';
                n1_pos = i;
            }
        }

        auto n0 = -1;
        for (size_t i = n1_pos+1; i < battery.size(); i++)
        {
            if (battery[i] - '0' > n0)
            {
                n0 = battery[i] - '0';
            }
        }

        total += ( n1 * 10 ) + n0;
    }

    std::cout << total << std::endl;
}