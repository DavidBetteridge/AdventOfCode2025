#include "common.cpp"

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
            auto num = std::to_string(i);
            auto isInValid = false;
            for(auto size=1; size<=num.size()/2; size++)
            {
                if (num.size() % size == 0)
                {
                    auto d = size;
                    auto first = std::stoi(num.substr(0, d));
                    auto ok = true;
                    while (d < num.size())
                    {
                        auto next = std::stoi(num.substr(d, size));
                        if (first != next) 
                        {
                            ok = false;
                            break;
                        }
                        d+=size;
                    }

                    if (ok)
                    {
                        isInValid = true;
                        break;
                    }
                }
            }

            if (isInValid)
                total+=i;

        }


    }

    std::cout << total << std::endl;
}