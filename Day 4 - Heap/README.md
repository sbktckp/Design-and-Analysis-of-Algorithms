# Lab Day 4: Heap

| No. | Program | File | Input |
|-----|---------|------|-------|
| 4.1 | Person Heap | `4.1_person_heap.c` | `data/inPerson.dat` |
| 4.2 | Fractional Knapsack | `4.2_knapsack.c` | `data/inKnapsack.dat` |
| 4.3 | Huffman Coding | `4.3_huffman.c` | `data/inHuffman.dat` |

## Run in your Codespace terminal

### 4.1 Person heap

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run 4.1
```

The menu:

```
1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit
```

Option 1 must come first, since everything else works on the array it
loads. A session that answers the question the sheet asks is `1`, then
`2`, then `4`, then `7`. It reports Norma Webster, age 23, weighing
65.77 kg.

### The compact version

No menu. It reads the file, builds the min-heap and prints the youngest
person's weight:

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run compact/4.1
```

### 4.2 Fractional knapsack

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run 4.2
```

The menu:

```
1. Read Data
2. Fill Knapsack (enter capacity)
3. Exit
```

Option 1 loads the items. Option 2 asks for a capacity, sorts the items
by profit/weight ratio, and prints exactly what got taken and the
resulting maximum profit. With the supplied data (weights 10, 20, 30
and profits 60, 100, 120) and capacity 50, it takes items 0 and 1 whole
plus 2/3 of item 2, for a maximum profit of 240.00.

The compact version, no menu, asks only for the capacity and prints the
final profit:

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run compact/4.2
```

### 4.3 Huffman coding

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run 4.3
```

The menu:

```
1. Read Data
2. Build Huffman Tree
3. Display Codes
4. Encode a Message
5. Display Tree
6. Exit
```

Option 1 loads character frequencies, option 2 builds the tree, option 3
lists each character's code, option 4 encodes a message you type using
those codes, and option 5 prints the tree itself, sideways in the
terminal. With the classic sample data (`a`=5, `b`=9, `c`=12, `d`=13,
`e`=16, `f`=45) the codes come out to `f`=0, `c`=100, `d`=101, `a`=1100,
`b`=1101, `e`=111, matching the standard textbook tree, and option 5
draws that same tree as:

```
    |   |   +-- 'e' (16)
    |   +-- (30)
    |   |       +-- 'b' (9)
    |   |   \-- (14)
    |   |       \-- 'a' (5)
    +-- (55)
    |       +-- 'd' (13)
    |   \-- (25)
    |       \-- 'c' (12)
(100)
    \-- 'f' (45)
```

The root is on the left, leaves on the right. Right children print above,
left children print below, and tracing any leaf back to the root and
reading right-branches as 1 and left-branches as 0 reproduces its code
from option 3.

The compact version, no menu, builds the tree and prints the codes:

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run compact/4.3
```

### Building this folder on its own

```bash
cd "Day 4 - Heap"
make
./bin/4.1_person_heap
./bin/4.2_knapsack
./bin/4.3_huffman
```

Stay inside the folder, since the programs open their `data/` files by a
relative path.

## Input format

### 4.1 Person heap

One record per line, comma separated so that names may contain spaces:

```
id,name,age,height,weight
0,Adarsh Hota,39,77,231
```

Commas rather than spaces matter here. `scanf("%s")` stops at the first space,
so "Adarsh Hota" would be read as "Adarsh" and everything after it would land in
the wrong field. The format `%29[^,]` means read up to 29 characters that are
not a comma, which keeps the name whole.

Weight is in pounds, as on the sheet, and option 4 converts to kilograms. The
youngest in the supplied file is Norma Webster at 23, weighing 145 lb, so option
4 prints 65.77 kg, matching the sheet exactly.

### 4.2 Fractional knapsack

One record per line: `weight,profit`

```
10,60
20,100
30,120
```

### 4.3 Huffman coding

One record per line: `character,frequency`

```
a,5
b,9
c,12
d,13
e,16
f,45
```

## What a heap actually is

A heap is an ordinary array that you agree to read as a tree. No pointers, no
nodes, just an indexing rule:

```
children of index i   ->  2i+1 and 2i+2
parent of index i     ->  (i-1)/2
```

So the array `23 24 38 47 56 39 63` is this tree:

```
            23
          /    \
        24      38
       /  \    /  \
     47   56  39   63
```

The one rule a min-heap keeps is that every parent is smaller than its children.
Notice what it does NOT promise: siblings are in no particular order, and the
array as a whole is not sorted. That weaker promise is exactly why a heap is
cheap to maintain, and it is still strong enough to guarantee the smallest
element of all is sitting at index 0.

That is the deal a heap offers. Give up full sorting, get the minimum for free.

## How 4.1 works

### The two repair operations

Everything a heap does is one of two moves.

**Sift down** takes an element that might be too big for its position and pushes
it downwards. Compare it with both children, swap it with the smaller one if
either is smaller, and repeat from the new position. Used when the root is
replaced or an element is made larger.

**Sift up** takes an element that might be too small and pushes it upwards.
Compare it with its parent, swap if it is smaller, repeat. Used after inserting
at the end of the array.

Both walk one path of the tree, so both cost O(log n).

### Building the heap in O(n), not O(n log n)

The obvious way to build a heap is to insert the elements one at a time, which
costs O(n log n). The better way, and the one the program uses, is bottom up:

```c
for (i = count / 2 - 1; i >= 0; i--)
    sift_down(i);
```

Start at the last element that has any children at all, `n/2 - 1`, and sift down
from there backwards to the root. Everything past that point is a leaf, and a
leaf is already a valid heap of one element, so there is nothing to do for the
entire second half of the array.

This is O(n) overall, and the reason is worth having ready: most of the elements
are near the bottom where sifting is short, and the few elements that could sift
a long way are near the top where there are hardly any of them. The sum works
out linear rather than n log n.

### One set of routines, two different heaps

Options 2 and 3 ask for two different heaps, a min-heap on age and a max-heap on
weight. Rather than writing the code twice, the program has a single comparison
function:

```c
static int precedes(const struct person *a, const struct person *b)
{
    if (kind == HEAP_MAX_WEIGHT)
        return a->weight > b->weight;
    return a->age < b->age;
}
```

Sift up and sift down both ask `precedes` which element should be nearer the
root, and never know which heap they are working on. Changing the key and
changing the direction are the same one line change. That is the real lesson: a
max-heap is not a different data structure, it is a flipped comparison.

### Why option 6 has to scan

Option 4 wants the youngest person, and in the min-heap on age that is simply
`people[0]`, an O(1) answer.

Option 6 wants the OLDEST person, and a min-heap says nothing useful about where
its largest element is. It could be any leaf. So the program scans, O(n), fills
the hole with the last element, and then repairs with a sift. Asking a heap for
the wrong end is a normal situation and worth being able to explain: if you need
both ends cheaply, you need two heaps or a different structure entirely.

### A small C detail

Names are copied with a hand written `dup_string` instead of `strdup`. `strdup`
is POSIX, not ISO C17, and would be flagged under `-Wpedantic`. Four lines of
`malloc` and `memcpy` keep the build clean.

## How 4.2 works

### The greedy rule

Every item has a profit/weight ratio. Sort items by that ratio, descending, and
fill the sack from the top of that order: take whole items while they fit, and
when one doesn't fit, take the fraction that does and stop.

```c
qsort(items, (size_t)count, sizeof *items, by_ratio_desc);
for (i = 0; i < count && remaining > 0.0; i++) {
    if (items[i].weight <= remaining) { /* take it whole */ }
    else { /* take remaining / items[i].weight of it, and stop */ }
}
```

### Why this greedy choice is actually optimal here

Fractional knapsack is one of the few knapsack variants where greedy provably
gives the optimal answer, and the reason is the ability to take a fraction. Any
solution that leaves unused capacity while a higher-ratio item still has
untaken weight can be improved by shifting weight from a lower-ratio item to
that higher-ratio item, strictly increasing profit for the same total weight.
So an optimal solution must exhaust capacity on the highest available ratios
first, which is exactly what the sort-and-fill does.

This breaks the moment items must be taken whole (0/1 knapsack), because then
a locally best ratio can force a bad combination overall, and the problem needs
dynamic programming instead. The fractional version is the base case where
greedy has a real optimality proof, not just a heuristic.

### Complexity

`qsort` costs O(n log n), the single pass to fill the sack costs O(n), so the
whole thing is O(n log n), dominated by the sort.

## How 4.3 works

### Why a min-heap

Building the tree means repeatedly asking "which two nodes have the smallest
combined frequency to merge next", and a min-heap answers "what's smallest"
in O(1) and lets you pop it in O(log n). That's the same heap machinery as
4.1, just keyed on `freq` instead of `age`.

```c
while (heap_size > 1) {
    struct node *left = heap_pop();
    struct node *right = heap_pop();
    struct node *parent = new_node('\0', left->freq + right->freq, left, right);
    heap_push(parent);
}
root = heap_pop();
```

Each iteration removes two nodes and adds one back, so after n-1 merges a
single node remains: the root of the Huffman tree.

### Why the merges give the optimal code

Merging the two least-frequent nodes first means the least-frequent characters
end up deepest in the tree, farthest from the root, so they get the longest
codes, and the most frequent characters end up shallow with the shortest
codes. That's exactly the tradeoff an optimal prefix code wants: spend more
bits on rare symbols, fewer bits on common ones, and the earliest, greedy
merges guarantee no better tree exists for these frequencies.

### Getting a code out of the tree

A code for a character is just the path from the root to its leaf, left
branches as 0, right branches as 1:

```c
path[depth] = '0'; recurse into left;
path[depth] = '1'; recurse into right;
```

No two characters can share a full path to another character's leaf, because
every character sits at a leaf and no leaf is an ancestor of another. That's
what makes Huffman codes prefix-free: no code is a prefix of another, so a
decoder reading bit by bit always knows the moment a code is complete.

### Drawing the tree sideways

Option 5 walks the same tree that produces the codes, but instead of
concatenating 0s and 1s it prints each node with connectors, right
children first (above) and left children after (below):

```c
if (n->right != NULL)
    print_tree(n->right, child_prefix, "+-- ", n->left != NULL);
printf("%s%s", prefix, branch);
...
if (n->left != NULL)
    print_tree(n->left, child_prefix, "\\-- ", 0);
```

`prefix` accumulates the guide bars/spaces inherited from ancestors, and
`has_sibling_below` tracks whether a node still has a left sibling
underneath it that needs a `|` to hang off. This is the same rotated,
root-on-the-left layout most terminal tree viewers use, and the leaf
reached by any path in this printout is the leaf reached by the
matching sequence of 0s and 1s in the codes.

### Complexity

Building the heap from n leaves and doing n-1 pop/push pairs costs
O(n log n). Reading a code by walking root to leaf costs O(depth), bounded
by O(n) in the worst (very skewed) case, O(log n) for a balanced tree.
Printing the whole tree visits every node once, O(n).

## Complexity summary

| Program | Operation | Cost | Why |
|---------|-----------|------|-----|
| 4.1 | Build heap | O(n) | bottom up, most elements are leaves |
| 4.1 | Insert | O(log n) | one sift up along a single path |
| 4.1 | Delete oldest | O(n) to find, O(log n) to repair | a min-heap cannot locate its maximum |
| 4.1 | Weight of youngest | O(1) | it is the root |
| 4.2 | Sort by ratio | O(n log n) | `qsort` |
| 4.2 | Fill knapsack | O(n) | one pass over the sorted items |
| 4.3 | Build tree | O(n log n) | n-1 pop/push pairs on a min-heap |
| 4.3 | Read a code | O(depth) | walk root to leaf |
| 4.3 | Display tree | O(n) | visits every node once |
