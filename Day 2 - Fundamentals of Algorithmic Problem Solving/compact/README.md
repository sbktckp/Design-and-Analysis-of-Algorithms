# Compact versions, Day 2

Shortest code that works, for copying into the lab record. Input and output sit
in each file's header comment.

Both run with no arguments at all, using the files in `../data/`:

```bash
./run compact/2.1
./run compact/2.3
```

Both also accept the arguments the question asks for. Paths are relative to THIS
folder, so they start with `../data/`:

```bash
./run compact/2.1 3 ../data/inDec.dat ../data/outBin.dat
./run compact/2.3 ../data/inGcd.dat ../data/outGcd.dat
```

## What was traded away

- no range check on the input numbers, so a value above 65535 silently loses
  its high bits when squeezed into 16 fits
- 2.1 divides by 2 and takes the remainder rather than shifting and masking,
  which reads more naturally in a record but means the same thing
- the count of pairs and the friendly messages of the full version are gone

The `fopen` results ARE checked, unlike the other compact programs. Two lines
were worth it here, because these programs take file names from the command line
and a typo would otherwise crash rather than explain.
