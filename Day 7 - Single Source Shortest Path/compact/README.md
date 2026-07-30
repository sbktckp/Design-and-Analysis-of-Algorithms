# Compact versions, Day 7

```bash
./run compact/7.1     # 5 vertices, source 1
```

Input and output are in the header comment.

## What was traded away

- the linear scan for the closest unsettled vertex instead of an indexed binary
  heap, so O(V^2) rather than O(E log V)
- 999999 for infinity, and an unreachable vertex therefore prints as 999999
  instead of the word INF that the full version uses
- no column alignment in the table

The recursive `path` function is worth keeping in your head: it calls itself on
the parent first and prints afterwards, which is what makes the arrows come out
from source to destination without building a list and reversing it.
