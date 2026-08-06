# Assignment 1: File Handling

| No. | Program | File | Input |
|-----|---------|------|-------|
| 1.1 | Compare Files | `1.1_compare_files.c` | two file names from the keyboard |
| 1.2 | Uppercase Convert | `1.2_uppercase_convert.c` | `data/test.txt`, or paths as arguments |
| 1.3 | Odd Even Split | `1.3_odd_even_split.c` | numbers from the keyboard |

Day 1 numbers its programs 1.1 to 1.4 as well, so name this folder in
front of the number when using `./run`.

## Run in your Codespace terminal

### 1.1 Compare two files

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run "assignment 1/1.1"
```

Type `data/first.txt`, then `data/second.txt`. They match, so it reports
the files are identical.

Run it again with `data/first.txt` and `data/third.txt`. Those differ by
one word, and it pinpoints character 41, `d` against `c`.

### 1.2 Convert a file to upper case

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run "assignment 1/1.2"
```

No typing needed. It converts `data/test.txt` into `data/upper.txt` and
prints the result.

With your own paths:

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run "assignment 1/1.2" data/first.txt data/shout.txt
```

### 1.3 Split numbers into odd and even files

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run "assignment 1/1.3"
```

Type `10 7 4 25 30 13 -1`. ODD gets 7 25 13, EVEN gets 10 4 30.

Try a negative odd number, say `-7`, and check it lands in the ODD file.
That is the sign trap explained below, and it is worth demonstrating.

### The compact versions

```bash
cd /workspaces/Design-and-Analysis-of-Algorithms
./run compact/1.1
./run compact/1.2
./run compact/1.3
```

If `./run` reports two matches, it prints the exact commands to choose
from.

### Building this folder on its own

```bash
cd "Assignment 1 - File Handling"
make
./bin/1.1_compare_files
./bin/1.2_uppercase_convert
./bin/1.3_odd_even_split
```

Stay inside the folder, since all three use relative `data/` paths.

## Five things about files in C that all three programs rely on

**A FILE pointer is a handle, not the file.** `fopen` returns a pointer to
bookkeeping the library keeps: where you are in the file, whether the end was
reached, buffered bytes not yet written. `fclose` flushes that buffer, which is
why a program that skips it can leave an output file short or empty.

**The mode string decides everything.** `"r"` needs the file to exist. `"w"`
creates it, and if it already exists it is emptied THE MOMENT IT OPENS. `"a"`
appends. That truncation is behind the most common bug in this assignment.

**EOF is not a character.** `getc` returns an `int`, not a `char`, because it has
to be able to return every possible byte value AND a separate end of file signal.
Store it in a `char` and one legitimate byte value becomes indistinguishable from
EOF, so the loop can stop early or never stop at all.

**Test before you write.** `while ((c = getc(f)) != EOF)` reads, checks, then
acts. A `do while` that writes before checking will always append one junk
character, because it processes the EOF signal as though it were data.

**Reading numbers is different from reading characters.** `fscanf(f, "%d", &x)`
returns how many items it managed to fill, so `== 1` is the natural end of loop
test for a file of numbers.

## How each program works

### 1.1 Are two files identical

Read both files one character at a time, in step. Stop at the first difference,
or when both reach the end together.

The part worth thinking about is what "identical" requires. It is not enough that
every character matched, because one file may simply have run out earlier. If the
loop ends with `c1 == c2` then both returned EOF at the same moment and the files
truly match. If one returned a real character while the other returned EOF, they
differ, and the code catches that with no extra work.

The full version also reports WHERE the difference is, and which file ended first,
which is genuinely useful and costs about six lines.

Both files are opened in `"rb"` mode. On Linux it changes nothing, but it is the
right habit: on Windows text mode quietly translates line endings, so a byte for
byte comparison should not use it.

### 1.2 Convert a file to upper case

Copy the file character by character through `toupper`, which lifts lowercase
letters and leaves digits, spaces and punctuation alone.

The trap is the output file. Opening the SAME name for writing empties it before
a single character can be read, so the result is always empty and it looks like a
logic error when it is really a mode error. Read from one name, write to another.

The second trap is loop shape, covered above: check for EOF before writing, or
the output gains a junk character at the end.

`toupper` comes from `<ctype.h>` and takes an `int`, which fits the `int` that
`getc` already returns.

### 1.3 Split numbers into odd and even files

Three short passes. Capture what the user types into DATA. Reopen DATA for
reading and send each number to ODD or EVEN. Reopen those two and display them.

The question specifically asks for the split to READ THE FILE rather than reuse an
array still sitting in memory, so the reopen is the point of the exercise, not
clumsiness.

**The sign trap, worth knowing well.** In C the remainder takes the sign of the
left operand, so `-7 % 2` is -1, not 1. Testing `x % 2 == 1` therefore files
negative odd numbers as even. Either test `x % 2 != 0`, which the full version
does, or lean on truthiness, since any non zero value counts as true:

```c
fprintf(x % 2 ? odd : even, "%d ", x);
```

The numbers are stored as text through `fprintf` rather than with `putw`. `putw`
writes the raw bytes of an int, so the file is unreadable in an editor and does
not transfer between machines that order bytes differently. Text costs nothing
here and can be checked by eye. If your record specifically wants `putw` and
`getw`, that is a two line change.

## About the handwritten originals

These are ISO C17 rather than Turbo C, so `void main`, `clrscr`, `getch`,
`fcloseall` and `process.h` are gone. None of them exist in standard C or on
Linux, so a Codespace or WSL rejects all of them.

Four real bugs from the original answers are fixed, and each is a good viva
question:

- **1.1** called `getc` once before the loop and again inside it, so the first
  character was never compared. It also reset its flag to 0 on every match,
  erasing any difference found earlier, and could not tell a file from its own
  prefix.
- **1.2** opened `test.txt` for reading and `test.txt` again for writing, so the
  input was destroyed before it could be read.
- **1.2** used `do while`, appending one junk character.
- **1.3** routed on `number % 2 == 0`, filing negative odd numbers as even.

## Complexity

| No. | Time | Space |
|-----|------|-------|
| 1.1 | O(n) in the shorter file | O(1) |
| 1.2 | O(n) | O(1) |
| 1.3 | O(n) over three passes | O(1), nothing held in memory |
