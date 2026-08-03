# Lab Day 9: Dynamic Programming, All Pair Shortest Path

| No. | Program | File | Input |
|-----|---------|------|-------|
| 9.1 | Floyd Warshall | `9.1_floyd_warshall.c` | `data/inDiAdjMat2.dat` |

## Run in the terminal

```bash
./run 9.1
```
```
Number of Vertices: 5

Shortest path weight matrix:
    0    1   -3    2   -4
    3    0   -4    1   -1
    7    4    0    5    3
    2   -1   -5    0   -2
    8    5    1    6    0

Enter the source and destination vertex: 2 5
Path: 2-->4-->1-->5
Cost: -1
```

The pair is asked for after the matrix is printed, so type `5`, look at the
matrix, then type `2 5` on one line.

Try `3 5` as well. The direct route does not exist, but the algorithm finds one
through other vertices, which is a good thing to demonstrate.

### The compact version

```bash
./run compact/9.1     # same 5, then 2 5
```

### Without the run script

```bash
cd "Day 9 - All Pair Shortest Path"
make
./bin/9.1_floyd_warshall
```

Stay inside the folder, since it opens `data/` by a relative path.

## Input format

A 5 by 5 cost adjacency matrix for a directed graph, 0 off the diagonal meaning
no edge. This graph carries a -4 and a -5, which is the reason it needs this
algorithm and not the Dijkstra of Day 7.

## How it works

### The idea, in one line

Allow one more vertex to act as a stopover on each pass.

After the pass for k, `d[i][j]` holds the best route from i to j that is allowed
to stop only at vertices numbered up to k. Start with k allowing nothing, so the
table is just the direct edges. Finish with k allowing everything, and the table
is the answer for all pairs at once.

Each pass asks one question for every pair:

```c
if (d[i][k] + d[k][j] < d[i][j])
    d[i][j] = d[i][k] + d[k][j];
```

That is it. Three nested loops, no priority queue, no per source run.

### The k loop must be outermost

This is the single most common way to get Floyd-Warshall wrong. The order has to
be k, then i, then j. Swap k inwards and each pair no longer considers every set
of allowed stopovers, and the results come out quietly wrong rather than
obviously broken. The reason is that the pass for k relies on the pass for k-1
being complete for every pair, which only holds if k is the outer loop.

### Negative weights are fine, negative cycles are not

Nothing here is ever declared final early, which is what let Day 7 fail on
negative edges. Every pair keeps getting reconsidered until the last pass, so a
negative edge is no problem at all.

A negative CYCLE is different. Going round it again always costs less, so there
is no shortest path, only an endless descent. The test is elegant: after the
algorithm finishes, look at the diagonal. `d[i][i]` should be 0, and anything
negative there means i can reach itself at a profit, which is a negative cycle.
The full version checks and refuses to print distances that would be meaningless.

### Reading a path back out

`pred[i][j]` holds the vertex just before j on the current best route from i.
When a shorter route through k is found, the update is:

```c
pred[i][j] = pred[k][j];       /* not k */
```

Writing `k` there is a real bug that is easy to talk yourself into. The step
before j on the new route is whatever came before j on the k to j route, which
may be several hops past k. Storing `pred[k][j]` keeps the whole chain
recoverable, so printing 2 to 5 gives `2-->4-->1-->5` rather than a single hop.

That path is also the clearest demonstration of what the algorithm buys. The
direct edge from 2 to 5 costs 7, but detouring through 4 and 1 picks up the -4
edge and ends up at -1.

### Infinity, handled carefully

There is no real infinity for an int, so a large constant stands in. The danger is
adding two of them and overflowing into something that looks small, which would
invent a path where none exists. The full version guards the addition by checking
both operands are finite first. The compact version relies on 9999 plus 9999
staying comfortably larger than any real path in this small graph, which is true
here but not a habit to carry to bigger inputs.

### Floyd-Warshall against running Dijkstra V times

Running Dijkstra from every vertex costs O(V E log V) and cannot handle negative
edges. Floyd-Warshall is O(V^3) flat, handles negative edges, detects negative
cycles, and is about six lines. On a dense graph it also wins outright, since E
approaches V^2.

## Complexity

| Part | Time | Space |
|------|------|-------|
| Main triple loop | O(n^3) | O(n^2) distances plus O(n^2) predecessors |
| Path reconstruction | O(length of path) | O(length of path) of stack |
