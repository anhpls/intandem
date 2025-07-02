# InTandem Algorithm 🚚📦

**InTandem** is a dynamic shipping route optimization algorithm that adjusts paths in real-time based on disruption severity—such as traffic, weather, fuel costs, and customs delays. It builds upon Dijkstra’s algorithm and applies weighted penalties to affected routes, enabling smarter, adaptive logistics planning.

---

## 📌 Problem Statement

Traditional shipping systems pre-plan routes and rarely adapt once disruptions occur. This results in delays, higher costs, and inefficiencies. The InTandem algorithm bridges this gap by re-evaluating route weights based on real-time conditions to ensure optimal delivery paths.

---

## 🧠 How It Works

- Uses Dijkstra's algorithm as a base
- Incorporates weighted disruption scores per route (edge)
- Applies a **quadratic penalty** to base cost if a disruption score exceeds a threshold
- Chooses paths that minimize total adjusted cost

### Pseudocode

```cpp
for each edge from current node:
    adjusted = baseWeight
    if disruption score > threshold:
        adjusted = baseWeight * (1 + (score - threshold)^2)
    if current_cost + adjusted < dist[to]:
        update dist[to]
```

---

## ✅ Test Plan & Results

| Test   | Description                                        | Expected | Actual                   |
| ------ | -------------------------------------------------- | -------- | ------------------------ |
| Test 1 | No disruptions (A→B→C, cost = 2+3)                 | 5        | ✅ 5                     |
| Test 2 | Disruption on C, penalty triggers                  | 9        | ✅ 9                     |
| Test 3 | Severe disruption reroutes via alternate path      | 6        | ✅ 6                     |
| Test 4 | Randomized disruptions (simulating real-time data) | Varies   | ✅ Outputs weighted cost |

---

## 🧪 Runtime & Memory

- **Time Complexity:** `O((V + E) log V)`
- **Space Complexity:** `O(V + E)`
  > Uses a priority queue (min-heap) and adjacency list for efficiency.

Tested on graphs of up to 50+ nodes for scalability evaluation.

---

## 🚀 Future Improvements

- Add API hooks for real-time disruption feeds
- Expand to multiple simultaneous shipments
- Include time window constraints and urgency levels
- Integrate with map or logistics data systems
- Handle different route optimization goals: shortest, fastest, safest, or cheapest

---

## 🔗 Repository

**GitHub:** [https://github.com/yourusername/intandem-algorithm](https://github.com/yourusername/intandem-algorithm)  
**Release Tag:** `v1.0-final`

---
