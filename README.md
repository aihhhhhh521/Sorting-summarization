# Sorting-summarization

This repository contains implementations of ten classic sorting algorithms in C language. The algorithms are implemented in a single file `sort.c` and include Bubble Sort, Selection Sort, Insertion Sort, Shell Sort, Merge Sort, Quick Sort, Heap Sort, Counting Sort, Bucket Sort, and Radix Sort (LSD).

## Table of Contents

- [Overview](#overview)
- [Algorithms Implemented](#algorithms-implemented)
- [Usage](#usage)

## Overview

This project aims to provide a comprehensive summary and implementation of various sorting algorithms. Each algorithm is implemented in a clear and concise manner, allowing users to easily understand and compare their performance and characteristics.

## Algorithms Implemented

1. **Bubble Sort**
   - A simple comparison-based sorting algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.

2. **Selection Sort**
   - An in-place comparison sorting algorithm that divides the input list into two parts: the sublist of items already sorted and the sublist of items remaining to be sorted.

3. **Insertion Sort**
   - A simple and intuitive sorting algorithm that builds the final sorted array one item at a time. It is much less efficient on large lists than more advanced algorithms.

4. **Shell Sort**
   - An optimization of insertion sort that allows the exchange of items that are far apart. The idea is to arrange the list of elements so that, starting anywhere, taking every hth element produces a sorted list.

5. **Merge Sort**
   - A divide-and-conquer algorithm that divides the unsorted list into n sublists, each containing one element, and then repeatedly merges sublists to produce new sorted sublists until there is only one sublist remaining.

6. **Quick Sort**
   - A highly efficient sorting algorithm that uses a divide-and-conquer approach. It works by selecting a 'pivot' element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot.

7. **Heap Sort**
   - A comparison-based sorting algorithm that uses a binary heap data structure. It divides its input into a sorted and an unsorted region, and iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region.

8. **Counting Sort**
   - A non-comparison-based sorting algorithm suitable for sorting integers within a specific range. It works by counting the number of objects that have each distinct key value and using arithmetic to determine the positions of each key.

9. **Bucket Sort**
   - A distribution sort that works by arranging elements into several 'buckets' which are then sorted individually by using a sorting algorithm, usually insertion sort, or by recursively applying the bucket sort algorithm.

10. **Radix Sort (LSD)**
    - A non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by the individual digits which share the same significant position and value. This implementation uses the Least Significant Digit (LSD) approach.

## Usage

To use this code, follow these steps:

1. **Navigate to the project directory:**
   ```bash
   cd Sorting-summarization
2. **Compile the code using a C compiler (e.g., GCC):**
   ```bash
   gcc -o sort sort.c
3. **Run the executable and provide input data:**
   ```bash
   ./sort
The program will prompt you to enter the number of elements and the elements themselves. After sorting, it will display the sorted array.
