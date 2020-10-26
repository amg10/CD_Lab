## Lab Assignment 6

LL1 Parser

## How to run the code?

#Question 1

Step 1: The given grammar is written in the file 'Grammar.txt' in the way (E->E + T|T) i.e each symbol in the production are seperated by space and there are no surrounding space.The dfa_states.txt file contains all the state information and dfa.txt specifies the transitions/edges among the states.

Step 2: Compile 'Parser.cpp' and execute it to obtain the parsing table.

Data structure called item and state is created internally. The dfa is a vector of state structure. State structure consists of array of items,con(contents) and array transitions(defining edges).
The item consists of lhs,rhs, point_loc(location of dot), and array of look_ahead symbols.
The dfa is formed and based on the dfa, parsing table is filled by considering all outgoing transitions and reducing states(found by checking the point_loc of each item).

#Question 2

Step 1: Compile 'LL1_Parser.cpp' and execute it. Enter to obtain the parsing table.

Step 2: Enter space seperated productions with start symbol S.The required parsing table is obtained.

To execute the C++ code:

```
g++ Predictive_Parser.cpp
./a.out
```

The trial inputs and results are attached in seperate files.