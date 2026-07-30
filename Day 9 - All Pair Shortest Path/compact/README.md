# Compact versions, Day 9

```bash
./run compact/9.1     # 5 vertices, then the pair 2 5
```

Input and output are in the header comment.

## What was traded away

- 9999 for infinity with no guard on the addition. Two infinities add to 19998
  and stay larger than any real path, so the answer is right for this graph,
  but on a graph with big weights that trick can break down. The full version
  checks that both operands are finite before adding.
- no negative cycle detection. If a negative cycle existed, this would print
  nonsense without saying so. The full version checks the diagonal for a
  negative entry and refuses.
- fixed 20 by 20 tables
