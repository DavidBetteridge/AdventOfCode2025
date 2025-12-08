#include "common.cpp"

struct junction_box
{
    int circuit_number;
    long x;
    long y;
    long z;

    junction_box(int circuit_number, long x, long y, long z) : circuit_number(circuit_number), x(x), y(y), z(z) {};

    long distance(junction_box const & other) const
    {
        return sqrt( pow((x - other.x),2) + pow((y - other.y),2) + pow((z - other.z),2)  );
    }
};

int createCircuit(std::vector<std::vector<int>>& circuits, const junction_box & box1, const junction_box & box2)
{
    std::vector<int> newCircuit({box1.circuit_number, box2.circuit_number});
    circuits.push_back(newCircuit);
    return circuits.size() - 1;
}

int circuitContaining(const std::vector<std::vector<int>>& circuits, const junction_box & box)
{
    for(auto c=0; c<circuits.size(); c++)
    {
        auto circuit = circuits[c];
        if(std::find(circuit.begin(), circuit.end(), box.circuit_number) != circuit.end()) {
            return c;
        }
    }
    return -1;
}

void addToCircuit(std::vector<std::vector<int>>& circuits, int circuitsId, const junction_box & box)
{
    circuits[circuitsId].push_back(box.circuit_number);
}

void mergeCircuits(std::vector<std::vector<int>>& circuits, int circuitsId1, int circuitsId2)
{
    auto source = circuits[circuitsId2];
    for(auto c=0; c<source.size(); c++)
        circuits[circuitsId1].push_back(source[c]);
    circuits[circuitsId2].clear();
}

int main()
{
    auto lines = read_lines_from_file("sample1.txt");

    std::vector<junction_box> junction_boxes;
    auto circuit_number = 0;
    for (const auto &line : lines)
    {
        auto parts = split_to_long(line, ",");
        junction_boxes.emplace_back(circuit_number,parts[0], parts[1], parts[2]);
        circuit_number++;
    }

    std::vector<std::vector<int>> circuits;
    for (const auto &box : junction_boxes)
    {
        long best_distance = 999999;
        const junction_box* best_box = nullptr;
        for (const auto &other : junction_boxes)
        {   
            long d = box.distance(other);
            if (d != 0 && d < best_distance)
            {
                best_distance = d;
                best_box = &other;
            }
        }

        auto baseCircuit = circuitContaining(circuits, box);
        if (baseCircuit == -1)
            baseCircuit = circuitContaining(circuits, *best_box);
        if (baseCircuit == -1)
            baseCircuit = createCircuit(circuits, box, *best_box);

        auto boxCircuit = circuitContaining(circuits, box);
        if (boxCircuit == -1)
            addToCircuit(circuits, baseCircuit, box);
        else if (boxCircuit != baseCircuit)
            mergeCircuits(circuits, baseCircuit, boxCircuit);  
            
        auto otherCircuit = circuitContaining(circuits, *best_box);
        if (otherCircuit == -1)
            addToCircuit(circuits, baseCircuit, *best_box);
        else if (otherCircuit != baseCircuit)
            mergeCircuits(circuits, baseCircuit, otherCircuit);              
    }

    return 0;
}