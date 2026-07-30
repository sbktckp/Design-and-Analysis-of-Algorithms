# Lab Day 2: Fundamentals of Algorithmic Problem Solving

Both programs take their file names from command line arguments and write their
results to a separate disc file, as the lab sheet asks.

| No. | Program | File | Arguments |
|-----|---------|------|-----------|
| 2.1 | Decimal to Binary | `2.1_decimal_to_binary.c` | `[<n> <source> <destination>]` |
| 2.3 | GCD of Pairs | `2.3_gcd_pairs.c` | `[<source> <destination>]` |

2.2 is not in the lab manual. It jumps from 2.1 to 2.3.

## Run

The arguments are optional. With none, both programs use the files in `data/`:

```bash
./run 2.1
./run 2.3
./run compact/2.1
./run compact/2.3
```

With arguments, exactly as the sheet writes it:

```bash
./run 2.1 150 data/inDec.dat data/outBin.dat
./run 2.3 data/inGcd.dat data/outGcd.dat
```

For the compact versions the paths are relative to the `compact/` folder, so
they need `../data/`:

```bash
./run compact/2.1 3 ../data/inDec.dat ../data/outBin.dat
./run compact/2.3 ../data/inGcd.dat ../data/outGcd.dat
```

Or by hand, the way the sheet writes it:

```bash
cd "Day 2 - Fundamentals of Algorithmic Problem Solving"
gcc 2.1_decimal_to_binary.c -o lab2q1
./lab2q1 150 data/inDec.dat data/outBin.dat
```

If you get `No such file or directory`, the program was started from the wrong
folder. `./run` takes care of that for you.

## How each program works

### Command line arguments, since both questions need them

`int main(int argc, char *argv[])` receives what you typed. `argc` counts the
words including the program name, and `argv` holds them as strings. So for
`./lab2q1 150 inDec.dat outBin.dat`, `argv[0]` is the program name, `argv[1]` is
the string `"150"`, `argv[2]` and `argv[3]` are the two file names. Since
`argv[1]` is text and not a number, `strtol` or `atoi` converts it.

Two habits here are not decoration, they are the difference between a program
that explains itself and one that dies with a segmentation fault:

- **check `argc` before touching `argv`.** Reading `argv[1]` when nothing was
  typed hands `atoi` a null pointer, and the crash happens before any of your
  code runs.
- **check what `fopen` returned.** A failed open gives back `NULL`, and passing
  `NULL` to `fscanf` crashes. A wrong path is the most likely thing to go wrong
  with these two programs, so it deserves a message rather than a signal 11.

Both programs here fall back to the files in `data/` when run bare, so there is
always a working way to start them.

### 2.1 Decimal to binary by recursion

The usual way to get binary digits is to divide by 2 repeatedly and collect the
remainders. The problem is that the remainders come out backwards: the first one
you get is the LAST digit you want to print.

Recursion fixes this for free, and this is the trick worth learning from the
whole day:

```c
write_binary(value >> 1, bits - 1, out);   /* go deeper first  */
fputc('0' + (value & 1), out);             /* print on the way back */
```

The function dives all the way down to the highest bit before printing anything.
Then, as each call returns, it prints its own digit. Because the deepest call
returns first, the most significant bit is printed first and the digits arrive
in the right order with no array and no reversing step. Anything that must be
produced in reverse order can use this shape.

The `bits` counter fixes the width at 16, which is what pads 30 out to
`0000000000011110` as the sheet shows. It also gives the recursion a clean
stopping condition. Sixteen bits means input has to stay inside 0 to 65535, so
the full version checks and refuses anything larger rather than silently
chopping off the top.

`value >> 1` is division by two and `value & 1` is the remainder. They are the
same arithmetic as `/ 2` and `% 2`, written the way it is usually written when
the subject is bits.

### 2.3 GCD of every pair by recursion

Euclid's insight is that any number dividing both a and b also divides their
remainder, so `gcd(a, b)` equals `gcd(b, a mod b)`. Each step shrinks the pair,
and when b hits 0 the answer is a.

```c
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
```

Watch it on 100 and 75: gcd(100,75), then gcd(75,25), then gcd(25,0), which is
25. Three steps, not a search through every possible divisor. The number of
steps grows like the logarithm of the smaller number, and the slowest case is
consecutive Fibonacci numbers, which is a neat thing to know if asked.

The loop reads two numbers at a time and stops when `fscanf` fails to fill both,
which handles the end of the file without needing a count. The full version also
takes absolute values first, since a negative input would otherwise produce a
negative GCD.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 2.1 | O(n x 16) for n numbers | 16 frames of recursion depth |
| 2.3 | O(log min(a, b)) per pair | same as the depth of recursion |
