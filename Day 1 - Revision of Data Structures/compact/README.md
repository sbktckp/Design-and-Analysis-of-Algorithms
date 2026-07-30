# Compact versions, Day 1

Shortest code that works, for copying into the lab record by hand. Each file
carries its own input and output in the header comment, so you can write the
program and the sample run straight out of it.

Run them from the repo root:

```bash
./run compact/1.1
./run compact/1.2
./run compact/1.3
./run compact/1.4
```

Or from in here:

```bash
make
./bin/1.1_second_smallest_largest
```

These read the same `data/` files as the full versions, one folder up, which is
why the paths inside say `../data/`.

## What was traded away

These are shorter because they give things up, and knowing which things is
usually the viva question:

- fixed `a[100]` arrays instead of `malloc`, so a bigger file overflows
- no check that `fopen` worked, so a missing file crashes rather than
  explaining itself
- 1.1 sorts the whole array, O(n^2) with bubble sort, where the full version
  finds both answers in one O(n) pass
- 1.3 counts each distinct value by scanning the array again, O(n^2), where
  the full version sorts once and scans, O(n log n)
- 1.1 here reports a repeated smallest value as the "second smallest", so for
  `5 5 9` it prints 5. The full version reports the second DISTINCT value.

Use the full versions when you want the algorithm to be right for its own
sake. Use these when you need to fill four pages of a lab record.
