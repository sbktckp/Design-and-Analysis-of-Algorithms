# Compact versions, Assignment 1

```bash
./run "assignment 1/compact" is not needed, just use the numbers:
./run compact/1.1
./run compact/1.2
./run compact/1.3
```

If `./run compact/1.1` reports two matches, Day 1 has a compact 1.1 as well.
Name this folder instead:

```bash
cd "Assignment 1 - File Handling/compact"
make
./bin/1.1_compare_files
```

Input and output are in each header comment.

## What was traded away

- **1.1** reports identical or not identical, and nothing else. The full
  version also says where the first difference is and which file ran out first.
- **1.2** has the input and output names hard coded rather than taking them
  from the command line.
- **1.3** does not count how many odd and even numbers it wrote.
- No `fopen` checks anywhere, so a wrong path crashes instead of explaining.

The important habits survive the shrinking, and they are the ones a viva asks
about: read into an `int` not a `char` so EOF is distinguishable, test for EOF
before writing rather than after, never open the same file for reading and
writing at once, and use `x % 2` truthiness so negative odd numbers land in the
odd file.
