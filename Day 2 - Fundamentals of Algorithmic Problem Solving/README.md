# Lab Day 2: Fundamentals of Algorithmic Problem Solving

Both programs take their file names from command line arguments and write their
results to a separate disc file, as the lab sheet asks.

| No. | Program | File | Arguments |
|-----|---------|------|-----------|
| 2.1 | Decimal to Binary | `2.1_decimal_to_binary.c` | `<n> <source> <destination>` |
| 2.3 | GCD of Pairs | `2.3_gcd_pairs.c` | `<source> <destination>` |

## Run

From the repo root, arguments after the number pass straight through:

```bash
./run 2.1 150 data/inDec.dat data/outBin.dat
./run 2.3 data/inGcd.dat data/outGcd.dat
```

Or build this folder on its own:

```bash
cd "Day 2 - Fundamentals of Algorithmic Problem Solving"
make
./bin/2.1_decimal_to_binary 150 data/inDec.dat data/outBin.dat
./bin/2.3_gcd_pairs data/inGcd.dat data/outGcd.dat
```

Compiling one file by hand, the way the sheet writes it:

```bash
gcc 2.1_decimal_to_binary.c -o lab2q1
./lab2q1 150 data/inDec.dat data/outBin.dat
```

Run from inside this folder so the relative `data/` paths resolve. The two
output files are generated, so they are gitignored.

## Notes

- **2.1** pads every value to 16 bits, matching the sample output where 30
  becomes `0000000000011110`. Input values must be in the range 0 to 65535.
  The recursion emits the high bit first, so no reversing step is needed.
- **2.3** uses the recursive Euclidean algorithm. `data/inGcd.dat` holds 20
  pairs, the minimum the sheet requires.
- 2.2 is not on the page I was given, so it is not in this folder yet.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 2.1 | O(n x bits) | O(bits) recursion depth, 16 frames |
| 2.3 | O(log min(a, b)) per pair | O(log min(a, b)) recursion depth |
