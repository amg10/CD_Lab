## Lab Assignment 1

## Recap of RE and Finite automata
Aim: To write a program (in C or other language) to generate NFA for a given Regular Expression. Consider some alphabet with 2-3 elements. The program/system should take any RE over the alphabet as input, and it should generate its corresponding NFA as output. Also implement functions to transform to DFA, simulate the Automaton.

## How to run the code?
Code can be compiled with following command on any systems with c++ compiler:

```
g++ RE_to_FA.cpp
```
Run the code with the commands as below:

```
./a.out
```
The code is intutive. It has alphabets 0 and 1 .
The steps for running the code are:
1. Enter any valid regular expression having any combination of above alphabets and symbols {"(","*","+",")"} 
2. Enter the option you want from the menu by entering either 1/2/3/4/5.
	If option 1 or 2 is selected it gives the output.
	If option 3 is selected,
		a. Enter a string that is to be stimulated (It also accepts epsilon as input in the form of 'e').
	If option 4 is opted, redo steps from step 1 .
	Option 5 will lead to exit.

(NOTE: 1.It does not accept epsilon as input for regular expression, however 'e' can be used to denote epsilon for the purpose of stimulation
	   2.It does nfa cnstruction, nfa to dfa transformation, stimulation but does not minimize the dfa.)
