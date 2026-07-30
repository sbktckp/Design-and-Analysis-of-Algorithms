# Assignment 1: File Handling

| No. | Program | File | Input |
|-----|---------|------|-------|
| 1.1 | Compare Files | `1.1_compare_files.c` | two file names from the keyboard |
| 1.2 | Uppercase Convert | `1.2_uppercase_convert.c` | `data/test.txt`, or paths as arguments |
| 1.3 | Odd Even Split | `1.3_odd_even_split.c` | numbers from the keyboard |

These numbers do not clash with Day 1, since `./run` and `make` work per folder
and this folder holds its own 1.1 to 1.3. Pass `A1.` nothing special, just run
them from here.

## Run

Build this folder and run from inside it:

```bash
cd "Assignment 1 - File Handling"
make

./bin/1.1_compare_files            # try data/first.txt and data/second.txt
./bin/1.2_uppercase_convert        # or: ./bin/1.2_uppercase_convert in.txt out.txt
./bin/1.3_odd_even_split           # type numbers, -1 to stop
```

Run from inside this folder so the relative `data/` paths resolve. The root
`./run 1.1` shortcut is ambiguous here, because Day 1 also numbers its programs
1.1 to 1.4, so `./run` will say so and ask you to pick. Use the paths above for
this folder.

## Sample runs

1.1 with `data/first.txt` and `data/second.txt` reports the files identical.
With `data/first.txt` and `data/third.txt` it reports the first difference at
character 41, `d` against `c`.

1.2 turns `data/test.txt` into `data/upper.txt` and prints the result.

1.3 with `10 7 4 25 30 13 -1` writes six numbers to `data/DATA.dat`, then
splits them into `data/ODD.dat` holding 7 25 13 and `data/EVEN.dat` holding
10 4 30.

## Supplied files

`data/test.txt` for 1.2, and `data/first.txt`, `data/second.txt`,
`data/third.txt` for 1.1, where the second is a copy of the first and the third
differs by one word. The files these programs generate, `upper.txt`,
`DATA.dat`, `ODD.dat` and `EVEN.dat`, are gitignored.

## Notes

These are written in ISO C17 rather than the Turbo C style of the original
handwritten answers, so `void main`, `clrscr`, `getch`, `fcloseall` and
`process.h` are gone. Four real bugs from the originals are worth naming, since
they are the kind of thing a viva question lands on:

- **1.1** must compare a freshly read pair of characters. The original read
  `getc` once before the loop and again inside it, so the first character was
  never compared, and it reset `flag` to 0 on every match, which erased any
  earlier difference. It also could not tell a file from its own prefix. Here
  the loop breaks on the first mismatch and treats "one file ended, the other
  did not" as a difference.
- **1.2** must write to a DIFFERENT file. The original opened `test.txt` for
  reading and then opened `test.txt` again for writing, which truncates it to
  zero length before a single character can be read, so the output was always
  empty.
- **1.2** must test for EOF before writing. A `do while` that converts and
  writes first appends one junk character, since EOF is not a character.
- **1.3** classifies with `number % 2 != 0` rather than `== 0`. In C the
  remainder takes the sign of the dividend, so `-7 % 2` is -1, and testing
  against 0 the wrong way round files negative odd numbers as even.

One deliberate change: the numbers travel as text through `fprintf` and
`fscanf` instead of the `putw` and `getw` of the original. Those two write raw
ints, so the files are unreadable in an editor and not portable between
machines of different endianness. Text costs nothing here and the data files
can be inspected by eye.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 1.1 | O(n) in the length of the shorter file | O(1) |
| 1.2 | O(n) | O(1) |
| 1.3 | O(n) over three passes | O(1), nothing is held in memory |
