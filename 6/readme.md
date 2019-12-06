# Day 6 - XOR Linked List

## Description

An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields, it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list; it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

If using a language that has no pointers (such as Python), you can assume you have access to get_pointer and dereference_pointer functions that converts between nodes and memory addresses.

## Solution

Yay! This doubly linked list stores one pointer. Traversing this doubly linked is not too difficult. Stepping through it only requires maintaining a copy of the address of the previously visited node. XOR effectily describes what bits are different in the two values. If you have one of the nodes, previous or next, you can figure out the next one given the "differences" because binary only has two values.

```
PREV --- NEXT --- XOR
  10 XOR 11   ->  01

 XOR --- PREV --- NEXT
  01 XOR 10   ->  11
```

The first line shows that the left bit is the same (0), but the right bit is different (1). If you have the XOR value, the next value can be calculated with XOR and PREV.

Given that it is a doubly linked list, I would think it could be indexed from the beginning or the end.

```
List:
  Start: Xor Node
  End: Xor Node

Xor Node:
  Xor Pointer
  Payload
```

Creating a list of this information is a bit more tricky. For the first element of a new list, the previous node pointer is NULL and the next node pointer is NULL. This first element becomes the start and end of this doubly linked list.

```
NULL <- (start) First (end) -> NULL        
```

When an element is added to the end of the list, the previous node is the current list end, and its next pointer is NULL, and the XOR of these values is stored in the new node. The XOR pointer of the previous end node in the list needs to be updated with regard to the new node. The end of the list then points to the newly created node.

```
NULL <- Start Node <-> ... <-> Prev End Node <-> New Node (end) -> NULL
```

If an element is added to the beginning of the list, its pevious node is NULL and next node is the current list start. The XOR pointer of the previous start node needs to be updated with regard to the new node. The start of the list then points to the newly created node.

```
NULL <- (start) New Node <-> Prev Start Node <-> ... <-> End Node -> NULL
```
