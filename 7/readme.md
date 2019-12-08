# Day 7 - Encoded Message

## Description

Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.

For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.

You can assume that the messages are decodable. For example, '001' is not allowed.

## Solution

We can approach the problem recursively. The valid characters, a to z, can be represented by 1 or 2 digits. Consider a string of N digits: If the input message is greater than 1 digit long, one must consider the first digit and the combined first and second digits as a possible decoding solution. If the first digit is a valid character, it is possible to continue decoding the message this way. If the combination of the first and second digit is a valid character, it is also possible to continue decoding the message this way. The above process can be repeated on the remainder of the string for each viable character decoding, just one digit and the possible combination. This recursive solution should return the sum of the number of valid decodings of N-1 and N-2, using the same input message less the digits removed for each intepretation.

It is possible that solutions to this will evaluate the same input string multiple times. This recursion could be short circuited with memoization. The input message is also a string of digits. Whether a string or integer, this could be used as the key to some data structure that returns the number of possible decodings given an input string/integer.
