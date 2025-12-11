#include "common.cpp"

std::vector<int> apply_button_to_volts(std::vector<int> volts, const int number_of_presses, const std::vector<int> & button)
{
    for (const int counter : button)
        volts[counter] -= number_of_presses;
    return volts;
}

std::vector<std::vector<int>> remove_buttons(const std::vector<std::vector<int>> & machine_buttons, const std::vector<int> & button_numbers_to_remove) {
    std::vector<std::vector<int>> result = machine_buttons;
    auto removed = 0;
    for(const auto & button : button_numbers_to_remove)
        result.erase(result.begin() + button - (removed++));
    return result;
}

// std::vector<std::vector<int>> remove_buttons(const std::vector<std::vector<int>> & machine_buttons, int button_number_to_remove1, int button_number_to_remove2) {
//     std::vector<std::vector<int>> result = machine_buttons;
//     if (button_number_to_remove1 > button_number_to_remove2) std::swap(button_number_to_remove1,button_number_to_remove2);
//     result.erase(result.begin() + button_number_to_remove1);
//     result.erase(result.begin() + button_number_to_remove2-1);
//     return result;
// }
//
// std::vector<std::vector<int>> remove_buttons(const std::vector<std::vector<int>> & machine_buttons, int button_number_to_remove1, int button_number_to_remove2, int button_number_to_remove3) {
//     std::vector<std::vector<int>> result = machine_buttons;
//     result.erase(result.begin() + button_number_to_remove1);
//     result.erase(result.begin() + button_number_to_remove2-1);
//     result.erase(result.begin() + button_number_to_remove3-2);
//     return result;
// }
//
// std::vector<std::vector<int>> remove_buttons(const std::vector<std::vector<int>> & machine_buttons, int button_number_to_remove1, int button_number_to_remove2, int button_number_to_remove3, int button_number_to_remove4) {
//     std::vector<std::vector<int>> result = machine_buttons;
//     result.erase(result.begin() + button_number_to_remove1);
//     result.erase(result.begin() + button_number_to_remove2-1);
//     result.erase(result.begin() + button_number_to_remove3-2);
//     result.erase(result.begin() + button_number_to_remove4-3);
//     return result;
// }

int solve(const int number_of_pushes, const std::vector<std::vector<int>> & machine_buttons, const std::vector<int> & volts)
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

    // Can we find a count which is controlled by exactly 1 button?
    for (size_t counter = 0; counter < volts.size(); counter++)
    {
        if (volts[counter] > 0)
        {
            std::vector<int> buttons_for_light;
            auto index = 0;
            for(const auto & button : machine_buttons)
            {
                for(const auto light : button)
                {
                    if (light == counter)
                    {
                        buttons_for_light.push_back(index);
                        break;
                    }
                }
                index++;
            }

            if (buttons_for_light.size() == 1)
            {
                // This light is controlled by exactly 2 points.  These buttons must be clicked a total of volts[size] times
                const auto updated_volts = apply_button_to_volts(volts, volts[counter], machine_buttons[buttons_for_light[0]]);
                const auto solution = solve(number_of_pushes + volts[counter], remove_buttons(machine_buttons,buttons_for_light), updated_volts);
                return solution;
            }
        }
    }


    // Can we find a count which is controlled by exactly two buttons?
    for (size_t counter = 0; counter < volts.size(); counter++)
    {
        if (volts[counter] > 0)
        {
            std::vector<int> buttons_for_light;
            auto index = 0;
            for(const auto & button : machine_buttons)
            {
                for(const auto light : button)
                {
                    if (light == counter)
                    {
                        buttons_for_light.push_back(index);
                        break;
                    }
                }
                index++;
            }

            if (buttons_for_light.size() == 2)
            {
                // This light is controlled by exactly 2 points.  These buttons must be clicked a total
                // of volts[size] times
                auto best_solution = 66666;
                for (int n = 0; n <= volts[counter]; n++)
                {
                    auto updated_volts = apply_button_to_volts(volts, volts[counter]-n, machine_buttons[buttons_for_light[0]]);
                    updated_volts = apply_button_to_volts(updated_volts, n, machine_buttons[buttons_for_light[1]]);
                    const auto solution = solve(number_of_pushes + volts[counter],
                        remove_buttons(machine_buttons,buttons_for_light), updated_volts);
                    if (solution < best_solution) best_solution = solution;
                }
                return best_solution;
            }

        }
    }

    // Can we find a count which is controlled by exactly three buttons?
    for (size_t counter = 0; counter < volts.size(); counter++)
    {
        if (volts[counter] > 0)
        {
            std::vector<int> buttons_for_light;
            auto index = 0;
            for(const auto & button : machine_buttons)
            {
                for(const auto light : button)
                {
                    if (light == counter)
                    {
                        buttons_for_light.push_back(index);
                        break;
                    }
                }
                index++;
            }

            if (buttons_for_light.size() == 3)
            {
                // This light is controlled by exactly 3 points.  These buttons must be clicked a total of volts[size] times
                auto best_solution = 88888;
                auto reduced_buttons = remove_buttons(machine_buttons, buttons_for_light);
                for (int m = 0; m <= volts[counter]; m++) {
                    auto updated_volts = apply_button_to_volts(volts, m, machine_buttons[buttons_for_light[0]]);
                    const auto remaining_volts = volts[counter]-m;
                    for (int n = 0; n <= remaining_volts; n++)
                    {
                        updated_volts = apply_button_to_volts(updated_volts, remaining_volts-n, machine_buttons[buttons_for_light[1]]);
                        updated_volts = apply_button_to_volts(updated_volts, n, machine_buttons[buttons_for_light[2]]);
                        const auto solution = solve(number_of_pushes + volts[counter], reduced_buttons, updated_volts);
                        if (solution < best_solution) best_solution = solution;
                    }
                }
                return best_solution;
            }

        }
    }

    // Can we find a count which is controlled by exactly four buttons?
    for (size_t counter = 0; counter < volts.size(); counter++)
    {
        if (volts[counter] > 0)
        {
            std::vector<int> buttons_for_light;
            auto index = 0;
            for(const auto & button : machine_buttons)
            {
                for(const auto light : button)
                {
                    if (light == counter)
                    {
                        buttons_for_light.push_back(index);
                        break;
                    }
                }
                index++;
            }

            if (buttons_for_light.size() == 4)
            {
                // This light is controlled by exactly 4 points.  These buttons must be clicked a total of volts[size] times
                auto best_solution = 77777;
                auto reduced_buttons = remove_buttons(machine_buttons, buttons_for_light);
                for (int m = 0; m <= volts[counter]; m++) {
                    auto updated_volts = apply_button_to_volts(volts, m, machine_buttons[buttons_for_light[0]]);
                    const auto remaining_volts = volts[counter]-m;

                    for (int q = 0; q <= remaining_volts; q++)
                    {
                        updated_volts = apply_button_to_volts(volts, q, machine_buttons[buttons_for_light[1]]);
                        const auto remaining_volts2 = remaining_volts - q;

                        for (int n = 0; n <= remaining_volts2; n++)
                        {
                            updated_volts = apply_button_to_volts(updated_volts, remaining_volts2-n, machine_buttons[buttons_for_light[2]]);
                            updated_volts = apply_button_to_volts(updated_volts, n, machine_buttons[buttons_for_light[3]]);
                            const auto solution = solve(number_of_pushes + volts[counter], reduced_buttons, updated_volts);
                            if (solution < best_solution) best_solution = solution;
                        }

                    }


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

        //COPY
        auto solution = solve(0, machine_buttons, volts);
        std::cout << solution << std::endl;
        total+=solution;
    }

    //6308208 to high
    std::cout << total << std::endl;
}