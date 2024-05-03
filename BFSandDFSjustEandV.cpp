#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to perform Depth First Search (DFS)
void dfs(int node, vector<int> adjList[], unordered_set<int>& visited) {
    cout << node << " ";
    visited.insert(node);
    for (int i = 0; i < adjList[node].size(); ++i) {
        int neighbor = adjList[node][i];
        if (visited.find(neighbor) == visited.end()) {
            dfs(neighbor, adjList, visited);
        }
    }
}

// Function to perform Breadth First Search (BFS)
void bfs(int start, vector<int> adjList[], unordered_set<int>& visited) {
    queue<int> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";
        for (int i = 0; i < adjList[current].size(); ++i) {
            int neighbor = adjList[current][i];
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}

int main() {
    // Number of vertices and edges
    int num_vertices, num_edges;
    cout << "Enter number of vertices: ";
    cin >> num_vertices;
    cout << "Enter number of edges: ";
    cin >> num_edges;

    // Graph representation using adjacency list as array of vectors
    vector<int> adjList[num_vertices];

    // User input for edges
    cout << "Enter edges (format: vertex1 vertex2):" << endl;
    for (int i = 0; i < num_edges; ++i) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        adjList[vertex1].push_back(vertex2);
        adjList[vertex2].push_back(vertex1); // Assuming undirected graph
    }

    // Starting node for traversal
    int start_node = 0; // Assuming starting from vertex 0

    cout << "DFS Traversal: ";
    unordered_set<int> visited1;
    for (int i = 0; i < num_vertices; ++i) {
        if (visited1.find(i) == visited1.end()) {
            dfs(i, adjList, visited1);
        }
    }
    cout << endl;

    cout << "BFS Traversal: ";
    unordered_set<int> visited2;
    for (int i = 0; i < num_vertices; ++i) {
        if (visited2.find(i) == visited2.end()) {
            bfs(i, adjList, visited2);
        }
    }
    cout << endl;

    return 0;
}
