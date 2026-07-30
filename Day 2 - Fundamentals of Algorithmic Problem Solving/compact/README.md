# Compact versions, Day 2

Shortest code that works, for copying into the lab record. Input and output sit
in each file's header comment.

```bash
./run compact/2.1 3 ../data/inDec.dat ../data/outBin.dat
./run compact/2.3 ../data/inGcd.dat ../data/outGcd.dat
```

Both take their file names from the command line, as the question requires. The
paths start with `../data/` because these live one folder deeper than the data.

## What was traded away

- no check that the files opened, so a wrong path crashes
- no range check on the input numbers, so a value above 65535 silently loses
  its high bits when squeezed into 16 fits
- 2.1 divides by 2 and takes the remainder rather than shifting and masking,
  which reads more naturally in a record but means the same thing
- the count of pairs and the friendly messages of the full version are gone
