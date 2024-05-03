#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// Class to represent vertices with their weights
class Pair {
public:
    int v, wt;
    Pair(int v, int wt) : v(v), wt(wt) {}
    // Overloaded < operator for priority queue comparison
    bool operator<(const Pair& p2) const {
        // Compare weights in ascending order
        return wt > p2.wt;
    }
};

// Function to create the graph adjacency list
void createGraph(vector<pair<int, int>> graph[], int numCities) {
    cout << "Enter the cost matrix:\n";
    for (int i = 0; i < numCities; ++i) {
        for (int j = i + 1; j < numCities; ++j) {
            int cost;
            // Ask for the cost to connect city i+1 and city j+1
            cout << "Cost to connect city " << i + 1 << " and city " << j + 1 << ": ";
            cin >> cost;
            // If cost is not -1, there's a connection
            if (cost != -1) {
                // Add j to the adjacency list of i, and vice versa (undirected graph)
                graph[i].push_back({j, cost});
                graph[j].push_back({i, cost});
            }
        }
    }
}

// Function to find the minimum total cost to connect all offices using Prim's algorithm
int primAlgo(vector<pair<int, int>> graph[], int numCities) {
    // Initialize a vector to keep track of visited vertices
    vector<bool> vis(numCities, false);
    // Initialize a priority queue to store vertices with their corresponding weights
    priority_queue<Pair> pq;
    // Start with the first vertex (0) with weight 0
    pq.push(Pair(0, 0));
    // Initialize the total cost
    int cost = 0;
    // Loop until the priority queue is empty
    while (!pq.empty()) {
        // Extract the vertex with the minimum weight from the priority queue
        Pair curr = pq.top(); pq.pop();
        int v = curr.v;   // Current vertex
        int wt = curr.wt; // Weight of the edge to the current vertex
        // If the current vertex is not visited yet
        if (!vis[v]) {
            // Mark the current vertex as visited
            vis[v] = true;
            // Add the weight of the edge to the total cost
            cost += wt;
            // Loop through the adjacent vertices of the current vertex
            for (int i = 0; i < graph[v].size(); ++i) {
                // Get the adjacent vertex and its weight
                int u = graph[v][i].first;    // Adjacent vertex
                int weight = graph[v][i].second; // Weight of the edge to the adjacent vertex
                // If the adjacent vertex is not visited yet
                if (!vis[u]) {
                    // Add the adjacent vertex to the priority queue with its weight
                    pq.push(Pair(u, weight));
                }
            }
        }
    }
    // Return the total cost
    return cost;
}

int main() {
    int numCities;
    // Ask user to enter the number of cities
    cout << "Enter the number of cities: ";
    cin >> numCities;
    // Create a vector of pairs to represent the graph (adjacency list)
    vector<pair<int, int>> graph[numCities];
    // Call the function to create the graph
    createGraph(graph, numCities);
    // Call the Prim's algorithm function to find the minimum total cost
    int totalCost = primAlgo(graph, numCities);
    // Output the minimum total cost to connect all offices
    cout << "Minimum total cost to connect all offices: " << totalCost << endl;
    return 0;
}

/*
Explanation and Logic:
1. Graph Creation:
   - The user is prompted to enter the cost matrix, representing the cost of connecting each pair of cities.
   - For each pair of cities, if there is a connection (cost is not -1), the cities are added to each other's adjacency list in the graph.

2. Priority Queue Initialization:
   - A priority queue is initialized to store vertices with their corresponding weights.
   - The algorithm starts with the first vertex (0) and weight 0.

3. Prim's Algorithm Execution:
   - Prim's algorithm is executed to find the minimum spanning tree of the graph.
   - The algorithm iteratively selects the vertex with the minimum weight from the priority queue.
   - It updates the total cost, marks the vertex as visited, and adds its adjacent vertices to the priority queue if they are not visited yet.

4. Vertex Extraction and Processing:
   - In each iteration of the algorithm, the vertex with the minimum weight is extracted from the priority queue.
   - If the vertex has not been visited yet, it is marked as visited, and its weight is added to the total cost.
   - The adjacent vertices of the current vertex are processed using a simple loop.

5. Output Minimum Total Cost:
   - Once all vertices are visited, and the total cost is computed, the minimum total cost required to connect all offices is outputted.
   - This cost represents the minimum amount of money needed to establish phone lines connecting all offices with each other.
*/
