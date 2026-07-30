# Compact versions, Day 3

Shortest code that works, for copying into the lab record. Input and output sit
in each file's header comment.

```bash
./run compact/3.1
./run compact/3.2
```

Both ask for one option, 1 ascending, 2 descending, 3 random, and read the
matching file from `../data/`. The array is a global `a[600]`, which is how the
file names and the recursion stay this short.

## What was traded away

- no output file. The sorted array goes to the screen only, where the full
  version also writes `outMergeAsce.dat` and friends as the question asks
- no execution timing in 3.1, since `clock_gettime` needs another include and
  a feature test macro
- 3.2 decides best or worst case by one crude comparison against 20n. The full
  version measures against both theoretical bounds and the recursion depth
- global arrays of fixed size 600 rather than reading the count and allocating
