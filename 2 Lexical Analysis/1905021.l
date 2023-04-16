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

ofstream logout;
ofstream tokenout;

int bucketSize = 10;
symbolTable symblTable(bucketSize);

int lineCount = 0;

void writelog(string token, string lexeme, bool newline=true){
    logout<<"Line# "<<totalLine<<": Token "<<"<"<<token<<">"<<" Lexeme "<<lexeme<<" found\n";
}

void writeToken(string token, string lexeme){
    tokenout<<"<"<<token<<", "<<lexeme<<">\n";
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

void errorFound(string errorMessage, string symbol){
    logout<<"Error at line# "<<totalLine<<": "<<errorMessage<<" "<<symbol<<"\n";
    totalError++;
}



string toUpper(string s){
    for(auto &ch:s) ch = toupper(ch);
    return s;
}

%}

/*=========Patterns=========*/
WHITESPACE [ \t\f\r\v]
KEYWORD if|for|do|int|float|void|switch|default|else|while|break|char|double|return|case|continue
LETTER [A-Za-z]
DIGIT [0-9]
EXP [Ee][-+]?[0-9]+
CONST_FLOAT {DIGIT}*(\.{DIGIT}+)?{EXP}?
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

/*=========Errors===========*/
/*INVALID_ID_SUFFIX_NUM_PREFIX_ERROR {CONST_FLOAT}+{IDENTIFIER}+*/



/*=========Translation Rules===========*/
/*=========Pattern Lines==============*/
%%


{KEYWORD} {
    writeKeyWord(toUpper(yytext),yytext);
}

{DIGIT}+ {
    writeConstNumber("CONST_INT",yytext);
}

{CONST_FLOAT} {
    writeConstNumber("CONST_FLOAT",yytext);
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
}
"*"|"/"|"%" {
    writeOperator("MULOP",yytext);
}
"++"|"--" {
    writeOperator("INCOP",yytext);
}
"<"|"<="|">"|">="|"=="|"!=" {
    writeOperator("RELOP",yytext);
}
"=" {
    writeOperator("ASSIGNOP",yytext);
}
"&&"|"||" {
    writeOperator("LOGICOP",yytext);
}
"&"|"|"|"^"|"<<"|">>" {
    writeOperator("BITOP",yytext);
}
"!" {
    writeOperator("NOT",yytext);
}
"(" {
    writeOperator("LPAREN",yytext);
}
")" {
    writeOperator("RPAREN",yytext);
}
"{" {
    writeOperator("LCURL",yytext);
    symblTable.enterScope();
}
"}" {
    writeOperator("RCURL",yytext);
    symblTable.exitScope();
}
"[" {
    writeOperator("LSQUARE",yytext);
}
"]" {
    writeOperator("RSQUARE",yytext);
}
"," {
    writeOperator("COMMA",yytext);
}
";" {
    writeOperator("SEMICOLON",yytext);
}

{IDENTIFIER} {
    writeID("ID",yytext);
    bool success = symblTable.insert(symbolInfo(yytext,"ID"),logout);
    if(success) symblTable.printAllScopeTable(logout);
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
	tokenout.open("1905021_token.txt");

	yyin= fin;
	yylex();
	fclose(yyin);

    symblTable.printAllScopeTable(logout);

    logout<<"Total lines: "<<totalLine<<endl;
    logout<<"Total errors: "<<totalError<<endl;

	logout.close();
    tokenout.close();
	return 0;
}