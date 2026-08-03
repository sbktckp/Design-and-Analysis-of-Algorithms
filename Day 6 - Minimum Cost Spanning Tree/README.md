# Lab Day 6: Greedy Techniques, Minimum Cost Spanning Tree

Both programs run on the same nine vertex graph from the sheet, read in the two
different formats the two questions specify.

| No. | Program | File | Input |
|-----|---------|------|-------|
| 6.1 | Prim MST | `6.1_prim_mst.c` | `data/inUnAdjMat.dat` cost adjacency matrix |
| 6.2 | Kruskal MST | `6.2_kruskal_mst.c` | `data/inEdgeList.dat` edge list |

## Run in the terminal

### 6.1 Prim's MST

```bash
./run 6.1
```
```
Enter the Number of Vertices: 9
Enter the Starting Vertex: 1

Cost adjacency matrix of the minimum spanning tree:
  0   4   0   0   0   0   0   8   0
  4   0   0   0   0   0   0   0   0
  ...

Selected edges:
  1 -- 2  cost 4
  6 -- 3  cost 4
  3 -- 4  cost 7
  4 -- 5  cost 9
  7 -- 6  cost 2
  8 -- 7  cost 1
  1 -- 8  cost 8
  3 -- 9  cost 2

Total Weight of the Spanning Tree: 37
```

### 6.2 Kruskal's MST

No keyboard input at all, it reads everything from the file:

```bash
./run 6.2
```
```
Vertices: 9   Edges: 14

Edge      Cost
7--8      1
3--9      2
6--7      2
1--2      4
3--6      4
3--4      7
1--8      8
4--5      9

Total Weight of the Spanning Tree: 37
```

Run both and point at the two totals. Same 37 by completely different routes,
and the edge lists differ where weights tie.

### The compact versions

```bash
./run compact/6.1     # same 9 and 1
./run compact/6.2
```

### Without the run script

```bash
cd "Day 6 - Minimum Cost Spanning Tree"
make
./bin/6.1_prim_mst
./bin/6.2_kruskal_mst
```

Stay inside the folder, since both open `data/` by a relative path.

## Input formats

`inUnAdjMat.dat` is a 9 by 9 symmetric matrix where 0 means no edge. Row i
column j holds the weight between i and j.

`inEdgeList.dat` starts with `n m`, then one line per edge holding `u v w`.

The two formats suit the two algorithms. Prim's asks "who are my neighbours",
which a matrix answers in one row lookup. Kruskal's asks "give me all edges
sorted", which an edge list already almost is.

## What a spanning tree is

Given a connected graph, a spanning tree is a selection of edges that touches
every vertex and contains no cycle. For n vertices that is always exactly n-1
edges. Minimum spanning tree means the selection with the smallest total weight.

Both algorithms today are greedy, both are provably correct, and they reach the
same total by opposite routes.

## How each program works

### 6.1 Prim's algorithm, grow one tree

Start at any vertex and keep one growing tree. At each step, take the cheapest
edge that leads from the tree to a vertex not yet in it. Repeat n-1 times.

The bookkeeping is what makes this efficient. For every vertex outside the tree,
`key[v]` holds the weight of the cheapest single edge that would attach v right
now, and `parent[v]` remembers the other end of that edge. Then each round is:

1. extract the vertex with the smallest key, which joins the tree
2. look at its neighbours, and if this new vertex offers a cheaper way in than
   they had before, lower their key and update their parent

Step 2 is DECREASE-KEY, and when it is done every parent array entry becomes an
edge of the finished tree.

**Why it is safe.** The cheapest edge leaving the current tree can never be a
mistake. If some minimum spanning tree omitted it, adding it would create a
cycle, and that cycle must contain another edge crossing out of the tree which is
at least as expensive. Swap them and the total does not get worse. That is the
cut property, and it is the whole proof.

**Why the queue is indexed.** A plain heap can find its minimum quickly, but
DECREASE-KEY needs to find one specific vertex inside the heap, which a plain
heap cannot do without scanning. So the full version keeps a `pos[]` array
recording which heap slot holds each vertex. With it, lowering a key is O(log V).
Without it, you are back to scanning, which is the compact version's O(V^2).
For 9 vertices the difference is invisible, but the question names the structure,
so the full version builds it properly.

### 6.2 Kruskal's algorithm, join many trees

Forget growing outwards. Sort every edge from cheapest to most expensive and take
each one unless its two ends are already connected. Stop after n-1 edges.

At any moment there is a forest of separate pieces, and each accepted edge welds
two pieces into one.

**The cycle test is the interesting part.** "Already connected" has to be answered
fast, thousands of times, and a graph traversal per edge would be far too slow.
Disjoint set solves it. Every vertex points at a parent, and following that chain
to the top gives a representative for its whole component. Two vertices are
connected exactly when they share a representative, so:

```
find(u) == find(v)   ->  taking this edge would close a cycle, skip it
otherwise            ->  take it, and point one representative at the other
```

Joining two components is one assignment. The full version adds two standard
improvements: union by rank attaches the shorter tree under the taller one, and
path compression rewires nodes to point nearer the top while walking up. Together
they make each test effectively constant time, so the sort dominates the running
time.

**Why it is safe.** Same cut property, seen differently. The cheapest edge that
joins two separate components cannot hurt, because any tree that excluded it
could swap it in for a costlier edge along the cycle it would form.

### Prim against Kruskal

| | Prim | Kruskal |
|---|---|---|
| Keeps | one growing tree | a forest that merges |
| Needs | fast "cheapest edge out of my tree" | edges in sorted order |
| Structure | min-priority queue | disjoint set |
| Suits | dense graphs | sparse graphs |
| Reads | adjacency matrix | edge list |

On ties the two can choose different edges, and this graph has two edges of
weight 2 and two of weight 4, so the printed lists differ. Every minimum spanning
tree of this graph still totals 37. A graph can have several different minimum
spanning trees, but they all share the same weight.

6.2 also reports when the graph turns out to be disconnected, rather than
silently printing a forest as though it were a tree.

## Complexity

| No. | Full version | Compact version |
|-----|--------------|-----------------|
| 6.1 | O(E log V) with the indexed heap | O(V^2) linear scan |
| 6.2 | O(E log E), dominated by the sort | O(E^2) bubble sort |
