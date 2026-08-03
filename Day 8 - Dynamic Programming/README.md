# Lab Day 8: Dynamic Programming

Both programs read from the keyboard.

| No. | Program | File |
|-----|---------|------|
| 8.1 | Matrix Chain Multiplication | `8.1_matrix_chain_multiplication.c` |
| 8.2 | Longest Common Subsequence | `8.2_longest_common_subsequence.c` |

## Run in the terminal

### 8.1 Matrix chain multiplication

```bash
./run 8.1
```
```
Enter number of matrices: 4
Enter row and col size of A1: 30 35
Enter row and col size of A2: 35 15
Enter row and col size of A3: 15 5
Enter row and col size of A4: 5 10

M Table:
0 15750 7875 9375
0 0 2625 4375
0 0 0 750
0 0 0 0

S Table:
0 1 1 3
0 0 2 3
0 0 0 3
0 0 0 0

Optimal parenthesization: ((A1 (A2 A3)) A4)
The optimal ordering of the given matrices requires 9375 scalar multiplications.
```

Try entering mismatched dimensions, say 30 35 then 20 15, and it refuses with a
clear message instead of printing a meaningless number.

### 8.2 Longest common subsequence

```bash
./run 8.2
```
```
Enter the first string into an array: 10010101
Enter the second string into an array: 010110110

LCS: 100110
LCS Length: 6
```

It takes any strings, not only binary ones. Try `ABCBDAB` and `BDCABA` for the
textbook example.

### The compact versions

```bash
./run compact/8.1
./run compact/8.2
```

### Without the run script

```bash
cd "Day 8 - Dynamic Programming"
make
./bin/8.1_matrix_chain_multiplication
./bin/8.2_longest_common_subsequence
```

Neither reads a data file, so these two work from anywhere.

## What dynamic programming is, in one paragraph

Some problems break into smaller versions of themselves, but the smaller pieces
overlap and get asked for again and again. Plain recursion solves the same piece
thousands of times and takes exponential time. Dynamic programming solves each
piece once, writes the answer in a table, and looks it up afterwards.

Two things follow from that, and both show up in today's programs. You need an
order of filling that guarantees a piece is already solved before anything needs
it, which is why both loops start small. And the table holds costs or lengths,
not the answers themselves, so a second walk is needed to recover the actual
bracketing or the actual subsequence.

## How each program works

### 8.1 Matrix chain multiplication

Matrix multiplication is associative, so `(A1 A2) A3` and `A1 (A2 A3)` give the
same matrix. They do not cost the same. Multiplying an a x b matrix by a b x c
matrix takes a x b x c scalar multiplications, so where the brackets go changes
the amount of arithmetic enormously. For the sample chain, the best bracketing
needs 9375 multiplications while going strictly left to right needs 87500.

`m[i][j]` is the cheapest cost of multiplying Ai through Aj. To fill one entry,
try every place k where the chain could be split, and pay three things: the cost
of the left part, the cost of the right part, and the single multiplication that
joins the two results.

```c
cost = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
```

Keep the smallest, and record the winning k in `s[i][j]`.

**The dimension array.** Four matrices need five numbers, because neighbours
share a dimension. Matrix Ai is `p[i-1]` by `p[i]`. So for 30x35, 35x15, 15x5,
5x10, p is `30 35 15 5 10`. That is why the joining cost reads
`p[i-1] * p[k] * p[j]`: the left result is p[i-1] by p[k], the right result is
p[k] by p[j].

**Fill order.** The outer loop is chain LENGTH, from 2 upwards, not i or j. A
chain of four leans on chains of three and two, which must already be finished.
Getting this order wrong is the classic way to produce a table full of garbage.

**Reading the answer out.** `m[1][n]` is the cost. The bracketing lives in the s
table, recovered recursively: to print Ai..Aj, print an open bracket, then
everything up to `s[i][j]`, then everything after it, then a close bracket.
Since `s[1][4]` is 3, the outermost split is after A3, giving `((A1 (A2 A3)) A4)`.

O(n^3) time, since there are O(n^2) entries and each tries up to n splits, and
O(n^2) space.

### 8.2 Longest common subsequence

A subsequence keeps the order of characters but is allowed to skip. So `100110`
is a subsequence of `10010101`, whereas a subSTRING would have to be contiguous.
That difference is the first thing to get straight.

`c[i][j]` is the LCS length of the first i characters of X and the first j of Y.
There are only two cases:

- **the characters match.** They can both be used, so take the answer for the
  two shorter prefixes and add one: `c[i-1][j-1] + 1`.
- **they do not match.** One of them has to be given up. Try both and keep the
  better: `max(c[i-1][j], c[i][j-1])`.

Row 0 and column 0 stay zero, since an empty string shares nothing. Filling row
by row means both neighbours and the diagonal are always ready.

**Recovering the subsequence.** The table only holds lengths, so start at the
bottom right and walk backwards. On a match, that character is part of the answer,
so record it and step diagonally. On a mismatch, step in whichever direction the
value came from. The characters arrive last first, which is why they are written
into the output buffer from the end towards the front.

**Several answers can be correct.** When there are ties, different tie breaking
gives a different subsequence of the same length. `100110` is one valid answer of
length 6 for the sample, and so are others. The LENGTH is unique, the string is
not.

O(mn) time and O(mn) space. If only the length were needed, two rows would be
enough, O(min(m,n)) space, but then the subsequence could not be recovered.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 8.1 | O(n^3) | O(n^2) for the two tables |
| 8.2 | O(mn) | O(mn), reducible if only the length is wanted |
