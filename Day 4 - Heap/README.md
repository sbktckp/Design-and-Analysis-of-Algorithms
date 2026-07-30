# Lab Day 4: Heap

| No. | Program | File | Input |
|-----|---------|------|-------|
| 4.1 | Person Heap | `4.1_person_heap.c` | `data/inPerson.dat` |

## Run

From the repo root:

```bash
./run 4.1
```

Or build this folder on its own:

```bash
cd "Day 4 - Heap"
make
./bin/4.1_person_heap
```

## Menu

```
1. Read Data
2. Create a Min-heap based on the age
3. Create a Max-heap based on the weight
4. Display weight of the youngest person
5. Insert a new person into the Min-heap
6. Delete the oldest person
7. Exit
```

Option 1 must run first, everything else works on the array it loads.

## Input format

One record per line, comma separated so that names may contain spaces:

```
id,name,age,height,weight
0,Adarsh Hota,39,77,231
```

Weight is in pounds, matching the sheet, and option 4 converts to kilograms.
With the supplied file the youngest is Norma Webster at 23, weighing 145 lb,
so option 4 prints 65.77 kg exactly as the sheet shows.

## Notes

- The array of `struct person` IS the heap, so no second structure is kept.
  `build_heap` is the bottom-up heapify, which costs O(n), not the O(n log n)
  you get from inserting one at a time.
- One pair of sift routines serves both heaps. Which key they compare, age or
  weight, and in which direction, is decided by the active heap kind, so
  option 2 and option 3 reuse the same code.
- Option 4 is O(1) when the min-heap on age is the active one, because the
  youngest is then the root. If a different heap is active it falls back to a
  linear scan rather than reporting a wrong answer.
- Option 6 finds the oldest by scan, since a min-heap on age gives no fast
  access to the maximum, then fills the hole with the last element and
  restores the heap property in O(log n).
- Names are copied with a hand written `dup_string` instead of `strdup`, which
  is not part of ISO C17 and would not compile cleanly under `-Wpedantic`.

## Complexity

| Operation | Time |
|-----------|------|
| Build heap | O(n) |
| Insert | O(log n) |
| Delete oldest | O(n) to find, O(log n) to repair |
| Weight of youngest | O(1) with the min-heap on age |
