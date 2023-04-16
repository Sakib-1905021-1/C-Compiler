/*Consists of 3 sections separated by %% lines*/
%option noyywrap

%{
#include<bits/stdc++.h>
#include "1905021_symbolTable.h"
using namespace std;


int line_count = 1;

ofstream logout;
ofstream tokenout;

int bucketSize = 7;
symbolTable symblTable(bucketSize);
%}

KEYWORD if|else
WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]
NEWLINE \n

%%

{NEWLINE} {line_count++;}

{KEYWORD} {
    tokenout<<"<"<<yytext<<">\n";
    logout<<"Line# "<<line_count<<": Token "<<"<"<<yytext<<">"<<" Lexeme "<<yytext<<" found\n"; 
}

"+"		|

"-"		{
    tokenout<<"<ADDOP, "<<yytext<<">\n";
    logout<<"Line# "<<line_count<<": Token "<<"<ADDOP>"<<" Lexeme "<<yytext<<" found\n";
			//(tokenout,"<ADDOP,%s>",yytext);
			//(logout,"Line# %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		}
		
{DIGIT}+ 	{
    tokenout<<"<CONST_INT, "<<yytext<<">\n";
    logout<<"Line# "<<line_count<<": Token "<<"<CONST_INT>"<<" Lexeme "<<yytext<<" found\n";
	bool success = symblTable.insert(symbolInfo(yytext,"CONST_INT"),logout);
    if(success) symblTable.printAllScopeTable(logout);
    			//(tokenout,"<CONST_INT,%s>",yytext);
				//(logout,"Line# %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
			}
			

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout.open("log.txt");
	tokenout.open("token.txt");

	yyin= fin;
	yylex();
	fclose(yyin);

    symblTable.printAllScopeTable(logout);

    logout<<"Total lines: "<<line_count<<endl;

	tokenout.close();
    logout.close();
	return 0;
}

