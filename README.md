<h1 align="center">DESIGN AND ANALYSIS OF ALGORITHMS</h1>
<p align="center">Algorithms Laboratory, CS39001. Every lab day, written twice: once properly, once short enough to copy into a record book.</p>

<p align="center">
  <img src="https://img.shields.io/github/last-commit/sbktckp/Design-and-Analysis-of-Algorithms?style=flat-square" alt="last commit" />
  <img src="https://img.shields.io/badge/language-C17-blue?style=flat-square" alt="C17" />
  <img src="https://img.shields.io/badge/programs-36-brightgreen?style=flat-square" alt="programs" />
</p>

---

## START HERE

Open the repo in a GitHub Codespace: green **Code** button, then **Codespaces**, then **Create codespace on main**. The container installs `gcc` and `make` and builds all 36 programs before it hands you a terminal.

Then run a program whichever way suits you.

**Open a .c file and press the Run button**, the triangle at the top right of the editor. It compiles and runs that one file in a terminal panel. Nothing to configure, it works for every program in the repo.

**Or use the terminal:**

```bash
./run              # list everything
./run 6.1          # Prim's minimum spanning tree, full version
./run compact/6.1  # the same thing, short enough to hand write
```

Words after the number go to the program:

```bash
./run 2.1 150 data/inDec.dat data/outBin.dat
```

`make` at the top rebuilds everything, `make clean` removes the binaries. No absolute paths anywhere, no Turbo C headers, standard C17 only, so it behaves the same in a Codespace, in WSL, on Linux and on macOS.

## TWO VERSIONS OF EVERY PROGRAM

Each day folder holds the full version, and a `compact/` folder beside it holds the short one.

**Full versions** are what the algorithm deserves. Dynamic allocation, every file open checked, real data structures where the question names one, and compiled clean under `-Wall -Wextra -Wpedantic`. Read these to understand the algorithm, and show these when the question specifically names a structure, for example the min-priority queue in Prim's or the heap sort inside fractional knapsack.

**Compact versions** are the shortest code that still works and still prints what the sheet expects. Fixed arrays, no error checking, linear scans where a heap would be faster. Every compact file carries its own sample input and real output in the header comment, so the program and its sample run can be copied into the record book straight from the file. Each `compact/README.md` lists exactly what was given up, since that is what a TA tends to ask about.

The rule of thumb: learn from the full one, write the compact one, and be ready to say why they differ.

## THE LAB DAYS

| Day | Topic | What it teaches |
|-----|-------|-----------------|
| [1](Day%201%20-%20Revision%20of%20Data%20Structures) | Revision of Data Structures | array traversal, one pass tracking, counting duplicates, in place rotation |
| [2](Day%202%20-%20Fundamentals%20of%20Algorithmic%20Problem%20Solving) | Fundamentals of Algorithmic Problem Solving | recursion that prints on the way out, Euclid's rule, files from `argv` |
| [3](Day%203%20-%20Divide%20and%20Conquer%20Method) | Divide and Conquer Method | why merge sort never varies and quick sort depends entirely on the data |
| [4](Day%204%20-%20Heap) | Heap | an array read as a tree, bottom up heapify in O(n), sift up and sift down |
| [5](Day%205%20-%20Greedy%20Techniques) | Greedy Techniques | when greedy is provably optimal, and building a Huffman tree by merging |
| [6](Day%206%20-%20Minimum%20Cost%20Spanning%20Tree) | Minimum Cost Spanning Tree | Prim grows one tree, Kruskal joins many, disjoint sets detect cycles |
| [7](Day%207%20-%20Single%20Source%20Shortest%20Path) | Single Source Shortest Path | relaxation, and why Dijkstra needs non negative weights |
| [8](Day%208%20-%20Dynamic%20Programming) | Dynamic Programming | filling a table smallest first, then walking it backwards for the answer |
| [9](Day%209%20-%20All%20Pair%20Shortest%20Path) | All Pair Shortest Path | one more allowed stopover per pass, and why the k loop must be outermost |
| [10](Day%2010%20-%20Amortization) | Amortization | expected cost against worst case, and potential function arguments |

Day 2 has no question 2.2. The lab sheet skips from 2.1 straight to 2.3.

## THE ASSIGNMENTS

| No. | Topic | What it teaches |
|-----|-------|-----------------|
| [1](Assignment%201%20-%20File%20Handling) | File Handling | why EOF needs an `int`, why you never open one file for read and write at once |

## WHAT IS IN A DAY FOLDER

```
Day 6 - Minimum Cost Spanning Tree/
  README.md            the questions, how to run, how each program works, complexities
  Makefile             builds every .c here into bin/
  6.1_prim_mst.c       full version, commented with the aim and the method
  6.2_kruskal_mst.c
  data/                whatever the question says to read from a disc file
  compact/
    README.md          what the short versions gave up
    Makefile
    6.1_prim_mst.c     short version, with its input and output in the header
    6.2_kruskal_mst.c
```

Program files are named by the number the lab sheet uses, then a short name, so `8.2_longest_common_subsequence.c` is question 8.2. Nothing is renamed to be tidy, because matching the sheet matters more.

## HOW THE RUN BUTTON IS SET UP

Most of these programs open a data file by a relative path, `data/inDec.dat` rather than a full path from the root. That means the folder a program is started FROM decides whether it finds its files.

`.vscode/tasks.json` sets `cwd` to the folder of the file you have open, so the Run button always starts a program in its own folder and the paths resolve. Without that one line the editor would launch from the repo root and every file-reading program would fail. `.vscode/launch.json` does the same for the debugger, so breakpoints work too.

Binaries land in that folder's `bin/`, which is gitignored and hidden from the Explorer, so the tree stays readable.

## IF SOMETHING GOES WRONG

**A program says it cannot open a data file.** It was started from the wrong folder. Use the Run button, or `./run 6.1`, or `cd` into the folder first.

**`./run` says permission denied.** The executable bit did not survive the clone. Run `chmod +x run` once, or call it as `bash run 6.1`.

**`./run 1.1` says the number exists in two places.** Day 1 and Assignment 1 both number their programs 1.1. It prints the two exact commands to choose from.

**Your copy behaves differently from what a README describes.** Pull first, with `git stash` before it if you have local edits.

**Codespaces will not open.** Nothing here depends on it. Any machine with `gcc` and `make` works:

```bash
wsl --install -d Ubuntu          # Windows only, then reboot
sudo apt install -y build-essential git
git clone https://github.com/sbktckp/Design-and-Analysis-of-Algorithms.git
cd Design-and-Analysis-of-Algorithms
make
./run 6.1
```

Built binaries and generated output files are gitignored, so running things never dirties the repo. `.gitattributes` pins line endings to LF, which is what keeps the Makefiles and the `run` script working when the repo is cloned on Windows.

## WHY IT IS PUBLIC

Mostly so I have one place to track my own work across the semester, and so it is easy to point someone at a specific solution when they ask. If you are taking a similar course and you found this, read the day READMEs rather than only copying the code. The explanations are the part that survives the exam.

---

<p align="center">Smit, updated as the semester goes.</p>
