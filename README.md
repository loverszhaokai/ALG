# ALG

This contains many useful algorithms.


## 1. Run

```
$ autoreconf --install
$ ./configure
$ make
$ make check
```

## 2. List of algorithms

### 2.1 tree traversal

Includes **recursively** and **iteratively** algorithms of preorder, inorder and postorder

### 2.2 combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n
```C
 For example,
 If n = 4 and k = 2, a solution is:
   [
     [2,4],
     [3,4],
     [2,3],
     [1,2],
     [1,3],
     [1,4],
   ]
```

From leetcode: https://leetcode.com/problems/combinations/

### 2.3 major elements

Majority element is the element that appears more than ⌊ n/2 ⌋ times

From leetcode: https://leetcode.com/problems/majority-element/

### 2.4 sort

Includes quick sort, insert sort, select sort, bubble sort, and merge sort

### 2.5 random shuffle

Randomly shuffle all the value in the array. Must ensure that every value has the same probability
of existing in all the positions of the array

### 2.6 dijkstra

Dijkstra algorithms

### 2.7 floyd

Floyd algorithms
