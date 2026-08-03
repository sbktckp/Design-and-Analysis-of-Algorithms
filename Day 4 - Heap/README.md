# Lab Day 4: Heap

| No. | Program | File | Input |
|-----|---------|------|-------|
| 4.1 | Person Heap | `4.1_person_heap.c` | `data/inPerson.dat` |

## Run in the terminal

```bash
./run 4.1
```

Option 1 must come first, since everything else works on the array it loads.
A full session that answers the question the sheet asks:

```
Enter option: 1

Data read from file:
Id   Name               Age   Height  Weight(pound)
0    Adarsh Hota        39    77      231
1    Levi Maier         56    77      129
...

Enter option: 2
Min-heap on age (root is the youngest):
...

Enter option: 4
Youngest person: Norma Webster, age 23
Weight of youngest person: 65.77 kg

Enter option: 7
```

Option 3 builds the max-heap on weight, option 5 asks for a new person's
details, option 6 deletes the oldest.

### The compact version

No menu, it reads the file, builds the min-heap and prints the youngest
person's weight:

```bash
./run compact/4.1
```

### Without the run script

```bash
cd "Day 4 - Heap"
make
./bin/4.1_person_heap
```

Stay inside the folder, since the program opens `data/inPerson.dat` by a
relative path.

## Input format

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

## How the program works

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

## Complexity

| Operation | Cost | Why |
|-----------|------|-----|
| Build heap | O(n) | bottom up, most elements are leaves |
| Insert | O(log n) | one sift up along a single path |
| Delete oldest | O(n) to find, O(log n) to repair | a min-heap cannot locate its maximum |
| Weight of youngest | O(1) | it is the root |
