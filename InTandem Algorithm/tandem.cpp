#include <iostream>
#include <queue>
#include <limits>
using namespace std;

// edge going to a node with base travel cost
struct Edge {
    string to;
    int baseWeight;
};

// tandem algorithm
unordered_map<string, int> tandem(
    unordered_map<string, vector<Edge>>& graph,
    const string& start,
    unordered_map<string, int>& thresholds
) {
    unordered_map<string, int> dist;

    // initiatlize all distances to infinity
    for (auto& node : graph) {
    dist[node.first] = INT_MAX;
    for (auto& edge : node.second) {
        dist[edge.to] = INT_MAX; // destination nodes are added
    }
}

    // priority queue for the shortest path
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cost, node] = pq.top(); pq.pop();
        if (cost > dist[node]) continue;

        for (auto& edge : graph[node]) {
            int adjusted = edge.baseWeight;

            // apply penalty if threshold is exceeded
            if (thresholds[edge.to] > 5) adjusted *= 3;

            if (cost + adjusted < dist[edge.to]) {
                dist[edge.to] = cost + adjusted;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }
    return dist;
}
