#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// define a structure to represent an edge (route) in the graph
struct Edge {
    string to; // destination node
    int baseWeight; // base cost of traveling this edge
    vector<int> disruptions; // disruptions specific to this edge [traffic, weather, fuel, customs]
};

// graph: a map where each node has a list of connected edges
// start: the starting node 
// thresholds: disruption thresholds for each node to apply penalties
unordered_map<string, int> intandem(
    unordered_map<string, vector<Edge>>& graph,
    const string& start,
    const vector<double>& weights
);