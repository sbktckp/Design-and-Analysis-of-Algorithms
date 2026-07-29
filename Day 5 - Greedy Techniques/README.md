# Lab Day 5: Greedy Techniques

Both programs read from the keyboard, so nothing here needs a data file.

| No. | Program | File |
|-----|---------|------|
| 5.1 | Fractional Knapsack | `5.1_fractional_knapsack.c` |
| 5.2 | Huffman Coding | `5.2_huffman_coding.c` |

## Run

```bash
cd "Day 5 - Greedy Techniques"
make
./bin/5.1_fractional_knapsack
./bin/5.2_huffman_coding
```

## Sample runs

5.1, using the sheet's numbers:

```
Enter the number of items: 3
Enter the profit and weight of item no 1: 27 16
Enter the profit and weight of item no 2: 14 12
Enter the profit and weight of item no 3: 26 13
Enter the capacity of knapsack: 18
```

gives item 3 taken whole, 0.3125 of item 1, nothing of item 2, profit
34.437500.

5.2, using the sheet's numbers:

```
Enter the number of distinct alphabets: 6
Enter the alphabets: a b c d e f
Enter its frequencies: 45 13 12 16 9 5
```

gives the in-order traversal `a c b f e d` and the CLRS code words
a=0, c=100, b=101, f=1100, e=1101, d=111.

## Notes

- **5.1** declares `struct ITEM` with the four members the sheet names and
  sorts by `profit_weight_ratio` using heap sort, as required. The trick is
  that building a MIN-heap and repeatedly moving the smallest ratio to the
  back leaves the array in non-increasing order, which is the order the greedy
  sweep wants, with no reversal step.
- Greedy is optimal for the FRACTIONAL problem because any leftover capacity
  can always be filled with a slice of the next densest item. The same
  argument does not hold for 0/1 knapsack.
- **5.2** builds the tree with a real min-priority queue keyed on frequency,
  not by sorting once, since every merge inserts a new internal node whose
  frequency must find its own place.
- The in-order traversal prints leaves only, since internal nodes carry sums
  rather than alphabets. Code words are printed as well, left edge 0 and right
  edge 1.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 5.1 | O(n log n) heap sort, O(n) greedy sweep | O(n) |
| 5.2 | O(n log n), n-1 merges of O(log n) | O(n) tree nodes |
