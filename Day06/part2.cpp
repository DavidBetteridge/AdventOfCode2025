#include "common.cpp"

std::vector<int> parse_operators(const std::string &line)
{
    std::vector<int> columns;
    for (auto i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
            columns.push_back(i);
    }
    return columns;
}

int main()
{
    auto lines = read_lines_from_file("input.txt");

    auto operators = lines[lines.size()-1];
    auto group_starts = parse_operators(operators);

    long grand_total = 0;

    for(auto group_number=0; group_number<group_starts.size(); group_number++)
    {
        auto group_start = group_starts[group_number];
        auto group_end = (group_number<(group_starts.size()-1)) ? group_starts[group_number+1]-1 : operators.size();
        auto op = operators[group_start];

        long total = op == '+' ? 0 : 1;
        for(auto c=group_start;c <group_end;c++)
        {
            long column_value = 0;

            // In each column, we need to find the first and last row which contains a value
            auto first_row = 0;
            while (lines[first_row][c] == ' ')
                first_row++;

            auto last_row = lines.size()-2;
            while (lines[last_row][c] == ' ')
                last_row--;

            for(int r=first_row;r<=last_row;r++)
            {
                column_value = (column_value * 10);
                if (lines[r][c] != ' ')
                    column_value += (lines[r][c] - '0');
            }
            // std::cout << column_value << ", ";
            if (op == '+')
                total += column_value;

            if (op == '*')
                total *= column_value;                    
        }

        // std::cout << total << std::endl;
        grand_total += total;        
    }


    std::cout << grand_total << std::endl;

}

