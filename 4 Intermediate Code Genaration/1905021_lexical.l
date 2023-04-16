%option noyywrap
/*forcing batch mode as it always reads from a file*/
%option batch 
%option yylineno

%x CHAR_STATE
%x STRING_STATE
%x SINGLE_LINE_COMMENT_STATE
%x MULTI_LINE_COMMENT_STATE

/*======== Declarations ========*/
/*========Rules Section========*/
%{
#include "bits/stdc++.h"
#include "1905021_symbolTable.h"
#include "y.tab.h" //system's input
#define TOKEN(t) return(t);


using namespace std;

int totalLine = 1;
int totalError = 0;
int line_count = 0;

string string_token;
string string_log;
string char_token;
string char_log;

int char_length;
string comment_log;

//variables declared here defined elsewhere
//extern YYSTYPE yylval;
//extern SymbolTable *table;
//void yyerror(char *);
extern ofstream parsetreeout;
extern ofstream logout;
extern ofstream errorout;



extern symbolTable* symblTable;


int lineCount = 0;

void writelog(string token, string lexeme, bool newline=true){
    logout<<"Line# "<<totalLine<<": Token "<<"<"<<token<<">"<<" Lexeme "<<lexeme<<" found\n";
}

void errorFound(string errorMessage, string symbol){
    //errorout<<"Error at line# "<<totalLine<<": "<<errorMessage<<" "<<symbol<<"\n";
    // totalError++;
}

void printError(string errorMessage, string error){
    errorout<<"Line# "<<totalLine<<": "<<errorMessage<<" "<<"'"<<error<<"'"<<"\n";
    totalError++;                                       
}

void printSyntaxError(string errorMessage){
    errorout<<"Line# "<<totalLine<<": "<<errorMessage<<"\n";
    totalError++;    

}


void writeToken(string token, string lexeme){
    //errorout<<"<"<<token<<", "<<lexeme<<">\n";
}

//====KeyWords====
void writeKeyWord(string token, string keyword){
    writeToken(token, keyword);
    writelog(token, keyword);
}

//====CONST_INT, CONST_FLOAT, CONST_CHAR====
void writeConstNumber(string token, string number){
    writeToken(token, number);
    writelog(token, number);
}

void writeOperator(string type, string symbol){
    writeToken(type, symbol);
    writelog(type, symbol);

}

void writeID(string token, string symbol){
    writeToken(token, symbol);
    writelog(token, symbol);

}

void writeChar(string token, string symbol){
    writeToken(token, symbol);
    writelog(token, symbol);

}

void writeString(string token, string symbol_token, string symbol_log){
    writeToken(token, symbol_token);
    writelog(token, symbol_log);

}


void writeComment(string token, string symbol){
    writelog(token,symbol);
}




string toUpper(string s){
    for(auto &ch:s) ch = toupper(ch);
    return s;
}

%}

/*=========Patterns=========*/
WHITESPACE [ \t\f\r\v]
DIGIT [0-9]
EXP [Ee][-+]?[0-9]+
CONST_FLOAT {DIGIT}*(\.{DIGIT}+)?{EXP}?
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

/*=========Errors===========*/
/*INVALID_ID_SUFFIX_NUM_PREFIX_ERROR {CONST_FLOAT}+{IDENTIFIER}+*/



/*=========Translation Rules===========*/
/*=========Pattern Lines==============*/
%%


"if" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","IF",totalLine);
    TOKEN(IF);
}
"else" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","ELSE",totalLine);
    TOKEN(ELSE);
}
"switch" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","SWITCH",totalLine);
    TOKEN(SWITCH);
}
"case" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","CASE",totalLine);
    TOKEN(CASE);
}
"default" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","DEFAULT",totalLine);
    TOKEN(DEFAULT);
}
"continue" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","CONTINUE",totalLine);
    TOKEN(CONTINUE);
}
"break" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","BREAK",totalLine);
    TOKEN(BREAK);
}
"for" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","FOR",totalLine);
    TOKEN(FOR);
}
"while" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","WHILE",totalLine);
    TOKEN(WHILE);
}
"do" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","DO",totalLine);
    TOKEN(DO);
}
"void" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","VOID",totalLine);
    TOKEN(VOID);
}
"int" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","INT",totalLine);
    TOKEN(INT);
}
"double" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","DOUBLE",totalLine);
    TOKEN(DOUBLE);
}
"float" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","FLOAT",totalLine);
    TOKEN(FLOAT);
}
"char" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","CHAR",totalLine);
    TOKEN(CHAR);
}
"printf" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","PRINTLN",totalLine);
    TOKEN(PRINTLN);
}
"return" {
    writeKeyWord(toUpper(yytext),yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "KEYWORD","RETURN",totalLine);
    TOKEN(RETURN);
}


{DIGIT}+ {
    writeConstNumber("CONST_INT",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "CONST_INT", "INT",totalLine);
    TOKEN(CONST_INT);
}

{CONST_FLOAT} {
    writeConstNumber("CONST_FLOAT",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "CONST_FLOAT", "FLOAT",totalLine);
    TOKEN(CONST_FLOAT);
}

([0-9]*\.[0-9]*\.[0-9\.Ee\+\-]*) {
    errorFound("TOO_MANY_DECIMAL_POINTS",yytext);
}

[0-9]*\.[0-9]*[Ee][\+\-]?([0-9\.\+\-eEe\.]*) {
    errorFound("ILLFORMED_NUMBER",yytext);
}

[0-9]*[Ee][\+\-]?([0-9\+\-Ee\.]*) {
    errorFound("ILLFORMED_NUMBER",yytext);
}

"+"|"-" {
    writeOperator("ADDOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "ADDOP","ADDOP",totalLine);
    TOKEN(ADDOP);
}
"*"|"/"|"%" {
    writeOperator("MULOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "MULOP","MULOP",totalLine);
    TOKEN(MULOP);
}
"++" {
    writeOperator("INCOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "INCOP","INCOP",totalLine);
    TOKEN(INCOP);
}
"--" {
    writeOperator("DECOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "DECOP","DECOP",totalLine);
    TOKEN(DECOP);
}
"<"|"<="|">"|">="|"=="|"!=" {
    writeOperator("RELOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "RELOP","RELOP",totalLine);
    TOKEN(RELOP);
}
"=" {
    writeOperator("ASSIGNOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "ASSIGNOP","ASSIGNOP",totalLine);
    TOKEN(ASSIGNOP);
}
"&&"|"||" {
    writeOperator("LOGICOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "LOGICOP","LOGICOP",totalLine);
    TOKEN(LOGICOP);
}
"&"|"|"|"^"|"<<"|">>" {
    writeOperator("BITOP",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "BITOP","BITOP",totalLine);
    TOKEN(BITOP);
}
"!" {
    writeOperator("NOT",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "NOT","NOT",totalLine);
    TOKEN(NOT);
}
"(" {
    writeOperator("LPAREN",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "LPAREN","LPAREN",totalLine);
    TOKEN(LPAREN);
}
")" {
    writeOperator("RPAREN",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "RPAREN","RPAREN",totalLine);
    TOKEN(RPAREN);
}
"{" {
    writeOperator("LCURL",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "LCURL","LCURL",totalLine);
    TOKEN(LCURL);
}
"}" {
    writeOperator("RCURL",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "RCURL","RCURL",totalLine);
    TOKEN(RCURL);
}
"[" {
    writeOperator("LSQUARE",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "LSQUARE","LSQUARE",totalLine);
    TOKEN(LSQUARE);
}
"]" {
    writeOperator("RSQUARE",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "RSQUARE","RSQUARE",totalLine);
    TOKEN(RSQUARE);
}
"," {
    writeOperator("COMMA",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "COMMA","COMMA",totalLine);
    TOKEN(COMMA);
}
";" {
    writeOperator("SEMICOLON",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "SEMICOLON","SEMICOLON",totalLine);
    TOKEN(SEMICOLON);
}

{IDENTIFIER} {
    writeID("ID",yytext);
    yylval.SymbolInfo = new symbolInfo(yytext, "ID","ID",totalLine);
    TOKEN(ID);
}

[0-9][A-Za-z0-9_]* {
    errorFound("INVALID_ID_SUFFIX_NUM_PREFIX",yytext);
}


' {
    char_length = 0;
    char_log = "'";
    char_token = "";
    BEGIN CHAR_STATE; /*switch to char mode*/
}

<CHAR_STATE>' {
    char_log +="'";
    if(char_length == 0){
        errorFound("EMPTY_CONST_CHAR",char_log);
    }
    else if(char_length == 1){
        writeChar("CONST_CHAR",char_token);
        yylval.SymbolInfo = new symbolInfo(char_token,"CONST_CHAR","CONST_CHAR",totalLine);
        TOKEN(CONST_CHAR);

    }
    else{
        errorFound("MULTICHAR_CONST_CHAR",char_log);
    }
    BEGIN INITIAL;
}

<CHAR_STATE>\\n {
    char_length++;
    char_token+="\n";
    char_log+="\\n";
}
<CHAR_STATE>\\t {
    char_length++;
    char_token+="\t";
    char_log+="\\t";
}
<CHAR_STATE>\\' {
    char_length++;
    char_token+="\'";
    char_log+="\\'";
}
<CHAR_STATE>\\\\ {
    char_length++;
    char_token+="\\";
    char_log+="\\\\";
}
<CHAR_STATE>\\a {
    char_length++;
    char_token+="\a";
    char_log+="\\a";
}
<CHAR_STATE>\\f {
    char_length++;
    char_token+="\f";
    char_log+="\\f";
}
<CHAR_STATE>\\r {
    char_length++;
    char_token+="\r";
    char_log+="\\r";
}
<CHAR_STATE>\\b {
    char_length++;
    char_token+="\b";
    char_log+="\\b";
}
<CHAR_STATE>\\v {
    char_length++;
    char_token+="\v";
    char_log+="\\v";
}
<CHAR_STATE>\\0 {
    char_length++;
    char_token+="\0";
    char_log+="\\0";
}
<CHAR_STATE>. {
    char_length++;
    char_token+=yytext[0];
    char_log+=yytext[0];
}
<CHAR_STATE>[\r]?\n {
    errorFound("UNFINISHED_CONST_CHAR",char_log);
    totalLine++;
    BEGIN INITIAL; /*return to regular mode*/
}

\" {
    line_count = 0;
    string_log = "\"";
    string_token = "";
    BEGIN STRING_STATE;
}
<STRING_STATE>"\"" {
    string_token+="";
    string_log+="\"";
    //writeString("STRING",string_token,string_log);
    if(line_count == 0) writeString("SINGLE LINE STRING", string_token, string_log);
    else writeString("MULTI LINE STRING", string_token, string_log);
    totalLine += line_count;
    BEGIN INITIAL;
}
<STRING_STATE>\\n {
    string_token += "\n";
    string_log += "\\n";
}
<STRING_STATE>\\t {
    string_token += "\t";
    string_log += "\\t";
}
<STRING_STATE>\\\\ {
    string_token += "\\";
    string_log += "\\\\";
}
<STRING_STATE>\\\" {
    string_token += "\"";
    string_log += "\\\"";

}
<STRING_STATE>\\a {
    string_token += "\a";
    string_log += "\\a";
}
<STRING_STATE>\\f {
    string_token += "\f";
    string_log += "\\f";
}
<STRING_STATE>\\r {
    string_token += "\r";
    string_log += "\\r";
}
<STRING_STATE>\\b {
    string_token += "\b";
    string_log += "\\b";
}
<STRING_STATE>\\v {
    string_token += "\v";
    string_log += "\\v";
}
<STRING_STATE>\\0 {
    string_token += "\0";
    string_log += "\\0";
}
<STRING_STATE>. {
    string_token += yytext;
    string_log += yytext;
}

<STRING_STATE>\\\r\n {
    string_log += "\\\r\n";
    line_count++;
}

<STRING_STATE>\\\n {
    string_log += "\\\n";
    line_count++;
}

<STRING_STATE>[\r]?\n {
    errorFound("UNFINISHED_STRING",string_log);
    line_count++;
    totalLine += line_count;
    BEGIN INITIAL;
}

<STRING_STATE><<EOF>> {
    errorFound("UNFINISHED_STRING",string_log);
    totalLine++;
    BEGIN INITIAL;

}




\/\* {
    comment_log = "/*";
    line_count = 0;
    BEGIN MULTI_LINE_COMMENT_STATE;
}
<MULTI_LINE_COMMENT_STATE>\*\/ {
    comment_log += "*/";
    writeComment("MULTI LINE COMMENT",comment_log);
    totalLine += line_count;
    BEGIN INITIAL;
}
<MULTI_LINE_COMMENT_STATE>\n {
    comment_log += "\n";
    line_count++;
}
<MULTI_LINE_COMMENT_STATE>\r {
    comment_log += "\r";
}
<MULTI_LINE_COMMENT_STATE>. {
    comment_log += yytext;
}
<MULTI_LINE_COMMENT_STATE><<EOF>> {
    errorFound("UNFINISHED_COMMENT",comment_log);
    totalLine += line_count;
    BEGIN INITIAL;
}

\/\/ {
    line_count = 0;
    comment_log = "//";
    BEGIN SINGLE_LINE_COMMENT_STATE;
}
<SINGLE_LINE_COMMENT_STATE>\\\r\n {
    comment_log += "\\\r\n";
    line_count++;
}
<SINGLE_LINE_COMMENT_STATE>\\\n {
    comment_log += "\\\n";
    line_count++;
}
<SINGLE_LINE_COMMENT_STATE>\\ {
    comment_log += "\\";
}
<SINGLE_LINE_COMMENT_STATE>. {
    comment_log += yytext;
}
<SINGLE_LINE_COMMENT_STATE>[\r]?\n {
    writeComment("SINGLE LINE COMMENT",comment_log);
    line_count++;
    totalLine += line_count;
    BEGIN INITIAL;
}
<SINGLE_LINE_COMMENT_STATE><<EOF>> {
    errorFound("UNFINISHED_COMMENT",comment_log);
    totalLine += line_count;
    BEGIN INITIAL;
}







{WHITESPACE}+ {}
. {
    errorFound("UNRECOGNIZED_CHAR",yytext);
}

"\n" {
    totalLine++;
}

%%

/*
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
	
	logout.open("1905021_log.txt");
	errorout.open("1905021_token.txt");

	yyin= fin;
	yylex();
	fclose(yyin);

    symblTable.printAllScopeTable(logout);

    logout<<"Total lines: "<<totalLine<<endl;
    logout<<"Total errors: "<<totalError<<endl;

	logout.close();
    errorout.close();
	return 0;
}
*/