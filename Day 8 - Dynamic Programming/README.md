# Lab Day 8: Dynamic Programming

Both programs read from the keyboard.

| No. | Program | File |
|-----|---------|------|
| 8.1 | Matrix Chain Multiplication | `8.1_matrix_chain_multiplication.c` |
| 8.2 | Longest Common Subsequence | `8.2_longest_common_subsequence.c` |

## Run

From the repo root:

```bash
./run 8.1
./run 8.2
```

Or build this folder on its own:

```bash
cd "Day 8 - Dynamic Programming"
make
./bin/8.1_matrix_chain_multiplication
./bin/8.2_longest_common_subsequence
```

## Sample runs

8.1 with the sheet's four matrices 30x35, 35x15, 15x5, 5x10 prints the M table,
the S table, the parenthesization `((A1 (A2 A3)) A4)` and 9375 scalar
multiplications.

8.2 with `10010101` and `010110110` prints `LCS: 100110` and `LCS Length: 6`.

## Notes

- **8.1** fills the tables by increasing chain length, because the cost of a
  long chain depends on shorter ones that must already be solved. `m[i][j]` is
  the cheapest cost and `s[i][j]` the split point that achieved it, which is
  all the information the recursive printer needs to rebuild the brackets.
- Dimension compatibility is validated while reading, so a chain like 3x4 then
  5x6 is rejected with a clear message instead of producing a meaningless
  number.
- The dimension array `p` has one more entry than the matrix count, since
  matrix Ai is `p[i-1]` by `p[i]`, which is why the recurrence multiplies
  `p[i-1] * p[k] * p[j]`.
- **8.2** builds the `c` table and then walks it backwards from `c[m][n]` to
  recover the subsequence itself. When several subsequences share the maximum
  length, one of them is reported, which is all the definition requires.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 8.1 | O(n^3) over all chain lengths and split points | O(n^2) for the two tables |
| 8.2 | O(mn) | O(mn), reducible to O(min(m,n)) if only the length is wanted |
