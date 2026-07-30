# Compact versions, Day 4

```bash
./run compact/4.1
```

Input and output are in the file's header comment.

## What was traded away

The menu is gone. This version does the three things worth showing, reads the
file, builds the min-heap on age, prints the youngest person's weight in
kilograms, and stops. The full version one folder up carries all seven menu
options including the max-heap on weight, insertion and deletion.

Other cuts: a fixed `p[50]` array, no `fopen` check, and no separate max-heap,
since swapping the comparison inside `down` is the only difference and saying
so in the viva is faster than writing it twice.
