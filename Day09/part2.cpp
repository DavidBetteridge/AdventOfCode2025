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
    horizontal_line(long y, long start_x, long end_x, long y_original, long start_x_original, long end_x_original) : 
        y(y), start_x(start_x), end_x(end_x) {};
};

int main()
{
    auto lines = read_lines_from_file("input.txt");
    
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
    for(auto i=0; i < original_tiles.size()-1; i++)
    {
        for(auto j=i+1; j < original_tiles.size(); j++)
        {
            auto size = (abs(original_tiles[i].x - original_tiles[j].x)+1) * (abs(original_tiles[i].y - original_tiles[j].y)+1);
            if (size > largest) 
            {
                auto fromX = compact_tiles[i].x;
                auto toX = compact_tiles[j].x;
                auto fromY = compact_tiles[i].y;
                auto toY = compact_tiles[j].y;
                if (toX < fromX) std::swap(fromX,toX);
                if (toY < fromY) std::swap(fromY,toY);

                // Horzontal rows
                auto ok = true;
                for(auto c=fromX; c <= toX; c++)
                {
                    auto i_match = false;
                    auto j_match = false;
                    for(const auto &horizontal_line : horizontal_lines)
                    {
                        if (horizontal_line.y <= fromY && horizontal_line.start_x <= c && horizontal_line.end_x >= c)
                            i_match = true;

                        if (horizontal_line.y >= toY && horizontal_line.start_x <= c && horizontal_line.end_x >= c)
                            j_match = true;      
                            
                        if (i_match && j_match) break;
                    }

                    if (!i_match || !j_match) 
                    {
                        ok=false;
                        break;
                    }
                }
                if (!ok) continue;


                // Vertical rows
                for(auto c=fromY; c <= toY; c++)
                {
                    auto i_match = false;
                    auto j_match = false;
                    for(const auto &vertical_line : vertical_lines)
                    {
                        if (vertical_line.x <= fromX && vertical_line.start_y <= c && vertical_line.end_y >= c)
                            i_match = true;

                        if (vertical_line.x >= toX && vertical_line.start_y <= c && vertical_line.end_y >= c)
                            j_match = true;      
                            
                        if (i_match && j_match) break;
                    }

                    if (!i_match || !j_match) 
                    {
                        ok=false;
                        break;
                    }
                }
                if (!ok) continue;

                largest = size;
            }
        }
    }


    std::cout << largest;

}