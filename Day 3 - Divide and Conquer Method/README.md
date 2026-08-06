# Lab Day 3: Divide and Conquer Method

| No. | Program | File | Input |
|-----|---------|------|-------|
| 3.1 | Merge Sort | `3.1_merge_sort.c` | `data/inAsce.dat` `data/inDesc.dat` `data/inRand.dat` |
| 3.2 | Quick Sort | `3.2_quick_sort.c` | the same three files |
| 3.3 | Min and Max | `3.3_min_max.c` | `data/3.3_input.txt` |
| 3.4 | Binary Search | `3.4_binary_search.c` | keyboard |

3.1 and 3.2 are menu driven and each option writes its own output file, so a run
never overwrites another one. Each input file holds 300 elements, inside the 300
to 500 range the sheet asks for: ascending is 10, 20, 30 and so on, descending
is the reverse, random is a shuffle of the same values.

## Run in the terminal

### 3.1 Merge sort

```bash
./run 3.1
```
```
MAIN MENU (MERGE SORT)
1. Ascending Data
2. Descending Data
3. Random Data
4. ERROR (EXIT)
Enter option: 3

...sorted output...
Elements sorted    : 300
Number of Comparisons: 2114
Execution Time     : 1652483 nanoseconds
```

Then `4` to leave. Option 1 gives 1308 comparisons, option 3 gives 2114. Nearly
the same work whatever the input order, which is the point of merge sort.

### 3.2 Quick sort

```bash
./run 3.2
```

Option 1, already sorted data, the killer case:

```
Enter option: 1

Number of Comparisons: 44850
Maximum recursion depth      : 300
Scenario: Worst-case partitioning
```

Option 3, shuffled data:

```
Enter option: 3

Number of Comparisons: 2719
Maximum recursion depth      : 17
Scenario: Best-case partitioning
```

Run both and put the two numbers side by side. 44850 is exactly 300 x 299 / 2,
which is the worst case formula, and it is the single most convincing thing you
can show for this question.

### 3.3 Minimum and maximum

```bash
./run 3.3
```
```
Size of the array (n): 15
Array read from file: 45 12 78 3 99 23 67 5 88 34 91 7 56 19 72

Minimum element: 3
Maximum element: 99

Comparisons made           : 21
A simple loop would need    : 28
Theoretical 3n/2 - 2        : 20
```

The three numbers together are the answer to this question. 21 against 28 is the
saving divide and conquer buys, and 20 is what the formula predicts.

### 3.4 Binary search

```bash
./run 3.4
```
```
Enter size of array: 10
Enter elements of the array in ascending order: 2 3 7 7 7 11 12 12 20 50
Enter the key to be searched: 7

7 found at index position 2
Number of comparisons: 3
```

Index 2 is the FIRST of the three sevens, which is what the question asks for.
Search for 8 and it reports not found, also in 3 comparisons. Feed it an
unsorted array and it refuses, since binary search on unsorted data returns
wrong answers quietly.

### The compact versions

```bash
./run compact/3.1
./run compact/3.2
./run compact/3.3
./run compact/3.4
```

### Without the run script

```bash
cd "Day 3 - Divide and Conquer Method"
make
./bin/3.1_merge_sort
./bin/3.3_min_max
```

Stay inside the folder, since 3.1, 3.2 and 3.3 open `data/` by a relative path.
3.4 reads only from the keyboard, so it works from anywhere.

## The idea behind all four

Divide and conquer means three steps: split the problem into smaller versions of
itself, solve those by calling yourself, then combine the answers. What changes
between the four programs is where the effort sits.

| | Split | Combine |
|---|---|---|
| Merge sort | trivial, cut in half | the real work |
| Quick sort | the real work | nothing to do |
| Min and max | trivial, cut in half | two comparisons |
| Binary search | one comparison decides | nothing, one half is discarded |

Binary search is the odd one out and worth noticing. It divides but does not
conquer both halves, it throws one away. That is why it is O(log n) rather than
O(n log n): the work per level is constant and there is only one branch.

## How each program works

### 3.1 Merge sort

Splitting is trivial: cut at the midpoint. The interesting part is `merge`. It
has two already sorted halves and walks them side by side, repeatedly taking
whichever front element is smaller, until one half runs out, then copying what
remains of the other.

Every comparison in the whole algorithm happens in that walk, which is why the
counter lives there and nowhere else.

Because the split is always down the middle, the recursion is always about
log2(n) levels deep, and each level touches all n elements once. So the cost is
O(n log n) no matter what the input looks like. The counts prove it: 1308
comparisons on ascending data against 2114 on random. Nearly the same work every
time, and that predictability is merge sort's selling point.

The price is the scratch array. Merging cannot be done in place without
considerable cleverness, so it needs O(n) extra space.

Timing uses `clock_gettime(CLOCK_MONOTONIC)` around the sort only, not around
the file reading or printing, since the question asks for the time to sort. The
`_POSIX_C_SOURCE` line at the top of the file is what makes that function
visible under `-std=c17`, which otherwise hides anything not in the C standard.

### 3.2 Quick sort

Partitioning is the whole algorithm. Pick a pivot, here the last element, then
sweep the range keeping a boundary `i` behind which everything is not greater
than the pivot. Whenever a small element turns up, the boundary moves forward
and the element is swapped into place. At the end the pivot is dropped just past
the boundary, so it lands exactly where it belongs in the finished array.

That gives a fact worth remembering: after one partition, the pivot is already
in its final position and never moves again.

Now the important part, since the sheet asks you to conclude which case you are
in. The cost depends entirely on where the pivot lands.

- **Best case**, the pivot lands near the middle. Each side is about half, the
  recursion is log n deep, cost O(n log n).
- **Worst case**, the pivot is the largest or smallest element. One side gets
  n-1 elements, the other gets nothing, the recursion is n deep, and the cost is
  n(n-1)/2 comparisons.

Sorted input is the worst case for this pivot choice, because the last element
of an ascending range is always its maximum. The numbers say it plainly: 44850
comparisons for 300 elements at recursion depth 300, against 2719 comparisons at
depth 17 for shuffled data.

The verdict in the full version is decided by measuring the comparison count
against both theoretical bounds and checking the recursion depth. It does not
decide by counting lopsided partitions alone, which sounds sensible but
misclassifies random input, because subarrays of size two or three nearly always
leave one side empty regardless of pivot quality.

Day 10 returns to this problem and fixes it properly by choosing the pivot at
random.

### 3.3 Minimum and maximum

The obvious way is one loop comparing every element against a running minimum
and a running maximum. That is 2(n-1) comparisons and it is perfectly correct.
The question is whether it can be done with fewer, and the answer is yes.

Split the range in half, get the min and max of each half recursively, then
combine with exactly two comparisons: the smaller of the two minimums, and the
larger of the two maximums.

The saving comes from the base cases, and this is the part worth understanding:

- **one element** is its own min and max, at a cost of ZERO comparisons
- **two elements** need exactly ONE comparison to sort out which is which

So the elements get paired up at the bottom of the recursion, one comparison per
pair rather than two per element, and everything above that is the two
comparisons per merge. The total works out to about 3n/2 - 2.

For 15 elements that is 21 against 28. Around a quarter fewer, which matters
when a comparison is expensive, for example comparing long strings or records
pulled from disk.

Both counts are printed so the difference is visible rather than asserted. This
is one of the neatest results in the course: the same answer, provably fewer
operations, purely from choosing a better shape of computation.

### 3.4 Binary search

The array must be sorted. Look at the middle element, and one comparison tells
you which half the key can possibly be in, so the other half is discarded
entirely. Repeat on what is left. The range halves each step, so at most
log2(n) steps are needed, which is why 10 elements take 3 comparisons and a
million would take about 20.

**The leftmost twist.** The question asks for the position of the FIRST
appearance, and with duplicates that is not what plain binary search gives. Plain
binary search returns the moment it finds a match, and with `2 3 7 7 7 11 ...`
that could be index 3 or 4 rather than 2.

The fix is one line. On a match, record the position but keep searching left:

```c
if (a[mid] == key) {
    answer = mid;
    hi = mid - 1;      /* an earlier one may still exist */
}
```

The cost is that the loop can never stop early, so the count is always about
log2(n) rather than sometimes less. That is a fair trade for a correct answer,
and being able to explain the trade is the point of the question.

**Two small details worth knowing.** `mid = lo + (hi - lo) / 2` rather than
`(lo + hi) / 2` avoids overflow when both are large, which is a famous bug that
sat in the Java standard library for years. And the full version checks the array
is actually sorted before searching, because binary search on unsorted input does
not crash, it just returns the wrong answer, which is far harder to notice.

## Complexity

| No. | Best | Worst | Space |
|-----|------|-------|-------|
| 3.1 | O(n log n) | O(n log n) | O(n) scratch buffer |
| 3.2 | O(n log n) even splits | O(n^2) on sorted input | O(log n) to O(n) stack |
| 3.3 | 3n/2 - 2 comparisons | same, it does not vary | O(log n) stack |
| 3.4 | O(log n) | O(log n) | O(1), the loop is iterative |
