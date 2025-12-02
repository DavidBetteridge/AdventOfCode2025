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
            auto is_invalid = false;
            for(auto size=1; size<=num_length/2; size++) //12341234 num_length=8, size 1...4
            {
                auto slices = num_length / size;   // slices 8.6.4.2

                auto a = powers[num_length / slices];  // 10,100,1000,10000
                auto repeat = i % a;    // 4,  34,  234,  1234

                // TODO Replace with a lookup
                auto times = 1;
                for(auto k=1; k<slices; k++)
                {
                    times += pow(a,k);
                }

                if (repeat * times == i )
                {
                    is_invalid = true;
                    break;
                }

            }


            if (is_invalid )
                total+=i;
        }


    }

    std::cout << total << std::endl;
}

//40028128307