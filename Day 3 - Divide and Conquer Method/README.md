# Lab Day 3: Divide and Conquer Method

Both programs are menu driven and share the same three input files. Each menu
option writes its own output file, so a run never overwrites another one.

| No. | Program | File | Input | Output |
|-----|---------|------|-------|--------|
| 3.1 | Merge Sort | `3.1_merge_sort.c` | `data/inAsce.dat` `data/inDesc.dat` `data/inRand.dat` | `data/outMergeAsce.dat` and friends |
| 3.2 | Quick Sort | `3.2_quick_sort.c` | same three files | `data/outQuickAsce.dat` and friends |

Each input file holds 300 elements, inside the 300 to 500 range the sheet asks
for. Ascending is 10, 20, 30 and so on, descending is the reverse, random is a
shuffle of the same values.

## Run in the terminal

From the repo root. Both are menu driven, so they keep asking until you pick 4.

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

### The compact versions

```bash
./run compact/3.1
./run compact/3.2
```

### Without the run script

```bash
cd "Day 3 - Divide and Conquer Method"
make
./bin/3.1_merge_sort
./bin/3.2_quick_sort
```

## The idea behind both

Divide and conquer means three steps: split the problem into smaller versions of
itself, solve those by calling yourself, then combine the answers. Merge sort
and quick sort are the same idea with the effort in different places.

Merge sort splits blindly down the middle and does its real work while combining.
Quick sort does its real work while splitting, and then has nothing to combine.
That one difference explains everything else about them, including why one is
reliable and the other is fast but temperamental.

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
leave one side empty regardless of pivot quality. The raw split counts are still
printed, they just do not get the final say.

Day 10 returns to this problem and fixes it properly by choosing the pivot at
random.

## Complexity

| No. | Best | Worst | Space |
|-----|------|-------|-------|
| 3.1 | O(n log n) | O(n log n) | O(n) scratch buffer |
| 3.2 | O(n log n) even splits | O(n^2) on sorted input | O(log n) to O(n) stack |
