# Lab Day 10: Amortization

All three programs are self contained and need no data files.

| No. | Program | File |
|-----|---------|------|
| 10.1 | Randomized Quicksort | `10.1_randomized_quicksort.c` |
| 10.2 | Fibonacci Fitstring | `10.2_fibonacci_fitstring.c` |
| 10.3 | Binary Counter Reset | `10.3_binary_counter_reset.c` |

## Run

```bash
./run 10.1     # enter 300
./run 10.2     # option 4 runs the self test
./run 10.3     # option 4 runs the sample sequence
./run compact/10.1
```

## Two ideas that sound alike and are not

**Expected cost** is an average over randomness inside the algorithm. 10.1 is
this. A single run could in principle be slow, but the dice would have to fall
badly, and the input has no say in it.

**Amortized cost** is an average over a SEQUENCE of operations, with no
randomness at all. 10.2 and 10.3 are this. Some individual operations really are
expensive, and the argument is that they cannot happen often, because the cheap
operations before them had to build up the conditions first.

Both get written as O(1) or O(n log n) with a qualifier in front, and mixing up
which qualifier applies is the mistake this day exists to prevent.

## How each program works

### 10.1 Randomized quicksort

Day 3 showed quicksort collapsing to O(n^2) on sorted input, because the last
element of an ascending range is always the largest, so every split is n-1
against nothing.

The fix is one line before partitioning:

```c
int r = lo + rand() % (hi - lo + 1);
swap(&a[r], &a[hi]);
```

Pick a random element and move it into the pivot slot. Now the quality of the
split depends on the dice, not on the data. The expected number of comparisons is
2n ln n, about 1.39 n log2 n, and that holds for EVERY input, including the one
that used to be fatal.

This program deliberately feeds it an already sorted array to show it. With 300
elements the deterministic version needs 44850 comparisons at recursion depth 300.
The randomized version needs somewhere around 2500 at depth 18, and the exact
number changes on each run since the pivots differ.

Say this precisely if asked: the worst case is still O(n^2), it has not been
eliminated. What changed is that reaching it now requires a run of bad luck
rather than a particular input, and no adversary can arrange it by choosing the
data.

### 10.2 Fibonacci fitstring

Instead of bits meaning 1, 2, 4, 8, the digits here mean Fibonacci numbers. A fit
at position i says Fi is part of the sum, and positions start at 2, since F1 and
F2 are both 1 and one of them would be redundant. So `101110` is F6+F4+F3+F2,
that is 8+3+2+1 = 14.

The hint on the sheet is the key to the whole problem: most numbers have MORE
THAN ONE valid fitstring. If you insisted on a single canonical form after every
operation, some increments would cost a lot of work. Allowing several forms is
what makes constant amortized time reachable.

So the array is allowed to hold a 2 for a moment, and three local identities
repair it:

```
carry     a[i] = 2            ->  2*Fi = F(i+1) + F(i-2)
combine   a[i] = a[i+1] = 1   ->  Fi + F(i+1) = F(i+2)
borrow                            Fi = F(i-1) + F(i-2)
```

All three are just the Fibonacci recurrence rearranged, and each keeps the value
of the number unchanged while making the representation tidier.

Increment is: add one at position 2, then repair. Decrement is: borrow downwards
until something worth 1 or 2 is available, take one away, then repair.

**The amortized argument.** Take the potential to be the number of set fits plus
the number of adjacent set pairs. Every repair is a fixed amount of work and every
repair lowers that potential. So a long chain of repairs can only happen if
earlier cheap operations spent a while pushing the potential up. Total work across
n operations stays proportional to n, so each increment or decrement is O(1)
amortized even though one particular call might do several repairs.

**Menu option 4 proves it works.** It counts from 0 up to any value you choose
and back down to 0, decoding the fitstring at every step and comparing it against
an ordinary counter. It passes for 0 to 2000, which is a much better answer than
"it looked right" if a TA asks whether the repair rules are correct.

### 10.3 Binary counter with RESET

Incrementing a binary counter flips the run of trailing 1s to 0 and then sets the
next bit up. Most increments flip one or two bits, an occasional one flips many,
and the classic result is about 2 flips on average, O(1) amortized.

RESET is what the question adds. Clearing all 32 bits every time would cost 32
whatever the counter held, so n resets would cost 32n and the O(n) target would
be missed. The hint says keep a pointer to the high order 1, and that pointer is
the entire solution: RESET clears only up to there, so it can never cost more
than what INCREMENT actually built up.

**The potential function.** Let PHI be the number of 1 bits plus (high + 1).

- INCREMENT clears t trailing ones and sets one bit, so the real cost is t+1.
  PHI falls by t-1 from the cleared bits and rises by at most 1 if the pointer
  moves up. Amortized cost at most 3.
- RESET costs high+2 and drives PHI down by at least high+1. Amortized cost at
  most 1.

Both constant, so any sequence of n operations costs O(n) in total, which is
exactly what was asked.

Option 4 reproduces the table from the sheet: five operations for 9 units. Notice
the second reset costs less than the first, because the counter had not climbed as
high. That is the pointer doing its job, and it is the clearest one line
explanation of the whole question.

## Complexity

| No. | Cost | Kind of claim |
|-----|------|---------------|
| 10.1 | O(n log n) expected, O(n^2) worst | expected, over the randomness |
| 10.2 | O(1) per increment or decrement | amortized, over a sequence |
| 10.3 | O(1) per INCREMENT or RESET | amortized, by potential function |
