#include "common.cpp"

int main()
{
    
    auto lines = read_lines_from_file("input.txt");
    auto width = lines[0].size();
    auto height = lines.size();

    std::vector<bool> beams;
    for(auto i=0;i<width;i++)
        beams.push_back(lines[0][i] == 'S');

    
    auto total = 0;
    for(auto r=0;r<height-1;r++)
    {
        std::vector<bool> new_beams;
        for(auto i=0;i<width;i++)
            new_beams.push_back(false);

        for(auto c=0;c<width;c++)
        {
            if (beams[c])
            {
                if (lines[r+1][c] == '^')
                {
                    new_beams[c-1] = true;
                    new_beams[c+1] = true;
                    total++;
                }
                else
                {
                    new_beams[c] = true;
                }
            }
        }

        beams = new_beams;
    }
    
    std::cout << total;
}