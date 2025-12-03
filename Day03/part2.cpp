#include "common.cpp"

int main()
{
    auto batteries = read_lines_from_file("input.txt");

    long total = 0;
    for(auto const battery : batteries)
    {
        long batteryTotal = 0;
        auto n_pos = -1;
        for (size_t x = 1; x <= 12; x++)
        {
            auto n = -1;
            for (size_t i = n_pos+1; i < battery.size() - (12 - x); i++)
            {
                if (battery[i] - '0' > n)
                {
                    n = battery[i] - '0';
                    n_pos = i;
                }
            }
            batteryTotal*=10;
            batteryTotal+=n;
        }
        

        total += batteryTotal;
    }

    std::cout << total << std::endl;
}