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

### RUNNING IT

Open the repo in a GitHub Codespace (Code, then Codespaces, then Create codespace on main) and the container arrives with `gcc` and `make` ready. Locally it's the same, as long as you have gcc. Then pick a folder and build it:

```bash
cd "Day 6 - Minimum Cost Spanning Tree"
make
./bin/6.1_prim_mst
```

`make` compiles every `.c` in that folder into `bin/`. Build just one with `make bin/6.1_prim_mst`, and clear the binaries with `make clean`.

Two things to remember:

- run the binaries from inside the folder, so the relative `data/` paths resolve
- some programs take command line arguments, which that folder's README lists

Built binaries and generated output files are gitignored, so running things never dirties the repo.

### WHY IT'S PUBLIC

Mostly so I have one place to track my own work across the semester, and so it's easy to point someone at a specific solution if they ask. If you're taking a similar course and stumble on this, feel free to look around, just don't expect a tutorial. It's my working notes, not a course.

---

<p align="center">Smit, updated as the semester goes.</p>
