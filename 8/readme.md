# Day 8 - Unival Tree

## Description

A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.

Given the root to a binary tree, count the number of unival subtrees.

For example, the following tree has 5 unival subtrees:

```
   0
  / \
 1   0
    / \
   1   0
  / \
 1   1
```

## Solution

A unival tree is a unival tree if both of its child nodes are also unival trees and if the node shares the same value as both its children.

From the problem description, it is clear that the leaf nodes are also unival trees. The nodes that would evaluate to be unival subtrees are circled below:

```
   0
  / \
(1)  0
    / \
  (1)  0
  / \
(1) (1)
```

A solution to this problem will recurse on its subtrees. Along with the logic detailed above, a root node is unival if its child nodes are unival, and it shares the same value as both its children.