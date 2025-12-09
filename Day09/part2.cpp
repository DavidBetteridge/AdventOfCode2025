#include "common.cpp"
#include <set>
#include <map>

struct tile
{
    long x;
    long y;

    tile(long x, long y) : x(x), y(y) {};
};

struct vertical_line
{
    long x;
    long start_y;
    long end_y;
    vertical_line(long x, long start_y, long end_y) : x(x), start_y(start_y), end_y(end_y) {};
};

struct horizontal_line
{
    long y;
    long start_x;
    long end_x;
    horizontal_line(long y, long start_x, long end_x) : y(y), start_x(start_x), end_x(end_x) {};
};

int main()
{
    auto lines = read_lines_from_file("sample1.txt");
    
    std::vector<tile> original_tiles;
    std::set<long> xs;
    std::set<long> ys;
    for(const auto &line : lines)
    {
        auto parts = split_to_long(line,",");
        original_tiles.emplace_back(parts[0], parts[1]);
        xs.insert(parts[0]);
        ys.insert(parts[1]);
    }

    // Old to new
    std::map<long,long> x_lookup;
    auto ind = 0;
    for(const auto & x : xs )
    {
        x_lookup[x] = ind;
        ind++;
    }

    std::map<long,long> y_lookup;
    ind = 0;
    for(const auto & y : ys )
    {
        y_lookup[y] = ind;
        ind++;
    }


    // Remap all the tiles
    std::vector<tile> compact_tiles;
    for(const auto &tile : original_tiles)
        compact_tiles.emplace_back(x_lookup[tile.x], y_lookup[tile.y]);


    // Build the ranges
    std::vector<vertical_line> vertical_lines;
    std::vector<horizontal_line> horizontal_lines;
    for(auto i=0; i < compact_tiles.size(); i++)
    {
        auto j = (i + 1) % compact_tiles.size();

        if (compact_tiles[i].x == compact_tiles[j].x)
        {
            // Vertical line
            if (compact_tiles[i].y < compact_tiles[j].y)
                vertical_lines.emplace_back(compact_tiles[i].x, compact_tiles[i].y, compact_tiles[j].y);
            else
                vertical_lines.emplace_back(compact_tiles[i].x, compact_tiles[j].y, compact_tiles[i].y);
        }
        else
        {
            // Horizontal line
            if (compact_tiles[i].x < compact_tiles[j].x)
                horizontal_lines.emplace_back(compact_tiles[i].y, compact_tiles[i].x, compact_tiles[j].x);
            else
                horizontal_lines.emplace_back(compact_tiles[i].y, compact_tiles[j].x, compact_tiles[i].x);            
        }

    }

    long largest = 0;
    long largest2 = 0;
    for(auto i=0; i < original_tiles.size()-1; i++)
    {
        for(auto j=i+1; j < original_tiles.size(); j++)
        {
            auto size = (abs(original_tiles[i].x - original_tiles[j].x)+1) * (abs(original_tiles[i].y - original_tiles[j].y)+1);
            if (size > largest) 
            {
                // Does this only include green/red original_tiles
                largest2 = (abs(compact_tiles[i].x - compact_tiles[j].x)+1) * (abs(compact_tiles[i].y - compact_tiles[j].y)+1);
                largest = size;

                // Every perimmiter cell has to be in the range.

                // e.g top row      compact_tiles[i].x, compact_tiles[i].y --> compact_tiles[j].x, compact_tiles[i].y
                // so for all compact_tiles[i].x ==> compact_tiles[j].x
                // Must be a horizontal range with y=compact_tiles[i].y,  startX <= compact_tiles[i].x and endY >= compact_tiles[j].x 
            }
        }
    }


    std::cout << largest << ' ' << largest2;

}