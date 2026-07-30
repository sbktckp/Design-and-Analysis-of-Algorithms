# Lab Day 3: Divide and Conquer Method

Both programs are menu driven and share the same three input files. Each menu
option writes its own output file, so a run never overwrites another one.

| No. | Program | File | Input | Output |
|-----|---------|------|-------|--------|
| 3.1 | Merge Sort | `3.1_merge_sort.c` | `data/inAsce.dat` `data/inDesc.dat` `data/inRand.dat` | `data/outMergeAsce.dat` `data/outMergeDesc.dat` `data/outMergeRand.dat` |
| 3.2 | Quick Sort | `3.2_quick_sort.c` | same three files | `data/outQuickAsce.dat` `data/outQuickDesc.dat` `data/outQuickRand.dat` |

Each input file holds 300 elements, inside the 300 to 500 range the sheet asks
for. Ascending is 10, 20, 30 and so on, descending is the reverse, random is a
shuffle of the same values.

## Run

From the repo root:

```bash
./run 3.1
./run 3.2
```

Or build this folder on its own:

```bash
cd "Day 3 - Divide and Conquer Method"
make
./bin/3.1_merge_sort
./bin/3.2_quick_sort
```

## Notes

- **3.1** times only the sort, not the file reading or printing, using
  `clock_gettime(CLOCK_MONOTONIC)` and reporting nanoseconds. Comparisons are
  counted inside the merge step, which is where merge sort actually compares.
  The count barely moves between the three inputs because merge sort does the
  same amount of work regardless of the starting order.
- **3.2** uses Lomuto partitioning with the last element as pivot. Sorted
  input therefore hits the worst case, 44850 comparisons for 300 elements,
  which is exactly n(n-1)/2 and a recursion depth of 300. Random input takes
  around 2700 comparisons at depth 18.
- The best or worst case verdict is decided by comparison count against the
  geometric midpoint of the two theoretical bounds, plus recursion depth. The
  raw split counts are printed too, but they are not used alone, because tiny
  subarrays almost always leave one side empty and would mislead the verdict.

## Complexity

| No. | Best | Worst | Space |
|-----|------|-------|-------|
| 3.1 | O(n log n) | O(n log n) | O(n) scratch buffer |
| 3.2 | O(n log n) even splits | O(n^2) sorted input | O(log n) to O(n) stack |
