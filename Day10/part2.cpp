#include "common.cpp"

std::vector<int> apply_button_to_volts(std::vector<int> volts, const int number_of_presses, const std::vector<int> & button)
{
    for (const int counter : button) {
        volts[counter] -= number_of_presses;
    }
    return volts;
}

std::vector<std::vector<int>> remove_buttons(const std::vector<std::vector<int>> & machine_buttons, const std::vector<int> & button_numbers_to_remove) {
    std::vector<std::vector<int>> result = machine_buttons;
    auto removed = 0;
    for(const auto & button : button_numbers_to_remove)
        result.erase(result.begin() + button - (removed++));
    return result;
}

std::vector<std::vector<int>> remove_button(const std::vector<std::vector<int>> & machine_buttons, const int button) {
    std::vector<std::vector<int>> result = machine_buttons;
    result.erase(result.begin() + button);
    return result;
}


int solve(const int number_of_pushes, const std::vector<std::vector<int>> & machine_buttons, const std::vector<int> & volts, const int & best_answer)
{
    // Is this a solution (or impossible?)
    auto is_solution = true;
    for (const int volt : volts)
    {
        if (volt > 0)
            is_solution = false;
        if (volt < 0)
            return 999999;
    } 
    if (is_solution) return number_of_pushes;

    if (machine_buttons.empty())
        return 999999;

    // Which lights are controlled by which buttons.
    std::vector<std::vector<int>> buttons_for_counter;
    buttons_for_counter.resize(volts.size());
    auto button_number = 0;
    for(const auto & button : machine_buttons) {
        for(const auto light : button)
            buttons_for_counter[light].push_back(button_number);
        button_number++;
    }

    // for (size_t counter = 0; counter < volts.size(); counter++)
    // {
    //     for(const auto & button : buttons_for_counter[counter])
    //         std::cout << 'x' << button << "+";
    //     std::cout << " = " << volts[counter] << std::endl;
    // }
    // return 0;

    // Is there a light which is only controlled by a single button?
    for (size_t counter = 0; counter < volts.size(); counter++)
    {
        if (buttons_for_counter[counter].size() == 1) {
            // This light is controlled by exactly 1 button.  This buttons must be clicked a total of volts[size] times
            const auto updated_volts = apply_button_to_volts(volts, volts[counter], machine_buttons[buttons_for_counter[counter][0]]);
            const auto solution = solve(number_of_pushes + volts[counter], remove_buttons(machine_buttons,buttons_for_counter[counter]), updated_volts, best_answer);
            return solution;
        }
    }

    // Is there a light which is only controlled by exactly two buttons?
    for (size_t counter = 0; counter < volts.size(); counter++)
    {
        if (buttons_for_counter[counter].size() == 2) {
            // This light is controlled by exactly 2 points.  These buttons must be clicked a total of volts[size] times
            auto best_solution = 999999;

            auto min_voltage = 999;
            for (const int light : machine_buttons[buttons_for_counter[counter][1]]) {
                if (volts[light] < min_voltage)
                    min_voltage = volts[light];
            }
            if (min_voltage == 999) return 999999;

            for (int n = 0; n <= min_voltage; n++)
            {
                auto updated_volts = apply_button_to_volts(volts, volts[counter]-n, machine_buttons[buttons_for_counter[counter][0]]);
                updated_volts = apply_button_to_volts(updated_volts, n, machine_buttons[buttons_for_counter[counter][1]]);
                const auto solution = solve(number_of_pushes + volts[counter],
                    remove_buttons(machine_buttons,buttons_for_counter[counter]), updated_volts, best_answer);
                if (solution < best_solution) best_solution = solution;

                if (best_solution < best_answer) return best_solution;
            }
            return best_solution;
        }
    }

    // // Which button controls the most lights?
    // size_t highest_count = 0;
    // size_t best_button = -1;
    // for (size_t i = 0; i <= machine_buttons.size(); i++) {
    //     if (machine_buttons[i].size() > highest_count) {
    //         highest_count = machine_buttons[i].size();
    //         best_button = i;
    //     }
    // }
    // if (best_button == -1) return 999999;
    //
    // // Which light controlled by this button needs the fewest number of volts
    // auto min_voltage = 999;
    // for (const int light : machine_buttons[best_button]) {
    //     if (volts[light] < min_voltage)
    //         min_voltage = volts[light];
    // }
    // if (min_voltage == 999) return 999999;
    //
    // auto best_solution = 999999;
    // for (int n = 0; n <= min_voltage; n++)
    // {
    //     auto updated_volts = apply_button_to_volts(volts, n, machine_buttons[best_button]);
    //     const auto solution = solve(number_of_pushes + n,
    //         remove_button(machine_buttons,best_button), updated_volts);
    //     if (solution < best_solution) best_solution = solution;
    // }
    // return best_solution;


    // Is there a light which is only controlled by exactly three buttons?
    for (size_t matches = 3; matches <= volts.size(); matches++) {
        for (size_t counter = 0; counter < volts.size(); counter++)
        {
            if (buttons_for_counter[counter].size() == matches) {
                // This light is controlled by exactly matches points.  These buttons must be clicked a total of volts[size] times
                auto best_solution = 999999;

                auto min_voltage = 999;
                for (const int light : machine_buttons[buttons_for_counter[counter][0]]) {
                    if (volts[light] < min_voltage)
                        min_voltage = volts[light];
                }
                if (min_voltage == 999) return 999999;

                for (int n = 0; n <= min_voltage; n++)
                {
                    auto updated_volts = apply_button_to_volts(volts, n, machine_buttons[buttons_for_counter[counter][0]]);
                    const auto solution = solve(number_of_pushes + n,
                        remove_button(machine_buttons,buttons_for_counter[counter][0]), updated_volts, best_answer);
                    if (solution < best_solution) best_solution = solution;
                }
                return best_solution;
            }
        }
    }
    return 99999;
}

int main()
{
    auto lines = read_lines_from_file("input.txt");
    unsigned long long total = 0;

    auto line_number=0;
    for(const auto & line : lines)
    {
        //[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
        auto parts = split(line, " ");

        // Parse buttons
        std::vector<std::vector<int>> machine_buttons;
        for (size_t i = 1; i < parts.size() - 1; i++)
        {
            auto lights = splitToInt(parts[i].substr(1, parts[i].size()-2), ",");
            machine_buttons.push_back(lights);
        }
     
        // Parse required volts
        const auto& finalList = parts[parts.size()-1];
        auto volts = splitToInt(finalList.substr(1, finalList.size()-2),",");

        auto best_answer = 0;
        for (const auto & volt : volts)
            if (volt > best_answer)
                best_answer = volt;

        //COPY
        auto solution = solve(0, machine_buttons, volts, best_answer);
        std::cout << (++line_number) << " :: " << solution << std::endl;
        total+=solution;
    }

    //18107 to high
    std::cout << total << std::endl;
}