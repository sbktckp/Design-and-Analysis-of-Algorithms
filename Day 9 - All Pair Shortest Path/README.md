# Lab Day 9: Dynamic Programming, All Pair Shortest Path

| No. | Program | File | Input |
|-----|---------|------|-------|
| 9.1 | Floyd Warshall | `9.1_floyd_warshall.c` | `data/inDiAdjMat2.dat` |

## Run

From the repo root:

```bash
./run 9.1      # 5 vertices, then the pair 2 5
```

Or build this folder on its own:

```bash
cd "Day 9 - All Pair Shortest Path"
make
./bin/9.1_floyd_warshall
```

Output for the supplied graph, matching the sheet:

```
   0    1   -3    2   -4
   3    0   -4    1   -1
   7    4    0    5    3
   2   -1   -5    0   -2
   8    5    1    6    0

Path: 2-->4-->1-->5
Cost: -1
```

## Input format

A 5 by 5 cost adjacency matrix for a directed graph. A 0 off the diagonal
means there is no edge. This graph carries a -4 and a -5, which is exactly why
it needs Floyd-Warshall rather than the Dijkstra of Day 7.

## Notes

- The k loop must be the outermost one. Each round permits one more vertex to
  serve as an intermediate, so by the end every possible intermediate set has
  been considered.
- The predecessor matrix is updated with `pred[i][j] = pred[k][j]`, not `k`,
  which is what lets `print_path` recurse and produce the full chain of
  intermediate vertices rather than a single hop.
- Negative edges are fine, negative cycles are not. A negative entry on the
  diagonal after the algorithm finishes proves one exists, and the program
  says so instead of printing distances that mean nothing.
- INF is a large finite constant rather than a real infinity, and additions
  are guarded by a check that both operands are finite, so no overflow can
  masquerade as a short path.

## Complexity

| Part | Time | Space |
|------|------|-------|
| Floyd-Warshall | O(n^3) | O(n^2) for distances plus O(n^2) for predecessors |
| Path reconstruction | O(length of path) | O(length of path) stack |
