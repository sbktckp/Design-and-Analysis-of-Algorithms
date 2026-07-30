# Compact versions, Day 6

```bash
./run compact/6.1     # 9 vertices, start 1
./run compact/6.2
```

Both reach a total of 37, the answer on the lab sheet. Input and output are in
each header comment.

## What was traded away

- **6.1** finds the cheapest vertex with a linear scan instead of an indexed
  binary heap, so it costs O(V^2) rather than O(E log V). The question says to
  maintain a min-priority queue, so if that phrase is being marked, show the
  full version. For 9 vertices the answer is identical.
- **6.1** prints only the chosen edges and the total, not the cost adjacency
  matrix of the tree.
- **6.2** sorts edges with bubble sort, O(E^2), and its disjoint-set has
  neither union by rank nor path compression, just a parent chain. Still
  correct, just slower on big graphs.
- 999999 stands in for infinity in 6.1, which is fine as long as no real edge
  weight comes near it.
