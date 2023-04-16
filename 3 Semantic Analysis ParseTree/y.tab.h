/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "1905021.y"

	#include <bits/stdc++.h>

#line 53 "y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    SWITCH = 260,                  /* SWITCH  */
    CASE = 261,                    /* CASE  */
    DEFAULT = 262,                 /* DEFAULT  */
    CONTINUE = 263,                /* CONTINUE  */
    LOWER_THAN_ELSE = 264,         /* LOWER_THAN_ELSE  */
    FOR = 265,                     /* FOR  */
    WHILE = 266,                   /* WHILE  */
    DO = 267,                      /* DO  */
    BREAK = 268,                   /* BREAK  */
    INT = 269,                     /* INT  */
    FLOAT = 270,                   /* FLOAT  */
    DOUBLE = 271,                  /* DOUBLE  */
    CHAR = 272,                    /* CHAR  */
    VOID = 273,                    /* VOID  */
    RETURN = 274,                  /* RETURN  */
    PRINTLN = 275,                 /* PRINTLN  */
    CONST_INT = 276,               /* CONST_INT  */
    CONST_FLOAT = 277,             /* CONST_FLOAT  */
    CONST_CHAR = 278,              /* CONST_CHAR  */
    ID = 279,                      /* ID  */
    ADDOP = 280,                   /* ADDOP  */
    MULOP = 281,                   /* MULOP  */
    RELOP = 282,                   /* RELOP  */
    LOGICOP = 283,                 /* LOGICOP  */
    NOT = 284,                     /* NOT  */
    ASSIGNOP = 285,                /* ASSIGNOP  */
    INCOP = 286,                   /* INCOP  */
    DECOP = 287,                   /* DECOP  */
    BITOP = 288,                   /* BITOP  */
    LPAREN = 289,                  /* LPAREN  */
    RPAREN = 290,                  /* RPAREN  */
    LCURL = 291,                   /* LCURL  */
    RCURL = 292,                   /* RCURL  */
    LSQUARE = 293,                 /* LSQUARE  */
    RSQUARE = 294,                 /* RSQUARE  */
    COMMA = 295,                   /* COMMA  */
    SEMICOLON = 296                /* SEMICOLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define SWITCH 260
#define CASE 261
#define DEFAULT 262
#define CONTINUE 263
#define LOWER_THAN_ELSE 264
#define FOR 265
#define WHILE 266
#define DO 267
#define BREAK 268
#define INT 269
#define FLOAT 270
#define DOUBLE 271
#define CHAR 272
#define VOID 273
#define RETURN 274
#define PRINTLN 275
#define CONST_INT 276
#define CONST_FLOAT 277
#define CONST_CHAR 278
#define ID 279
#define ADDOP 280
#define MULOP 281
#define RELOP 282
#define LOGICOP 283
#define NOT 284
#define ASSIGNOP 285
#define INCOP 286
#define DECOP 287
#define BITOP 288
#define LPAREN 289
#define RPAREN 290
#define LCURL 291
#define RCURL 292
#define LSQUARE 293
#define RSQUARE 294
#define COMMA 295
#define SEMICOLON 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 160 "1905021.y"

	symbolInfo* SymbolInfo;

#line 159 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
