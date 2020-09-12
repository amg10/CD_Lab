## Lab Assignment 2

## Lexical Analysis
Aim: To Implement a lexical analyzer (using any programming language) for the considered tokens/patterns given below. The program should take a statement as input and return the sequence of tokens as output.
The patterns for the tokens is considered as follows:

  digit-> \[0-9]
  digits->digit+
  number->digits(.digits)?(E\[+-]?digits)?
  letter->\[A-Za-z]
  id->letter(letter | digit)
  if-> if
  then-> then
  else-> else
  relop-> <|>|<=|>=|<>

## How to run the code?
Code can be compiled with following command on any systems with c++ compiler:

```
g++ Lexical_analyzer.cpp
```
Run the code with the commands as below:

```
./a.out
```
The code is intutive.
The steps for running the code are:
1. Input a line of code and hit enter.
2. The tokens will be displayed on the screen.

The code must be re-executed to enter new line of code.
