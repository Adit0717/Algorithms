#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <chrono>
#include <queue> // For priority_queue

using namespace std;

// Define an arbitrarily large number for infinity
const int INF = INT_MAX;

// 1. Graph Representation: Adjacency List (Node, Weight)
using AdjList = vector<vector<pair<int, int>>>;

// Basic Dijkstra's Implementation: O(V^2)
void dijkstra_basic(int V, const AdjList& graph, int src) {
    // 2. Distance Array and Visited Array
    vector<int> dist(V, INF);
    vector<bool> visited(V, false);

    dist[src] = 0;

    // Outer loop runs V times
    for (int count = 0; count < V - 1; ++count) {
        
        // 3a. Find the unvisited node 'u' with the minimum distance
        int u = -1;
        int min_dist = INF;
        
        // O(V) scan to find the minimum
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && dist[v] <= min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        // If no more reachable nodes, break
        if (u == -1) break;

        // 3b. Mark u as visited
        visited[u] = true;

        // 3c. Relaxation step: For every neighbor 'v' of 'u'
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Check if v is not visited and a shorter path is found
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Optional: Print results
    // cout << "Basic Dijkstra's Results (O(V^2)):\n";
    // for (int i = 0; i < V; ++i) {
    //     cout << "Node " << i << ": " << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
    // }
}

// Optimized Dijkstra's Implementation: O((V+E) log V)
void dijkstra_optimized(int V, const AdjList& graph, int src) {
    // Distance array
    vector<int> dist(V, INF);
    
    // Priority Queue: pair<distance, node>. std::greater creates a Min-Heap
    // We want the smallest distance to be at the top.
    using P = pair<int, int>;
    priority_queue<P, vector<P>, greater<P>> pq;

    dist[src] = 0;
    pq.push({0, src}); // (distance, node)

    while (!pq.empty()) {
        
        // 3a. Extract the minimum distance node 'u'
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // 3b. Handle stale entries: if current distance 'd' is greater than 
        // the best distance found so far for 'u', ignore it.
        if (d > dist[u]) {
            continue;
        }

        // 3c. Relaxation step
        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Check for shorter path (relaxation)
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                
                // Push the new, shorter path to the heap
                pq.push({dist[v], v});
            }
        }
    }

    // Optional: Print results
    // cout << "Optimized Dijkstra's Results (O((V+E)logV)):\n";
    // for (int i = 0; i < V; ++i) {
    //     cout << "Node " << i << ": " << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
    // }
}

// Helper function to generate a large, sparse graph
AdjList generate_sparse_graph(int V, int E) {
    AdjList graph(V);
    // Simple pseudo-random generation to ensure connectivity and non-negativity
    for (int i = 0; i < E; ++i) {
        int u = rand() % V;
        int v = rand() % V;
        int weight = 1 + rand() % 100; // Weights between 1 and 100
        
        // Avoid self-loops and redundant edges for simplicity
        if (u != v) {
            graph[u].push_back({v, weight});
            // graph[v].push_back({u, weight}); // Uncomment for an undirected graph
        }
    }
    return graph;
}

// Timer Utility
double benchmark(void (*func)(int, const AdjList&, int), int V, const AdjList& graph, int src) {
    auto start = chrono::high_resolution_clock::now();
    func(V, graph, src);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    srand(time(0)); // Seed for random generator

    // --- Configuration for a SPARSE Graph ---
    const int V_sparse = 10000;  // 10,000 vertices
    const int E_sparse = 50000;  // 50,000 edges (E is much less than V^2)
    const int SOURCE = 0;

    cout << "--- Benchmarking on a SPARSE Graph (V=" << V_sparse << ", E=" << E_sparse << ") ---\n";
    AdjList sparse_graph = generate_sparse_graph(V_sparse, E_sparse);

    // 1. Benchmark Basic (O(V^2))
    double time_basic = benchmark(dijkstra_basic, V_sparse, sparse_graph, SOURCE);
    cout << "1. Basic (O(V^2)) Time: " << time_basic << " seconds\n";

    // 2. Benchmark Optimized (O((V+E)logV))
    double time_optimized = benchmark(dijkstra_optimized, V_sparse, sparse_graph, SOURCE);
    cout << "2. Optimized (O((V+E)logV)) Time: " << time_optimized << " seconds\n";

    // --- Configuration for a DENSE Graph (Optional, for completeness) ---
    // Note: O(V^2) might be faster than O((V+E)logV) if E is very close to V^2
    const int V_dense = 1000;
    const int E_dense = V_dense * (V_dense - 1) / 2; // Close to fully connected

    cout << "\n--- Benchmarking on a DENSE Graph (V=" << V_dense << ", E ~" << E_dense << ") ---\n";
    AdjList dense_graph = generate_sparse_graph(V_dense, E_dense);

    // 1. Benchmark Basic (O(V^2))
    time_basic = benchmark(dijkstra_basic, V_dense, dense_graph, SOURCE);
    cout << "1. Basic (O(V^2)) Time: " << time_basic << " seconds\n";

    // 2. Benchmark Optimized (O((V+E)logV))
    time_optimized = benchmark(dijkstra_optimized, V_dense, dense_graph, SOURCE);
    cout << "2. Optimized (O((V+E)logV)) Time: " << time_optimized << " seconds\n";
    
    return 0;
}