#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "intandem.h" 
#include <cstdlib>
#include <ctime> 
using namespace std;

int main() {


    /*
        Traffic Severity 1 (clear) - 10 (jammed)
        Weather Delay 0 (clear) - 10 (storm)
        Fuel Surcharge 1 (normal) - 8 (peak)
        Customs Congestion 0 (none) - 10 (heavy)
    */

    /* 
        Test 1: Base shortest path without disruptions
        Graph: 
        A --2--> B --3--> C 
        A ------12------> C

     */
{
    unordered_map<string, vector<Edge>> graph;
    // A->B with no disruptions
    graph["A"].push_back({"B", 2, {}});

    // B->C with no disruptions
    graph["B"].push_back({"C", 3, {}});

    // A->C with no disruptions
    graph["A"].push_back({"C", 12, {}});

    vector<double> weights = {0.5, 0.3, 0.1, 0.1}; // Weight of Traffic, Weather, Fuel, Customs Congestion 

    cout << "------------------------------" << endl;
    cout << "\tTest 1: Base Shortest Path without Disruptions" << endl;
    auto result = intandem(graph, "A", weights);
    cout << "Expected shortest cost to C: 5 (A->B->C: 2+3)" << endl;
    cout << "Actual shortest cost to C: " << result["C"] << endl;
    if (result["C"] == 5) {
        cout << "Correctly routes A->B->C (5) instead of A->C(12)" << endl;
    } else {
        cout << "Test 1 failed" << endl;
    }
}

    /* 
    Weighted Disruption Penalty Influences Routing
    Graph: 
    A --2--> B --3--> C 
    A ------12------> C

    Disruption only on B->C edge
*/
{
    unordered_map<string, vector<Edge>> graph;
    // A->B with no disruptions
    graph["A"].push_back({"B", 2, {}});

    // B->C with disruptions (10 traffic, 4 weather, 0 fuel, 0 customs)
    graph["B"].push_back({"C", 3, {10, 4, 0, 0}});

    // A->C with no disruptions
    graph["A"].push_back({"C", 12, {}});

    vector<double> weights = {0.5, 0.3, 0.1, 0.1};

    cout << "------------------------------" << endl;
    cout << "\tTest 2: Weighted Disruption Penalty Influences Routing" << endl;
    auto result = intandem(graph, "A", weights);
    
    // Calculate expected penalty:
    // weightedScore = 0.5*10 + 0.3*4 + 0.1*0 + 0.1*0 = 5 + 1.2 = 6.2
    // penalty = 1 + pow(6.2 - 5, 2) = 1 + 1.44 = 2.44
    // adjusted B->C weight = 3 * 2.44 ≈ 7.32
    // total A->B->C = 2 + 7.32 ≈ 9.32 (rounding to int gives 9)
    
    cout << "Expected shortest cost to C: 9 (2 + adjusted ~7)" << endl;
    cout << "Actual shortest cost to C: " << result["C"] << endl;
    if (result["C"] == 9) {
        cout << "Correctly routed A->B->C (~9) instead of A->C (12)" << endl;
    } else {
        cout << "Test 2 failed" << endl;
    }
}

    /*
    Extreme Disruption Forces Reroute to Longer but Undisturbed Path
    Graph: 
        A --1--> B --2--> C
        A -------8------> C (direct)
        A ------5-------> D --1--> C

    C has extreme disruption, making B→C penalized heavily.
    D->C is unaffected 
    
    A->D->C should be selected.
    */
{
    unordered_map<string, vector<Edge>> graph;
    // A->B has no disruptions
    graph["A"].push_back({"B", 1, {}});

    // B->C has extreme disruptions
    graph["B"].push_back({"C", 2, {10, 10, 8, 10}});

    // A->C direct has no disruptions (but longer base distance)
    graph["A"].push_back({"C", 8, {}});

    // A->D has no disruptions
    graph["A"].push_back({"D", 5, {}});

    // D->C has no disruptions
    graph["D"].push_back({"C", 1, {}});

    vector<double> weights = {0.5, 0.3, 0.1, 0.1};

    cout << "------------------------------" << endl;
    cout << "\tTest 3: Extreme Disruption Only Affects B->C" << endl;
    auto result = intandem(graph, "A", weights);
    cout << "Expected shortest cost to C: 6 (A->D->C)" << endl;
    cout << "Actual shortest cost to C: " << result["C"] << endl;
    if (result["C"] == 6) {
        cout << "Correctly routed around high-penalty B->C path via A -> D -> C" << endl;
    } else {
        cout << "failed. Route cost: " << result["C"]
             << "meaning it used a penalized or sub-optimal path" << endl;
    }
}

    /* 
    Test 4: Live Randomized Disruptions at Node C
    Graph: 
    A --2--> B --3--> C 
    A ------12------> C
*/
{
    srand(static_cast<unsigned int>(time(0))); // seed randomness

    unordered_map<string, vector<Edge>> graph;

    vector<double> weights = {0.5, 0.3, 0.1, 0.1};

    vector<int> randomDisruptions = {
        rand() % 11, // traffic
        rand() % 11, // weather
        rand() % 9,  // fuel
        rand() % 11  // customs
    };

    graph["A"].push_back({"B", 2, {}});
    graph["B"].push_back({"C", 3, randomDisruptions});
    graph["A"].push_back({"C", 12, {}});

    cout << "------------------------------" << endl;
    cout << "\tTest 4: Live Randomized Disruptions at Node C" << endl;
    cout << "Generated disruptions for B → C:\n";
    cout << "Traffic: " << randomDisruptions[0] << "\n";
    cout << "Weather: " << randomDisruptions[1] << "\n";
    cout << "Fuel:    " << randomDisruptions[2] << "\n";
    cout << "Customs: " << randomDisruptions[3] << "\n";

    auto result = intandem(graph, "A", weights);
    
    cout << "Shortest cost to C: " << result["C"] << "\n";
}

    return 0;
}