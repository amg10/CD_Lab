## Lab Assignment 9

Generating Intermediate Representation

## How to run the code

Step 1 : Compile the flex code and the yacc code in each folder.
Step 2 : Rename the generated yacc C code and header file ad y.tab.c and y.ytab.h
Step 3 : Compile and excute the C code generated.
Step 4 : Enter the input expression and hit enter.End the input with ctrl+D.

```
flex acd.lex
bison -d -v adc.y
gcc y.tab.c
./a.out
```

Explanation of transformation grammar used is in seperate file along with a sample input and output.