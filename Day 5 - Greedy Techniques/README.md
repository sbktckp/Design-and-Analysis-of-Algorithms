# Lab Day 5: Greedy Techniques

Both programs read from the keyboard, so nothing here needs a data file.

| No. | Program | File |
|-----|---------|------|
| 5.1 | Fractional Knapsack | `5.1_fractional_knapsack.c` |
| 5.2 | Huffman Coding | `5.2_huffman_coding.c` |

## Run in the terminal

### 5.1 Fractional knapsack

```bash
./run 5.1
```
```
Enter the number of items: 3
Enter the profit and weight of item no 1: 27 16
Enter the profit and weight of item no 2: 14 12
Enter the profit and weight of item no 3: 26 13
Enter the capacity of knapsack: 18

Item No   profit       Weight       Amount to be taken
3         26.000000    13.000000    1.000000
1         27.000000    16.000000    0.312500
2         14.000000    12.000000    0.000000
Maximum profit: 34.437500
```

### 5.2 Huffman coding

```bash
./run 5.2
```
```
Enter the number of distinct alphabets: 6
Enter the alphabets: a b c d e f
Enter its frequencies: 45 13 12 16 9 5

In-order traversal of the tree (Huffman): a c b f e d
Character codes:
  Ch Freq  Code
  a  45    0
  c  12    100
  b  13    101
  f  5     1100
  e  9     1101
  d  16    111
```

### The compact versions

Same inputs, shorter code:

```bash
./run compact/5.1
./run compact/5.2
```

### Without the run script

```bash
cd "Day 5 - Greedy Techniques"
make
./bin/5.1_fractional_knapsack
./bin/5.2_huffman_coding
```

Neither reads a data file, so these two work from anywhere.

## What greedy means, and when it is allowed

A greedy algorithm takes the best looking option right now and never
reconsiders. It is the simplest strategy there is, and usually wrong. The
interesting question is never "what is the greedy choice", it is "why is the
greedy choice safe here".

Both of today's problems have an answer to that, and they are different answers,
which is why both are on the same sheet.

## How each program works

### 5.1 Fractional knapsack

Work out profit divided by weight for each item, that is its value density.
Take the densest item first, as much of it as fits, then move down the list. The
last item to go in is usually a fraction.

Why it is safe: any leftover capacity can always be filled with a SLICE of the
next best item. So if the bag is full and you took the densest things available,
no swap can improve the total. Suppose some optimal packing left out a bit of a
denser item in favour of a lighter one; trade them and the total goes up, which
contradicts it being optimal.

Now notice how much that argument leans on the word fractional. In 0/1 knapsack
you must take an item whole or not at all, the slice trade is impossible, and
greedy quietly starts giving wrong answers. That is the single most likely viva
question on this program, and the answer is one sentence: you cannot fill the
gap with part of an item any more, so the exchange argument collapses. That is
also why 0/1 knapsack needs dynamic programming, which is Day 8's subject.

The sample data shows the mechanics. Item 3 has ratio 2.00, item 1 has 1.69,
item 2 has 1.17. So item 3 goes in whole using 13 of the 18 capacity, then 5/16
of item 1 fills the rest, giving 0.3125, and item 2 never gets a look. Profit
26 + 27 x 0.3125 = 34.4375.

**On the heap sort.** The question specifically asks for heap sort to order the
items. The full version obliges, with one twist worth understanding: it builds a
MIN-heap and repeatedly moves the smallest ratio to the BACK of the array. After
n-1 rounds the array is in non-increasing order, which is what greedy wants,
with no reversal step. Heap sort with a max-heap would produce ascending order
and need reading backwards. The compact version uses bubble sort instead, so if
the heap sort is the thing being marked, show the full one.

### 5.2 Huffman coding

The goal is a code where common characters get short bit strings and rare ones
get long strings, so the total encoded length is as small as possible. The clever
part is that the tree gets built from the bottom.

Take the two RAREST symbols. They deserve the longest codes, so they belong
deepest in the tree. Join them under a new internal node whose frequency is the
sum of theirs, and put that node back into the pool as if it were a symbol.
Repeat. After n-1 merges one node remains, and that is the root.

Each merge pushes the two rarest things one level deeper, which is precisely
what you want, and every subsequent merge treats the pair as a single unit
because from then on they always share a prefix.

Trace the sample: frequencies a45 b13 c12 d16 e9 f5.

```
f5  + e9   -> 14
c12 + b13  -> 25
14  + d16  -> 30
25  + 30   -> 55
a45 + 55   -> 100   root
```

Reading down, left edges as 0 and right edges as 1, gives a=0, c=100, b=101,
f=1100, e=1101, d=111. The most common letter a needs one bit, the rarest f
needs four. No code is a prefix of another, which is what makes decoding
unambiguous with no separators.

**Why a priority queue and not a single sort.** Sorting once is not enough,
because every merge creates a NEW frequency that has to find its own place among
the remaining ones. The full version uses a real binary min-heap keyed on
frequency for that. The compact version scans linearly for the smallest, which is
O(n^2) but gives an identical tree at these sizes.

**The in-order traversal.** The question asks to display the tree in order:
visit the left subtree, then the node, then the right subtree. Only leaves are
printed, since internal nodes hold sums rather than letters, which gives
`a c b f e d` for the sample.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 5.1 | O(n log n) for the heap sort, then O(n) for the greedy sweep | O(n) |
| 5.2 | O(n log n), n-1 merges each costing O(log n) | O(n) tree nodes |
