/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "1905021.y"

#include <bits/stdc++.h>
#include <typeinfo>
#include "1905021_symbolTable.h"

using namespace std;

ofstream parsetreeout;
ofstream logout;
ofstream errorout;


symbolTable* symblTable = new symbolTable(11);
symbolInfo* symbolInfoArguments = new symbolInfo();


extern int totalLine;
extern int totalError;
extern FILE *yyin;

void printGrammarRule(string parent,string children){
	logout<<parent<<" : "<<children<<endl;
}



// extern void errorFound(string errorMessage, string symbol);
extern void printError(string errorMessage, string error);
extern void printSyntaxError(string errorMessage);

void insertFunctionIntoScopeTable(symbolInfo* funcName, symbolInfo* typeSpecifier){
	funcName->setTypeSpecifier(typeSpecifier->getTypeSpecifier());
	funcName->setParamList(symbolInfoArguments->getParamList());
	funcName->setMethodDefinition(true);
	bool insertSuccess = symblTable->insert(funcName);
	if(insertSuccess) return;
	auto sameDeclaration = symblTable->lookup(funcName->getName());

	if(!sameDeclaration->isMethodDeclaration()){
		printError("Redeclaration of function ",funcName->getName());
	}
	else{
		if(sameDeclaration->getTypeSpecifier() != funcName->getTypeSpecifier()){
			printError("Conflicting types for",funcName->getName());
		}
		if(sameDeclaration->getParamList().size() != funcName->getParamList().size()){
			printError("Too few arguments to function ",funcName->getName());
		}
		if(sameDeclaration->getParamList().size() != funcName->getParamList().size()){
			printError("Too many arguments to function ",funcName->getName());
		}
		else{
			auto argListDeclaration = sameDeclaration->getParamList();
			auto argListDefinition = funcName->getParamList();
			for(int i=0; i<argListDeclaration.size(); ++i){
				if(argListDeclaration[i]->getTypeSpecifier() != argListDefinition[i]->getTypeSpecifier()){
					printError("Type mismatch for argument "+to_string(i+1)+" of", funcName->getName());
				}
			}
		}
	}

}

bool foundVoidTypeSpecifier(symbolInfo* typeSpecifier){
	if(typeSpecifier->getTypeSpecifier() == "VOID"){
		errorout<<"Line# "<<totalLine<<": "<<"Variable or field "<<"'"<<typeSpecifier->getName()<<"'"<<" declared void"<<endl;
		totalError++;
		return true;
	}
	return false;
}

string typeCast(symbolInfo* leftSymbol, symbolInfo* rightSymbol){
	string leftSymbolType = leftSymbol->getTypeSpecifier();
	string rightSymbolType = rightSymbol->getTypeSpecifier();
	if(leftSymbolType == "VOID" or rightSymbolType == "VOID") return "error";
	if(leftSymbolType == "error" or rightSymbolType == "error") return "error";
	if(leftSymbolType == "FLOAT" or rightSymbolType == "FLOAT") return "FLOAT";
	return "INT";
}

string setupName(vector<symbolInfo*> symblInfs){
	string symblName = "";
	for(auto SymbolInfo: symblInfs){
		symblName += SymbolInfo->getName();
		if(SymbolInfo->getType() == "TYPE_SPECIFIER" or SymbolInfo->getType() == "KEYWORD" ) symblName += " ";
	}
	return symblName;
}

void yyerror(string s){

}

int yyparse(void);
int yylex(void);



#line 172 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 211 "y.tab.c"

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
#line 109 "1905021.y"

	symbolInfo* SymbolInfo;

#line 317 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_SWITCH = 5,                     /* SWITCH  */
  YYSYMBOL_CASE = 6,                       /* CASE  */
  YYSYMBOL_DEFAULT = 7,                    /* DEFAULT  */
  YYSYMBOL_CONTINUE = 8,                   /* CONTINUE  */
  YYSYMBOL_LOWER_THAN_ELSE = 9,            /* LOWER_THAN_ELSE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_DO = 12,                        /* DO  */
  YYSYMBOL_BREAK = 13,                     /* BREAK  */
  YYSYMBOL_INT = 14,                       /* INT  */
  YYSYMBOL_FLOAT = 15,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 16,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 17,                      /* CHAR  */
  YYSYMBOL_VOID = 18,                      /* VOID  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_PRINTLN = 20,                   /* PRINTLN  */
  YYSYMBOL_CONST_INT = 21,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 22,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 23,                /* CONST_CHAR  */
  YYSYMBOL_ID = 24,                        /* ID  */
  YYSYMBOL_ADDOP = 25,                     /* ADDOP  */
  YYSYMBOL_MULOP = 26,                     /* MULOP  */
  YYSYMBOL_RELOP = 27,                     /* RELOP  */
  YYSYMBOL_LOGICOP = 28,                   /* LOGICOP  */
  YYSYMBOL_NOT = 29,                       /* NOT  */
  YYSYMBOL_ASSIGNOP = 30,                  /* ASSIGNOP  */
  YYSYMBOL_INCOP = 31,                     /* INCOP  */
  YYSYMBOL_DECOP = 32,                     /* DECOP  */
  YYSYMBOL_BITOP = 33,                     /* BITOP  */
  YYSYMBOL_LPAREN = 34,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 35,                    /* RPAREN  */
  YYSYMBOL_LCURL = 36,                     /* LCURL  */
  YYSYMBOL_RCURL = 37,                     /* RCURL  */
  YYSYMBOL_LSQUARE = 38,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 39,                   /* RSQUARE  */
  YYSYMBOL_COMMA = 40,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 41,                 /* SEMICOLON  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_start = 43,                     /* start  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_unit = 45,                      /* unit  */
  YYSYMBOL_func_declaration = 46,          /* func_declaration  */
  YYSYMBOL_func_definition = 47,           /* func_definition  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_parameter_list = 51,            /* parameter_list  */
  YYSYMBOL_compound_statement = 52,        /* compound_statement  */
  YYSYMBOL_var_declaration = 53,           /* var_declaration  */
  YYSYMBOL_type_specifier = 54,            /* type_specifier  */
  YYSYMBOL_declaration_list = 55,          /* declaration_list  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_expression_statement = 58,      /* expression_statement  */
  YYSYMBOL_variable = 59,                  /* variable  */
  YYSYMBOL_expression = 60,                /* expression  */
  YYSYMBOL_logic_expression = 61,          /* logic_expression  */
  YYSYMBOL_rel_expression = 62,            /* rel_expression  */
  YYSYMBOL_simple_expression = 63,         /* simple_expression  */
  YYSYMBOL_term = 64,                      /* term  */
  YYSYMBOL_unary_expression = 65,          /* unary_expression  */
  YYSYMBOL_factor = 66,                    /* factor  */
  YYSYMBOL_argument_list = 67,             /* argument_list  */
  YYSYMBOL_arguments = 68,                 /* arguments  */
  YYSYMBOL_LCURL_ = 69                     /* LCURL_  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   121,   121,   130,   136,   144,   150,   157,   163,   172,
     186,   200,   214,   214,   221,   221,   228,   228,   237,   249,
     261,   271,   286,   294,   303,   315,   331,   340,   347,   354,
     363,   371,   380,   388,   398,   405,   413,   420,   427,   434,
     440,   446,   452,   458,   467,   475,   482,   489,   498,   521,
     545,   553,   572,   581,   590,   599,   614,   623,   635,   645,
     665,   679,   692,   703,   712,   750,   757,   765,   773,   786,
     801,   809,   820,   828,   836,   846
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "LOWER_THAN_ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "FLOAT", "DOUBLE", "CHAR", "VOID", "RETURN", "PRINTLN",
  "CONST_INT", "CONST_FLOAT", "CONST_CHAR", "ID", "ADDOP", "MULOP",
  "RELOP", "LOGICOP", "NOT", "ASSIGNOP", "INCOP", "DECOP", "BITOP",
  "LPAREN", "RPAREN", "LCURL", "RCURL", "LSQUARE", "RSQUARE", "COMMA",
  "SEMICOLON", "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "$@1", "$@2", "$@3", "parameter_list",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor",
  "argument_list", "arguments", "LCURL_", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     133,   -75,   -75,   -75,   -75,    23,    61,   -75,   -75,   -75,
     -75,     2,   -75,   -75,   -16,    -6,    68,   -75,    20,    27,
      17,   -75,    19,    16,   -24,    43,    41,    48,    53,   -75,
      60,    57,    38,   -75,   -75,    80,   -75,    60,   -75,   -75,
      63,   -75,    60,    81,    76,   -75,    22,    86,    89,    91,
     149,    93,   -75,   -75,    31,   149,   149,   149,   -75,   -75,
     -75,   -75,     6,    92,   -75,   -75,    59,    96,   -75,   102,
     -13,   112,   -75,   -75,   -75,   -75,   -75,   -75,   -75,   149,
     143,   149,   108,   128,   149,   149,    87,   -75,   -75,   118,
     116,   115,   -75,   -75,   149,   -75,   -75,   -75,   149,   149,
     149,   149,   123,   143,   124,   -75,   125,   -75,   126,     7,
     127,   -75,   -75,   -75,   112,   138,   -75,   121,   149,   121,
     134,   -75,   -75,   149,   -75,   165,   141,   -75,   -75,   -75,
     121,   121,   -75,   -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     8,    27,    28,    29,     0,     0,     4,     6,     7,
       5,     0,     1,     3,     0,    32,     0,    26,     0,     0,
       0,    25,     0,    16,     0,    21,     0,    30,    14,    11,
       0,    12,     0,    20,    33,     0,    10,     0,    75,    17,
       0,     9,     0,    19,     0,    15,     0,     0,     0,     0,
       0,     0,    66,    67,    48,     0,     0,     0,    24,    45,
      38,    36,     0,     0,    34,    37,    63,     0,    50,    52,
      54,    56,    58,    62,    13,    18,    31,    23,    47,     0,
       0,     0,     0,     0,    72,     0,    63,    60,    61,     0,
      32,     0,    22,    35,     0,    68,    69,    46,     0,     0,
       0,     0,     0,     0,     0,    44,     0,    74,     0,     0,
       0,    65,    51,    53,    57,    55,    59,     0,     0,     0,
       0,    64,    71,     0,    49,    40,     0,    42,    43,    73,
       0,     0,    41,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -75,   -75,   -75,   173,   -75,   -75,   -75,   -75,   -75,   -75,
     -15,    13,    18,   -75,   -75,   -59,   -63,   -55,   -48,   -74,
      82,    85,    83,   -50,   -75,   -75,   -75,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    42,    37,    30,    24,
      60,    61,    62,    16,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,   108,   109,    40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      86,    86,    82,    14,    93,    87,    88,    14,   122,    89,
     107,    31,    99,    10,   100,    39,    32,   103,    11,    10,
     112,    22,    45,    12,    11,    17,    15,    74,    18,    86,
      90,   102,    19,   104,     2,     3,    25,   110,     4,    86,
     118,    27,   -70,    86,    86,    86,    86,   123,    26,   129,
      43,   116,     2,     3,    28,    23,     4,    29,   125,    77,
     127,    -2,     1,    78,    46,    84,    47,    33,    86,    85,
     126,   132,   133,    48,    49,     2,     3,     2,     3,     4,
      34,     4,    50,    51,    52,    53,    35,    54,    55,    94,
      95,    96,    56,    91,    36,    47,    38,    57,    41,    38,
      58,    44,    48,    49,    59,    75,     2,     3,    20,    21,
       4,    50,    51,    52,    53,    76,    54,    55,    95,    96,
      79,    56,    91,    80,    47,    81,    57,    83,    38,    92,
      98,    48,    49,    59,     1,     2,     3,    97,   101,     4,
      50,    51,    52,    53,    91,    54,    55,     2,     3,   105,
      56,     4,   106,   111,    19,    57,    78,    38,   117,   119,
     120,   121,    59,    99,    52,    53,   124,    54,    55,   130,
      52,    53,    56,    54,    55,   128,   131,    57,    56,    13,
     113,     0,   114,    57,    59,   115
};

static const yytype_int16 yycheck[] =
{
      55,    56,    50,     1,    63,    55,    56,     1,     1,    57,
      84,    35,    25,     0,    27,    30,    40,    80,     0,     6,
      94,     1,    37,     0,     6,    41,    24,    42,    34,    84,
      24,    79,    38,    81,    14,    15,    18,    85,    18,    94,
     103,    24,    35,    98,    99,   100,   101,    40,    21,   123,
      32,   101,    14,    15,    35,    35,    18,    41,   117,    37,
     119,     0,     1,    41,     1,    34,     3,    24,   123,    38,
     118,   130,   131,    10,    11,    14,    15,    14,    15,    18,
      39,    18,    19,    20,    21,    22,    38,    24,    25,    30,
      31,    32,    29,     1,    41,     3,    36,    34,    41,    36,
      37,    21,    10,    11,    41,    24,    14,    15,    40,    41,
      18,    19,    20,    21,    22,    39,    24,    25,    31,    32,
      34,    29,     1,    34,     3,    34,    34,    34,    36,    37,
      28,    10,    11,    41,     1,    14,    15,    41,    26,    18,
      19,    20,    21,    22,     1,    24,    25,    14,    15,    41,
      29,    18,    24,    35,    38,    34,    41,    36,    35,    35,
      35,    35,    41,    25,    21,    22,    39,    24,    25,     4,
      21,    22,    29,    24,    25,    41,    35,    34,    29,     6,
      98,    -1,    99,    34,    41,   100
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    14,    15,    18,    43,    44,    45,    46,    47,
      53,    54,     0,    45,     1,    24,    55,    41,    34,    38,
      40,    41,     1,    35,    51,    54,    21,    24,    35,    41,
      50,    35,    40,    24,    39,    38,    41,    49,    36,    52,
      69,    41,    48,    54,    21,    52,     1,     3,    10,    11,
      19,    20,    21,    22,    24,    25,    29,    34,    37,    41,
      52,    53,    54,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    52,    24,    39,    37,    41,    34,
      34,    34,    60,    34,    34,    38,    59,    65,    65,    60,
      24,     1,    37,    57,    30,    31,    32,    41,    28,    25,
      27,    26,    60,    58,    60,    41,    24,    61,    67,    68,
      60,    35,    61,    62,    64,    63,    65,    35,    58,    35,
      35,    35,     1,    40,    39,    57,    60,    57,    41,    61,
       4,    35,    57,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    46,
      46,    46,    48,    47,    49,    47,    50,    47,    51,    51,
      51,    51,    52,    52,    52,    53,    53,    54,    54,    54,
      55,    55,    55,    55,    56,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    67,    68,    68,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     6,
       6,     5,     0,     7,     0,     7,     0,     6,     4,     3,
       2,     1,     3,     3,     2,     3,     3,     1,     1,     1,
       3,     6,     1,     4,     1,     2,     1,     1,     1,     7,
       5,     7,     5,     5,     3,     1,     2,     2,     1,     4,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       2,     2,     1,     1,     4,     3,     1,     1,     2,     2,
       1,     2,     0,     3,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 121 "1905021.y"
               {
		//write your code in this block in all the similar blocks below
		printGrammarRule("start","program");
		(yyval.SymbolInfo) = new symbolInfo("","start");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		
	}
#line 1742 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 130 "1905021.y"
                       {
		printGrammarRule("program","program unit");
		(yyval.SymbolInfo) = new symbolInfo("","program");
		
		
	}
#line 1753 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 136 "1905021.y"
               {
		printGrammarRule("program","unit");
		(yyval.SymbolInfo) = new symbolInfo("","program");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		
	}
#line 1764 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 144 "1905021.y"
                       {
		printGrammarRule("unit","var_declaration");
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		
	}
#line 1775 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 150 "1905021.y"
                       {
		printGrammarRule("unit","func_declaration");
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		

	}
#line 1787 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 157 "1905021.y"
                      {
		printGrammarRule("unit","func_definition");
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		
	}
#line 1798 "y.tab.c"
    break;

  case 8: /* unit: error  */
#line 163 "1905021.y"
                {
		yyclearin;
		yyerrok;
		errorout<<"Line# "<<totalLine<<": "<<"Syntax error at unit"<<"\n";
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName("err");
	}
#line 1810 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 172 "1905021.y"
                                                                            {
		printGrammarRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","func_declaration");
		(yyvsp[-4].SymbolInfo)->setMethodDeclaration(true);
		(yyvsp[-4].SymbolInfo)->setParamList((yyvsp[-2].SymbolInfo)->getParamList());
		(yyvsp[-4].SymbolInfo)->setTypeSpecifier((yyvsp[-5].SymbolInfo)->getTypeSpecifier());
		symbolInfoArguments->setParamList({});

		bool insertSuccess = symblTable->insert((yyvsp[-4].SymbolInfo));
		if(!insertSuccess){
			printError("Redefinition of function",(yyvsp[-4].SymbolInfo)->getName());
		}
		
	}
#line 1829 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 186 "1905021.y"
                                                          {
		printGrammarRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","func_declaration");
		(yyvsp[-4].SymbolInfo)->setMethodDeclaration(true);
		// $2->setParamList($4->getParamList());
		(yyvsp[-4].SymbolInfo)->setTypeSpecifier((yyvsp[-5].SymbolInfo)->getTypeSpecifier());
		symbolInfoArguments->setParamList({});

		bool insertSuccess = symblTable->insert((yyvsp[-4].SymbolInfo));
		if(!insertSuccess){
			printError("Redefinition of function",(yyvsp[-4].SymbolInfo)->getName());
		}
		
	}
#line 1848 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 200 "1905021.y"
                                                    {
		printGrammarRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","func_declaration");
		(yyvsp[-3].SymbolInfo)->setMethodDeclaration(true);
		(yyvsp[-3].SymbolInfo)->setTypeSpecifier((yyvsp[-4].SymbolInfo)->getTypeSpecifier());

		bool insertSuccess = symblTable->insert((yyvsp[-3].SymbolInfo));
		if(!insertSuccess){
			printError("Redefinition of function",(yyvsp[-3].SymbolInfo)->getName());
		}
		
	}
#line 1865 "y.tab.c"
    break;

  case 12: /* $@1: %empty  */
#line 214 "1905021.y"
                                                                 {insertFunctionIntoScopeTable((yyvsp[-3].SymbolInfo),(yyvsp[-4].SymbolInfo)); }
#line 1871 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 214 "1905021.y"
                                                                                                                            {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","func_definition");
		


	}
#line 1883 "y.tab.c"
    break;

  case 14: /* $@2: %empty  */
#line 221 "1905021.y"
                                                { insertFunctionIntoScopeTable((yyvsp[-3].SymbolInfo),(yyvsp[-4].SymbolInfo)); }
#line 1889 "y.tab.c"
    break;

  case 15: /* func_definition: type_specifier ID LPAREN error RPAREN $@2 compound_statement  */
#line 221 "1905021.y"
                                                                                                            {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","func_definition");
		printSyntaxError("Syntax error at parameter list of function definiton");
		
	
	}
#line 1901 "y.tab.c"
    break;

  case 16: /* $@3: %empty  */
#line 228 "1905021.y"
                                          {insertFunctionIntoScopeTable((yyvsp[-2].SymbolInfo),(yyvsp[-3].SymbolInfo)); }
#line 1907 "y.tab.c"
    break;

  case 17: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 228 "1905021.y"
                                                                                                     {
		printGrammarRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","func_definition");
		

	}
#line 1918 "y.tab.c"
    break;

  case 18: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 237 "1905021.y"
                                                         {
		printGrammarRule("parameter_list","parameter_list COMMA type_specifier ID");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		(yyval.SymbolInfo)->setParamList((yyvsp[-3].SymbolInfo)->getParamList());
		(yyvsp[0].SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		foundVoidTypeSpecifier((yyvsp[-1].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());
		


	}
#line 1935 "y.tab.c"
    break;

  case 19: /* parameter_list: parameter_list COMMA type_specifier  */
#line 249 "1905021.y"
                                              {
		printGrammarRule("parameter_list","parameter_list COMMA type_specifier");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		symbolInfo* onlyID = new symbolInfo("","ID");
		onlyID->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setParamList((yyvsp[-2].SymbolInfo)->getParamList());
		(yyval.SymbolInfo)->insertParameter(onlyID);
		foundVoidTypeSpecifier((yyvsp[0].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());
		

	}
#line 1952 "y.tab.c"
    break;

  case 20: /* parameter_list: type_specifier ID  */
#line 261 "1905021.y"
                            {
		printGrammarRule("parameter_list","type_specifier ID");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		(yyvsp[0].SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		foundVoidTypeSpecifier((yyvsp[-1].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());
		

	}
#line 1967 "y.tab.c"
    break;

  case 21: /* parameter_list: type_specifier  */
#line 271 "1905021.y"
                         {
		printGrammarRule("parameter_list","type_specifier");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		symbolInfo* onlyID = new symbolInfo("","ID");
		onlyID->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->insertParameter(onlyID);
		foundVoidTypeSpecifier((yyvsp[0].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());
		

	}
#line 1984 "y.tab.c"
    break;

  case 22: /* compound_statement: LCURL_ statements RCURL  */
#line 286 "1905021.y"
                                             {
		printGrammarRule("compound_statement","LCURL statements RCURL");
		(yyval.SymbolInfo) = new symbolInfo("","compound_statement");
		
		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

	}
#line 1997 "y.tab.c"
    break;

  case 23: /* compound_statement: LCURL_ error RCURL  */
#line 294 "1905021.y"
                             {
		printGrammarRule("compound_statement","LCURL_ statements RCURL");
		(yyval.SymbolInfo) = new symbolInfo("","compound_statement");

		
		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

	}
#line 2011 "y.tab.c"
    break;

  case 24: /* compound_statement: LCURL_ RCURL  */
#line 303 "1905021.y"
                       {
		printGrammarRule("compound_statement","LCURL RCURL");
		(yyval.SymbolInfo) = new symbolInfo("","compound_statement");
		

		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();
	

	}
#line 2026 "y.tab.c"
    break;

  case 25: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 315 "1905021.y"
                                                            {
		printGrammarRule("var_declaration","type_specifier declaration_list SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","var_declaration");

		if(!foundVoidTypeSpecifier((yyvsp[-2].SymbolInfo))){
			for(auto SymbolInfo:(yyvsp[-1].SymbolInfo)->getDeclarationList()){
				SymbolInfo->setTypeSpecifier((yyvsp[-2].SymbolInfo)->getTypeSpecifier());
				bool insertSuccess = symblTable->insert(SymbolInfo);
				if(!insertSuccess){
					printError("Redeclared variable",SymbolInfo->getName());
				}
			}
		}
		

	}
#line 2047 "y.tab.c"
    break;

  case 26: /* var_declaration: type_specifier error SEMICOLON  */
#line 331 "1905021.y"
                                         {
		printGrammarRule("var_declaration","type_specifier declaration_list SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","var_declaration");
		(yyval.SymbolInfo)->setName("");
		printSyntaxError("Syntax error at declaration list of variable declaration");

	}
#line 2059 "y.tab.c"
    break;

  case 27: /* type_specifier: INT  */
#line 340 "1905021.y"
                      {
		printGrammarRule("type_specifier","INT");
		(yyval.SymbolInfo) = new symbolInfo("","type_specifier");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		
	}
#line 2071 "y.tab.c"
    break;

  case 28: /* type_specifier: FLOAT  */
#line 347 "1905021.y"
                {
		printGrammarRule("type_specifier","FLOAT");
		(yyval.SymbolInfo) = new symbolInfo("","type_specifier");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		
	}
#line 2083 "y.tab.c"
    break;

  case 29: /* type_specifier: VOID  */
#line 354 "1905021.y"
               {
		printGrammarRule("type_specifier","VOID");
		(yyval.SymbolInfo) = new symbolInfo("","type_specifier");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		
	}
#line 2095 "y.tab.c"
    break;

  case 30: /* declaration_list: declaration_list COMMA ID  */
#line 363 "1905021.y"
                                             {
		printGrammarRule("declaration_list","declaration_list COMMA ID");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyval.SymbolInfo)->setDeclarationList((yyvsp[-2].SymbolInfo)->getDeclarationList());
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[0].SymbolInfo));
		

	}
#line 2108 "y.tab.c"
    break;

  case 31: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 371 "1905021.y"
                                                              {
		printGrammarRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyval.SymbolInfo)->setDeclarationList((yyvsp[-5].SymbolInfo)->getDeclarationList());
		(yyvsp[-3].SymbolInfo)->setArray(true);
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[-3].SymbolInfo));
		

	}
#line 2122 "y.tab.c"
    break;

  case 32: /* declaration_list: ID  */
#line 380 "1905021.y"
             {
		printGrammarRule("declaration_list","ID");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[0].SymbolInfo));
		

	}
#line 2135 "y.tab.c"
    break;

  case 33: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 388 "1905021.y"
                                       {
		printGrammarRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyvsp[-3].SymbolInfo)->setArray(true);
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[-3].SymbolInfo));
		

	}
#line 2148 "y.tab.c"
    break;

  case 34: /* statements: statement  */
#line 398 "1905021.y"
                       {
		printGrammarRule("statements","statement");
		(yyval.SymbolInfo) = new symbolInfo("","statements");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		

	}
#line 2160 "y.tab.c"
    break;

  case 35: /* statements: statements statement  */
#line 405 "1905021.y"
                               {
		printGrammarRule("statements","statements statement");
		(yyval.SymbolInfo) = new symbolInfo("","statements");
		

	}
#line 2171 "y.tab.c"
    break;

  case 36: /* statement: var_declaration  */
#line 413 "1905021.y"
                            {
		printGrammarRule("statement","var_declaration");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		

	}
#line 2183 "y.tab.c"
    break;

  case 37: /* statement: expression_statement  */
#line 420 "1905021.y"
                               {
		printGrammarRule("statement","expression_statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		

	}
#line 2195 "y.tab.c"
    break;

  case 38: /* statement: compound_statement  */
#line 427 "1905021.y"
                             {
		printGrammarRule("statement","compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		

	}
#line 2207 "y.tab.c"
    break;

  case 39: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 434 "1905021.y"
                                                                                           {
		printGrammarRule("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		

	}
#line 2218 "y.tab.c"
    break;

  case 40: /* statement: IF LPAREN expression RPAREN statement  */
#line 440 "1905021.y"
                                                                      {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		

	}
#line 2229 "y.tab.c"
    break;

  case 41: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 446 "1905021.y"
                                                               {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		

	}
#line 2240 "y.tab.c"
    break;

  case 42: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 452 "1905021.y"
                                                   {
		printGrammarRule("statement","WHILE LPAREN expression RPAREN statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		

	}
#line 2251 "y.tab.c"
    break;

  case 43: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 458 "1905021.y"
                                             {
		printGrammarRule("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		if(!symblTable->lookup((yyvsp[-2].SymbolInfo)->getName())) {
			printError("Undeclared variable",(yyvsp[-2].SymbolInfo)->getName());
		}
		

	}
#line 2265 "y.tab.c"
    break;

  case 44: /* statement: RETURN expression SEMICOLON  */
#line 467 "1905021.y"
                                      {
		printGrammarRule("statement","RETURN expression SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		

	}
#line 2276 "y.tab.c"
    break;

  case 45: /* expression_statement: SEMICOLON  */
#line 475 "1905021.y"
                                 {
		printGrammarRule("expression_statement","SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","expression_statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		

	}
#line 2288 "y.tab.c"
    break;

  case 46: /* expression_statement: expression SEMICOLON  */
#line 482 "1905021.y"
                               {
		printGrammarRule("expression_statement","expression SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","expression_statement");
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		

	}
#line 2300 "y.tab.c"
    break;

  case 47: /* expression_statement: error SEMICOLON  */
#line 489 "1905021.y"
                          {
		yyclearin;
		yyerrok;
		printSyntaxError("Syntax error at expression of expression statement");
		(yyval.SymbolInfo) = new symbolInfo("","expression_statement");
		
	}
#line 2312 "y.tab.c"
    break;

  case 48: /* variable: ID  */
#line 498 "1905021.y"
              {
		printGrammarRule("variable","ID");
		(yyval.SymbolInfo) = new symbolInfo("","variable");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		auto lookSymbol = symblTable->lookup((yyvsp[0].SymbolInfo)->getName());
		if(!lookSymbol){
			printError("Undeclared variable",(yyvsp[0].SymbolInfo)->getName());
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else if(lookSymbol->isArray()){
			errorout<<"Line# "<<totalLine<<": "<<"Type mismatch "<<"'"<<(yyvsp[0].SymbolInfo)->getName()<<"'"<<" is an array"<<"\n";
			totalError++;
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier(lookSymbol->getTypeSpecifier());
			(yyval.SymbolInfo)->setArray(lookSymbol->isArray());
		}
		


	}
#line 2340 "y.tab.c"
    break;

  case 49: /* variable: ID LSQUARE expression RSQUARE  */
#line 521 "1905021.y"
                                        {
		printGrammarRule("variable","ID LSQUARE expression RSQUARE");
		(yyval.SymbolInfo) = new symbolInfo("","variable");
		auto lookSymbol = symblTable->lookup((yyvsp[-3].SymbolInfo)->getName());
		if(!lookSymbol){
			printError("Undeclared variable",(yyvsp[-3].SymbolInfo)->getName());
		}
		else if(!lookSymbol->isArray()){
			errorout<<"Line# "<<totalLine<<": "<<"'"<<(yyvsp[-3].SymbolInfo)->getName()<<"'"<<" is not an array"<<"\n";
			totalError++;
			(yyval.SymbolInfo)->setTypeSpecifier(lookSymbol->getTypeSpecifier());
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier(lookSymbol->getTypeSpecifier());
		}
		if((yyvsp[-1].SymbolInfo)->getTypeSpecifier() != "CONST_INT" and (yyvsp[-1].SymbolInfo)->getTypeSpecifier() != "INT"){
			printSyntaxError("Array subscript is not an integer");
			
		}
		

	}
#line 2367 "y.tab.c"
    break;

  case 50: /* expression: logic_expression  */
#line 545 "1905021.y"
                              {
		printGrammarRule("expression","logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		

	}
#line 2380 "y.tab.c"
    break;

  case 51: /* expression: variable ASSIGNOP logic_expression  */
#line 553 "1905021.y"
                                             {
		printGrammarRule("expression","variable ASSIGNOP logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","expression");
		// $$->setTypeSpecifier($1->getTypeSpecifier());
		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if((yyvsp[-2].SymbolInfo)->getTypeSpecifier() == "FLOAT" and (yyvsp[0].SymbolInfo)->getTypeSpecifier() == "INT"){

		}
		else if((yyvsp[-2].SymbolInfo)->getTypeSpecifier() != (yyvsp[-1].SymbolInfo)->getTypeSpecifier() and (yyvsp[-2].SymbolInfo)->getTypeSpecifier() != "error" and (yyvsp[0].SymbolInfo)->getTypeSpecifier() != "error"){
			printSyntaxError("Type mismatch in logical expression");
			
		}
		

	}
#line 2402 "y.tab.c"
    break;

  case 52: /* logic_expression: rel_expression  */
#line 572 "1905021.y"
                                  {
		printGrammarRule("logic_expression","rel_expression");
		(yyval.SymbolInfo) = new symbolInfo("","logic_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());
		

	}
#line 2416 "y.tab.c"
    break;

  case 53: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 581 "1905021.y"
                                                {
		printGrammarRule("logic_expression","rel_expression LOGICOP rel_expression");
		(yyval.SymbolInfo) = new symbolInfo("","logic_expression");
		(yyval.SymbolInfo)->setTypeSpecifier("INT");
		

	}
#line 2428 "y.tab.c"
    break;

  case 54: /* rel_expression: simple_expression  */
#line 590 "1905021.y"
                                   {
		printGrammarRule("rel_expression","simple_expression");
		(yyval.SymbolInfo) = new symbolInfo("","rel_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());
		

	}
#line 2442 "y.tab.c"
    break;

  case 55: /* rel_expression: simple_expression RELOP simple_expression  */
#line 599 "1905021.y"
                                                    {
		printGrammarRule("rel_expression","simple_expression RELOP simple_expression");
		(yyval.SymbolInfo) = new symbolInfo("","rel_expression");
		if((yyvsp[-2].SymbolInfo)->getTypeSpecifier() == "VOID" or (yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier("INT");
		}
		

	}
#line 2460 "y.tab.c"
    break;

  case 56: /* simple_expression: term  */
#line 614 "1905021.y"
                         {
		printGrammarRule("simple_expression","term");
		(yyval.SymbolInfo) = new symbolInfo("","simple_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());
		

	}
#line 2474 "y.tab.c"
    break;

  case 57: /* simple_expression: simple_expression ADDOP term  */
#line 623 "1905021.y"
                                       {
		printGrammarRule("simple_expression","simple_expression ADDOP term");
		(yyval.SymbolInfo) = new symbolInfo("","simple_expression");
		(yyval.SymbolInfo)->setTypeSpecifier(typeCast((yyvsp[-2].SymbolInfo),(yyvsp[0].SymbolInfo)));
		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		

	}
#line 2489 "y.tab.c"
    break;

  case 58: /* term: unary_expression  */
#line 635 "1905021.y"
                        {
		printGrammarRule("term","unary_expression");
		(yyval.SymbolInfo) = new symbolInfo("","term");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());
		
		

	}
#line 2504 "y.tab.c"
    break;

  case 59: /* term: term MULOP unary_expression  */
#line 645 "1905021.y"
                                   {
		printGrammarRule("term","term MULOP unary_expression");
		(yyval.SymbolInfo) = new symbolInfo("","term");
		(yyval.SymbolInfo)->setTypeSpecifier(typeCast((yyvsp[-2].SymbolInfo),(yyvsp[0].SymbolInfo)));
		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if((yyvsp[-1].SymbolInfo)->getName() == "%" and (yyvsp[0].SymbolInfo)->getName() == "0"){
			printSyntaxError("Warning: division by zero");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else if((yyvsp[-1].SymbolInfo)->getName() == "%" and ((yyvsp[-2].SymbolInfo)->getTypeSpecifier() != "INT" or (yyvsp[0].SymbolInfo)->getTypeSpecifier() != "INT") ){
			printSyntaxError("Operands of modulus must be integers");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		

	}
#line 2527 "y.tab.c"
    break;

  case 60: /* unary_expression: ADDOP unary_expression  */
#line 665 "1905021.y"
                                          {
		printGrammarRule("unary_expression","ADDOP unary_expression");
		(yyval.SymbolInfo) = new symbolInfo("","unary_expression");
		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		}
		


	}
#line 2546 "y.tab.c"
    break;

  case 61: /* unary_expression: NOT unary_expression  */
#line 679 "1905021.y"
                               {
		printGrammarRule("unary_expression","NOT unary_expression");
		(yyval.SymbolInfo) = new symbolInfo("","unary_expression");
		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier("INT");
		}
		

	}
#line 2564 "y.tab.c"
    break;

  case 62: /* unary_expression: factor  */
#line 692 "1905021.y"
                 {
		printGrammarRule("unary_expression","factor");
		(yyval.SymbolInfo) = new symbolInfo("","unary_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());
		

	}
#line 2578 "y.tab.c"
    break;

  case 63: /* factor: variable  */
#line 703 "1905021.y"
                  {
		printGrammarRule("factor","variable");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());
		

	}
#line 2592 "y.tab.c"
    break;

  case 64: /* factor: ID LPAREN argument_list RPAREN  */
#line 712 "1905021.y"
                                         {
		printGrammarRule("factor","ID LPAREN argument_list RPAREN");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		auto lookedSymbol = symblTable->lookup((yyvsp[-3].SymbolInfo)->getName());
		if(!lookedSymbol){
			printError("Undeclared function",(yyvsp[-3].SymbolInfo)->getName());
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier(lookedSymbol->getTypeSpecifier());
			if(!lookedSymbol->isMethodDeclaration() and !lookedSymbol->isMethodDefinition()){
				printError("Undeclared function",(yyvsp[-3].SymbolInfo)->getName());
			}
			else if((yyvsp[-1].SymbolInfo)->getParamList().size() < lookedSymbol->getParamList().size()){
				printError("Too few arguments to function ",(yyvsp[-3].SymbolInfo)->getName());
			}
			else if((yyvsp[-1].SymbolInfo)->getParamList().size() > lookedSymbol->getParamList().size()){
				printError("Too few arguments to function ",(yyvsp[-3].SymbolInfo)->getName());
			}
			else{
				auto funcParamList = (yyvsp[-1].SymbolInfo)->getParamList();
				auto symblParamList = lookedSymbol->getParamList();
				for(int i=0; i<funcParamList.size(); ++i){
					if(funcParamList[i]->getTypeSpecifier() != symblParamList[i]->getTypeSpecifier()){
						printError("Type mismatch for argument "+to_string(i+1)+" of", (yyvsp[-3].SymbolInfo)->getName());
					}
					if(funcParamList[i]->isArray() and !symblParamList[i]->isArray()){
						printError("Type mismatch for argument "+to_string(i+1)+" of", (yyvsp[-3].SymbolInfo)->getName());
					}
					else if(!funcParamList[i]->isArray() and symblParamList[i]->isArray()){
						printError("Type mismatch for argument "+to_string(i+1)+" of", (yyvsp[-3].SymbolInfo)->getName());
					}

				}
			}
		}
		

	}
#line 2635 "y.tab.c"
    break;

  case 65: /* factor: LPAREN expression RPAREN  */
#line 750 "1905021.y"
                                   {
		printGrammarRule("factor","LPAREN expression RPAREN");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[-2].SymbolInfo)->getTypeSpecifier());
		

	}
#line 2647 "y.tab.c"
    break;

  case 66: /* factor: CONST_INT  */
#line 757 "1905021.y"
                    {
		printGrammarRule("factor","CONST_INT");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier("INT");
		

	}
#line 2660 "y.tab.c"
    break;

  case 67: /* factor: CONST_FLOAT  */
#line 765 "1905021.y"
                      {
		printGrammarRule("factor","CONST_FLOAT");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier("FLOAT");
		

	}
#line 2673 "y.tab.c"
    break;

  case 68: /* factor: variable INCOP  */
#line 773 "1905021.y"
                         {
		printGrammarRule("factor","variable INCOP");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		if((yyvsp[-1].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		}
		

	}
#line 2691 "y.tab.c"
    break;

  case 69: /* factor: variable DECOP  */
#line 786 "1905021.y"
                         {
		printGrammarRule("factor","variable DECOP");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		if((yyvsp[-1].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		}
		

	}
#line 2709 "y.tab.c"
    break;

  case 70: /* argument_list: arguments  */
#line 801 "1905021.y"
                          {
		printGrammarRule("argument_list","arguments");
		(yyval.SymbolInfo) = new symbolInfo("","argument_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setParamList((yyvsp[0].SymbolInfo)->getParamList());
		

	}
#line 2722 "y.tab.c"
    break;

  case 71: /* argument_list: arguments error  */
#line 809 "1905021.y"
                          {
		printGrammarRule("argument_list","arguments");
		yyclearin;
		yyerrok;
		printSyntaxError("Syntax error at parameter list of arguments");
		(yyval.SymbolInfo) = new symbolInfo("","argument_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[-1].SymbolInfo)}));
		(yyval.SymbolInfo)->setParamList((yyvsp[-1].SymbolInfo)->getParamList());
		

	}
#line 2738 "y.tab.c"
    break;

  case 72: /* argument_list: %empty  */
#line 820 "1905021.y"
          {
		printGrammarRule("argument_list","arguments");
		(yyval.SymbolInfo) = new symbolInfo("","argument_list");
		

	}
#line 2749 "y.tab.c"
    break;

  case 73: /* arguments: arguments COMMA logic_expression  */
#line 828 "1905021.y"
                                             {
		printGrammarRule("arguments","arguments COMMA logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","arguments");
		(yyval.SymbolInfo)->setParamList((yyvsp[-2].SymbolInfo)->getParamList());
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		

	}
#line 2762 "y.tab.c"
    break;

  case 74: /* arguments: logic_expression  */
#line 836 "1905021.y"
                           {
		printGrammarRule("arguments","logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","arguments");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		

	}
#line 2775 "y.tab.c"
    break;

  case 75: /* LCURL_: LCURL  */
#line 846 "1905021.y"
               {
	(yyval.SymbolInfo) = (yyvsp[0].SymbolInfo);
	symblTable->enterScope();
	for(auto SymbolInfo:symbolInfoArguments->getParamList()){
		if(SymbolInfo->getName() == "") continue;
		if(SymbolInfo->getTypeSpecifier() == "VOID"){
			SymbolInfo->setTypeSpecifier("error");
		}
		bool insertSuccess = symblTable->insert(SymbolInfo);
		if(!insertSuccess){
			printError("Redefinition of parameter",SymbolInfo->getName());
		}
	}
	symbolInfoArguments->setParamList({});

}
#line 2796 "y.tab.c"
    break;


#line 2800 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 864 "1905021.y"

int main(int argc,char *argv[]){
	FILE *fp;

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout.open("log.txt");
	errorout.open("error.txt");
	
	//parsetreeout.open("parsetree.txt");
	

	yyin=fp;
	yyparse();

	symblTable->printAllScopeTable(logout);
	logout<<"Total Lines: "<<totalLine<<endl;
	logout<<"Total Errors: "<<totalError<<endl;
	

	fclose(yyin);
	logout.close();
	errorout.close();
	
	//parsetreeout.close();
	
	return 0;
}

