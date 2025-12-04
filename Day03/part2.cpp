#include "common.cpp"

int main()
{
    auto batteries = read_lines_from_file("input.txt");

    long total = 0;
    for(auto const battery : batteries)
    {
        // auto bt = std::stol(battery.substr(battery.size()-12,12));
        // auto head = floor(bt / pow(10, 11));
        // for (int x = battery.size()-13; x >= 0; x--)
        // {
        //     auto next = battery[x] - '0';
        //     if (next >= head)
        //     {
        //         bt = bt / 10;
        //         bt = bt + (next * pow(10, 11));
        //         head = floor(bt / pow(10, 11));
        //     }
        // }

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

    // 169709990062889
    std::cout << total << std::endl;
}