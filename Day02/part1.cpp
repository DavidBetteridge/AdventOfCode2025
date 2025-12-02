#include "common.cpp"

int main()
{
    auto lines = read_lines_from_file("input.txt");
    auto ranges = split(lines[0], ",");

    long total = 0;
    for(const auto &range : ranges)
    {
        auto bounds = split_to_long(range,"-");
        auto bounds2 = split(range,"-");

        for(auto i=bounds[0];i<=bounds[1];i++)
        {
            auto num = std::to_string(i);
            if (num.size() % 2 == 0)
            {
                auto lhs = std::stoi(num.substr(0, num.size()/2));
                auto rhs = std::stoi(num.substr(num.size()/2, num.size()));
                if (lhs == rhs && num.size() % 2 == 0)
                {
                //  std::cout << i << std::endl;
                    total+=i;
                }
            }
        }

        // std::cout << bounds[0] << '-' << bounds[1] << ' ' << bounds2[1].size() - bounds2[0].size() << std::endl;
        // if (bounds2[1].size() == bounds2[0].size())
        // {
        //     auto lhs0 = std::stoi(bounds2[0].substr(0, bounds2[0].size()/2));
        //     auto rhs0 = std::stoi(bounds2[0].substr(bounds2[0].size()/2, bounds2[0].size()));
        //     auto lhs1 = std::stoi(bounds2[1].substr(0, bounds2[1].size()/2));
        //     auto rhs1 = std::stoi(bounds2[1].substr(bounds2[1].size()/2, bounds2[1].size()));
        // }

    }

    std::cout << total << std::endl;
}