# Custom Linked List Implementation in C++

## Overview
This repository contains a from-scratch implementation of a Linked List data structure in C++.
The primary goal of this project is to demonstrate a deep understanding of low-level memory
management, pointer arithmetic, and Object-Oriented Programming (OOP) without relying on the
C++ Standard Template Library (STL).

## Features
- **O(1) Insertion:** A tail pointer eliminates the need to traverse the list on every add operation.
- **Rule of Three:** Properly implements a copy constructor, copy assignment operator, and
  destructor to prevent double-free errors and memory corruption.
- **Core Operations:**
  - `Add` — Appends a new node to the end of the list in O(1) time.
  - `Delete` — Safely removes a node and frees associated memory; returns `bool`.
  - `Search` — Traverses the list to locate specific data; returns `bool`.
  - `Print` — Displays the current state of the list.
  - `Size` — Returns the number of elements in the list.
- **Generic Template Design:** Built with `template <typename T>`, supporting any data type.
- **Encapsulation:** The internal `Node` struct is private to `LinkedList` — no implementation
  details leak to the outside.
- **Const Correctness:** Read-only methods (`Search`, `Print`, `Size`) are marked `const`.

## Technical Focus
- **Language:** C++
- **Key Concepts:** Raw Pointers, Dynamic Memory Allocation (`new` / `delete`),
  Memory Leak Prevention, Rule of Three, Template Programming, Const Correctness.

## How to Run
To compile and run this project from the terminal:
```bash
g++ linked_list.cpp -o linkedlist
./linkedlist
```

## File Structure
```
Linked-List/
└── linked_list.cpp   # Full implementation + interactive menu
```
