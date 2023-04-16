%code requires{
	#include <bits/stdc++.h>
}

%{
#include <bits/stdc++.h>
#include <typeinfo>
#include "1905021_symbolTable.h"

using namespace std;

ofstream parsetreeout;
ofstream logout;
ofstream errorout;


symbolTable* symblTable = new symbolTable(11);
symbolInfo* symbolInfoArguments = new symbolInfo();
TreeNode* parseTree = nullptr;


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


%}


%error-verbose

%union{
	symbolInfo* SymbolInfo;
}
%token<SymbolInfo> IF ELSE SWITCH CASE DEFAULT CONTINUE LOWER_THAN_ELSE FOR WHILE DO BREAK INT FLOAT DOUBLE CHAR VOID RETURN PRINTLN CONST_INT CONST_FLOAT CONST_CHAR ID ADDOP MULOP RELOP LOGICOP NOT ASSIGNOP INCOP DECOP BITOP LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON 
%type<SymbolInfo> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments LCURL_

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : program{
		//write your code in this block in all the similar blocks below
		printGrammarRule("start","program");
		$$ = new symbolInfo("","start");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"start","program");
		parseTree = new TreeNode(prseMessage);
		parseTree->nodeList.push_back($1->getRoot());

		
		
		
	}
	;

program : program unit {
		printGrammarRule("program","program unit");
		$$ = new symbolInfo("","program");
		$$->setName(setupName({$1}));
		
		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"program","program unit");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		$$->getRoot()->nodeList.push_back($2->getRoot());

		  

		 

		
	}
	| unit {
		printGrammarRule("program","unit");
		$$ = new symbolInfo("","program");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"program","unit");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		 
		
	}
	;
	
unit : var_declaration {
		printGrammarRule("unit","var_declaration");
		$$ = new symbolInfo("","unit");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"unit","var_declaration");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		
	}
    | func_declaration {
		printGrammarRule("unit","func_declaration");
		$$ = new symbolInfo("","unit");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"unit","func_declaration");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
    | func_definition {
		printGrammarRule("unit","func_definition");
		$$ = new symbolInfo("","unit");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"unit","func_definition");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		
	}
	| error {
		yyclearin;
		yyerrok;
		errorout<<"Line# "<<totalLine<<": "<<"Syntax error at unit"<<"\n";
		$$ = new symbolInfo("","unit");
		$$->setName("err");
	}
    ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
		printGrammarRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$ = new symbolInfo("","func_declaration");
		$2->setMethodDeclaration(true);
		$2->setParamList($4->getParamList());
		$2->setTypeSpecifier($1->getTypeSpecifier());
		symbolInfoArguments->setParamList({});
		$$->setName(setupName({$1}));

		bool insertSuccess = symblTable->insert($2);
		if(!insertSuccess){
			printError("Redefinition of function",$2->getName());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		$$->getRoot()->nodeList.push_back($4->getRoot());
		insertTerminal($$,$5);
		insertTerminal($$,$6);
		
		 
		 
		
		
	}
	| type_specifier ID LPAREN error RPAREN SEMICOLON {
		printGrammarRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$ = new symbolInfo("","func_declaration");
		$2->setMethodDeclaration(true);
		// $2->setParamList($4->getParamList());
		$2->setTypeSpecifier($1->getTypeSpecifier());
		symbolInfoArguments->setParamList({});

		bool insertSuccess = symblTable->insert($2);
		if(!insertSuccess){
			printError("Redefinition of function",$2->getName());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		$$->getRoot()->nodeList.push_back($5->getRoot());
		insertTerminal($$,$6);

		 
		 
		
		
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON {
		printGrammarRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
		$$ = new symbolInfo("","func_declaration");
		$2->setMethodDeclaration(true);
		$2->setTypeSpecifier($1->getTypeSpecifier());

		bool insertSuccess = symblTable->insert($2);
		if(!insertSuccess){
			printError("Redefinition of function",$2->getName());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		insertTerminal($$,$4);
		insertTerminal($$,$5);

		 
		 
		 
		
	}
	;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {insertFunctionIntoScopeTable($2,$1); } compound_statement {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new symbolInfo("","func_definition");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		$$->getRoot()->nodeList.push_back($4->getRoot());
		insertTerminal($$,$5);
		$$->getRoot()->nodeList.push_back($7->getRoot());
		
		 
		 
		

	}
	| type_specifier ID LPAREN error RPAREN { insertFunctionIntoScopeTable($2,$1); } compound_statement {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new symbolInfo("","func_definition");
		printSyntaxError("Syntax error at parameter list of function definition");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		insertTerminal($$,$5);
		$$->getRoot()->nodeList.push_back($7->getRoot());

		 
		 
		
		
	
	}
	| type_specifier ID LPAREN RPAREN {insertFunctionIntoScopeTable($2,$1); } compound_statement {
		printGrammarRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		$$ = new symbolInfo("","func_definition");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		insertTerminal($$,$4);
		$$->getRoot()->nodeList.push_back($6->getRoot());

		 
		 
		

	}
 	;				


parameter_list  : parameter_list COMMA type_specifier ID {
		printGrammarRule("parameter_list","parameter_list COMMA type_specifier ID");
		$$ = new symbolInfo("","parameter_list");
		$$->setParamList($1->getParamList());
		$4->setTypeSpecifier($3->getTypeSpecifier());
		$$->insertParameter($4);
		foundVoidTypeSpecifier($3);
		symbolInfoArguments->setParamList($$->getParamList());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"parameter_list","parameter_list COMMA type_specifier ID");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);

		 
		

		 
		


	}
	| parameter_list COMMA type_specifier {
		printGrammarRule("parameter_list","parameter_list COMMA type_specifier");
		$$ = new symbolInfo("","parameter_list");
		symbolInfo* onlyID = new symbolInfo("","ID");
		onlyID->setTypeSpecifier($3->getTypeSpecifier());
		$$->setParamList($1->getParamList());
		$$->insertParameter(onlyID);
		foundVoidTypeSpecifier($3);
		symbolInfoArguments->setParamList($$->getParamList());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"parameter_list","parameter_list COMMA type_specifier");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 
		
		
		

	}
 	| type_specifier ID {
		printGrammarRule("parameter_list","type_specifier ID");
		$$ = new symbolInfo("","parameter_list");
		$2->setTypeSpecifier($1->getTypeSpecifier());
		$$->insertParameter($2);
		foundVoidTypeSpecifier($1);
		symbolInfoArguments->setParamList($$->getParamList());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"parameter_list","type_specifier ID");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);

		  
		
		

	}
	| type_specifier {
		printGrammarRule("parameter_list","type_specifier");
		$$ = new symbolInfo("","parameter_list");
		$$->setName(setupName({$1}));
		symbolInfo* onlyID = new symbolInfo("","ID");
		onlyID->setTypeSpecifier($1->getTypeSpecifier());
		$$->insertParameter(onlyID);
		foundVoidTypeSpecifier($1);
		symbolInfoArguments->setParamList($$->getParamList());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"parameter_list","type_specifier");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		
		

	}
 	;

 		
compound_statement : LCURL_ statements RCURL {
		printGrammarRule("compound_statement","LCURL statements RCURL");
		$$ = new symbolInfo("","compound_statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"compound_statement","LCURL statements RCURL");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		$$->getRoot()->nodeList.push_back($2->getRoot());
		insertTerminal($$,$3);
		
		
		 

		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

		 
		

	}
	| LCURL_ error RCURL {
		printGrammarRule("compound_statement","LCURL statements RCURL");
		$$ = new symbolInfo("","compound_statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"compound_statement","LCURL statements RCURL");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$3);

		
		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

		  



	}
 	| LCURL_ RCURL {
		printGrammarRule("compound_statement","LCURL RCURL");
		$$ = new symbolInfo("","compound_statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"compound_statement","LCURL RCURL");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		

		symblTable->printAllScopeTable(logout);
		symblTable->exitScope();

		  

	}
 	;
 		    
var_declaration : type_specifier declaration_list SEMICOLON {
		printGrammarRule("var_declaration","type_specifier declaration_list SEMICOLON");
		$$ = new symbolInfo("","var_declaration");

		if(!foundVoidTypeSpecifier($1)){
			for(auto SymbolInfo:$2->getDeclarationList()){
				SymbolInfo->setTypeSpecifier($1->getTypeSpecifier());
				bool insertSuccess = symblTable->insert(SymbolInfo);
				if(!insertSuccess){
					printError("Conflicting types for",SymbolInfo->getName());
				}
			}
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"var_declaration","type_specifier declaration_list SEMICOLON");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		$$->getRoot()->nodeList.push_back($2->getRoot());
		insertTerminal($$,$3);

		 
		
	}
	| type_specifier error SEMICOLON {
		printGrammarRule("var_declaration","type_specifier declaration_list SEMICOLON");
		$$ = new symbolInfo("","var_declaration");
		$$->setName("err");
		printSyntaxError("Syntax error at declaration list of variable declaration");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"var_declaration","type_specifier declaration_list SEMICOLON");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$3);

		  
		

		

	}
 	;
 		 
type_specifier	: INT {
		printGrammarRule("type_specifier","INT");
		$$ = new symbolInfo("","type_specifier");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"type_specifier","INT");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		
		
		
	}
 	| FLOAT {
		printGrammarRule("type_specifier","FLOAT");
		$$ = new symbolInfo("","type_specifier");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"type_specifier","FLOAT");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		
		
	}
 	| VOID {
		printGrammarRule("type_specifier","VOID");
		$$ = new symbolInfo("","type_specifier");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"type_specifier","VOID");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		
		
	}
 	;
 		
declaration_list : declaration_list COMMA ID {
		printGrammarRule("declaration_list","declaration_list COMMA ID");
		$$ = new symbolInfo("","declaration_list");
		$$->setDeclarationList($1->getDeclarationList());
		$$->insertDeclaration($3);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"declaration_list","declaration_list COMMA ID");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);

		
		 
		

	}
 	| declaration_list COMMA ID LSQUARE CONST_INT RSQUARE {
		printGrammarRule("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		$$ = new symbolInfo("","declaration_list");
		$$->setDeclarationList($1->getDeclarationList());
		$3->setArray(true);
		$$->insertDeclaration($3);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		insertTerminal($$,$4);
		insertTerminal($$,$5);
		insertTerminal($$,$6);

		 
		 
		   
		

	}
 	| ID {
		printGrammarRule("declaration_list","ID");
		$$ = new symbolInfo("","declaration_list");
		$$->setName(setupName({$1}));
		$$->insertDeclaration($1);
		
		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"declaration_list","ID");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		

	}
 	| ID LSQUARE CONST_INT RSQUARE {
		printGrammarRule("declaration_list","ID LSQUARE CONST_INT RSQUARE");
		$$ = new symbolInfo("","declaration_list");
		$1->setArray(true);
		$$->insertDeclaration($1);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"declaration_list","ID LSQUARE CONST_INT RSQUARE");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		insertTerminal($$,$4);	
		
		 
		
	}
 	;
 		  
statements : statement {
		printGrammarRule("statements","statement");
		$$ = new symbolInfo("","statements");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statements","statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
	| statements statement {
		printGrammarRule("statements","statements statement");
		$$ = new symbolInfo("","statements");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statements","statements statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		$$->getRoot()->nodeList.push_back($2->getRoot());
		
		 

	}
	;
	   
statement : var_declaration {
		printGrammarRule("statement","var_declaration");
		$$ = new symbolInfo("","statement");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","var_declaration");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		
		

	}
	| expression_statement {
		printGrammarRule("statement","expression_statement");
		$$ = new symbolInfo("","statement");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","expression_statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
	| compound_statement {
		printGrammarRule("statement","compound_statement");
		$$ = new symbolInfo("","statement");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","compound_statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		printGrammarRule("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$ = new symbolInfo("","statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		$$->getRoot()->nodeList.push_back($4->getRoot());
		$$->getRoot()->nodeList.push_back($5->getRoot());
		insertTerminal($$,$6);
		$$->getRoot()->nodeList.push_back($7->getRoot());

		 
		 
		

	}
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement");
		$$ = new symbolInfo("","statement");
		
		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);
		$$->getRoot()->nodeList.push_back($5->getRoot());

		  
		 
		 
		
	}
	| IF LPAREN expression RPAREN statement ELSE statement {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$ = new symbolInfo("","statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);
		$$->getRoot()->nodeList.push_back($5->getRoot());
		insertTerminal($$,$6);
		$$->getRoot()->nodeList.push_back($7->getRoot());

		 
		 
		

		

	}
	| WHILE LPAREN expression RPAREN statement {
		printGrammarRule("statement","WHILE LPAREN expression RPAREN statement");
		$$ = new symbolInfo("","statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","WHILE LPAREN expression RPAREN statement");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);
		$$->getRoot()->nodeList.push_back($5->getRoot());

		 
		 
		 
		
		

	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON {
		printGrammarRule("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = new symbolInfo("","statement");
		if(!symblTable->lookup($3->getName())) {
			printError("Undeclared variable",$3->getName());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		insertTerminal($$,$3);
		insertTerminal($$,$4);
		insertTerminal($$,$5);

		 
		  
		
		

	}
	| RETURN expression SEMICOLON {
		printGrammarRule("statement","RETURN expression SEMICOLON");
		$$ = new symbolInfo("","statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","RETURN expression SEMICOLON");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		$$->getRoot()->nodeList.push_back($2->getRoot());
		insertTerminal($$,$3);

		 
		  
		
		

	}
	;
	  
expression_statement : SEMICOLON {
		printGrammarRule("expression_statement","SEMICOLON");
		$$ = new symbolInfo("","expression_statement");
		$$->setName(setupName({$1}));

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"expression_statement","SEMICOLON");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		
		

	}			
	| expression SEMICOLON {
		printGrammarRule("expression_statement","expression SEMICOLON");
		$$ = new symbolInfo("","expression_statement");
		$$->setTypeSpecifier($1->getTypeSpecifier());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"expression_statement","expression SEMICOLON");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);

		 
		

	} 
	| error SEMICOLON {
		yyclearin;
		yyerrok;
		printSyntaxError("Syntax error at expression of expression statement");
		$$ = new symbolInfo("","expression_statement");
		$$->setName("err");

		$$->setLineCount($2->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"expression_statement","expression SEMICOLON");
		$$->setRoot(prseMessage);
		insertTerminal($$,$2);

		
		
	}
	;
	  
variable : ID {
		printGrammarRule("variable","ID");
		$$ = new symbolInfo("","variable");
		$$->setName(setupName({$1}));
		auto lookSymbol = symblTable->lookup($1->getName());
		if(!lookSymbol){
			printError("Undeclared variable",$1->getName());
			$$->setTypeSpecifier("error");
		}
		else if(lookSymbol->isArray()){
			errorout<<"Line# "<<totalLine<<": "<<"Type mismatch "<<"'"<<$1->getName()<<"'"<<" is an array"<<"\n";
			totalError++;
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier(lookSymbol->getTypeSpecifier());
			$$->setArray(lookSymbol->isArray());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"variable","ID");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		


	}	
	| ID LSQUARE expression RSQUARE {
		printGrammarRule("variable","ID LSQUARE expression RSQUARE");
		$$ = new symbolInfo("","variable");

		auto lookSymbol = symblTable->lookup($1->getName());
		if(!lookSymbol){
			printError("Undeclared variable",$1->getName());
		}
		else if(!lookSymbol->isArray()){
			errorout<<"Line# "<<totalLine<<": "<<"'"<<$1->getName()<<"'"<<" is not an array"<<"\n";
			totalError++;
			$$->setTypeSpecifier(lookSymbol->getTypeSpecifier());
		}
		else{
			$$->setTypeSpecifier(lookSymbol->getTypeSpecifier());
		}
		if($3->getTypeSpecifier() != "CONST_INT" and $3->getTypeSpecifier() != "INT"){
			printSyntaxError("Array subscript is not an integer");
			
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"variable","ID LSQUARE expression RSQUARE");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);

		 
		
		
		

	} 
	;
	 
expression : logic_expression {
		printGrammarRule("expression","logic_expression");
		$$ = new symbolInfo("","expression");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"expression","logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}	
	| variable ASSIGNOP logic_expression {
		printGrammarRule("expression","variable ASSIGNOP logic_expression");
		$$ = new symbolInfo("","expression");

		// $$->setTypeSpecifier($1->getTypeSpecifier());
		if($3->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if($1->getTypeSpecifier() == "FLOAT" and $3->getTypeSpecifier() == "INT"){

		}
		else if($1->getTypeSpecifier() != $3->getTypeSpecifier() and $1->getTypeSpecifier() != "error" and $3->getTypeSpecifier() != "error"){
			printSyntaxError("Warning: possible loss of data in assignment of FLOAT to INT");
			
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"expression","variable ASSIGNOP logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 


		

	}	
	;
			
logic_expression : rel_expression {
		printGrammarRule("logic_expression","rel_expression");
		$$ = new symbolInfo("","logic_expression");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"logic_expression","rel_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		
		

	}	
	| rel_expression LOGICOP rel_expression {
		printGrammarRule("logic_expression","rel_expression LOGICOP rel_expression");
		$$ = new symbolInfo("","logic_expression");
		$$->setTypeSpecifier("INT");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"logic_expression","rel_expression LOGICOP rel_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 
		
		

	} 	
	;
			
rel_expression : simple_expression {
		printGrammarRule("rel_expression","simple_expression");
		$$ = new symbolInfo("","rel_expression");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"rel_expression","simple_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}	 
	| simple_expression RELOP simple_expression {
		printGrammarRule("rel_expression","simple_expression RELOP simple_expression");
		$$ = new symbolInfo("","rel_expression");

		if($1->getTypeSpecifier() == "VOID" or $3->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier("INT");
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"rel_expression","simple_expression RELOP simple_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 
		

	}	
	;
				
simple_expression : term {
		printGrammarRule("simple_expression","term");
		$$ = new symbolInfo("","simple_expression");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"simple_expression","term");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
	| simple_expression ADDOP term {
		printGrammarRule("simple_expression","simple_expression ADDOP term");
		$$ = new symbolInfo("","simple_expression");
		$$->setTypeSpecifier(typeCast($1,$3));
		if($3->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"simple_expression","simple_expression ADDOP term");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 
		  

	} 
	;
					
term : unary_expression {
		printGrammarRule("term","unary_expression");
		$$ = new symbolInfo("","term");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"term","unary_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		
		
		
		

	}
    |  term MULOP unary_expression {
		printGrammarRule("term","term MULOP unary_expression");
		$$ = new symbolInfo("","term");
		$$->setTypeSpecifier(typeCast($1,$3));

		if($3->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if($2->getName() == "%" and $3->getName() == "0"){
			printSyntaxError("Warning: division by zero");
			$$->setTypeSpecifier("error");
		}
		else if($2->getName() == "%" and ($1->getTypeSpecifier() != "INT" or $3->getTypeSpecifier() != "INT") ){
			printSyntaxError("Operands of modulus must be integers");
			$$->setTypeSpecifier("error");
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"term","term MULOP unary_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 

	}
    ;

unary_expression : ADDOP unary_expression {
		printGrammarRule("unary_expression","ADDOP unary_expression");
		$$ = new symbolInfo("","unary_expression");
		if($2->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier($2->getTypeSpecifier());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"unary_expression","ADDOP unary_expression");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		$$->getRoot()->nodeList.push_back($2->getRoot());

		  


	}	 
	| NOT unary_expression {
		printGrammarRule("unary_expression","NOT unary_expression");
		$$ = new symbolInfo("","unary_expression");
		if($2->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier("INT");
		}
		
		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"unary_expression","NOT unary_expression");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		$$->getRoot()->nodeList.push_back($2->getRoot());

		  
		  

	} 
	| factor {
		printGrammarRule("unary_expression","factor");
		$$ = new symbolInfo("","unary_expression");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"unary_expression","factor");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	} 
	;
	
factor : variable {
		printGrammarRule("factor","variable");
		$$ = new symbolInfo("","factor");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier($1->getTypeSpecifier());
		$$->setArray($1->isArray());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","variable");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	} 
	| ID LPAREN argument_list RPAREN {
		printGrammarRule("factor","ID LPAREN argument_list RPAREN");
		$$ = new symbolInfo("","factor");

		auto lookedSymbol = symblTable->lookup($1->getName());
		if(!lookedSymbol){
			// printError("Undeclared function",$1->getName());
		}
		else{
			$$->setTypeSpecifier(lookedSymbol->getTypeSpecifier());
			if(!lookedSymbol->isMethodDeclaration() and !lookedSymbol->isMethodDefinition()){
				printError("Undeclared function",$1->getName());
			}
			else if($3->getParamList().size() < lookedSymbol->getParamList().size()){
				printError("Too few arguments to function ",$1->getName());
			}
			else if($3->getParamList().size() > lookedSymbol->getParamList().size()){
				printError("Too few arguments to function ",$1->getName());
			}
			else{
				auto funcParamList = $3->getParamList();
				auto symblParamList = lookedSymbol->getParamList();
				for(int i=0; i<funcParamList.size(); ++i){
					if(funcParamList[i]->getTypeSpecifier() != symblParamList[i]->getTypeSpecifier()){
						printError("Type mismatch for argument "+to_string(i+1)+" of", $1->getName());
					}
					if(funcParamList[i]->isArray() and !symblParamList[i]->isArray()){
						printError("Type mismatch for argument "+to_string(i+1)+" of", $1->getName());
					}
					else if(!funcParamList[i]->isArray() and symblParamList[i]->isArray()){
						printError("Type mismatch for argument "+to_string(i+1)+" of", $1->getName());
					}

				}
			}
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","ID LPAREN argument_list RPAREN");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);

		 
		
		
		

	}
	| LPAREN expression RPAREN {
		printGrammarRule("factor","LPAREN expression RPAREN");
		$$ = new symbolInfo("","factor");
		$$->setTypeSpecifier($1->getTypeSpecifier());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","LPAREN expression RPAREN");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		$$->getRoot()->nodeList.push_back($2->getRoot());
		insertTerminal($$,$3);

		 
		
		
		

	}
	| CONST_INT {
		printGrammarRule("factor","CONST_INT");
		$$ = new symbolInfo("","factor");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier("INT");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","CONST_INT");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		
		
		 
		

	} 
	| CONST_FLOAT {
		printGrammarRule("factor","CONST_FLOAT");
		$$ = new symbolInfo("","factor");
		$$->setName(setupName({$1}));
		$$->setTypeSpecifier("FLOAT");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","CONST_FLOAT");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);

		
		

	}
	| variable INCOP {
		printGrammarRule("factor","variable INCOP");
		$$ = new symbolInfo("","factor");
		if($1->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier($1->getTypeSpecifier());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","variable INCOP");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);

		 
		
		

	} 
	| variable DECOP {
		printGrammarRule("factor","variable DECOP");
		$$ = new symbolInfo("","factor");
		if($1->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier($1->getTypeSpecifier());
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"factor","variable DECOP");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);

		 
		

	}
	;
	
argument_list : arguments {
		printGrammarRule("argument_list","arguments");
		$$ = new symbolInfo("","argument_list");
		$$->setName(setupName({$1}));
		$$->setParamList($1->getParamList());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"argument_list","arguments");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		
		

	}
	| arguments error {
		printGrammarRule("argument_list","arguments");
		yyclearin;
		yyerrok;
		printSyntaxError("Syntax error at parameter list of arguments");
		$$ = new symbolInfo("","argument_list");
		$$->setName(setupName({$1}));
		$$->setParamList($1->getParamList());

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"argument_list","arguments");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		

	}
	| {
		printGrammarRule("argument_list","arguments");
		$$ = new symbolInfo("","argument_list");


	}
	;
	
arguments : arguments COMMA logic_expression {
		printGrammarRule("arguments","arguments COMMA logic_expression");
		$$ = new symbolInfo("","arguments");
		$$->setParamList($1->getParamList());
		$$->insertParameter($3);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"arguments","arguments COMMA logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 
		

	}
	| logic_expression {
		printGrammarRule("arguments","logic_expression");
		$$ = new symbolInfo("","arguments");
		$$->setName(setupName({$1}));
		$$->insertParameter($1);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"arguments","logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
	;

LCURL_ : LCURL {
	$$ = $1;
	symblTable->enterScope();
	for(auto SymbolInfo:symbolInfoArguments->getParamList()){
		if(SymbolInfo->getName() == "err") continue;
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
 

%%
int main(int argc,char *argv[]){
	FILE *fp;

	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	logout.open("log.txt");
	errorout.open("error.txt");
	parsetreeout.open("parsetree.txt");
	

	yyin=fp;
	yyparse();

	parseTree->setSpace(0);
	preOrderTraversal(parseTree);

	symblTable->printAllScopeTable(logout);
	logout<<"Total Lines: "<<totalLine<<endl;
	logout<<"Total Errors: "<<totalError<<endl;
	removeSymbolTable();
	

	fclose(yyin);
	logout.close();
	errorout.close();
	parsetreeout.close();
	
	return 0;
}

void insertTerminal(symbolInfo* lsInfo,symbolInfo* sInfo){
	string parseMessage = getTerminalReduceMessage(sInfo->getLineCount(), sInfo->getTypeSpecifier(),sInfo->getName());
	TreeNode* terminalNode = new TreeNode(parseMessage);
	lsInfo->getRoot()->nodeList.push_back(terminalNode);
}