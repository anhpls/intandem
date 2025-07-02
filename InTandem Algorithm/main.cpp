#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "tandem.h" 
using namespace std;

int main() {
    // graph: A -> B -> C
    unordered_map<string, vector<Edge>> graph;
    graph["A"].push_back({"B", 2}); // edge from A to B with weight 2
    graph["B"].push_back({"C", 3}); // edge from B to C with weight 3

    // set thresholds for each node (used to determine if penalty should apply)
    unordered_map<string, int> thresholds;
    thresholds["B"] = 0;   // no penalty
    thresholds["C"] = 6;   // threshold triggers penalty (>5)

    // run the tandem algorithm starting from node A
    auto result = tandem(graph, "A", thresholds);

    // print total cost to reach node C
    cout << "Shortest cost to C: " << result["C"] << endl;
    
    // checking to see if results match the expectation
    // A -> B = 2 ; B -> C gets penalized to 9 so total should be 11
    if (result["C"] == 11) {
        cout << "Test passed!" << endl;     // everything worked as expected
    } else {
        cout << "Test failed. Expected 11, got " << result["C"] << endl;    // error somewhere
    }

    return 0;   // end 
}