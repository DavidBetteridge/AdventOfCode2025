#include "common.cpp"
#include <map>

struct device {
    std::string name;
    std::vector<std::string> connections;

    device(std::string name, std::vector<std::string> connections) : name(std::move(name)), connections(std::move(connections)) {
    }
};

int walk(const std::map<std::string,device> & devices, const std::string &device_name) {
    if (device_name == "out") {
        return 1;
    }

    auto const& current = devices.at(device_name);

    auto result = 0;
    for (const auto& connection : current.connections) {
        result += walk(devices, connection);
    }
    return result;
}

int main() {
    const auto lines = read_lines_from_file("input.txt");

    std::map<std::string,device> devices;
    for (const auto& line : lines) {
        const auto parts = split(line, ": ");
        const auto connections = split(parts[1], " ");
        devices.emplace(parts[0], device{parts[0],connections});
    }
    const auto total = walk(devices, "you");

    std::cout << total << std::endl;

}