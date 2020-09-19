## Lab Assignment 4

## Left Recursion removal, Left factoring, Top-down parsing

## How to run the code?
Code can be compiled with following command on any systems with c++ compiler:

```
g++ question1.cpp
```
Run the code with the commands as below:

```
./a.out
```
The code is intuitive and also mentions all the assumptions taken.
The assumptions are as follows:
1. The non- terminals are denoted as single capital/Upper Case alphabets.(Prevent using last 10 alphabets).
2. The terminals are lower case alphabets except e. 'e' is considered as epsilon.
3. The productions does not contain indirect left recursion.

The process to enter the input is as follows:
1. Enter the number of productions you want to enter.
2. Enter each production on a new line without space. For example : E->E+T|E-T|T .
3. For question 3, enter the string containing terminals.

Few sample input trials are included in the trial_input file for each question. 
