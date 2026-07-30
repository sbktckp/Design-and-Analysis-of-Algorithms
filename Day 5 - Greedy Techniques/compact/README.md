# Compact versions, Day 5

```bash
./run compact/5.1
./run compact/5.2
```

Both read from the keyboard. Input and output are in each header comment.

## What was traded away

- **5.1** sorts by ratio with bubble sort instead of heap sort. The question
  asks for heap sort, so if that is being marked, use the full version. Bubble
  sort is here only because it is six lines and the answer is identical.
- **5.1** uses four parallel arrays rather than `struct ITEM`. The question
  names the structure, so again the full version is the safer one to show.
- **5.2** finds the smallest frequency with a linear scan instead of a real
  min-priority queue, which turns O(n log n) into O(n^2). At six symbols it
  makes no difference, and the tree that comes out is the same.
- **5.2** builds the tree in three flat arrays, `lf`, `rt` and `fq`, instead of
  pointers. Index -1 stands in for a null child.
