## Lab Assignment 8

Simple calculator

## How to run the code

Step 1 : Compile the flex code and the yacc code.
Step 2 : Rename the generated C code and header file ad y.tab.c and y.ytab.h
Step 3 : Compile and excute the C code generated.
Step 4 : Enter the input expression and hit enter.End the input with ctrl+D.

```
flex part1.lex
bison -d -v lang_model.y
gcc lex.yy.c y.tab.c
./a.out
```

Question 1 is in seperate file along with a sample output.