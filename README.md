# InTandem Algorithm 🚚📦

**InTandem** is a dynamic shipping route optimization algorithm that adjusts paths in real-time based on disruption severity—such as traffic, weather, fuel costs, and customs delays. It builds upon Dijkstra’s algorithm and applies weighted penalties to affected routes, enabling smarter, adaptive logistics planning.

---

## Problem Statement

Traditional shipping systems pre-plan routes and rarely adapt once disruptions occur. This results in delays, higher costs, and inefficiencies. The InTandem algorithm bridges this gap by re-evaluating route weights based on real-time conditions to ensure optimal delivery paths.

---

## How It Works

- Uses Dijkstra's algorithm as a base
- Incorporates weighted disruption scores per route (edge)
- Applies a **quadratic penalty** to base cost if a disruption score exceeds a threshold
- Chooses paths that minimize total adjusted cost

### Core Algorithm

```cpp
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
```

---

## Test Plan & Results

| Test   | Description                                        | Expected | Actual                |
| ------ | -------------------------------------------------- | -------- | --------------------- |
| Test 1 | No disruptions (A→B→C, cost = 2+3)                 | 5        | 5                     |
| Test 2 | Disruption on C, penalty triggers                  | 9        | 9                     |
| Test 3 | Severe disruption reroutes via alternate path      | 6        | 6                     |
| Test 4 | Randomized disruptions (simulating real-time data) | Varies   | Outputs weighted cost |

---

## Runtime & Memory

- **Time Complexity:** `O((V + E) log V)`
- **Space Complexity:** `O(V + E)`
  > Uses a priority queue (min-heap) and adjacency list for efficiency.

---

## Future Improvements

- Add API hooks for real-time disruption feeds
- Expand to multiple simultaneous shipments
- Include time window constraints and urgency levels
- Integrate with map or logistics data systems
- Handle different route optimization goals: shortest, fastest, safest, or cheapest

---

## Build & Run Instructions

To compile and run:

```bash
g++ -std=c++17 main.cpp intandem.cpp -o intandem
./intandem
```

---

## Repository

**GitHub:** [https://github.com/anhpls/intandem](https://github.com/anhpls/intandem)  
**Release Tag:** `v1.0-final`

---
