## Lab Assignment 10

Generating 3 Address Code Representation

## How to run the code

Step 1 : Compile the flex code and the yacc code.
Step 2 : Rename the generated yacc C code and header file ad y.tab.c and y.ytab.h
Step 3 : Compile the C code generated.
Step 4 : Enter the input HLL into the input.txt file.
Step 5 : Execute the code

```
flex assign10.lex
bison -d -v assign10.y
gcc y.tab.c
./a.out
```

Explanation of transformation grammar used is in seperate file along with a sample input and output.