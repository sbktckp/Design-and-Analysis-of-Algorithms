# Lab Day 6: Greedy Techniques, Minimum Cost Spanning Tree

Both programs run on the same nine vertex graph from the sheet, but they read
it in the two different formats the two questions specify.

| No. | Program | File | Input |
|-----|---------|------|-------|
| 6.1 | Prim MST | `6.1_prim_mst.c` | `data/inUnAdjMat.dat` cost adjacency matrix |
| 6.2 | Kruskal MST | `6.2_kruskal_mst.c` | `data/inEdgeList.dat` edge list |

## Run

```bash
cd "Day 6 - Minimum Cost Spanning Tree"
make
./bin/6.1_prim_mst      # asks for 9 vertices, starting vertex 1
./bin/6.2_kruskal_mst   # reads n, m and the edges from the file
```

Both report a total cost of 37, which is the answer the sheet gives.

## Input formats

`inUnAdjMat.dat` is a 9 by 9 symmetric matrix where 0 means no edge.

`inEdgeList.dat` starts with `n m`, then one line per edge holding `u v w`.

## Notes

- **6.1** keeps `key[v]`, the weight of the cheapest edge joining v to the
  tree, in an indexed binary min-heap. The `pos[]` array records where each
  vertex currently sits in the heap, which is what makes DECREASE-KEY O(log V)
  instead of a linear search. Output is the cost adjacency matrix of the tree,
  the selected edges, and the total.
- **6.2** sorts every edge by weight and adds an edge only when its two ends
  are in different components. The disjoint-set uses union by rank plus path
  compression, so each test is effectively constant time and the sort
  dominates.
- The two algorithms can pick different edges when weights tie, here between
  the two edges of weight 2 and the two of weight 4, but any minimum spanning
  tree of this graph totals 37.
- 6.2 also reports when the graph turns out to be disconnected instead of
  silently printing a forest as if it were a tree.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 6.1 | O(E log V) with the indexed heap | O(V^2) for the matrix |
| 6.2 | O(E log E) dominated by the sort | O(V + E) |
