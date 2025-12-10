#include "common.cpp"
#include <queue>
#include <unordered_set>

struct queue_entry
{
    int current_state;
    int number_of_button_presses;

    queue_entry(int current_state, int number_of_button_presses) : 
    current_state(current_state), number_of_button_presses(number_of_button_presses) {}
};

int main()
{
    auto lines = read_lines_from_file("input.txt");
    long total = 0;
    for(const auto & line : lines)
    {
        auto parts = split(line, " ");

        int ril = 0;
        for (size_t i =1; i < parts[0].size() -1; i++)
        {
            ril <<= 1;
            if (parts[0][i] == '#')
                ril++;
        }


        std::vector<int> machine_buttons;
        for (size_t i = 1; i < parts.size() - 1; i++)
        {
            int action = 0;
            auto buttons = splitToInt(parts[i].substr(1, parts[i].size()-2), ",");
            for(const auto & button : buttons)
                action = action | ( 1 << (parts[0].size()-2 - button - 1));
            machine_buttons.push_back(action);
        }
       

        std::unordered_set<int> seen_buttons;
        std::queue<queue_entry> q;
        q.emplace(0,0);

        while (!q.empty())
        {
            auto head = q.front();
            q.pop();

            if (head.current_state == ril)
            {
                total += head.number_of_button_presses;
                break;
            }

            if (seen_buttons.find(head.current_state) != seen_buttons.end())
                continue;

            seen_buttons.insert(head.current_state);

            for(const auto & machine_button : machine_buttons)
            {
                q.emplace(machine_button ^ head.current_state, head.number_of_button_presses+1);
            }

        }

    }

    
    std::cout << total << std::endl;
}