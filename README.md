<h1 align="center">DESIGN AND ANALYSIS OF ALGORITHMS</h1>
<p align="center">Weekly lab work, written up as I go through the semester.</p>

<p align="center">
  <img src="https://img.shields.io/github/last-commit/sbktckp/Design-and-Analysis-of-Algorithms?style=flat-square" alt="last commit" />
  <img src="https://img.shields.io/badge/status-in%20progress-yellow?style=flat-square" />
</p>

---

### WHAT THIS IS

This is where I'm keeping the code from my Design and Analysis of Algorithms lab, week by week. It's a college course repo, not a polished library, so expect it to look like a semester in progress rather than a finished project.

I'll add each week's work as it happens: the problem, the approach, and whatever implementation the lab actually asked for. If a particular topic gets an interesting edge case or a cleaner solution later, I'll probably come back and note that too.

### HOW IT'S ORGANIZED

One folder per lab day, named after the topic it covers. Inside each: the programs numbered exactly as the lab sheet numbers them (1.1, 1.2, ...), a `data/` folder for any input the question says to read from a disc file, a `Makefile`, and a short README with the question list and complexities.

| Day | Topic |
|-----|-------|
| 1 | Revision of Data Structures |

### RUNNING IT

Everything is plain C, no dependencies. Open the repo in a GitHub Codespace (Code -> Codespaces -> Create codespace on main) and the container comes with `gcc` and `make` ready. Then:

```bash
cd "Day 1 - Revision of Data Structures"
make
./bin/1.1_second_smallest_largest
```

`make` compiles every `.c` in the folder into `bin/`. Run the binaries from inside the day folder so the relative `data/` paths resolve. Locally it's the same thing, as long as you have gcc.

### WHY IT'S PUBLIC

Mostly so I have one place to track my own work across the semester, and so it's easy to point someone at a specific solution if they ask. If you're taking a similar course and stumble on this, feel free to look around, just don't expect a tutorial. It's my working notes, not a course.

---

<p align="center">Smit, updated as the semester goes.</p>
