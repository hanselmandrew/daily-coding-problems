# Day 4

## Description

Given an array of integers, find the first missing positive integer in linear time and constant space. In other words, find the lowest positive integer that does not exist in the array. The array can contain duplicates and negative numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

You can modify the input array in-place.

## Solution

The problem specifically states to find the first missing positive integer. While negative values exist, they can be ignored. Zero can be ignored as well.

This could be solved with one pass on the array if there was no constant memory constraint. This pass could mark values that exist by marking the index in some way. This cannot be done in place without 'corrupting' the value in some way. An additional pass could then find the first non-marked value. This would require additional linear space requirement.

If the first value checked is 3, the value stored at index 3 can be made negative to indicate that 3 is present. Given that negative values are present, their presence would conflict with this marking of present values.

Alternatively, one pass on the array can move all non-positive values to a bounded section of the array using swaps or some other method. The start of postive values can be treated as the start of the missing search. The above method of doing a pass, taking the initial value, and negating the value indexed by the initial value, is now meaningful because all values in this new bounded section are guaranteed to be positive initially.

Therefore, values that exist should be marked by a negative value in their respective index. The index of the first positive value marks the first missing value.

```
[3, 4, -1, 1]
[-1, 4, 3, 1]
  ^     ^
[-1] | [4, 3, 1] <- seperate the values
```

```
[4, 3, 1]  <- no negating, 4 is larger than the remaining values
 ^
[4, 3, -1] <- negate the value at index 3
    ^
[-4, 3, -1] <- negate the value at index 1
                ^
```

```
[ -4, 3, -1] 
      ^
   1 (2)  3 <- 2 is the first missing value as it is not negative
```