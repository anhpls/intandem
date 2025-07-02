#include <iostream> 
#include <queue> 
#include <limits> 
#include <cmath>
#include "intandem.h"
using namespace std; 

unordered_map<string, int> intandem(
    unordered_map<string, vector<Edge>>& graph,
    const string& start,
    const vector<double>& weights
) {
    unordered_map<string, int> dist;
    
    // Initialize all distances to infinity
    for (auto& node : graph) {
        dist[node.first] = INT_MAX;
        for (auto& edge : node.second) {
            dist[edge.to] = INT_MAX;
        }
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        auto [cost, node] = pq.top(); pq.pop();
        if (cost > dist[node]) continue;

        for (auto& edge : graph[node]) {
            int adjusted = edge.baseWeight;

            // calculate weighted disruption score for this specific edge
            if (!edge.disruptions.empty()) {
                double weightedScore = 0.0;
                for (size_t i = 0; i < weights.size() && i < edge.disruptions.size(); ++i) {
                    weightedScore += weights[i] * edge.disruptions[i];
                }
                if (weightedScore > 5) {
                    // if the combined disruption score exceeds the threshold (5),
                    // apply a quadratic penalty to the base cost to reflect severity
                    adjusted = static_cast<int>(round(edge.baseWeight * (1 + pow(weightedScore - 5, 2))));
                }
            }
            
            // update shortest path if this new adjusted cost is better
            if (cost + adjusted < dist[edge.to]) {
                dist[edge.to] = cost + adjusted;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }
    return dist;
}