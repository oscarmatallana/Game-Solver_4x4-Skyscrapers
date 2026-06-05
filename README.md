*This project has been created as part of the 42 Piscine by omatalla, dbali and jdev.*

# 4x4 Skyscrapers Game Solver

## About the Project

Skyscrapers (also known as Towers) is a logic puzzle that combines deceptively simple rules with surprisingly challenging solutions.

The objective is to fill the grid with skyscrapers of different heights while respecting a set of visibility and placement constraints.

This project was developed with:
- [Diana Bali](https://github.com/dianabali)
- [Jony Dev](https://github.com/devjony)

### Rules

* Each cell contains a number representing the height of a skyscraper.
* Heights range from 1 to the size of the grid (for example: 1 to 4 in a 4×4 puzzle).
* A height cannot appear twice in the same row or column.
* The numbers around the grid indicate how many skyscrapers are visible from that perspective.
* Just like in a real skyline, taller buildings hide smaller ones behind them.

### Project Focus

This project explores:

* Logical problem-solving
* Backtracking and constraint-based reasoning
* Algorithmic thinking
* Clean and structured implementation in C

At first glance the puzzle looks simple, until the grid starts fighting back!

---

# Description

This project implements a solver for the 4×4 Skyscrapers puzzle in C.

Given 16 visibility clues around the border of the grid, the program searches for a valid arrangement of skyscraper heights that satisfies both:

1. The uniqueness constraint:

   * No number can appear twice in the same row.
   * No number can appear twice in the same column.

2. The visibility constraints:

   * The clues around the grid specify how many skyscrapers are visible from each direction.

The solver automatically explores possible solutions and prints the completed grid when a valid arrangement is found.

If the input is invalid or no solution exists, the program prints:

```text
Error
```

---

# Example

Input:

```bash
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```

Possible output:

```text
1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3
```

---

# How the Puzzle Works

Consider the row:

```text
1 2 3 4
```

Viewed from the left:

```text
1 2 3 4
```

every new building is taller than the previous one.

Visible skyscrapers:

```text
4
```

Now consider:

```text
4 1 2 3
```

Viewed from the left:

```text
4 1 2 3
```

The first skyscraper has height 4 and completely blocks all shorter buildings behind it.

Visible skyscrapers:

```text
1
```

The clues around the grid are based on this visibility principle.

---

# Algorithm

## Why Backtracking?

The puzzle requires finding a combination of values that satisfies multiple constraints simultaneously.

A greedy strategy can easily get stuck because a value that looks correct early on may later make the puzzle unsolvable.

Backtracking solves this problem by:

1. Trying a value.
2. Continuing the search.
3. Detecting contradictions.
4. Returning ("backtracking") to the previous decision.
5. Trying another value.

This guarantees that every valid possibility is explored until a solution is found.

---

## High-Level Strategy

The solver works cell by cell.

For every empty position:

1. Try values from 1 to 4.
2. Check whether the value already exists in the row.
3. Check whether the value already exists in the column.
4. If valid, place the value.
5. Move to the next cell.
6. If the search later fails, remove the value and try another one.
7. When the entire grid is filled, verify all visibility clues.

---

## Search Tree

The algorithm can be visualized as a decision tree:

```text
Cell (0,0)
├── 1
│   ├── Cell (0,1)
│   ├── ...
│
├── 2
│   ├── Cell (0,1)
│   ├── ...
│
├── 3
│   ├── Cell (0,1)
│   ├── ...
│
└── 4
```

Whenever a branch violates the rules, it is abandoned immediately.

---

# Detailed Code Walkthrough

## 1. Parsing the Input

File:

```text
parse.c
```

Main functions:

```c
parse_input()
parse_recursive()
```

Purpose:

* Extract the 16 clues from the command-line argument.
* Ignore spaces.
* Verify that exactly 16 valid clue values are provided.

Example:

```text
"4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```

becomes:

```text
[4][3][2][1]
[1][2][2][2]
[4][3][2][1]
[1][2][2][2]
```

stored internally as a character array.

---

## 2. Creating the Grid

File:

```text
grid.c
```

Functions:

```c
init_grid()
zero_row()
free_grid()
```

Purpose:

* Dynamically allocate the 4×4 grid.
* Initialize every cell to zero.
* Release memory when the program finishes.

Initially:

```text
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
```

---

## 3. Checking Row and Column Constraints

File:

```text
check.c
```

Functions:

```c
check_row()
check_col()
is_valid()
```

Purpose:

Verify that a candidate value does not already exist in:

* the current row
* the current column

Example:

```text
1 2 0 4
```

Trying to place:

```text
2
```

would fail because the row already contains a 2.

---

## 4. Solving the Puzzle

File:

```text
solve.c
```

Functions:

```c
solve_grid()
try_value()
next_cell()
```

This is the core of the project.

### solve_grid()

Controls the recursive search.

### try_value()

Attempts values:

```text
1
2
3
4
```

for the current cell.

### next_cell()

Moves to the next position in the grid.

The recursion ends when:

```c
row == 4
```

meaning the entire grid has been filled.

---

## 5. Visibility Verification

File:

```text
clues.c
```

Functions:

```c
count_visible()
get_row()
get_column()
check_row_visibility()
check_col_visibility()
```

These functions verify whether the completed grid satisfies all clues.

### count_visible()

Counts visible skyscrapers from one direction.

Example:

```text
1 3 2 4
```

Visible:

```text
1
3
4
```

Total:

```text
3
```

because the skyscraper of height 2 is hidden behind the skyscraper of height 3.

---

## 6. Final Validation

File:

```text
grid_valid.c
```

Function:

```c
is_grid_valid()
```

Purpose:

Verify that:

* every row satisfies its clues
* every column satisfies its clues

Only then is the solution accepted.

---

## 7. Output

File:

```text
print.c
```

Functions:

```c
print_grid()
print_row()
ft_putnbr()
```

Purpose:

Print the solved puzzle.

Example:

```text
1 2 3 4
2 3 4 1
3 4 1 2
4 1 2 3
```

---

# Project Structure

```text
rush01.c           Program entry point
│
├── parse.c        Input validation and clue parsing
├── grid.c         Grid creation and memory management
├── check.c        Row and column validation
├── solve.c        Backtracking solver
├── clues.c        Visibility calculations
├── grid_valid.c   Final clue verification
├── print.c        Solution printing
└── print_error.c  Error handling
```

---

# Instructions

## Compilation

Compile all source files:

```bash
cc -Wall -Wextra -Werror *.c -o rush-01
```

## Execution

Run the program with 16 clues:

```bash
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```

---

# Complexity Discussion

The search space grows exponentially.

For a 4×4 puzzle:

```text
4^(16)
```

possible assignments exist in theory.

However, the row and column validation functions prune invalid branches very early, dramatically reducing the number of states explored in practice.

This pruning is what makes backtracking efficient enough for the project.

---

# Resources

## Documentation

* 42 Subject: Rush 01
* Linux Manual Pages (`man`)
* The C Programming Language — Brian Kernighan & Dennis Ritchie

## Learning Resources

* Backtracking Algorithms
* Constraint Satisfaction Problems (CSP)
* Recursive Problem Solving
* Skyscrapers Puzzle Rules and Examples
* https://pythontutor.com

## AI Usage

AI tools were used as supplementary learning resources during the development of this project.

The AI was primarily used for:

* Visualizing recursive execution.
* Understanding backtracking algorithms.
* Exploring alternative solving strategies.
* Reviewing edge cases and visibility calculations.
* Improving project documentation and explanations.

All source code, implementation decisions, debugging, compilation, testing, and final validation were completed and verified by the project authors.

---

## Author

**Oscar Matallana**

42 Berlin — `omatalla`

Email: [omatalla@student.42berlin.de](mailto:omatalla@student.42berlin.de)

GitHub: https://github.com/oscarmatallana
