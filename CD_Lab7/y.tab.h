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

#ifndef YY_YY_LANG_MODEL_TAB_H_INCLUDED
# define YY_YY_LANG_MODEL_TAB_H_INCLUDED
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
    COMMA = 261,
    DEF = 262,
    DIV = 263,
    DOT = 264,
    ELSE = 265,
    END = 266,
    EQ = 267,
    EXITLOOP = 268,
    FLOAT = 269,
    FLOAT_CONST = 270,
    FORMAT = 271,
    FROM = 272,
    FUN = 273,
    GE = 274,
    GLOBAL = 275,
    GT = 276,
    ID = 277,
    IF = 278,
    INT = 279,
    INT_CONST = 280,
    LEFT_PAREN = 281,
    LEFT_SQ_BKT = 282,
    LE = 283,
    LT = 284,
    MINUS = 285,
    MOD = 286,
    MULT = 287,
    NE = 288,
    NOT = 289,
    NUL = 290,
    OR = 291,
    PLUS = 292,
    PRINT = 293,
    PRODUCT = 294,
    READ = 295,
    RETURN = 296,
    RETURNS = 297,
    RIGHT_PAREN = 298,
    RIGHT_SQ_BKT = 299,
    SEMICOLON = 300,
    SKIP = 301,
    STEP = 302,
    TO = 303,
    WHILE = 304,
    STRING = 305
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

#endif /* !YY_YY_LANG_MODEL_TAB_H_INCLUDED  */
