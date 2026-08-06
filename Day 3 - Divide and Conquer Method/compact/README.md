# Compact versions, Day 3

Shortest code that works, for copying into the lab record. Input and output sit
in each file's header comment.

```bash
./run compact/3.1
./run compact/3.2
./run compact/3.3
./run compact/3.4
```

3.1, 3.2 and 3.3 read from `../data/`, since they live one folder deeper than
the data. 3.4 reads only from the keyboard.

## What was traded away

- **3.1 and 3.2** write no output file. The sorted array goes to the screen
  only, where the full versions also write `outMergeAsce.dat` and friends as the
  question asks.
- **3.1** has no execution timing, since `clock_gettime` needs another include
  and a feature test macro.
- **3.2** decides best or worst case by one crude comparison against 20n. The
  full version measures against both theoretical bounds and the recursion depth.
- **3.3** returns its two answers through pointer parameters rather than a
  struct, which is shorter to write but slightly harder to read.
- **3.4** does not check that the array is sorted first. Binary search on
  unsorted input returns a wrong answer quietly, so the full version guards
  against it.
- Global arrays of fixed size throughout, rather than reading a count and
  allocating.

The leftmost search logic in 3.4 survives the shrinking, since `hi = mid - 1` on
a match IS the answer to that question and cannot be cut.
