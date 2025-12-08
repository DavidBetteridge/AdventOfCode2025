#include "common.cpp"
#include "queue"

struct junction_box
{
    int circuit_number;
    long x;
    long y;
    long z;

    junction_box(int circuit_number, long x, long y, long z) : circuit_number(circuit_number), x(x), y(y), z(z) {};

    long distance(junction_box const & other) const
    {
        //return sqrt( pow((x - other.x),2) + pow((y - other.y),2) + pow((z - other.z),2)  );
        return pow((x - other.x),2) + pow((y - other.y),2) + pow((z - other.z),2);
    }
};

int createCircuit(std::vector<std::vector<int>>& circuits, const int & box1, const int & box2)
{
    std::vector<int> newCircuit({box1, box2});
    circuits.push_back(newCircuit);
    return circuits.size() - 1;
}

int circuitContaining(const std::vector<std::vector<int>>& circuits, const int & box)
{
    for(auto c=0; c<circuits.size(); c++)
    {
        auto circuit = circuits[c];
        if(std::find(circuit.begin(), circuit.end(), box) != circuit.end()) {
            return c;
        }
    }
    return -1;
}

void addToCircuit(std::vector<std::vector<int>>& circuits, int circuitsId, const int & box)
{
    circuits[circuitsId].push_back(box);
}

void mergeCircuits(std::vector<std::vector<int>>& circuits, int circuitsId1, int circuitsId2)
{
    auto source = circuits[circuitsId2];
    for(auto c=0; c<source.size(); c++)
        circuits[circuitsId1].push_back(source[c]);
    circuits[circuitsId2].clear();
}

struct connection
{
    int box1;
    int box2;
    long distance;

    connection(int box1, long box2, long distance) : box1(box1), box2(box2), distance(distance) {};
};

int main()
{
    auto lines = read_lines_from_file("input.txt");

    std::vector<junction_box> junction_boxes;
    auto circuit_number = 0;
    for (const auto &line : lines)
    {
        auto parts = split_to_long(line, ",");
        junction_boxes.emplace_back(circuit_number,parts[0], parts[1], parts[2]);
        circuit_number++;
    }

    auto cmp = [](connection left, connection right) { return (left.distance) > (right.distance); };
    std::priority_queue<connection, std::vector<connection>, decltype(cmp)> Q(cmp);

    for(auto x=0; x<junction_boxes.size()-1; x++)
    {
        for(auto y=x+1; y<junction_boxes.size(); y++)
        {
            auto d = junction_boxes[x].distance(junction_boxes[y]);
            Q.emplace(junction_boxes[x].circuit_number, junction_boxes[y].circuit_number, d);
        }
    }

    std::vector<std::vector<int>> circuits;
    while (!Q.empty())
    {
        auto shortest = Q.top();
        Q.pop();

        auto baseCircuit = circuitContaining(circuits, shortest.box1);
        if (baseCircuit == -1)
            baseCircuit = circuitContaining(circuits, shortest.box2);
        if (baseCircuit == -1)
            baseCircuit = createCircuit(circuits, shortest.box1, shortest.box2);

        auto boxCircuit = circuitContaining(circuits, shortest.box1);
        if (boxCircuit == -1)
            addToCircuit(circuits, baseCircuit, shortest.box1);
        else if (boxCircuit != baseCircuit)
            mergeCircuits(circuits, baseCircuit, boxCircuit);  
            
        auto otherCircuit = circuitContaining(circuits, shortest.box2);
        if (otherCircuit == -1)
            addToCircuit(circuits, baseCircuit, shortest.box2);
        else if (otherCircuit != baseCircuit)
            mergeCircuits(circuits, baseCircuit, otherCircuit);         

        if (circuits[baseCircuit].size() == junction_boxes.size())
        {
            long total = junction_boxes[shortest.box1].x * junction_boxes[shortest.box2].x;
            std::cout << total;
            break;
        }
    }
    
    return 0;
}