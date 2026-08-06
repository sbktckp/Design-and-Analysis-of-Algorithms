# Lab Day 7: Greedy Techniques, Single Source Shortest Path

| No. | Program | File | Input |
|-----|---------|------|-------|
| 7.1 | Dijkstra Shortest Path | `7.1_dijkstra_shortest_path.c` | `data/inDiAdjMat1.dat` |

## Run in your Codespace terminal

### 7.1 Dijkstra's shortest path

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run 7.1
```

Type `5` for the vertex count, then `1` for the source. Output:

```
Source   Destination  Cost   Path
1        1            0      -
1        2            8      1->4->2
1        3            9      1->4->2->3
1        4            5      1->4
1        5            7      1->4->5
```

Run it again with source `4`. It is a directed graph, so the answers are
not symmetric, which is worth showing if asked whether direction matters.

### The compact version

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run compact/7.1
```

### Building this folder on its own

```bash
cd "Day 7 - Single Source Shortest Path"
make
./bin/7.1_dijkstra_shortest_path
```

Stay inside the folder, since it opens `data/` by a relative path.

## Input format

A 5 by 5 cost adjacency matrix for a DIRECTED graph, where 0 means no edge. Row
i column j is the weight of the edge from i to j, so unlike Day 6 the matrix is
not symmetric.

## How it works

### Relaxation, the one idea to take away

Every vertex carries a running guess, `dist[v]`, of how far it is from the
source. The source starts at 0 and everything else starts at infinity, meaning
no route is known yet.

Relaxing an edge from u to v asks one question: is going to u and then taking
this edge better than the guess I already have for v?

```c
if (dist[u] + weight(u, v) < dist[v]) {
    dist[v] = dist[u] + weight(u, v);
    parent[v] = u;
}
```

That is the entire mechanism. Guesses only ever go down, never up, and every
shortest path algorithm in the course is some strategy for choosing which edges
to relax and in what order. Dijkstra's strategy is to always work from the
closest unsettled vertex.

### The loop

1. take the unsettled vertex with the smallest distance, call it settled
2. relax all its outgoing edges
3. repeat until nothing is left

See it on the sample. Vertex 1 starts at 0 and relaxes its edges, giving vertex
2 a guess of 10 and vertex 4 a guess of 5. The smallest unsettled is now vertex 4
at 5. Relaxing from vertex 4 offers vertex 2 a route costing 5 + 3 = 8, which
beats 10, so vertex 2 drops to 8 and its parent becomes 4. That is why the answer
reads `1->4->2` rather than the direct edge, and it is worth pointing at if
someone asks what relaxation buys you.

### Why settling is allowed to be final

When a vertex is pulled out with the smallest remaining distance, that distance
is its true answer and can never improve. The reason is that any other route to
it would have to pass through some vertex that is at least as far away already,
and every edge adds a non negative amount, so such a route could only be longer
or equal.

That argument rests entirely on weights not being negative. Put one negative edge
in and it breaks: a vertex could be settled early and cheaply, then a long path
carrying a big negative weight arrives later offering something better, too late.
This is exactly why Day 9 uses Floyd-Warshall on the graph carrying a -4 and
a -5, and it is the standard follow up question here.

### The priority queue

Step 1 needs the minimum repeatedly and step 2 needs to lower specific keys, so
the full version reuses the same indexed binary heap as Prim's in Day 6, with
`pos[]` recording where each vertex sits so DECREASE-KEY stays O(log V). Overall
O(E log V).

The compact version scans the array for the minimum instead, which is O(V^2).
On a dense graph that is actually competitive, since E approaches V^2 anyway.

### Printing the path

Only `parent[]` is stored, one vertex per entry, so the path exists only
backwards. Rather than collecting it into an array and reversing it, the printer
recurses to the source first and prints on the way back out:

```c
static void print_path(const int *parent, int v)
{
    if (parent[v] >= 0) {
        print_path(parent, parent[v]);
        printf("->");
    }
    printf("%d", v + 1);
}
```

Same trick as the binary conversion in Day 2. Anything that must come out in
reverse can be produced this way.

Unreachable vertices print as INF in the full version rather than being skipped
or shown as a huge number.

## Complexity

| Part | Full version | Compact version |
|------|--------------|-----------------|
| Main loop | O(E log V) | O(V^2) |
| Reading the matrix | O(V^2) | O(V^2) |
| Printing one path | O(length of path) | same |
