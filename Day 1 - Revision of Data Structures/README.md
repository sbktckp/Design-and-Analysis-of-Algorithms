# Lab Day 1: Revision of Data Structures

| No. | Program | File | Input source |
|-----|---------|------|--------------|
| 1.1 | Second Smallest & Largest | `1.1_second_smallest_largest.c` | `data/1.1_input.txt` |
| 1.2 | Prefix Sum Array | `1.2_prefix_sum.c` | keyboard |
| 1.3 | Duplicate Element Count | `1.3_duplicate_elements.c` | `data/1.3_input.txt` |
| 1.4 | Rotate Right Array | `1.4_rotate_right.c` | keyboard |

## Run

```bash
cd "Day 1 - Revision of Data Structures"
make            # builds every .c into bin/
./bin/1.1_second_smallest_largest
./bin/1.2_prefix_sum
./bin/1.3_duplicate_elements
./bin/1.4_rotate_right
```

Run the binaries from inside this folder so the relative `data/` paths resolve.
Build one program only: `make bin/1.2_prefix_sum`. Clean up: `make clean`.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 1.1 | O(n) single pass | O(1) |
| 1.2 | O(n) | O(n) |
| 1.3 | O(n log n) sort-and-scan | O(n) |
| 1.4 | O(p2) swaps | O(1) |
