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
fstream asmcodeout;


symbolTable* symblTable = new symbolTable(11);
symbolInfo* symbolInfoArguments = new symbolInfo();
TreeNode* parseTree = nullptr;


extern int totalLine;
extern int totalError;
extern FILE *yyin;

string stringArr[101];
string retType = "";
vector<pair<string,string>>globalVar;
vector<string> globalVariables;
vector<string> parameterList;
vector<pair<string,string>> argList;
int paramListLineNum = 0;
int decrementStack = 0;
int incrementStack = -2;
int internalLabelCount = 0;
int memsize = 0;
int in_main_func = 0;
stack<int> whileLabelStack;
int whileLoopCount = 0;
stack<int> forLabelStack;
int forLoopCount = 0;
stack<int> conditionLabelStack;
int conditionCount = 0;
int labelCount=0;
int tempCount=0;

int separateString(string s, char splitterCh){
	int counter = 1;
	int currentIdx = 0, i =0;
	int initialIdx = 0, lastIdx = 0;
	while(i <= s.length()){
		if(s[i] == splitterCh || i == s.length()){
			counter++;
			lastIdx = i;
			string subString = "";
			subString.append(s,initialIdx,lastIdx-initialIdx);
			stringArr[currentIdx] = subString;
			currentIdx += 1;
			initialIdx = lastIdx + 1;
		}
		i++;
	}
	return counter;
}

void optimizeAssembly(){
	cout<<"In optimizeAss"<<"\n";
	vector<string> assemblyCodes;
	fstream assemblyFile;
	assemblyFile.open("asmcode.asm",ios::in);

	if(assemblyFile.is_open()){
		string temp;
		while(getline(assemblyFile,temp)){
			cout<<"In while Loop"<<"\n";
			cout<<temp<<"\n";
			assemblyCodes.push_back(temp);
		}
		assemblyFile.close();
	}

	assemblyFile.open("optimizedAsmcode.asm",ios::out);
	for(int i=0; i<assemblyCodes.size(); ++i){
		if(assemblyCodes[i].substr(0,3) == "MOV" && assemblyCodes[i+1].substr(0,3) == "MOV"){
			string movInstruction1 = assemblyCodes[i].substr(4,assemblyCodes[i].length()-1);
			string movInstruction2 = assemblyCodes[i+1].substr(4,assemblyCodes[i].length()-1);
			char splitterCh = ',';
			int counter = separateString(movInstruction1,splitterCh);
			string instruction1 = stringArr[0];
			string instruction2 = stringArr[1];

			counter = separateString(movInstruction2,splitterCh);
			string m1 = stringArr[0];
			string m2 = stringArr[1];

			if(instruction1 == m2 && instruction2 == m1){
				assemblyFile<<assemblyCodes[i]<<"\n";
				assemblyFile<<"; "<<assemblyCodes[i+1]<<"\n";
				i++;
				continue;
			}
			else{
				assemblyFile<<assemblyCodes[i]<<"\n";
			}
		}
		else if(assemblyCodes[i].substr(0,3) == "PUSH" && assemblyCodes[i+1].substr(0,3) == "POP"){
			if(assemblyCodes[i].substr(4,assemblyCodes[i].length()-1) == assemblyCodes[i+1].substr(4,assemblyCodes[i].length()-1)){
				assemblyFile<<"; "<<assemblyCodes[i]<<"\n";
				assemblyFile<<"; "<<assemblyCodes[i+1]<<"\n";
				i += 2;
			}
			else{
				assemblyFile<<assemblyCodes[i]<<"\n";
			}
		}
		else{
			cout<<"Writing in optimized..."<<"\n";
			assemblyFile<<assemblyCodes[i]<<endl;
		}

		
	}
}

void modifyMain(){
	vector<string> assemblyCodes;
	fstream assemblyFile;
	assemblyFile.open("asmcode.asm",ios::in);
	if(assemblyFile.is_open()){
		string temp;
		while(getline(assemblyFile,temp)){
			assemblyCodes.push_back(temp);
		}
		assemblyFile.close();
	}
	int found = 0;
	assemblyFile.open("asmcode.asm",ios::out);
	for(int i=0; i<assemblyCodes.size(); i++){
		if(assemblyCodes[i] == "main PROC"){
			found = 1;
		}
		if(found == 1 && assemblyCodes[i] == "RET 0"){
			i += 2;
		}
		else{
			if(assemblyFile.is_open()){
				assemblyFile<<assemblyCodes[i]<<"\n";
			}
		}
	}

}

//return newLabel as L0 L1 ...
char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

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
		// printError("Redeclaration of function ",funcName->getName());
		errorout<<"Line# "<<totalLine<<": "<<"'"<<funcName->getName()<<"' "<<"redeclared as different kind of symbol"<<"\n";
		totalError++;
	}
	else{
		auto argListDeclaration = sameDeclaration->getParamList();
		auto argListDefinition = funcName->getParamList();
		int declareSize = argListDeclaration.size();
		int defineSize = argListDefinition.size();
		if(sameDeclaration->getTypeSpecifier() != funcName->getTypeSpecifier()){
			printError("Conflicting types for",funcName->getName());
		}
		if(sameDeclaration->getParamList().size() != funcName->getParamList().size()){
			printError("Conflicting types for",funcName->getName());
		}
		if(sameDeclaration->getParamList().size() != funcName->getParamList().size()){
			// printError("Too many arguments to function ",funcName->getName());
		}
		if(declareSize > defineSize){
			// printError("Too few arguments to function ",funcName->getName());
		}
		else if(declareSize < defineSize){
			printError("Too many arguments to function ",funcName->getName());
		}
		else{
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
		// else if(SymbolInfo->getName() == ";" or SymbolInfo->getName() = "{") symblName += "\n";
		else if(SymbolInfo->getName() == "}") {}
	}
	return symblName;
}

void eraseMemory(symbolInfo* sInfo){
	if(sInfo != NULL) delete sInfo;
}

void removeSymbolTable(){
	if(symblTable != nullptr) delete symblTable;
}

string getReduceMessage(int lineCount1, int lineCount2, string head, string body){
	string parseMessage = head + " : " + body + " \t<Line: " + to_string(lineCount1) + "-" + to_string(lineCount2) + ">\n";
	return parseMessage;
}

string getTerminalReduceMessage(int lineCount, string head, string body){
	string parseTerminalMessage = head + " : " + body + "\t<Line: " + to_string(lineCount) + ">\n";
	return parseTerminalMessage;
}

void preOrderTraversal(TreeNode* root){
	string parsingSpace;
	if(root != nullptr){
		int space = root->getSpace();
		while(space > 0){
			parsingSpace += " ";
			space -= 1;
		}
		parsetreeout<<parsingSpace+root->getParseMessage();
		for(TreeNode* treeNode:root->nodeList){
			if(treeNode != nullptr){
				treeNode->setSpace(root->getSpace()+1);
			}
			preOrderTraversal(treeNode);
		}
	}
}

void insertTerminal(symbolInfo*,symbolInfo*);

void yyerror(string s){

}

int yyparse(void);
int yylex(void);



#line 375 "y.tab.c"

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

#line 414 "y.tab.c"

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
#line 312 "1905021.y"

	symbolInfo* SymbolInfo;

#line 520 "y.tab.c"

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
  YYSYMBOL_44_1 = 44,                      /* $@1  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_unit = 46,                      /* unit  */
  YYSYMBOL_func_declaration = 47,          /* func_declaration  */
  YYSYMBOL_func_definition = 48,           /* func_definition  */
  YYSYMBOL_49_2 = 49,                      /* $@2  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_51_4 = 51,                      /* $@4  */
  YYSYMBOL_parameter_list = 52,            /* parameter_list  */
  YYSYMBOL_compound_statement = 53,        /* compound_statement  */
  YYSYMBOL_var_declaration = 54,           /* var_declaration  */
  YYSYMBOL_type_specifier = 55,            /* type_specifier  */
  YYSYMBOL_declaration_list = 56,          /* declaration_list  */
  YYSYMBOL_statements = 57,                /* statements  */
  YYSYMBOL_statement = 58,                 /* statement  */
  YYSYMBOL_59_5 = 59,                      /* $@5  */
  YYSYMBOL_60_6 = 60,                      /* $@6  */
  YYSYMBOL_61_7 = 61,                      /* $@7  */
  YYSYMBOL_62_8 = 62,                      /* $@8  */
  YYSYMBOL_63_9 = 63,                      /* $@9  */
  YYSYMBOL_IF_ = 64,                       /* IF_  */
  YYSYMBOL_65_10 = 65,                     /* $@10  */
  YYSYMBOL_expression_statement = 66,      /* expression_statement  */
  YYSYMBOL_variable = 67,                  /* variable  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_69_11 = 69,                     /* $@11  */
  YYSYMBOL_logic_expression = 70,          /* logic_expression  */
  YYSYMBOL_71_12 = 71,                     /* $@12  */
  YYSYMBOL_rel_expression = 72,            /* rel_expression  */
  YYSYMBOL_73_13 = 73,                     /* $@13  */
  YYSYMBOL_simple_expression = 74,         /* simple_expression  */
  YYSYMBOL_75_14 = 75,                     /* $@14  */
  YYSYMBOL_term = 76,                      /* term  */
  YYSYMBOL_77_15 = 77,                     /* $@15  */
  YYSYMBOL_unary_expression = 78,          /* unary_expression  */
  YYSYMBOL_factor = 79,                    /* factor  */
  YYSYMBOL_argument_list = 80,             /* argument_list  */
  YYSYMBOL_arguments = 81,                 /* arguments  */
  YYSYMBOL_82_16 = 82,                     /* $@16  */
  YYSYMBOL_LCURL_ = 83                     /* LCURL_  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   186

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

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
       0,   324,   324,   324,   360,   377,   392,   405,   419,   432,
     441,   471,   498,   525,   525,   580,   580,   600,   600,   647,
     678,   701,   720,   743,   766,   785,   804,   850,   870,   885,
     899,   915,   933,   962,   976,  1001,  1015,  1030,  1045,  1059,
    1073,  1081,  1091,  1073,  1120,  1138,  1161,  1167,  1161,  1198,
    1227,  1250,  1250,  1275,  1289,  1304,  1321,  1352,  1389,  1404,
    1404,  1469,  1486,  1486,  1524,  1540,  1540,  1635,  1651,  1651,
    1685,  1702,  1702,  1744,  1769,  1790,  1808,  1854,  1909,  1927,
    1945,  1962,  2012,  2063,  2082,  2098,  2106,  2106,  2129,  2147
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
  "SEMICOLON", "$accept", "start", "$@1", "program", "unit",
  "func_declaration", "func_definition", "$@2", "$@3", "$@4",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@5",
  "$@6", "$@7", "$@8", "$@9", "IF_", "$@10", "expression_statement",
  "variable", "expression", "$@11", "logic_expression", "$@12",
  "rel_expression", "$@13", "simple_expression", "$@14", "term", "$@15",
  "unary_expression", "factor", "argument_list", "arguments", "$@16",
  "LCURL_", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-79)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-87)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -79,    12,    52,   -79,   -79,   -79,   -79,   -79,    57,   -79,
     -79,   -79,   -79,     8,   -79,   -20,   -18,    81,   -79,    10,
       5,    17,   -79,    20,    28,   -22,    60,    42,    50,    58,
     -79,    75,    73,    36,   -79,   -79,    97,   -79,    75,   -79,
     -79,    76,   -79,    75,   104,    92,   -79,    -8,    98,    99,
     102,   140,   106,   -79,   -79,    40,   140,   140,   140,   -79,
     -79,   -79,   -79,    13,   105,   -79,   139,   -79,    72,   109,
     -79,   110,    82,   121,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   140,    18,   -79,   116,   127,   140,   140,    61,   -79,
     -79,   125,   128,   126,   -79,   -79,   134,   -79,   -79,   141,
     -79,   -79,   -79,   -79,   -79,   137,   -79,   140,   -79,   138,
     -79,   142,     9,   143,   -79,   -79,   140,   140,   140,   140,
     140,   -79,    18,   144,   135,   -79,   -79,   145,   -79,   -79,
     -79,   121,   153,   -79,   134,   -79,   -79,   -79,   140,   -79,
     140,   134,   -79,   146,   -79,   -79,   134,   -79
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     9,    28,    29,    30,     0,     5,
       7,     8,     6,     0,     4,     0,    33,     0,    27,     0,
       0,     0,    26,     0,    17,     0,    22,     0,    31,    15,
      12,     0,    13,     0,    21,    34,     0,    11,     0,    89,
      18,     0,    10,     0,    20,     0,    16,     0,     0,     0,
       0,     0,     0,    79,    80,    56,     0,     0,     0,    25,
      53,    39,    37,     0,     0,    35,    44,    38,    76,     0,
      58,    61,    64,    67,    70,    75,    14,    19,    32,    24,
      55,     0,     0,    46,     0,     0,    85,     0,    76,    73,
      74,     0,    33,     0,    23,    36,     0,    81,    82,     0,
      54,    62,    68,    65,    71,     0,    40,     0,    50,     0,
      88,     0,     0,     0,    78,    45,     0,     0,     0,     0,
       0,    51,     0,     0,     0,    77,    84,     0,    57,    60,
      63,    69,    66,    72,     0,    41,    47,    49,     0,    52,
       0,     0,    87,     0,    48,    42,     0,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -79,   -79,   172,   -79,   -79,   -79,   -79,   -79,
     -79,   -16,    74,    15,   -79,   -79,   -61,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -76,   -55,   -51,   -79,   -78,   -79,
      66,   -79,    65,   -79,    68,   -79,   -52,   -79,   -79,   -79,
     -79,   -79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    10,    11,    43,    38,    31,
      25,    61,    62,    63,    17,    64,    65,   122,   140,   146,
     107,   141,    66,   134,    67,    68,    69,    99,    70,   117,
      71,   119,    72,   118,    73,   120,    74,    75,   111,   112,
     127,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    88,    88,    95,    89,    90,   106,    91,   110,    15,
     126,    23,     3,    32,    15,    40,    19,    13,    33,    93,
      20,    18,    46,    13,     5,     6,    27,    76,     7,    79,
     105,    88,    16,    80,    26,   115,   113,    92,   129,    53,
      54,    28,    55,    56,   -83,    24,   135,    57,    44,   -86,
       5,     6,    58,     4,     7,    29,   123,    -3,     4,    60,
     142,    88,    88,    88,    88,    88,     5,     6,   133,    30,
       7,     5,     6,   139,    86,     7,    12,    47,    87,    48,
     144,    35,    12,    88,    34,   147,    49,    50,    36,   143,
       5,     6,    97,    98,     7,    51,    52,    53,    54,    37,
      55,    56,   -59,    97,    98,    57,    93,   102,    48,   103,
      58,    39,    39,    59,    42,    49,    50,    60,    45,     5,
       6,    21,    22,     7,    51,    52,    53,    54,    77,    55,
      56,    78,    81,    82,    57,    93,    83,    48,   101,    58,
      85,    39,    94,    96,    49,    50,    60,   104,     5,     6,
     100,   109,     7,    51,    52,    53,    54,   108,    55,    56,
     114,    53,    54,    57,    55,    56,    20,    80,    58,    57,
      39,   116,   121,   124,    58,    60,   137,   125,   102,   136,
      14,   145,   128,   130,   132,   138,   131
};

static const yytype_uint8 yycheck[] =
{
      51,    56,    57,    64,    56,    57,    82,    58,    86,     1,
       1,     1,     0,    35,     1,    31,    34,     2,    40,     1,
      38,    41,    38,     8,    14,    15,    21,    43,    18,    37,
      81,    86,    24,    41,    19,    96,    87,    24,   116,    21,
      22,    24,    24,    25,    35,    35,   122,    29,    33,    40,
      14,    15,    34,     1,    18,    35,   107,     0,     1,    41,
     138,   116,   117,   118,   119,   120,    14,    15,   120,    41,
      18,    14,    15,   134,    34,    18,     2,     1,    38,     3,
     141,    39,     8,   138,    24,   146,    10,    11,    38,   140,
      14,    15,    31,    32,    18,    19,    20,    21,    22,    41,
      24,    25,    30,    31,    32,    29,     1,    25,     3,    27,
      34,    36,    36,    37,    41,    10,    11,    41,    21,    14,
      15,    40,    41,    18,    19,    20,    21,    22,    24,    24,
      25,    39,    34,    34,    29,     1,    34,     3,    28,    34,
      34,    36,    37,     4,    10,    11,    41,    26,    14,    15,
      41,    24,    18,    19,    20,    21,    22,    41,    24,    25,
      35,    21,    22,    29,    24,    25,    38,    41,    34,    29,
      36,    30,    35,    35,    34,    41,    41,    35,    25,    35,
       8,    35,    39,   117,   119,    40,   118
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    44,     0,     1,    14,    15,    18,    45,    46,
      47,    48,    54,    55,    46,     1,    24,    56,    41,    34,
      38,    40,    41,     1,    35,    52,    55,    21,    24,    35,
      41,    51,    35,    40,    24,    39,    38,    41,    50,    36,
      53,    83,    41,    49,    55,    21,    53,     1,     3,    10,
      11,    19,    20,    21,    22,    24,    25,    29,    34,    37,
      41,    53,    54,    55,    57,    58,    64,    66,    67,    68,
      70,    72,    74,    76,    78,    79,    53,    24,    39,    37,
      41,    34,    34,    34,    68,    34,    34,    38,    67,    78,
      78,    68,    24,     1,    37,    58,     4,    31,    32,    69,
      41,    28,    25,    27,    26,    68,    66,    62,    41,    24,
      70,    80,    81,    68,    35,    58,    30,    71,    75,    73,
      77,    35,    59,    68,    35,    35,     1,    82,    39,    70,
      72,    76,    74,    78,    65,    66,    35,    41,    40,    58,
      60,    63,    70,    68,    58,    35,    61,    58
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    44,    43,    45,    45,    46,    46,    46,    46,
      47,    47,    47,    49,    48,    50,    48,    51,    48,    52,
      52,    52,    52,    53,    53,    53,    54,    54,    55,    55,
      55,    56,    56,    56,    56,    57,    57,    58,    58,    58,
      59,    60,    61,    58,    58,    58,    62,    63,    58,    58,
      58,    65,    64,    66,    66,    66,    67,    67,    68,    69,
      68,    70,    71,    70,    72,    73,    72,    74,    75,    74,
      76,    77,    76,    78,    78,    78,    79,    79,    79,    79,
      79,    79,    79,    80,    80,    80,    82,    81,    81,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     1,
       6,     6,     5,     0,     7,     0,     7,     0,     6,     4,
       3,     2,     1,     3,     3,     2,     3,     3,     1,     1,
       1,     3,     6,     1,     4,     1,     2,     1,     1,     1,
       0,     0,     0,    10,     1,     3,     0,     0,     7,     5,
       3,     0,     6,     1,     2,     2,     1,     4,     1,     0,
       4,     1,     0,     4,     1,     0,     4,     1,     0,     4,
       1,     0,     4,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     2,     0,     0,     4,     1,     1
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
  case 2: /* $@1: %empty  */
#line 324 "1905021.y"
        {
		asmcodeout<<"\n.MODEL SMALL\n.STACK 1000H\n.CODE"<<"\n";
		asmcodeout<<"\nnew_line proc\npush ax\npush dx\nmov ah,2\nmov dl,0AH\nint 21h\nmov dl,0DH\nint 21h\npop dx\npop ax\nret\nnew_line endp\n";
		asmcodeout<<"\nprintln proc ;print what is in ax\npush ax\npush bx\npush cx\npush dx\npush si\nlea si, number\nmov bx,10\nadd si,4\ncmp ax,0\njnge negate\nprint:\nxor dx,dx\ndiv bx\nmov [si],dl\nadd [si],'0'\ndec si\ncmp ax,0\njne print\ninc si\nlea dx,si\nmov ah,9\nint 21h\npop si\npop dx\npop cx\npop bx\npop ax\nret\nnegate:\npush ax\nmov ah,2\nmov dl,'-'\nint 21h\npop ax\nneg ax\njmp print\nprintln endp";

		}
#line 1970 "y.tab.c"
    break;

  case 3: /* start: $@1 program  */
#line 331 "1905021.y"
                       {
		//write your code in this block in all the similar blocks below
		printGrammarRule("start","program");
		(yyval.SymbolInfo) = new symbolInfo("","start");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"start","program");
		parseTree = new TreeNode(prseMessage);
		parseTree->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		asmcodeout<<"\n.DATA\nnumber DB '00000$'";
		for(int i=0; i<globalVar.size(); ++i){
			if(globalVar[i].second == "0"){
				asmcodeout<<"\n"<<globalVar[i].first<<" DW ?";
			}
			else{
				asmcodeout<<"\n"<<globalVar[i].first<<" DW "<<globalVar[i].second<<" DUP (0)";
			}
			
		}
		asmcodeout<<"\nEND main\n"<<endl;
		modifyMain();
		optimizeAssembly();
		
		
	}
#line 2002 "y.tab.c"
    break;

  case 4: /* program: program unit  */
#line 360 "1905021.y"
                       {
		printGrammarRule("program","program unit");
		(yyval.SymbolInfo) = new symbolInfo("","program");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[-1].SymbolInfo)}));
		
		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"program","program unit");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		  

		 

		
	}
#line 2024 "y.tab.c"
    break;

  case 5: /* program: unit  */
#line 377 "1905021.y"
               {
		printGrammarRule("program","unit");
		(yyval.SymbolInfo) = new symbolInfo("","program");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"program","unit");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		
	}
#line 2042 "y.tab.c"
    break;

  case 6: /* unit: var_declaration  */
#line 392 "1905021.y"
                       {
		printGrammarRule("unit","var_declaration");
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"unit","var_declaration");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		
	}
#line 2060 "y.tab.c"
    break;

  case 7: /* unit: func_declaration  */
#line 405 "1905021.y"
                       {
		printGrammarRule("unit","func_declaration");
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"unit","func_declaration");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 2079 "y.tab.c"
    break;

  case 8: /* unit: func_definition  */
#line 419 "1905021.y"
                      {
		printGrammarRule("unit","func_definition");
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"unit","func_definition");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		
	}
#line 2097 "y.tab.c"
    break;

  case 9: /* unit: error  */
#line 432 "1905021.y"
                {
		yyclearin;
		yyerrok;
		errorout<<"Line# "<<totalLine<<": "<<"Syntax error at unit"<<"\n";
		(yyval.SymbolInfo) = new symbolInfo("","unit");
		(yyval.SymbolInfo)->setName("err");
	}
#line 2109 "y.tab.c"
    break;

  case 10: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 441 "1905021.y"
                                                                            {
		printGrammarRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","func_declaration");
		(yyvsp[-4].SymbolInfo)->setMethodDeclaration(true);
		(yyvsp[-4].SymbolInfo)->setParamList((yyvsp[-2].SymbolInfo)->getParamList());
		(yyvsp[-4].SymbolInfo)->setTypeSpecifier((yyvsp[-5].SymbolInfo)->getTypeSpecifier());
		symbolInfoArguments->setParamList({});
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[-5].SymbolInfo)}));


		bool insertSuccess = symblTable->insert((yyvsp[-4].SymbolInfo));
		if(!insertSuccess){
			printError("Redefinition of function",(yyvsp[-4].SymbolInfo)->getName());
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-5].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-5].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-2].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));
		
		 
		 
		
		
	}
#line 2144 "y.tab.c"
    break;

  case 11: /* func_declaration: type_specifier ID LPAREN error RPAREN SEMICOLON  */
#line 471 "1905021.y"
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

		(yyval.SymbolInfo)->setLineCount((yyvsp[-5].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-5].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		 
		
		
	}
#line 2176 "y.tab.c"
    break;

  case 12: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 498 "1905021.y"
                                                    {
		printGrammarRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","func_declaration");
		(yyvsp[-3].SymbolInfo)->setMethodDeclaration(true);
		(yyvsp[-3].SymbolInfo)->setTypeSpecifier((yyvsp[-4].SymbolInfo)->getTypeSpecifier());

		bool insertSuccess = symblTable->insert((yyvsp[-3].SymbolInfo));
		if(!insertSuccess){
			printError("Redefinition of function",(yyvsp[-3].SymbolInfo)->getName());
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-4].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-4].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		 
		 
		
	}
#line 2206 "y.tab.c"
    break;

  case 13: /* $@2: %empty  */
#line 525 "1905021.y"
                                                                 {
		insertFunctionIntoScopeTable((yyvsp[-3].SymbolInfo),(yyvsp[-4].SymbolInfo));
		//StackOffset used
		memsize = parameterList.size();
		int stckOffset = -2-(2*memsize);
		for(int i=0; i<memsize; ++i){
			cout<<parameterList[i]<<"\n";
			symbolInfo* si = symblTable->lookup(parameterList[i]);
			si->setStackOffset(stckOffset);
			stckOffset += 2;
		}
		//Stackoffset used
		cout<<parameterList.size()<<endl;
		parameterList.clear();
		asmcodeout<<"\n"<<(yyvsp[-3].SymbolInfo)->getName()<<" PROC ;Line:"<<totalLine<<"Definition of function "<<(yyvsp[-3].SymbolInfo)->getName();
		if((yyvsp[-3].SymbolInfo)->getName() == "main"){
			asmcodeout<<"\nMOV DX,@DATA\nMOV DS,DX ;Line:"<<totalLine<<" Moving segment data to AX register";
		}
		asmcodeout<<"\nPUSH BP\nMOV BP,SP ;Moving StackPointer to BasePointer";
		retType = "";
		
		
		}
#line 2234 "y.tab.c"
    break;

  case 14: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@2 compound_statement  */
#line 547 "1905021.y"
                                     {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","func_definition");

		asmcodeout<<"\nADD SP,"<<decrementStack; //+to_string(-$7->getStackOffset())
		decrementStack = 0;
		incrementStack = -2;
		if((yyvsp[-5].SymbolInfo)->getName() == "main"){
			asmcodeout<<"\nPOP BP";
			asmcodeout<<"\nMOV AH,4CH\nINT 21h ;Line:"<<totalLine<<"return control to the OS";
		}
		else{
			asmcodeout<<"\nPOP BP\nRET"<<memsize*2;
			memsize = 0;
		}
		in_main_func--;
		asmcodeout<<"\n"<<(yyvsp[-5].SymbolInfo)->getName()<<" ENDP "<<"\n";

		(yyval.SymbolInfo)->setLineCount((yyvsp[-6].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-6].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-5].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());
		
		 
		 
		

	}
#line 2272 "y.tab.c"
    break;

  case 15: /* $@3: %empty  */
#line 580 "1905021.y"
                                                { insertFunctionIntoScopeTable((yyvsp[-3].SymbolInfo),(yyvsp[-4].SymbolInfo)); }
#line 2278 "y.tab.c"
    break;

  case 16: /* func_definition: type_specifier ID LPAREN error RPAREN $@3 compound_statement  */
#line 580 "1905021.y"
                                                                                                            {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","func_definition");
		printSyntaxError("Syntax error at parameter list of function definition");

		(yyval.SymbolInfo)->setLineCount((yyvsp[-6].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-6].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-5].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		 
		
		
	
	}
#line 2303 "y.tab.c"
    break;

  case 17: /* $@4: %empty  */
#line 600 "1905021.y"
                                          {
		insertFunctionIntoScopeTable((yyvsp[-2].SymbolInfo),(yyvsp[-3].SymbolInfo));
		asmcodeout<<"\n"<<(yyvsp[-2].SymbolInfo)->getName()<<" PROC ;Line:"<<totalLine<<"Definition of function "<<(yyvsp[-2].SymbolInfo)->getName();
		if((yyvsp[-2].SymbolInfo)->getName() == "main"){
			asmcodeout<<"\nMOV DX,@DATA\nMOV DS,DX ;Line:"<<totalLine<<" Moving segment data to AX register";
		}
		asmcodeout<<"\nPUSH BP\nMOV BP,SP ;Moving StackPointer to BasePointer";
		retType = "";


		}
#line 2319 "y.tab.c"
    break;

  case 18: /* func_definition: type_specifier ID LPAREN RPAREN $@4 compound_statement  */
#line 610 "1905021.y"
                                     {
		printGrammarRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","func_definition");

		asmcodeout<<"\nADD SP,"<<decrementStack<<"; Line : "<<totalLine<<" SP = SP + stackOffset";
		//to_string(-$6->getStackOffset())
		decrementStack = 0;
		incrementStack = -2;
		if((yyvsp[-4].SymbolInfo)->getName() == "main"){
			asmcodeout<<"\nPOP BP";
			asmcodeout<<"\nMOV AH,4CH\nINT 21h ;Line:"<<totalLine<<" return control to OS";
		}
		else{
			asmcodeout<<"\nPOP BP\nRET "<<memsize*2;
			memsize = 0;
		}

		in_main_func--;
		asmcodeout<<"\n"<<(yyvsp[-4].SymbolInfo)->getName()<<" ENDP "<<endl;

		(yyval.SymbolInfo)->setLineCount((yyvsp[-5].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-5].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		 
		

	}
#line 2358 "y.tab.c"
    break;

  case 19: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 647 "1905021.y"
                                                         {
		printGrammarRule("parameter_list","parameter_list COMMA type_specifier ID");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		(yyval.SymbolInfo)->setParamList((yyvsp[-3].SymbolInfo)->getParamList());
		(yyvsp[0].SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		foundVoidTypeSpecifier((yyvsp[-1].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());

		paramListLineNum = totalLine;
		parameterList.push_back((yyvsp[0].SymbolInfo)->getName());


		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"parameter_list","parameter_list COMMA type_specifier ID");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));



		 
		

		 
		


	}
#line 2394 "y.tab.c"
    break;

  case 20: /* parameter_list: parameter_list COMMA type_specifier  */
#line 678 "1905021.y"
                                              {
		printGrammarRule("parameter_list","parameter_list COMMA type_specifier");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		symbolInfo* onlyID = new symbolInfo("","ID");
		onlyID->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setParamList((yyvsp[-2].SymbolInfo)->getParamList());
		(yyval.SymbolInfo)->insertParameter(onlyID);
		foundVoidTypeSpecifier((yyvsp[0].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"parameter_list","parameter_list COMMA type_specifier");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-2].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		
		
		

	}
#line 2422 "y.tab.c"
    break;

  case 21: /* parameter_list: type_specifier ID  */
#line 701 "1905021.y"
                            {
		printGrammarRule("parameter_list","type_specifier ID");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		(yyvsp[0].SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		foundVoidTypeSpecifier((yyvsp[-1].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"parameter_list","type_specifier ID");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		  
		
		

	}
#line 2446 "y.tab.c"
    break;

  case 22: /* parameter_list: type_specifier  */
#line 720 "1905021.y"
                         {
		printGrammarRule("parameter_list","type_specifier");
		(yyval.SymbolInfo) = new symbolInfo("","parameter_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		symbolInfo* onlyID = new symbolInfo("","ID");
		onlyID->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->insertParameter(onlyID);
		foundVoidTypeSpecifier((yyvsp[0].SymbolInfo));
		symbolInfoArguments->setParamList((yyval.SymbolInfo)->getParamList());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"parameter_list","type_specifier");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		
		

	}
#line 2471 "y.tab.c"
    break;

  case 23: /* compound_statement: LCURL_ statements RCURL  */
#line 743 "1905021.y"
                                             {
		printGrammarRule("compound_statement","LCURL statements RCURL");
		(yyval.SymbolInfo) = new symbolInfo("","compound_statement");

		(yyval.SymbolInfo)->setStackOffset(symblTable->getCurrScopeTable()->getStackOffset());

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"compound_statement","LCURL statements RCURL");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));
		
		
		 

		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

		 
		

	}
#line 2499 "y.tab.c"
    break;

  case 24: /* compound_statement: LCURL_ error RCURL  */
#line 766 "1905021.y"
                             {
		printGrammarRule("compound_statement","LCURL statements RCURL");
		(yyval.SymbolInfo) = new symbolInfo("","compound_statement");

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"compound_statement","LCURL statements RCURL");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

		  



	}
#line 2523 "y.tab.c"
    break;

  case 25: /* compound_statement: LCURL_ RCURL  */
#line 785 "1905021.y"
                       {
		printGrammarRule("compound_statement","LCURL RCURL");
		(yyval.SymbolInfo) = new symbolInfo("","compound_statement");

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"compound_statement","LCURL RCURL");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));
		

		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

		  

	}
#line 2545 "y.tab.c"
    break;

  case 26: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 804 "1905021.y"
                                                            {
		printGrammarRule("var_declaration","type_specifier declaration_list SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","var_declaration");

		if(!foundVoidTypeSpecifier((yyvsp[-2].SymbolInfo))){
			for(auto SymbolInfo:(yyvsp[-1].SymbolInfo)->getDeclarationList()){
				SymbolInfo->setTypeSpecifier((yyvsp[-2].SymbolInfo)->getTypeSpecifier());
				bool insertSuccess = symblTable->insert(SymbolInfo);
				if(!insertSuccess){
					printError("Conflicting types for",SymbolInfo->getName());
				}
				else if(symblTable->getCurrScopeTable()->getTableId() == 1){
					SymbolInfo->setStackOffset(0);
					globalVariables.push_back(SymbolInfo->getName());
					if(SymbolInfo->isArray()){
						int tempSize = 2*SymbolInfo->getSize();
						globalVar.push_back(make_pair(SymbolInfo->getName(),to_string(tempSize)));
					}
					else{
						globalVar.push_back(make_pair(SymbolInfo->getName(),"0"));
					}
					
				}
				else{
					if(SymbolInfo->isArray()){
						decrementStack += 2*SymbolInfo->getSize();
						asmcodeout<<"\nSUB SP,"<<(2*SymbolInfo->getSize());
					}
					else{
						decrementStack += 2;
						asmcodeout<<"\nSUB SP,2 ;Line "<<totalLine<<" : Stack Pointer Set for variables";
					}
				}
			}
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"var_declaration","type_specifier declaration_list SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-2].SymbolInfo)->getRoot());
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		
	}
#line 2596 "y.tab.c"
    break;

  case 27: /* var_declaration: type_specifier error SEMICOLON  */
#line 850 "1905021.y"
                                         {
		printGrammarRule("var_declaration","type_specifier declaration_list SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","var_declaration");
		(yyval.SymbolInfo)->setName("err");
		printSyntaxError("Syntax error at declaration list of variable declaration");

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"var_declaration","type_specifier declaration_list SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-2].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		  
		

		

	}
#line 2619 "y.tab.c"
    break;

  case 28: /* type_specifier: INT  */
#line 870 "1905021.y"
                      {
		printGrammarRule("type_specifier","INT");
		(yyval.SymbolInfo) = new symbolInfo("","type_specifier");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"type_specifier","INT");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		
		
	}
#line 2639 "y.tab.c"
    break;

  case 29: /* type_specifier: FLOAT  */
#line 885 "1905021.y"
                {
		printGrammarRule("type_specifier","FLOAT");
		(yyval.SymbolInfo) = new symbolInfo("","type_specifier");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"type_specifier","FLOAT");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		
	}
#line 2658 "y.tab.c"
    break;

  case 30: /* type_specifier: VOID  */
#line 899 "1905021.y"
               {
		printGrammarRule("type_specifier","VOID");
		(yyval.SymbolInfo) = new symbolInfo("","type_specifier");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"type_specifier","VOID");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		
	}
#line 2677 "y.tab.c"
    break;

  case 31: /* declaration_list: declaration_list COMMA ID  */
#line 915 "1905021.y"
                                             {
		printGrammarRule("declaration_list","declaration_list COMMA ID");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyval.SymbolInfo)->setDeclarationList((yyvsp[-2].SymbolInfo)->getDeclarationList());
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[0].SymbolInfo));

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"declaration_list","declaration_list COMMA ID");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-2].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		 
		

	}
#line 2700 "y.tab.c"
    break;

  case 32: /* declaration_list: declaration_list COMMA ID LSQUARE CONST_INT RSQUARE  */
#line 933 "1905021.y"
                                                              {
		printGrammarRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyval.SymbolInfo)->setDeclarationList((yyvsp[-5].SymbolInfo)->getDeclarationList());
		(yyvsp[-3].SymbolInfo)->setArray(true);
		string temp = (yyvsp[-1].SymbolInfo)->getName();
		istringstream is(temp);
		int arrSize;
		is >> arrSize;

		(yyvsp[-3].SymbolInfo)->setSize(arrSize);
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[-3].SymbolInfo));

		(yyval.SymbolInfo)->setLineCount((yyvsp[-5].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-5].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		 
		   
		

	}
#line 2734 "y.tab.c"
    break;

  case 33: /* declaration_list: ID  */
#line 962 "1905021.y"
             {
		printGrammarRule("declaration_list","ID");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[0].SymbolInfo));
		
		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"declaration_list","ID");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		

	}
#line 2753 "y.tab.c"
    break;

  case 34: /* declaration_list: ID LSQUARE CONST_INT RSQUARE  */
#line 976 "1905021.y"
                                       {
		printGrammarRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");
		(yyval.SymbolInfo) = new symbolInfo("","declaration_list");
		(yyvsp[-3].SymbolInfo)->setArray(true);

		string temp = (yyvsp[-1].SymbolInfo)->getName();
		istringstream is(temp);
		int arrSize;
		is>>arrSize;
		(yyvsp[-3].SymbolInfo)->setSize(arrSize);
		(yyval.SymbolInfo)->insertDeclaration((yyvsp[-3].SymbolInfo));

		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"declaration_list","ID LSQUARE CONST_INT RSQUARE");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));	
		
		 
		
	}
#line 2781 "y.tab.c"
    break;

  case 35: /* statements: statement  */
#line 1001 "1905021.y"
                       {
		printGrammarRule("statements","statement");
		(yyval.SymbolInfo) = new symbolInfo("","statements");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statements","statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 2800 "y.tab.c"
    break;

  case 36: /* statements: statements statement  */
#line 1015 "1905021.y"
                               {
		printGrammarRule("statements","statements statement");
		(yyval.SymbolInfo) = new symbolInfo("","statements");

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statements","statements statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());
		
		 

	}
#line 2818 "y.tab.c"
    break;

  case 37: /* statement: var_declaration  */
#line 1030 "1905021.y"
                            {
		printGrammarRule("statement","var_declaration");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","var_declaration");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		
		

	}
#line 2838 "y.tab.c"
    break;

  case 38: /* statement: expression_statement  */
#line 1045 "1905021.y"
                               {
		printGrammarRule("statement","expression_statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","expression_statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 2857 "y.tab.c"
    break;

  case 39: /* statement: compound_statement  */
#line 1059 "1905021.y"
                             {
		printGrammarRule("statement","compound_statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","compound_statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 2876 "y.tab.c"
    break;

  case 40: /* $@5: %empty  */
#line 1073 "1905021.y"
                                         {
		asmcodeout<<"\nFOR_"<<forLoopCount<<": ; Line "<<totalLine<<" : Label of for loop";
		forLabelStack.push(forLoopCount);
		forLoopCount++;

	
	
		}
#line 2889 "y.tab.c"
    break;

  case 41: /* $@6: %empty  */
#line 1081 "1905021.y"
                                    {
		asmcodeout<<"\n; Line "<<totalLine<<" : Checking Conditional of for loop";
		asmcodeout<<"\nPUSH CX";
		asmcodeout<<"\nPOP AX";
		asmcodeout<<"\nCMP AX,1\nJNE FOR_BREAK_"<<forLabelStack.top();
		asmcodeout<<"\nJMP FOR_INTERNAL_"<<forLabelStack.top();
		asmcodeout<<"\nFOR_LOOP_INC_DEC_"<<forLabelStack.top()<<":";

		}
#line 2903 "y.tab.c"
    break;

  case 42: /* $@7: %empty  */
#line 1091 "1905021.y"
                                 {
		asmcodeout<<"\nJMP FOR_"<<forLabelStack.top()<<" ; Line "<<totalLine<<" : Jump to for loop";
		asmcodeout<<"\nFOR_INTERNAL_"<<forLabelStack.top()<<":";

		}
#line 2913 "y.tab.c"
    break;

  case 43: /* statement: FOR LPAREN expression_statement $@5 expression_statement $@6 expression RPAREN $@7 statement  */
#line 1096 "1905021.y"
                          {
		asmcodeout<<"\nJMP FOR_LOOP_INC_DEC_"<<forLabelStack.top()<<" ; Line "<<totalLine<<" : Increment or Decrement in for loop";
		asmcodeout<<"\nFOR_BREAK_"<<forLabelStack.top()<<":";
		forLabelStack.pop();

		printGrammarRule("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");

		(yyval.SymbolInfo)->setLineCount((yyvsp[-9].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-9].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-8].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-7].SymbolInfo)->getRoot());
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-5].SymbolInfo)->getRoot());
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		 
		

	}
#line 2942 "y.tab.c"
    break;

  case 44: /* statement: IF_  */
#line 1120 "1905021.y"
                                    {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		
		asmcodeout<<"\nIF_END_"<<conditionLabelStack.top()<<": ;Line "<<totalLine<<" conditional block end";
		conditionLabelStack.pop();
		
		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());
		

		  
		 
		 
		
	}
#line 2965 "y.tab.c"
    break;

  case 45: /* statement: IF_ ELSE statement  */
#line 1138 "1905021.y"
                             {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");

		asmcodeout<<"\nIF_END_"<<conditionLabelStack.top()<<": ;Line "<<totalLine<<" conditional block end";
		conditionLabelStack.pop();


		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-2].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		 
		

		

	}
#line 2993 "y.tab.c"
    break;

  case 46: /* $@8: %empty  */
#line 1161 "1905021.y"
                      {
		asmcodeout<<"\nWHILE_"<<whileLoopCount<<": ;Line "<<totalLine<<" : While loop begins";
		whileLabelStack.push(whileLoopCount);
		whileLoopCount++;

		}
#line 3004 "y.tab.c"
    break;

  case 47: /* $@9: %empty  */
#line 1167 "1905021.y"
                                 {
		asmcodeout<<"\nPUSH CX";
		asmcodeout<<"\nPOP AX";
		asmcodeout<<"\nCMP AX,0\nJE WHILE_BREAK_"<<whileLabelStack.top()<<": ;Line "<<totalLine<<" while loop ends";


		}
#line 3016 "y.tab.c"
    break;

  case 48: /* statement: WHILE LPAREN $@8 expression RPAREN $@9 statement  */
#line 1174 "1905021.y"
                          {
		printGrammarRule("statement","WHILE LPAREN expression RPAREN statement");
		(yyval.SymbolInfo) = new symbolInfo("","statement");

		asmcodeout<<"\nJMP WHILE_"<<whileLabelStack.top()<<" ;Line "<<totalLine<<" : goto while loop begin";
		asmcodeout<<"\nWHILE_BREAK_"<<whileLabelStack.top()<<": ; Line "<<totalLine<<" : while loop exits";
		whileLabelStack.pop();

		(yyval.SymbolInfo)->setLineCount((yyvsp[-6].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","WHILE LPAREN expression RPAREN statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-6].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-5].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		 
		 
		
		

	}
#line 3045 "y.tab.c"
    break;

  case 49: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 1198 "1905021.y"
                                             {
		printGrammarRule("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","statement");
		if(!symblTable->lookup((yyvsp[-2].SymbolInfo)->getName())) {
			printError("Undeclared variable",(yyvsp[-2].SymbolInfo)->getName());
		}
		else{
			auto lookedSymbol = symblTable->lookup((yyvsp[-2].SymbolInfo)->getName());
			(yyval.SymbolInfo)->setStackOffset(lookedSymbol->getStackOffset());
			if((yyval.SymbolInfo)->getStackOffset() != 0) (yyval.SymbolInfo)->variableName = to_string((yyval.SymbolInfo)->getStackOffset())+"[BP]";
			else (yyval.SymbolInfo)->variableName = (yyvsp[-2].SymbolInfo)->getName(); //global var
			asmcodeout<<"\nMOV AX, "<<-(lookedSymbol->getStackOffset())<<"[BP]";
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-4].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		  
		
		

	}
#line 3079 "y.tab.c"
    break;

  case 50: /* statement: RETURN expression SEMICOLON  */
#line 1227 "1905021.y"
                                      {
		printGrammarRule("statement","RETURN expression SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","statement");

		asmcodeout<<"\nADD SP, "<<decrementStack;
		asmcodeout<<"\nPOP BP\nRET "<<memsize*2;
		asmcodeout<<"\n ; Line "<<totalLine<<" : Return back to caller function";
		memsize = 0;

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","RETURN expression SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		  
		
		

	}
#line 3106 "y.tab.c"
    break;

  case 51: /* $@10: %empty  */
#line 1250 "1905021.y"
                                 {
		conditionLabelStack.push(conditionCount);
		conditionCount++;
		asmcodeout<<"\nPUSH CX";
		asmcodeout<<"\nPOP AX";
		asmcodeout<<"\nCMP AX,1\nJNE IF_FALSE_"<<conditionLabelStack.top()<<"; Line "<<totalLine<<" : Branch Condition checked and jumped";


		}
#line 3120 "y.tab.c"
    break;

  case 52: /* IF_: IF LPAREN expression RPAREN $@10 statement  */
#line 1259 "1905021.y"
                         {
		asmcodeout<<"\nJMP IF_END_"<<conditionLabelStack.top()<<" ;Line "<<totalLine<<" End of If Label";
		asmcodeout<<"\nIF_FALSE_"<<conditionLabelStack.top()<<": ;Line "<<totalLine<<" : Condition is false of If Label";

		(yyval.SymbolInfo) = new symbolInfo("","IF_");
		(yyval.SymbolInfo)->setLineCount((yyvsp[-5].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement ELSE statement");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		
		insertTerminal((yyval.SymbolInfo),(yyvsp[-5].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-4].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());
		}
#line 3140 "y.tab.c"
    break;

  case 53: /* expression_statement: SEMICOLON  */
#line 1275 "1905021.y"
                                 {
		printGrammarRule("expression_statement","SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","expression_statement");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"expression_statement","SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		

	}
#line 3159 "y.tab.c"
    break;

  case 54: /* expression_statement: expression SEMICOLON  */
#line 1289 "1905021.y"
                               {
		printGrammarRule("expression_statement","expression SEMICOLON");
		(yyval.SymbolInfo) = new symbolInfo("","expression_statement");
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[-1].SymbolInfo)->getTypeSpecifier());

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"expression_statement","expression SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		

	}
#line 3179 "y.tab.c"
    break;

  case 55: /* expression_statement: error SEMICOLON  */
#line 1304 "1905021.y"
                          {
		yyclearin;
		yyerrok;
		printSyntaxError("Syntax error at expression of expression statement");
		(yyval.SymbolInfo) = new symbolInfo("","expression_statement");
		(yyval.SymbolInfo)->setName("err");

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"expression_statement","expression SEMICOLON");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		
	}
#line 3199 "y.tab.c"
    break;

  case 56: /* variable: ID  */
#line 1321 "1905021.y"
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
			(yyval.SymbolInfo)->setStackOffset(lookSymbol->getStackOffset());
			if((yyval.SymbolInfo)->getStackOffset() != 0) (yyval.SymbolInfo)->variableName = to_string((yyval.SymbolInfo)->getStackOffset())+"[BP]";
			else (yyval.SymbolInfo)->variableName = (yyvsp[0].SymbolInfo)->getName();
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"variable","ID");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		


	}
#line 3235 "y.tab.c"
    break;

  case 57: /* variable: ID LSQUARE expression RSQUARE  */
#line 1352 "1905021.y"
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

		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"variable","ID LSQUARE expression RSQUARE");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		
		
		

	}
#line 3275 "y.tab.c"
    break;

  case 58: /* expression: logic_expression  */
#line 1389 "1905021.y"
                              {
		printGrammarRule("expression","logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"expression","logic_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 3295 "y.tab.c"
    break;

  case 59: /* $@11: %empty  */
#line 1404 "1905021.y"
                  {
		if((yyvsp[0].SymbolInfo)->getName().find('[') != std::string::npos){
			asmcodeout<<"\nPUSH CX"<<"\n";
		}

		}
#line 3306 "y.tab.c"
    break;

  case 60: /* expression: variable $@11 ASSIGNOP logic_expression  */
#line 1410 "1905021.y"
                                          {
		printGrammarRule("expression","variable ASSIGNOP logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","expression");

		// $$->setTypeSpecifier($1->getTypeSpecifier());
		if((yyvsp[-1].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if((yyvsp[-3].SymbolInfo)->getTypeSpecifier() == "FLOAT" and (yyvsp[-1].SymbolInfo)->getTypeSpecifier() == "INT"){

		}
		else if((yyvsp[-3].SymbolInfo)->getTypeSpecifier() != (yyvsp[-1].SymbolInfo)->getTypeSpecifier() and (yyvsp[-3].SymbolInfo)->getTypeSpecifier() != "error" and (yyvsp[-1].SymbolInfo)->getTypeSpecifier() != "error"){
			printSyntaxError("Warning: possible loss of data in assignment of FLOAT to INT");
			
		}
		if((yyvsp[-3].SymbolInfo)->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString((yyvsp[-3].SymbolInfo)->getName(),splitterCh);
			string arrName = stringArr[0];
			string idx = stringArr[1].substr(0,stringArr[1].length()-1);
			auto lookSymbol = symblTable->lookup(arrName);
			asmcodeout<<"\nPOP AX\nXCHG AX,CX";
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV PTR WORD [BP],AX\nMOV CX,AX\nPOP BP";

		}
		else{
			auto lookSymbol = symblTable->lookup((yyvsp[-3].SymbolInfo)->getName());
			if(lookSymbol != nullptr)
				asmcodeout<<"\nMOV "<<lookSymbol->getStackOffset()<<"[BP],CX"<<" ; Line "<<totalLine<<" : Assign value to "<<(yyvsp[-3].SymbolInfo)->getName();
			else{
				int found = 0;
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == (yyvsp[-3].SymbolInfo)->getName()){
						found = 1;
						asmcodeout<<"\nMOV "<<(yyvsp[-3].SymbolInfo)->getName()<<" ,CX";
					}
				}
				
			}
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"expression","variable ASSIGNOP logic_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 


		

	}
#line 3368 "y.tab.c"
    break;

  case 61: /* logic_expression: rel_expression  */
#line 1469 "1905021.y"
                                  {
		printGrammarRule("logic_expression","rel_expression");
		(yyval.SymbolInfo) = new symbolInfo("","logic_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"logic_expression","rel_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		
		

	}
#line 3390 "y.tab.c"
    break;

  case 62: /* $@12: %empty  */
#line 1486 "1905021.y"
                                {
		asmcodeout<<"\nPUSH CX";

		}
#line 3399 "y.tab.c"
    break;

  case 63: /* logic_expression: rel_expression LOGICOP $@12 rel_expression  */
#line 1490 "1905021.y"
                               {
		printGrammarRule("logic_expression","rel_expression LOGICOP rel_expression");
		(yyval.SymbolInfo) = new symbolInfo("","logic_expression");
		(yyval.SymbolInfo)->setTypeSpecifier("INT");

		if((yyvsp[-2].SymbolInfo)->getName() == "&&"){
			asmcodeout<<"\nJCXZ AND_0_"<<internalLabelCount<<" ;Line "<<totalLine<<" : First operand is zero";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,0\nJE AND_0_"<<internalLabelCount<<" ;Line "<<totalLine<<" : Second operand is zero";
			asmcodeout<<"\nMOV CX,1\nJMP EXIT_AND_"<<internalLabelCount<<" ;Line "<<totalLine<<" : value returns true";
			asmcodeout<<"\nAND_0_"<<internalLabelCount<<":";
			asmcodeout<<"\nMOV CX,0\nEXIT_AND_"<<internalLabelCount<<": ;Line "<<totalLine<<" : value returns false";
			internalLabelCount++;
		}
		else{
			asmcodeout<<"\nCMP CX,1\nJE OR_1_"<<internalLabelCount<<"\n";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,1\nJE OR_1_"<<internalLabelCount<<"\n";
			asmcodeout<<"\nMOV CX,0\nJMP EXIT_OR_"<<internalLabelCount<<"\n";
			asmcodeout<<"OR_1_"<<internalLabelCount<<":"<<endl;
			asmcodeout<<"MOV CX,1\nEXIT_OR_"<<internalLabelCount<<":"<<endl;
			internalLabelCount++;
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"logic_expression","rel_expression LOGICOP rel_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

	}
#line 3436 "y.tab.c"
    break;

  case 64: /* rel_expression: simple_expression  */
#line 1524 "1905021.y"
                                   {
		printGrammarRule("rel_expression","simple_expression");
		(yyval.SymbolInfo) = new symbolInfo("","rel_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"rel_expression","simple_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 3457 "y.tab.c"
    break;

  case 65: /* $@13: %empty  */
#line 1540 "1905021.y"
                                 {
		asmcodeout<<"\nPUSH CX";

		}
#line 3466 "y.tab.c"
    break;

  case 66: /* rel_expression: simple_expression RELOP $@13 simple_expression  */
#line 1544 "1905021.y"
                                  {
		printGrammarRule("rel_expression","simple_expression RELOP simple_expression");
		(yyval.SymbolInfo) = new symbolInfo("","rel_expression");

		if((yyvsp[-3].SymbolInfo)->getTypeSpecifier() == "VOID" or (yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier("INT");
		}

		if((yyvsp[-2].SymbolInfo)->getName() == "<"){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a < b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJL RELOP_LESS_THAN_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_LESS_THAN_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;
		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "<="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a <= b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJLE RELOP_LESS_THAN_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_LESS_THAN_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if((yyvsp[-2].SymbolInfo)->getName() == ">"){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a > b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJG RELOP_GREATER_THAN_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_GREATER_THAN_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if((yyvsp[-2].SymbolInfo)->getName() == ">="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a >= b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJGE RELOP_GREATER_THAN_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_GREATER_THAN_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "=="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a == b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJE RELOP_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "!="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a != b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJNE RELOP_NOT_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_NOT_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"rel_expression","simple_expression RELOP simple_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		

	}
#line 3560 "y.tab.c"
    break;

  case 67: /* simple_expression: term  */
#line 1635 "1905021.y"
                         {
		printGrammarRule("simple_expression","term");
		(yyval.SymbolInfo) = new symbolInfo("","simple_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"simple_expression","term");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 3581 "y.tab.c"
    break;

  case 68: /* $@14: %empty  */
#line 1651 "1905021.y"
                                 {
		asmcodeout<<"\nPUSH CX";

		}
#line 3590 "y.tab.c"
    break;

  case 69: /* simple_expression: simple_expression ADDOP $@14 term  */
#line 1655 "1905021.y"
                     {
		printGrammarRule("simple_expression","simple_expression ADDOP term");
		(yyval.SymbolInfo) = new symbolInfo("","simple_expression");
		(yyval.SymbolInfo)->setTypeSpecifier(typeCast((yyvsp[-3].SymbolInfo),(yyvsp[0].SymbolInfo)));
		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}

		if((yyvsp[-2].SymbolInfo)->getName() == "+"){
			asmcodeout<<"\nPOP AX\nADD AX,CX\nMOV CX,AX";
		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "-"){
			asmcodeout<<"\nPOP AX\nSUB AX,CX\nMOV CX,AX";
		}



		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"simple_expression","simple_expression ADDOP term");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		  

	}
#line 3623 "y.tab.c"
    break;

  case 70: /* term: unary_expression  */
#line 1685 "1905021.y"
                        {
		printGrammarRule("term","unary_expression");
		(yyval.SymbolInfo) = new symbolInfo("","term");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"term","unary_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());
		
		
		
		

	}
#line 3645 "y.tab.c"
    break;

  case 71: /* $@15: %empty  */
#line 1702 "1905021.y"
                 {
		asmcodeout<<"\nPUSH CX";

		}
#line 3654 "y.tab.c"
    break;

  case 72: /* term: term MULOP $@15 unary_expression  */
#line 1706 "1905021.y"
                                 {
		printGrammarRule("term","term MULOP unary_expression");
		(yyval.SymbolInfo) = new symbolInfo("","term");
		(yyval.SymbolInfo)->setTypeSpecifier(typeCast((yyvsp[-3].SymbolInfo),(yyvsp[0].SymbolInfo)));

		if((yyvsp[0].SymbolInfo)->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "%" and (yyvsp[0].SymbolInfo)->getName() == "0"){
			printSyntaxError("Warning: division by zero");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "%" and ((yyvsp[-3].SymbolInfo)->getTypeSpecifier() != "INT" or (yyvsp[0].SymbolInfo)->getTypeSpecifier() != "INT") ){
			printSyntaxError("Operands of modulus must be integers");
			(yyval.SymbolInfo)->setTypeSpecifier("error");
		}

		if((yyvsp[-2].SymbolInfo)->getName() == "*"){
			asmcodeout<<"\nPOP AX\nIMUL CX\nMOV CX,AX";
		}
		else if((yyvsp[-2].SymbolInfo)->getName() == "%"){
			asmcodeout<<"\nPOP AX\nCWD\nIDIV CX\n MOV CX,DX";
		}



		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"term","term MULOP unary_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 

	}
#line 3695 "y.tab.c"
    break;

  case 73: /* unary_expression: ADDOP unary_expression  */
#line 1744 "1905021.y"
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

		if((yyvsp[-1].SymbolInfo)->getName() == "-"){
			asmcodeout<<"\nPOP CX\nNEG CX\nPUSH CX"<<" ; Line "<<totalLine<<" : Negate the value of CX register";
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"unary_expression","ADDOP unary_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		  


	}
#line 3725 "y.tab.c"
    break;

  case 74: /* unary_expression: NOT unary_expression  */
#line 1769 "1905021.y"
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
		
		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"unary_expression","NOT unary_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		  
		  

	}
#line 3751 "y.tab.c"
    break;

  case 75: /* unary_expression: factor  */
#line 1790 "1905021.y"
                 {
		printGrammarRule("unary_expression","factor");
		(yyval.SymbolInfo) = new symbolInfo("","unary_expression");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"unary_expression","factor");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 3772 "y.tab.c"
    break;

  case 76: /* factor: variable  */
#line 1808 "1905021.y"
                  {
		printGrammarRule("factor","variable");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[0].SymbolInfo)->getTypeSpecifier());
		(yyval.SymbolInfo)->setArray((yyvsp[0].SymbolInfo)->isArray());

		if((yyvsp[0].SymbolInfo)->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString((yyvsp[0].SymbolInfo)->getName(),splitterCh);
			string arrName = stringArr[0];
			symbolInfo* lookedSymbol = symblTable->lookup(arrName);
			
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookedSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV CX,PTR WORD[BP]\nPOP BP";
		}
		else{
			int found = 0;
			symbolInfo* lookedSymbol = symblTable->lookup((yyvsp[0].SymbolInfo)->getName());
			if(lookedSymbol == nullptr){
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == (yyvsp[0].SymbolInfo)->getName()){
						asmcodeout<<"\nMOV CX,"<<(yyvsp[0].SymbolInfo)->getName();
						found = 1;

					}
				}
				
			}
			else{
				asmcodeout<<"\nMOV CX,"<<-(lookedSymbol->getStackOffset())<<"[BP]"<<" ; Line "<<totalLine<<" : Mov the value of "<<(yyvsp[0].SymbolInfo)->getName()<<" to CX register";

			}
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","variable");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 3823 "y.tab.c"
    break;

  case 77: /* factor: ID LPAREN argument_list RPAREN  */
#line 1854 "1905021.y"
                                         {
		printGrammarRule("factor","ID LPAREN argument_list RPAREN");
		(yyval.SymbolInfo) = new symbolInfo("","factor");

		auto lookedSymbol = symblTable->lookup((yyvsp[-3].SymbolInfo)->getName());
		if(!lookedSymbol){
			// printError("Undeclared function",$1->getName());
		}
		else{
			(yyval.SymbolInfo)->setTypeSpecifier(lookedSymbol->getTypeSpecifier());
			if(!lookedSymbol->isMethodDeclaration() and !lookedSymbol->isMethodDefinition()){
				// printError("Undeclared function",$1->getName());
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

		asmcodeout<<"\nMOV AX,CX\nCALL "<<(yyvsp[-3].SymbolInfo)->getName()<<" ; Line "<<totalLine<<" : Call function "<<(yyvsp[-3].SymbolInfo)->getName();
		in_main_func++;


		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","ID LPAREN argument_list RPAREN");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-3].SymbolInfo));
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		
		
		

	}
#line 3883 "y.tab.c"
    break;

  case 78: /* factor: LPAREN expression RPAREN  */
#line 1909 "1905021.y"
                                   {
		printGrammarRule("factor","LPAREN expression RPAREN");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setTypeSpecifier((yyvsp[-2].SymbolInfo)->getTypeSpecifier());

		(yyval.SymbolInfo)->setLineCount((yyvsp[-2].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","LPAREN expression RPAREN");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[-2].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		
		
		

	}
#line 3906 "y.tab.c"
    break;

  case 79: /* factor: CONST_INT  */
#line 1927 "1905021.y"
                    {
		printGrammarRule("factor","CONST_INT");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier("INT");

		asmcodeout<<"\nMOV CX,"<<(yyvsp[0].SymbolInfo)->getName();

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","CONST_INT");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));
		
		
		 
		

	}
#line 3929 "y.tab.c"
    break;

  case 80: /* factor: CONST_FLOAT  */
#line 1945 "1905021.y"
                      {
		printGrammarRule("factor","CONST_FLOAT");
		(yyval.SymbolInfo) = new symbolInfo("","factor");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setTypeSpecifier("FLOAT");

		asmcodeout<<"\nMOV CX,"<<(yyvsp[0].SymbolInfo)->getName();

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","CONST_FLOAT");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		
		

	}
#line 3951 "y.tab.c"
    break;

  case 81: /* factor: variable INCOP  */
#line 1962 "1905021.y"
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

		if((yyvsp[-1].SymbolInfo)->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString((yyvsp[-1].SymbolInfo)->getName(),splitterCh);
			string arrName = stringArr[0];
			auto lookSymbol = symblTable->lookup(arrName);
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV CX,PTR WORD[BP]";
			asmcodeout<<"\nMOV AX,CX\nADD AX,1\nMOV PTR WORD [BP],AX\nPOP BP";
		}
		else{
			auto lookSymbol = symblTable->lookup((yyvsp[-1].SymbolInfo)->getName());
			int found = 0;
			if(lookSymbol == nullptr){
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == (yyvsp[-1].SymbolInfo)->getName()){
						asmcodeout<<"\nMOV CX,"<<(yyvsp[-1].SymbolInfo)->getName();
						asmcodeout<<"\nADD CX,1\nMOV "<<(yyvsp[-1].SymbolInfo)->getName()<<",CX";
					}
				}
			}
			else{
				asmcodeout<<"\nMOV CX,"<<-(lookSymbol->getStackOffset())<<"[BP]";
				asmcodeout<<"\nMOV AX,CX\nADD AX,1\nMOV "<<-(lookSymbol->getStackOffset())<<",AX";
			}
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","variable INCOP");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		
		

	}
#line 4006 "y.tab.c"
    break;

  case 82: /* factor: variable DECOP  */
#line 2012 "1905021.y"
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

		if((yyvsp[-1].SymbolInfo)->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString((yyvsp[-1].SymbolInfo)->getName(),splitterCh);
			string arrName = stringArr[0];
			auto lookSymbol = symblTable->lookup(arrName);
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV CX,PTR WORD[BP]";
			asmcodeout<<"\nMOV AX,CX\nSUB AX,1\nMOV PTR WORD [BP],AX\nPOP BP";
		}
		else{
			auto lookSymbol = symblTable->lookup((yyvsp[-1].SymbolInfo)->getName());
			int found = 0;
			if(lookSymbol == nullptr){
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == (yyvsp[-1].SymbolInfo)->getName()){
						asmcodeout<<"\nMOV CX,"<<(yyvsp[-1].SymbolInfo)->getName();
						asmcodeout<<"\nSUB CX,1\nMOV "<<(yyvsp[-1].SymbolInfo)->getName()<<",CX";
					}
				}
			}
			else{
				asmcodeout<<"\nMOV CX,"<<-(lookSymbol->getStackOffset())<<"[BP]";
				asmcodeout<<"\nMOV AX,CX\nSUB AX,1\nMOV "<<-(lookSymbol->getStackOffset())<<",AX";
			}
		}

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"factor","variable DECOP");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[0].SymbolInfo));

		 
		

	}
#line 4060 "y.tab.c"
    break;

  case 83: /* argument_list: arguments  */
#line 2063 "1905021.y"
                          {
		printGrammarRule("argument_list","arguments");
		(yyval.SymbolInfo) = new symbolInfo("","argument_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->setParamList((yyvsp[0].SymbolInfo)->getParamList());

		asmcodeout<<"\nPUSH CX";
		(yyval.SymbolInfo)->setStackOffset((yyvsp[0].SymbolInfo)->getStackOffset());

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"argument_list","arguments");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		
		

	}
#line 4084 "y.tab.c"
    break;

  case 84: /* argument_list: arguments error  */
#line 2082 "1905021.y"
                          {
		printGrammarRule("argument_list","arguments");
		yyclearin;
		yyerrok;
		printSyntaxError("Syntax error at parameter list of arguments");
		(yyval.SymbolInfo) = new symbolInfo("","argument_list");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[-1].SymbolInfo)}));
		(yyval.SymbolInfo)->setParamList((yyvsp[-1].SymbolInfo)->getParamList());

		(yyval.SymbolInfo)->setLineCount((yyvsp[-1].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"argument_list","arguments");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-1].SymbolInfo)->getRoot());
		

	}
#line 4105 "y.tab.c"
    break;

  case 85: /* argument_list: %empty  */
#line 2098 "1905021.y"
          {
		printGrammarRule("argument_list","arguments");
		(yyval.SymbolInfo) = new symbolInfo("","argument_list");


	}
#line 4116 "y.tab.c"
    break;

  case 86: /* $@16: %empty  */
#line 2106 "1905021.y"
                     {
		asmcodeout<<"\nPUSH CX";

		}
#line 4125 "y.tab.c"
    break;

  case 87: /* arguments: arguments $@16 COMMA logic_expression  */
#line 2110 "1905021.y"
                                       {
		printGrammarRule("arguments","arguments COMMA logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","arguments");
		(yyval.SymbolInfo)->setParamList((yyvsp[-3].SymbolInfo)->getParamList());
		(yyval.SymbolInfo)->insertParameter((yyvsp[-1].SymbolInfo));

		(yyval.SymbolInfo)->setStackOffset((yyvsp[-3].SymbolInfo)->getStackOffset()+2);

		(yyval.SymbolInfo)->setLineCount((yyvsp[-3].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"arguments","arguments COMMA logic_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[-3].SymbolInfo)->getRoot());
		insertTerminal((yyval.SymbolInfo),(yyvsp[-1].SymbolInfo));
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		 
		

	}
#line 4149 "y.tab.c"
    break;

  case 88: /* arguments: logic_expression  */
#line 2129 "1905021.y"
                           {
		printGrammarRule("arguments","logic_expression");
		(yyval.SymbolInfo) = new symbolInfo("","arguments");
		(yyval.SymbolInfo)->setName(setupName({(yyvsp[0].SymbolInfo)}));
		(yyval.SymbolInfo)->insertParameter((yyvsp[0].SymbolInfo));
		(yyval.SymbolInfo)->setStackOffset(2);

		(yyval.SymbolInfo)->setLineCount((yyvsp[0].SymbolInfo)->getLineCount());
		string prseMessage = getReduceMessage((yyval.SymbolInfo)->getLineCount(),totalLine,"arguments","logic_expression");
		(yyval.SymbolInfo)->setRoot(prseMessage);
		(yyval.SymbolInfo)->getRoot()->nodeList.push_back((yyvsp[0].SymbolInfo)->getRoot());

		
		

	}
#line 4170 "y.tab.c"
    break;

  case 89: /* LCURL_: LCURL  */
#line 2147 "1905021.y"
               {
	(yyval.SymbolInfo) = (yyvsp[0].SymbolInfo);
	symblTable->enterScope();
	int offset = 2;
	
	for(int i=symbolInfoArguments->getParamList().size()-1; i>=0; i--){
		auto SymbolInfo = symbolInfoArguments->getParamList()[i];
		if(SymbolInfo->getName() == "err") continue;
		if(SymbolInfo->getTypeSpecifier() == "VOID"){
			SymbolInfo->setTypeSpecifier("error");
		}
		offset+=2;
		SymbolInfo->setStackOffset(offset);
		bool insertSuccess = symblTable->insert(SymbolInfo);
		if(!insertSuccess){
			offset -= 2;
			printError("Redefinition of parameter",SymbolInfo->getName());
		}
	}
	symbolInfoArguments->setParamList({});

}
#line 4197 "y.tab.c"
    break;


#line 4201 "y.tab.c"

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

#line 2171 "1905021.y"

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
	asmcodeout.open("asmcode.asm");
	
	

	yyin=fp;
	yyparse();
	

	//parseTree->setSpace(0);
	//preOrderTraversal(parseTree);
	
	symblTable->printAllScopeTable(logout);
	logout<<"Total Lines: "<<totalLine<<endl;
	logout<<"Total Errors: "<<totalError<<endl;
	removeSymbolTable();
	
	

	fclose(yyin);
	logout.close();
	errorout.close();
	//parsetreeout.close();
	asmcodeout.close();
	
	return 0;
}

void insertTerminal(symbolInfo* lsInfo,symbolInfo* sInfo){
	string parseMessage = getTerminalReduceMessage(sInfo->getLineCount(), sInfo->getTypeSpecifier(),sInfo->getName());
	TreeNode* terminalNode = new TreeNode(parseMessage);
	lsInfo->getRoot()->nodeList.push_back(terminalNode);
}
