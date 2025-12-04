#include "common.cpp"

static std::array<std::pair<int,int>, 8> moves = {
    std::pair<int,int>(-1,-1 ),
    std::pair<int,int>(-1,+0 ),
    std::pair<int,int>(-1,+1 ),
    std::pair<int,int>(0,+1 ),
    std::pair<int,int>(0,-1 ),
    std::pair<int,int>(+1,-1 ),
    std::pair<int,int>(+1,+0 ),
    std::pair<int,int>(+1,+1 ),
};

int main()
{
    auto lines = read_lines_from_file("input.txt");
    auto height = lines.size();
    auto width = lines[0].size();

    std::vector<bool> grid;
    for(auto r=0;r<height;r++)
    {
        for(auto c=0;c<width;c++)
            grid.push_back(lines[r][c] == '@');
    }


    auto grand_total = 0;
    auto next_grid = grid; //Copy
    auto total = -1;
    while (total != 0)
    {
        total = 0;
        for(auto r=0;r<height;r++)
        {
            for(auto c=0;c<width;c++)
            {
                auto index = (width * r) + c;
                if (grid[index])
                {
                    auto rolls = 0;
                    for(auto const &move : moves)
                    {
                        auto x = c + move.first;
                        auto y = r + move.second;
                        if (x >= 0 && x < width && y >= 0 && y < height && grid[(width * y) + x])
                            rolls++;
                    }

                    if (rolls < 4)
                    {
                        total++;
                        next_grid[index]=false;
                    }
                }
            }
        }
        grand_total += total;
        grid = next_grid; //Copy
    }

    std::cout << grand_total << std::endl;

}