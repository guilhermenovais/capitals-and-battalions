# Patrol Planning Over Connected Urban Centers

## Table of Contents
- [Introduction](#introduction)
- [Problem Description](#problem-description)
- [Features](#features)
- [Project Structure](#project-structure)
- [How to Run](#how-to-run)
- [Algorithmic Approach](#algorithmic-approach)
- [Code Structure](#code-structure)
- [Assumptions](#assumptions)

---

## Introduction

This project focuses on solving a graph-based problem that involves determining patrol routes over urban centers using a directed graph. The central challenge is to define a **capital** city (vertex) that has the capability to reach all other cities with the lowest total distance. Furthermore, each **strongly connected component (SCC)** of the graph that does not include the capital is assigned a **secondary battalion**, and patrol routes are created for each battalion. These routes ensure that patrols cover all possible roads (edges) between cities and return to the battalion they started from.

---

## Problem Description

Given a directed graph where:
- Each **vertex** represents an **urban center** (city).
- Each **directed edge** represents a **one-way road** between two urban centers.

The main tasks are:
1. **Define a capital:** Identify a vertex that can reach all other vertices with the smallest total path cost.
2. **Determine secondary battalions:** For each SCC (Strongly Connected Component) that does *not* contain the capital, select a secondary battalion to serve as the starting point for patrols.
3. **Plan patrol routes:** For each SCC, generate a route that covers all edges at least once, returning to the starting point (battalion), ensuring that all roads are patrolled.

---

## Features

- Determines and prints the **capital** of the graph.
- Identifies appropriate **secondary battalions** for each SCC.
- Computes **patrol routes** for each SCC where all roads are traversed.
- Efficiently handles directed graphs with **BFS**, **DFS**, and **Kosaraju's Algorithm** for determining SCCs.
  
---

## Project Structure

```plaintext
./
│  
├── include/                    # Header files
│   ├── graph.hpp               # Graph class header (models the graph and core logic)
│   └── solution.hpp            # Solution class header (encapsulates the main problem-solving steps)
│
├── src/                        # Source code files
│   ├── graph.cpp               # Implements the Graph class
│   └── solution.cpp            # Implements the Solution class
│
├── obj/                        # Directory for object files (created during compilation)
├── main.cpp                    # Main program file (starts the solution)
├── testcases                   # Directory with testcases
│   ├── inputs                  # Inputs for the testcases
│   └── outputs                 # Outputs for the testcases
├── Makefile                    # Makefile for compiling and running the project
└── README.md                   # Documentation
```

---

## How to Run

### Prerequisites:
- **g++** or any C++ compiler that supports C++11 or higher.
- **Make** (if using the provided `Makefile`).

### Compile the project:

Using the **Makefile** (recommended):
```bash
make
```

The executable will be placed under the `bin/` directory.

### Running the program:

```bash
./bin/program.out < test_input.txt
```

`test_input.txt` should contain the number of cities/urban centers and roads, followed by the list of roads (edges) between cities. For example:

```plaintext
6 8
Rhedrise Vandrad
Vandrad Benith
Khudealine Thonet
Thonet Khudealine
Rhedrise Khudealine
Benith Vandrad
Vandrad Muafland
Muafland Vandrad
```

### Expected Output:

```
Capital: Rhedrise
Rhedrise Vandrad Benith Vandrad Muafland Vandrad
Khudealine Thonet Khudealine
```

---

## Algorithmic Approach

1. **Capital Selection**:
   - The **capital** is chosen as the city that can reach all other cities and has the lowest total path cost. This is done by running a **BFS (Breadth-First Search)** from each vertex and selecting the one that minimizes the sum of distances to other vertices.

2. **SCC Discovery**:
   - Using **Kosaraju's Algorithm**, the graph is decomposed into **strongly connected components (SCCs)**. This allows us to identify groups of cities where each city is reachable from every other city in the same group.

3. **Secondary Battalions**:
   - **Secondary battalions** are assigned to each SCC (if the SCC does not contain the capital), choosing a vertex that minimizes the distance to the capital.

4. **Patrol Routes**:
   - A **DFS (Depth-First Search)**-based patrol planner is implemented to traverse each SCC, ensuring that all roads (edges) are crossed at least once. In case the SCC forms cycles, vertices and edges may be visited multiple times.

---

## Code Structure

### Core Classes:

1. **Graph (graph.hpp & graph.cpp)**:
   - **Purpose**: Models the directed graph, with methods to add vertices and edges. Also responsible for finding the capital, SCCs, secondary battalions, and determining patrol routes.
   - **Key Methods**:
     - `addVertex()`: Adds a vertex (city) to the graph.
     - `addEdge()`: Adds a directional edge (road) between two cities.
     - `findCapital()`: Selects the capital city based on reachability and total distances.
     - `findSCCs()`: Identifies SCCs using Kosaraju's Algorithm.
     - `definePatrols()`: Generates the patrol routes for each SCC.

2. **Solution (solution.hpp & solution.cpp)**:
   - **Purpose**: Encapsulates the problem-solving logic, invoking the necessary graph methods and managing the overall solution process.
   - **Key Methods**:
     - `solve()`: Coordinates the solution steps (capital selection, SCC detection, battalions, and patrols).

---

## Assumptions

- The input graph is **directed** and **weakly connected**.
- At least one vertex (city) will always be able to reach all other cities, ensuring the existence of a **capital**.
- Roads between cities are represented as **one-way routes**.

---
