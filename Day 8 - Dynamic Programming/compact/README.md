# Compact versions, Day 8

```bash
./run compact/8.1
./run compact/8.2
```

Both read from the keyboard. Input and output are in each header comment.

## What was traded away

- **8.1** does not validate that the dimensions line up, so entering 3x4
  followed by 5x6 quietly produces a meaningless number instead of an error
- fixed `m[20][20]` tables, so at most 19 matrices
- **8.2** uses a fixed `c[200][200]`, so strings up to 199 characters
- no memory freeing, since nothing is allocated

Both still print the M table, the S table, the bracketing and the counts that
the lab sheet expects, so either version is fine to show.
