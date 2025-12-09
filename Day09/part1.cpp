#include "common.cpp"

struct tile
{
    long x;
    long y;

    tile(long x, long y) : x(x), y(y) {};
};

int main()
{
    auto lines = read_lines_from_file("input.txt");
    
    std::vector<tile> tiles;
    for(const auto &line : lines)
    {
        auto parts = split_to_long(line,",");
        tiles.emplace_back(parts[0], parts[1]);
    }

    long largest = 0;


    for(auto i=0; i < tiles.size()-1; i++)
    {
        for(auto j=i+1; j < tiles.size(); j++)
        {
            auto size = (abs(tiles[i].x - tiles[j].x)+1) * (abs(tiles[i].y - tiles[j].y)+1);
            if (size > largest) largest = size;
        }
    }


    std::cout << largest;

}