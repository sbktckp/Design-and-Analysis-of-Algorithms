# Lab Day 7: Greedy Techniques, Single Source Shortest Path

| No. | Program | File | Input |
|-----|---------|------|-------|
| 7.1 | Dijkstra Shortest Path | `7.1_dijkstra_shortest_path.c` | `data/inDiAdjMat1.dat` |

## Run

```bash
cd "Day 7 - Single Source Shortest Path"
make
./bin/7.1_dijkstra_shortest_path   # 5 vertices, source vertex 1
```

Output for the supplied graph, matching the sheet:

```
Source   Destination  Cost   Path
1        1            0      -
1        2            8      1->4->2
1        3            9      1->4->2->3
1        4            5      1->4
1        5            7      1->4->5
```

## Input format

A 5 by 5 cost adjacency matrix for a directed graph, where 0 means there is no
edge. Row i column j is the weight of the edge from i to j.

## Notes

- The min-priority queue is the same indexed binary heap used for Prim in Day
  6. Each vertex knows its slot through `pos[]`, so relaxing an edge is a
  DECREASE-KEY in O(log V) rather than a scan.
- Correctness rests on non-negative weights. Once a vertex is extracted its
  distance is final, because any later route to it would have to pass through
  a vertex that is already at least as far away. Negative edges break that
  argument, which is why Day 9 uses Floyd-Warshall for the graph with a -4 and
  a -5 on it.
- `parent[]` is filled during relaxation and the path is printed by recursing
  to the source first, then unwinding, which produces the arrows in the right
  order without reversing anything.
- Unreachable vertices are reported as INF rather than being skipped.

## Complexity

| Part | Time |
|------|------|
| Dijkstra with an indexed binary heap | O(E log V) |
| Reading the matrix | O(V^2) |
| Printing one path | O(length of path) |
