#include "common.cpp"

int main()
{
    std::ifstream file("input.txt");
    if (!file.is_open())
    { 
        std::cerr << "Error: Could not open file. " << "input.txt" << std::endl;
        return -1;
    }

    std::string rotation;
    auto total = 0;
    auto dial = 50;
    while (std::getline(file, rotation))
    {
        auto direction = rotation.substr(0,1);
        auto distance =  std::stoi(rotation.substr(1, rotation.size()-1));

        total += floor(distance / 100);
        distance = distance % 100;

        if (direction == "L")
        {
            // We are going to cross the zero
            if (distance >= dial && dial != 0)
                total++;
            dial -= distance;
        }
        else
        {
            // We are going to cross the zero
            if (distance > (99-dial) && dial != 0)
                total++;
            dial += distance;                
        }

        dial = mod(dial, 100);
    }

    std::cout << total << std::endl;
    return total;
}