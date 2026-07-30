# Compact versions, Day 10

```bash
./run compact/10.1     # enter 300
./run compact/10.2     # 1 increment, 2 decrement, 3 exit
./run compact/10.3     # 1 increment, 2 reset, 3 exit
```

Input and output are in each header comment.

## What was traded away

- **10.1** prints comparison counts but not the recursion depth or the
  theoretical expectation, and does not verify the output is sorted
- **10.2** has no self test. The full version can count from 0 up to any value
  and back down while checking the decoded value at every step, which is how it
  proves the fit repair rules are right
- **10.3** shows only the low 8 bits and does not print the potential function
  argument

10.2 is the one question in the whole lab where the compact version is barely
shorter, because the three repair rules ARE the answer. Nothing can be cut
without breaking it.
