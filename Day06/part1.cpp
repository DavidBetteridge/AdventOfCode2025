#include "common.cpp"

std::vector<char> parse_operators(const std::string &line)
{
    std::vector<char> operators;
    for (auto i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
            operators.push_back(line[i]);
    }
    return operators;
}

int main()
{
    auto lines = read_lines_from_file("input.txt");

    auto operators = parse_operators(lines[lines.size()-1]);

    long grand_total = 0;

    std::vector<std::vector<long>> values;
    for(auto line_number=0; line_number < (lines.size()-1); line_number++)
    {
        // Read the values from the line
        std::vector<long> line_values;
        auto line = lines[line_number];
        long current_value = 0;
        for (auto i = 0; i < line.size(); i++)
        {
            if (line[i] != ' ')
                current_value = (current_value * 10) + ( line[i] - '0');
            else
            {
                if (current_value != 0)
                {
                    line_values.push_back(current_value);
                    current_value = 0;
                }
            }
        }
        if (current_value != 0)
            {
                line_values.push_back(current_value);
                current_value = 0;
            }        
        values.push_back(line_values);
    }

    for (auto column_number = 0; column_number < values[0].size(); column_number++)
    {
        // Apply the operator
        long total = operators[column_number] == '+' ? 0 : 1;
        for (auto row_number = 0; row_number < (values.size()); row_number++)
        {
            if (operators[column_number] == '+')
                total += values[row_number][column_number];

            if (operators[column_number] == '*')
                total *= values[row_number][column_number];              
        }

        // std::cout << total << std::endl;
        grand_total += total;
    }

    std::cout << grand_total << std::endl;

}

