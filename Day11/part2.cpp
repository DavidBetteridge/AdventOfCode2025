#include "common.cpp"
#include <map>
#include <set>

struct device {
    std::string name;
    std::vector<std::string> connections_out;
    std::vector<std::string> connections_in;

    device(std::string name, std::vector<std::string> connections) : name(std::move(name)), connections_out(std::move(connections)) {
    }
};

static std::set<std::string> avoid;
static std::set<std::string> avoid2;


int walk(const std::map<std::string,device> & devices, const std::string &device_name,
         const std::string &target_device_name, std::set<std::string> &path) {
    if (device_name == target_device_name) {
        return 1;
    }
    if (device_name == "out") {
        return 0;
    }

    auto const& current = devices.at(device_name);

    auto result = 0;
    for (const auto& connection : current.connections_out) {
        if (avoid.find(connection) == avoid.end() && avoid2.find(connection) == avoid2.end()) {
            result += walk(devices, connection, target_device_name, path);
        }
    }
    return result;
}


long walk_back(const std::map<std::string,device> & devices, const std::string &device_name,
         const std::string &target_device_name, std::set<std::string> &path) {
    if (device_name == target_device_name) {
        // All the entries in path can be avoided when walking dac --> fft
        for (const auto& connection : path)
            avoid.insert(connection);

        return 1;
    }

    auto const& current = devices.at(device_name);

    long result = 0;
    for (const auto& connection : current.connections_in) {
        path.insert(connection);
        result += walk_back(devices, connection, target_device_name, path);
        path.erase(connection);
    }
    return result;
}

long walk_back2(const std::map<std::string,device> & devices, const std::string &device_name,
         const std::string &target_device_name, std::set<std::string> &path) {
    if (device_name == target_device_name) {
        for (const auto& connection : path)
            avoid2.insert(connection);
        return 1;
    }

    auto const& current = devices.at(device_name);

    long result = 0;
    for (const auto& connection : current.connections_in) {
        if (avoid.find(connection) == avoid.end()) {
            path.insert(connection);
            result += walk_back2(devices, connection, target_device_name, path);
            path.erase(connection);
        }
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

    for (const auto& device : devices) {
        for (const auto& connection : device.second.connections_out) {
            if (devices.find(connection) != devices.end()) {
                devices.at(connection).connections_in.push_back(device.first);
            }
        }
    }

    // a \                          a \
    //    c - d is the same as          d  (if c != dac and c != fft)
    // b /                          b /

    // i.e. c only has one edge leaving it.
    std::vector<std::string> to_remove;
    for (const auto& level2 : devices) {
        if (level2.second.connections_out.size() == 1 && level2.first != "dac" && level2.first != "fft" ) {
            const auto level3 = level2.second.connections_out[0];

            // d no longer has c coming in
            if (level3 != "out") {
                auto& ins = devices.at(level3).connections_in;
                ins.erase(std::remove(ins.begin(), ins.end(), level2.second.name), ins.end());
            }

            for (auto& level1 : level2.second.connections_in) {

                // d now has a, b coming in
                if (level3 != "out") {
                    auto& ins = devices.at(level3).connections_in;
                    ins.push_back(level1);
                }

                // a,b now go out to c
                auto& outs = devices.at(level1).connections_out;
                outs.push_back(level3);

                // a,b no longer goes out to d
                outs.erase(std::remove(outs.begin(), outs.end(), level2.second.name), outs.end());
            }
            to_remove.push_back(level2.first);
        }
    }
    for (const auto& name : to_remove) {
        devices.erase(name);
    }


    // Only 1 edge into C,  so if A calls C,  then A-->C can be replaced by all children of C (E,F).  So A -> EF
    /*
     *          B                           B
     *      /       / E
     *  A  -    C               -->  A ->   D
     *      \       \ F                     E
     *          D                           F
     */
    to_remove.clear();
    for (const auto& level2 : devices) {
        if (level2.second.connections_in.size() == 1 && level2.first != "dac" && level2.first != "fft" ) {
            const auto level1 = level2.second.connections_in[0];
            auto& outs = devices.at(level1).connections_out;

            for (auto& level3 : level2.second.connections_out) {
                // A now goes to E and F
                outs.push_back(level3);

                // E and F now come from A,  not C
                if (level3 != "out") {
                    auto& ins = devices.at(level3).connections_in;
                    ins.push_back(level1);
                    ins.erase(std::remove(ins.begin(), ins.end(), level2.second.name), ins.end());
                }
            }

            // A no longer goes to C
            outs.erase(std::remove(outs.begin(), outs.end(), level2.second.name), outs.end());
            to_remove.push_back(level2.first);
        }
    }
    for (const auto& name : to_remove) {
        devices.erase(name);
    }

    std::set<std::string> path;
    long total = walk_back(devices, "fft", "svr", path);
    std::cout << total << std::endl;
    long final = total;

    total = walk_back2(devices, "dac", "fft", path);
    std::cout << total << std::endl;
    final *= total;

    total = walk(devices, "dac", "out", path);
    std::cout << total << std::endl;
    final *= total;

    std::cout << final << std::endl;
}