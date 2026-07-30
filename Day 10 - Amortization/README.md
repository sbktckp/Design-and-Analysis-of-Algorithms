# Lab Day 10: Amortization

All three programs are self contained and need no data files.

| No. | Program | File |
|-----|---------|------|
| 10.1 | Randomized Quicksort | `10.1_randomized_quicksort.c` |
| 10.2 | Fibonacci Fitstring | `10.2_fibonacci_fitstring.c` |
| 10.3 | Binary Counter Reset | `10.3_binary_counter_reset.c` |

## Run

From the repo root:

```bash
./run 10.1     # enter 300
./run 10.2     # option 4 runs the self test
./run 10.3     # option 4 runs the sample sequence
```

Or build this folder on its own:

```bash
cd "Day 10 - Amortization"
make
./bin/10.1_randomized_quicksort
./bin/10.2_fibonacci_fitstring
./bin/10.3_binary_counter_reset
```

## Notes

**10.1** sorts an already sorted array, the input that forces deterministic
quicksort into O(n^2). With 300 elements the deterministic version needs 44850
comparisons at recursion depth 300, while the randomized version needs about
2700 at depth 18. The expected number of comparisons is 2n ln n, roughly
1.39 n log2 n, and it holds for every input because the pivot rank is decided
by the coin rather than by the data. Worst case is still O(n^2), but reaching
it now requires pathological luck instead of sorted input.

**10.2** keeps an array of fits where fit i says whether Fibonacci number Fi is
included, indexed from 2 upward since F1 and F2 are both 1. The fitstring
101110 is F6 + F4 + F3 + F2 = 8 + 3 + 2 + 1 = 14. As the hint says, a number
has more than one valid fitstring, so the representation is deliberately
redundant and repaired with three local rules:

- carry, `2*Fi = F(i+1) + F(i-2)`
- combine, `Fi + F(i+1) = F(i+2)`
- borrow, `Fi = F(i-1) + F(i-2)`

Each repair is O(1) work and lowers the potential "number of set fits plus
number of adjacent set pairs", so a long chain of repairs is always paid for
by the cheap operations that built the potential up. Increment and decrement
are therefore O(1) amortized. Menu option 4 counts from 0 up to a chosen value
and back down, checking the decoded value at every step, and prints PASSED.

**10.3** stores the counter as an array of bits plus a pointer to the
high-order 1. RESET clears only the bits up to that pointer instead of the
whole array, which is what keeps a sequence of n operations at O(n).

With potential PHI = (number of 1 bits) + (high + 1):

- INCREMENT clears t trailing ones and sets one bit, costing t + 1, while PHI
  falls by t - 1 and rises by at most 1, so amortized cost is at most 3.
- RESET costs high + 2 and drives PHI down by at least high + 1, so amortized
  cost is at most 1.

Option 4 reproduces the sheet's table, where five operations cost 9 units in
total.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 10.1 | O(n log n) expected, O(n^2) worst | O(log n) expected stack |
| 10.2 | O(1) amortized per increment or decrement | O(number of fits) |
| 10.3 | O(1) amortized per INCREMENT or RESET | O(bits) |
