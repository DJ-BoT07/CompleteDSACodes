#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
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
void bfs(int start, vector<int> adjList[]) {
    queue<int> q;
    unordered_set<int> visited;
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
    // Number of landmarks
    const int num_landmarks = 6;

    // Landmarks (nodes) represented by numbers
    unordered_map<string, int> landmarks = {
        {"Main Gate", 0},
        {"Library", 1},
        {"Cafeteria", 2},
        {"Admin Building", 3},
        {"Student Center", 4},
        {"Auditorium", 5}
    };

    // Graph representation using adjacency list as array of vectors
    vector<int> adjList[num_landmarks];

    // User input for connections between landmarks
    cout << "Enter connections between landmarks:" << endl;
    cout << "Format: Landmark1 Landmark2 (separated by space), enter 'done' to finish input" << endl;
    string landmark1, landmark2;
    while (cin >> landmark1 >> landmark2) {
        if (landmarks.find(landmark1) != landmarks.end() && landmarks.find(landmark2) != landmarks.end()) {
            int node1 = landmarks[landmark1];
            int node2 = landmarks[landmark2];
            adjList[node1].push_back(node2);
            adjList[node2].push_back(node1); // Assuming undirected graph
        } else {
            cout << "Invalid landmarks. Please try again." << endl;
        }
    }

    // Starting node for traversal
    int start_node = 0; // Assuming starting from Main Gate

    cout << "DFS Traversal: ";
    unordered_set<int> visited;
    dfs(start_node, adjList, visited); // Starting DFS from Main Gate
    cout << endl;

    cout << "BFS Traversal: ";
    bfs(start_node, adjList); // Starting BFS from Main Gate
    cout << endl;

    return 0;
}
