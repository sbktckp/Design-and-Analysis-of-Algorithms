<h1 align="center">DESIGN AND ANALYSIS OF ALGORITHMS</h1>
<p align="center">Algorithms Laboratory, CS39001. Weekly lab work, written up as I go through the semester.</p>

<p align="center">
  <img src="https://img.shields.io/github/last-commit/sbktckp/Design-and-Analysis-of-Algorithms?style=flat-square" alt="last commit" />
  <img src="https://img.shields.io/badge/language-C17-blue?style=flat-square" alt="C17" />
  <img src="https://img.shields.io/badge/status-in%20progress-yellow?style=flat-square" alt="status" />
</p>

---

### WHAT THIS IS

This is where I'm keeping the code from my Design and Analysis of Algorithms lab, week by week. It's a college course repo, not a polished library, so expect it to look like a semester in progress rather than a finished project.

Every program is plain C with no dependencies, compiled with `-std=c17 -O2 -Wall -Wextra -Wpedantic` and clean under all of them. Where the sheet gives sample input and expected output, the program reproduces it exactly.

### QUICK START

Open the repo in a GitHub Codespace: green **Code** button, then **Codespaces**, then **Create codespace on main**. The container installs `gcc` and `make` and builds every program before handing you the terminal. Then just run one:

```bash
./run              # list every program in the repo
./run 6.1          # build and run Prim's MST
./run 3.1          # the merge sort menu
```

`./run` figures out which folder the program lives in and starts it there, so the relative `data/` paths always resolve no matter where you are in the tree. Arguments after the number go to the program:

```bash
./run 2.1 150 data/inDec.dat data/outBin.dat
```

To rebuild everything by hand, `make` at the top level walks every folder. `make clean` removes all the binaries.

Nothing here is machine specific: no absolute paths, no `conio.h`, no Turbo C calls, standard C17 only. It behaves the same in a Codespace, in WSL, on Linux, or on macOS.

### HOW IT'S ORGANIZED

One folder per lab day, plus a folder per assignment, named after the topic it covers. Inside each folder:

- programs numbered exactly as the sheet numbers them, `1.1`, `3.2`, `10.3` and so on, with a short name after the number
- a `data/` folder for anything the question says to read from a disc file
- a `Makefile` that builds every program in that folder into `bin/`
- a `README.md` with the question list, how to run it, implementation notes and complexities

### THE LAB DAYS

| Day | Topic | Programs |
|-----|-------|----------|
| [1](Day%201%20-%20Revision%20of%20Data%20Structures) | Revision of Data Structures | second smallest and largest, prefix sum, duplicate elements, rotate right |
| [2](Day%202%20-%20Fundamentals%20of%20Algorithmic%20Problem%20Solving) | Fundamentals of Algorithmic Problem Solving | decimal to binary by recursion, GCD of pairs by recursion |
| [3](Day%203%20-%20Divide%20and%20Conquer%20Method) | Divide and Conquer Method | merge sort with timing, quick sort with case analysis |
| [4](Day%204%20-%20Heap) | Heap | min-heap and max-heap over a person record |
| [5](Day%205%20-%20Greedy%20Techniques) | Greedy Techniques | fractional knapsack by heap sort, Huffman coding |
| [6](Day%206%20-%20Minimum%20Cost%20Spanning%20Tree) | Minimum Cost Spanning Tree | Prim with a min-priority queue, Kruskal with disjoint sets |
| [7](Day%207%20-%20Single%20Source%20Shortest%20Path) | Single Source Shortest Path | Dijkstra with path reconstruction |
| [8](Day%208%20-%20Dynamic%20Programming) | Dynamic Programming | matrix chain multiplication, longest common subsequence |
| [9](Day%209%20-%20All%20Pair%20Shortest%20Path) | All Pair Shortest Path | Floyd-Warshall with intermediate vertices |
| [10](Day%2010%20-%20Amortization) | Amortization | randomized quicksort, Fibonacci fitstrings, binary counter with reset |

Day 2 has no question 2.2. The lab sheet skips from 2.1 to 2.3.

### THE ASSIGNMENTS

| No. | Topic | Programs |
|-----|-------|----------|
| [1](Assignment%201%20-%20File%20Handling) | File Handling | compare two files, convert a file to upper case, split numbers into odd and even files |

### RUNNING IT WITHOUT CODESPACES

Any machine with `gcc` and `make` works. On Windows the least painful route is WSL:

```bash
wsl --install -d Ubuntu
sudo apt install -y build-essential git
git clone https://github.com/sbktckp/Design-and-Analysis-of-Algorithms.git
cd Design-and-Analysis-of-Algorithms
make
./run 6.1
```

If `./run` reports a permission error, the executable bit did not survive the clone. Either `chmod +x run` once, or call it as `bash run 6.1`.

You can also build a single folder on its own:

```bash
cd "Day 6 - Minimum Cost Spanning Tree"
make
./bin/6.1_prim_mst
```

Built binaries and generated output files are gitignored, so running things never dirties the repo. Line endings are pinned to LF by `.gitattributes`, which keeps the Makefiles and the `run` script working even when the repo is cloned on Windows.

### WHY IT'S PUBLIC

Mostly so I have one place to track my own work across the semester, and so it's easy to point someone at a specific solution if they ask. If you're taking a similar course and stumble on this, feel free to look around, just don't expect a tutorial. It's my working notes, not a course.

---

<p align="center">Smit, updated as the semester goes.</p>
