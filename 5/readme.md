# Day 5 - Functional Programming

## Description

`cons(a, b)` constructs a pair, and `car(pair)` and `cdr(pair)` returns the first and last element of that pair. For example, `car(cons(3, 4))` returns 3, and `cdr(cons(3, 4))` returns 4.

Given this implementation of cons:

``` python
def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair
```

Implement `car` and `cdr`.

## Prep Thoughts

Not really sure how to approach functional programming in C. I am somewhat familiar with it via a friend in web development who really likes the language Elm. And some cursory exposure when a book that heavily used Lisp.

## Solution

Yeah. This one ain't happenin. C doesn't treat functions as first-class objects. That is, they are not treated the same way as all other variables. They can't be passed around by value or allocated at run-time. The question is proposed in Python, which is a language that treats functions as first class. A quick search of the internet revealed this simple solution: 

[Source](https://gist.githubusercontent.com/housecricket/e996b6b604bce838d6d11e3ef36db4d7/raw/643f8e47487dd30779c6a5262e155d5edf50edbc/daily-coding-problem-%235.py)

``` python
def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair

def car(func):
    return func(lambda x, y: x)

def cdr(func):
    return func(lambda x, y: y)
```
