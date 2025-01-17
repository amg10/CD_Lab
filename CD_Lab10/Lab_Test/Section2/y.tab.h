/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_LABTEST_TAB_H_INCLUDED
# define YY_YY_LABTEST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    AND = 258,
    ASSIGN = 259,
    COLON = 260,
    DIV = 261,
    ELSE = 262,
    END = 263,
    EQ = 264,
    EXITLOOP = 265,
    FLOAT = 266,
    FLOAT_CONST = 267,
    FORMAT = 268,
    FROM = 269,
    GE = 270,
    MAIN = 271,
    GT = 272,
    ID = 273,
    IF = 274,
    INT = 275,
    INT_CONST = 276,
    LEFT_PAREN = 277,
    LEFT_SQ_BKT = 278,
    LE = 279,
    LT = 280,
    MINUS = 281,
    MOD = 282,
    MULT = 283,
    NE = 284,
    NOT = 285,
    NUL = 286,
    OR = 287,
    PLUS = 288,
    PRINT = 289,
    PRODUCT = 290,
    READ = 291,
    RIGHT_PAREN = 292,
    RIGHT_SQ_BKT = 293,
    SEMICOLON = 294,
    STEP = 295,
    TO = 296,
    WHILE = 297,
    STRING = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LABTEST_TAB_H_INCLUDED  */
