## Lab Test

Section 2

## How to run the code

Step 1 : Write the input in input.txt file.
Step 2 : Compile the flex code and the yacc code.
Step 3 : Rename the generated C code and header file ad y.tab.c and y.ytab.h
Step 4 : Compile and excute the C code generated.

```
flex part1.lex
bison -d -v lang_model.y
gcc lex.yy.c y.tab.c
./a.out
```

The trial was done the results are attached in seperate file.