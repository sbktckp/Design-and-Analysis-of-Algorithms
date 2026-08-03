# Lab Day 1: Revision of Data Structures

| No. | Program | File | Input source |
|-----|---------|------|--------------|
| 1.1 | Second Smallest & Largest | `1.1_second_smallest_largest.c` | `data/1.1_input.txt` |
| 1.2 | Prefix Sum Array | `1.2_prefix_sum.c` | keyboard |
| 1.3 | Duplicate Element Count | `1.3_duplicate_elements.c` | `data/1.3_input.txt` |
| 1.4 | Rotate Right Array | `1.4_rotate_right.c` | keyboard |

## Run in the terminal

From the repo root. Each block shows the command, then what to type when it
asks, then what comes back.

### 1.1 Second smallest and largest

```bash
./run 1.1
```
```
Size of the array (n): 10

Second smallest: 5
Second largest : 66
```

### 1.2 Prefix sum

```bash
./run 1.2
```
```
Size of the array (N): 5
Enter 5 elements: 3 4 5 1 2

Input Array : 3 4 5 1 2
Output Array: 3 7 12 13 15
```

### 1.3 Duplicate elements

```bash
./run 1.3
```
```
Enter how many numbers you want to read from file: 15

Total number of duplicate values = 4
The most repeating element in the array = 10 (5 times)
```

### 1.4 Rotate right

```bash
./run 1.4
```
```
Size of the array (N): 9
Enter an array A of size N (9): 11 22 33 44 55 66 77 88 99
Number of elements to rotate (p2): 5

Before ROTATE: 11 22 33 44 55 66 77 88 99
After  ROTATE: 55 11 22 33 44 66 77 88 99
```

### The compact versions

Same numbers with `compact/` in front, same inputs:

```bash
./run compact/1.1
./run compact/1.2
./run compact/1.3
./run compact/1.4
```

### Without the run script

```bash
cd "Day 1 - Revision of Data Structures"
make
./bin/1.1_second_smallest_largest
```

Stay inside the folder, since 1.1 and 1.3 open `data/` by a relative path.

## How each program works

### 1.1 Second smallest and second largest

The obvious approach is to sort and then read index 1 and index n-2. That works,
and the compact version does exactly that, but it costs O(n log n) at best and
does far more work than the question needs.

The full version keeps four variables and reads the file once. Think of it as
holding two podiums. `min1` is the smallest seen so far and `min2` is the
runner up. When a new number arrives there are three possibilities: it beats
`min1`, in which case the old champion is demoted to runner up and the new
number takes first place; or it sits between the two, in which case it becomes
the new runner up; or it is bigger than both and is ignored. The same three
cases run in parallel for the two largest values.

The subtle part is the word DISTINCT. For input `5 5 9`, sorting and reading
index 1 answers 5, which is just the same value twice. The full version demands
`x > min1` before considering `x` as a runner up, so it reports 9. That is why
the two versions can disagree, and it is the kind of edge case a viva likes.

One pass, four variables, no array stored at all: O(n) time, O(1) space.

### 1.2 Prefix sum

A prefix sum array answers the question "what do all the elements up to here add
up to" without adding them up again. The naive way is a loop inside a loop,
O(n^2). The insight is that `prefixSum[i]` is just `prefixSum[i-1] + arr[i]`,
because the previous entry already contains everything before it. So one running
total in one loop does it, O(n).

Seed the first entry with `arr[0]`, since there is nothing before it to add.

This is worth understanding properly rather than memorising, because prefix sums
turn up constantly: any "sum between index i and j" question becomes
`prefix[j] - prefix[i-1]`, a single subtraction instead of a loop.

### 1.3 Duplicate count and most repeating element

Two answers are needed: how many values occur more than once, and which value
occurs most often. Note the first is a count of VALUES, not of extra copies. In
the sample data 10 appears five times but contributes 1 to the duplicate count.

The compact version compares every element against every other, O(n^2), and
skips any value it has already handled so nothing is counted twice.

The full version sorts a COPY of the array first. Once sorted, equal values sit
together in runs, so a single walk can measure each run: a run longer than one
means a duplicated value, and the longest run wins the most repeating title.
That is O(n log n) for the sort plus O(n) for the walk. The copy matters, because
the question also asks to display the array in its original order.

### 1.4 Rotate the first p2 elements right by one

The question insists on doing it with a swap function, `EXCHANGE(p, q)`, and
with pointers, so `p1` is the address of the array and `p2` is how many elements
take part.

Walk from the back of the block towards the front, swapping each neighbouring
pair. Watch it happen on `11 22 33 44 55` with p2 = 5. Swap positions 4 and 3
and 55 moves left of 44. Swap 3 and 2, and 55 moves again. Keep going and 55
walks all the way to the front while everything it passes shifts one place
right. That is exactly a rotation, done with p2-1 swaps and no temporary array.

Going front to back instead would drag the FIRST element to the end, which is a
left rotation. The direction of the loop is the whole difference.

## Complexity

| No. | Full version | Compact version |
|-----|--------------|-----------------|
| 1.1 | O(n) time, O(1) space | O(n^2) bubble sort |
| 1.2 | O(n) time, O(n) space | same |
| 1.3 | O(n log n) sort and scan | O(n^2) pairwise counting |
| 1.4 | O(p2) swaps, O(1) space | same |
