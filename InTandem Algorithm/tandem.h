#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// edge structure; connection and base cost
struct Edge {
    string to;
    int baseWeight;
};

unordered_map<string, int> tandem(
    unordered_map<string, vector<Edge>>& graph,
    const string& start,
    unordered_map<string, int>& thresholds
);