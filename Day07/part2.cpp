#include "common.cpp"

int main()
{
    
    auto lines = read_lines_from_file("input.txt");
    auto width = lines[0].size();
    auto height = lines.size();

    std::vector<bool> beams;
    std::vector<long> routes;
    for(auto i=0;i<width;i++)
    {
        beams.push_back(lines[0][i] == 'S');
        routes.push_back(lines[0][i] == 'S' ? 1 : 0);
    }
       
    
    for(auto r=0;r<height-1;r++)
    {
        std::vector<bool> new_beams;
        std::vector<long> new_routes;
        for(auto i=0;i<width;i++)
        {
            new_beams.push_back(false);
            new_routes.push_back(0);
        }

        for(auto c=0;c<width;c++)
        {
            if (beams[c])
            {
                if (lines[r+1][c] == '^')
                {
                    new_beams[c-1] = true;
                    new_beams[c+1] = true;
                    new_routes[c-1] = new_routes[c-1] + routes[c];
                    new_routes[c+1] = new_routes[c+1] + routes[c];
                }
                else
                {
                    new_beams[c] = true;
                    new_routes[c] = new_routes[c] + routes[c];
                }
            }
        }

        beams = new_beams;
        routes = new_routes;
    }
    
    long total = 0;
    for(auto i=0;i<width;i++)
    {
        total+=routes[i];
    }

    std::cout << total;
}