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

    auto total = 0;


    for(auto r=0;r<height;r++)
    {
        for(auto c=0;c<width;c++)
        {
            if (lines[r][c] == '@')
            {
                auto rolls = 0;
                for(auto const &move : moves)
                {
                    auto x = c + move.first;
                    auto y = r + move.second;
                    if (x >= 0 && x < width && y >= 0 && y < height && lines[y][x] == '@')
                        rolls++;
                }

                if (rolls < 4)
                    total++;
            }
        }
    }



    std::cout << total << std::endl;

}