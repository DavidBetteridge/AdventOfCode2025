#include "common.cpp"

int main()
{
    auto rotations = read_lines_from_file("input.txt");

    auto total = 0;
    auto dial = 50;
    for (const auto &rotation : rotations)
    {
        auto direction = rotation.substr(0,1);
        auto distance =  std::stoi(rotation.substr(1, rotation.size()-1));

        if (direction == "L")
            dial = mod(dial-distance, 100);
        else
            dial = mod(dial+distance, 100);

        if (dial == 0)
            total++;
    }

    std::cout << total << std::endl;
    return 0;
}