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
int LABEL_COUNTER = 0;
int getLabelCounter(){
	
	return LABEL_COUNTER;
}
string newLabel(){
	LABEL_COUNTER++;
	return "label"+to_string(LABEL_COUNTER);
}

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


%}


%error-verbose

%union{
	symbolInfo* SymbolInfo;
}
%token<SymbolInfo> IF ELSE SWITCH CASE DEFAULT CONTINUE LOWER_THAN_ELSE FOR WHILE DO BREAK INT FLOAT DOUBLE CHAR VOID RETURN PRINTLN CONST_INT CONST_FLOAT CONST_CHAR ID ADDOP MULOP RELOP LOGICOP NOT ASSIGNOP INCOP DECOP BITOP LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON 
%type<SymbolInfo> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement IF_ expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments LCURL_

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

start : {
		asmcodeout<<"\n.MODEL SMALL\n.STACK 1000H\n.CODE"<<"\n";
		asmcodeout<<"\nnew_line proc\npush ax\npush dx\nmov ah,2\nmov dl,0AH\nint 21h\nmov dl,0DH\nint 21h\npop dx\npop ax\nret\nnew_line endp\n";
		asmcodeout<<"\nprintln proc ;print what is in ax\npush ax\npush bx\npush cx\npush dx\npush si\nlea si, number\nmov bx,10\nadd si,4\ncmp ax,0\njnge negate\nprint:\nxor dx,dx\ndiv bx\nmov [si],dl\nadd [si],'0'\ndec si\ncmp ax,0\njne print\ninc si\nlea dx,si\nmov ah,9\nint 21h\npop si\npop dx\npop cx\npop bx\npop ax\nret\nnegate:\npush ax\nmov ah,2\nmov dl,'-'\nint 21h\npop ax\nneg ax\njmp print\nprintln endp";

		}
		
		program{
		//write your code in this block in all the similar blocks below
		printGrammarRule("start","program");
		$$ = new symbolInfo("","start");
		$$->setName(setupName({$2}));

		$$->setLineCount($2->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"start","program");
		parseTree = new TreeNode(prseMessage);
		parseTree->nodeList.push_back($2->getRoot());

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
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {
		insertFunctionIntoScopeTable($2,$1);
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
		asmcodeout<<"\n"<<$2->getName()<<" PROC ;Line:"<<totalLine<<"Definition of function "<<$2->getName();
		if($2->getName() == "main"){
			asmcodeout<<"\nMOV DX,@DATA\nMOV DS,DX ;Line:"<<totalLine<<" Moving segment data to AX register";
		}
		asmcodeout<<"\nPUSH BP\nMOV BP,SP ;Moving StackPointer to BasePointer";
		retType = "";
		
		
		} compound_statement {
		printGrammarRule("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new symbolInfo("","func_definition");

		asmcodeout<<"\nADD SP,"<<decrementStack; //+to_string(-$7->getStackOffset())
		decrementStack = 0;
		incrementStack = -2;
		if($2->getName() == "main"){
			asmcodeout<<"\nPOP BP";
			asmcodeout<<"\nMOV AH,4CH\nINT 21h ;Line:"<<totalLine<<"return control to the OS";
		}
		else{
			asmcodeout<<"\nPOP BP\nRET"<<memsize*2;
			memsize = 0;
		}
		in_main_func--;
		asmcodeout<<"\n"<<$2->getName()<<" ENDP "<<"\n";

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
	| type_specifier ID LPAREN RPAREN {
		insertFunctionIntoScopeTable($2,$1);
		asmcodeout<<"\n"<<$2->getName()<<" PROC ;Line:"<<totalLine<<"Definition of function "<<$2->getName();
		if($2->getName() == "main"){
			asmcodeout<<"\nMOV DX,@DATA\nMOV DS,DX ;Line:"<<totalLine<<" Moving segment data to AX register";
		}
		asmcodeout<<"\nPUSH BP\nMOV BP,SP ;Moving StackPointer to BasePointer";
		retType = "";


		} compound_statement {
		printGrammarRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
		$$ = new symbolInfo("","func_definition");

		asmcodeout<<"\nADD SP,"<<decrementStack<<"; Line : "<<totalLine<<" SP = SP + stackOffset";
		//to_string(-$6->getStackOffset())
		decrementStack = 0;
		incrementStack = -2;
		if($2->getName() == "main"){
			asmcodeout<<"\nPOP BP";
			asmcodeout<<"\nMOV AH,4CH\nINT 21h ;Line:"<<totalLine<<" return control to OS";
		}
		else{
			asmcodeout<<"\nPOP BP\nRET "<<memsize*2;
			memsize = 0;
		}

		in_main_func--;
		asmcodeout<<"\n"<<$2->getName()<<" ENDP "<<endl;

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

		paramListLineNum = totalLine;
		parameterList.push_back($4->getName());


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

		$$->setStackOffset(symblTable->getCurrScopeTable()->getStackOffset());

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
		string temp = $5->getName();
		istringstream is(temp);
		int arrSize;
		is >> arrSize;

		$3->setSize(arrSize);
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

		string temp = $3->getName();
		istringstream is(temp);
		int arrSize;
		is>>arrSize;
		$1->setSize(arrSize);
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
	| FOR LPAREN expression_statement{
		asmcodeout<<"\nFOR_"<<forLoopCount<<": ; Line "<<totalLine<<" : Label of for loop";
		forLabelStack.push(forLoopCount);
		forLoopCount++;

	
	
		} 
		expression_statement{
		asmcodeout<<"\n; Line "<<totalLine<<" : Checking Conditional of for loop";
		asmcodeout<<"\nPUSH CX";
		asmcodeout<<"\nPOP AX";
		asmcodeout<<"\nCMP AX,1\nJNE FOR_BREAK_"<<forLabelStack.top();
		asmcodeout<<"\nJMP FOR_INTERNAL_"<<forLabelStack.top();
		asmcodeout<<"\nFOR_LOOP_INC_DEC_"<<forLabelStack.top()<<":";

		} 
		
		expression RPAREN{
		asmcodeout<<"\nJMP FOR_"<<forLabelStack.top()<<" ; Line "<<totalLine<<" : Jump to for loop";
		asmcodeout<<"\nFOR_INTERNAL_"<<forLabelStack.top()<<":";

		} 
		statement {
		asmcodeout<<"\nJMP FOR_LOOP_INC_DEC_"<<forLabelStack.top()<<" ; Line "<<totalLine<<" : Increment or Decrement in for loop";
		asmcodeout<<"\nFOR_BREAK_"<<forLabelStack.top()<<":";
		forLabelStack.pop();

		printGrammarRule("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$ = new symbolInfo("","statement");

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		$$->getRoot()->nodeList.push_back($5->getRoot());
		$$->getRoot()->nodeList.push_back($7->getRoot());
		insertTerminal($$,$8);
		$$->getRoot()->nodeList.push_back($10->getRoot());

		 
		 
		

	}
	| IF_ %prec LOWER_THAN_ELSE {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement");
		$$ = new symbolInfo("","statement");
		
		asmcodeout<<"\nIF_END_"<<conditionLabelStack.top()<<": ;Line "<<totalLine<<" conditional block end";
		conditionLabelStack.pop();
		
		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		

		  
		 
		 
		
	}
	| IF_ ELSE statement {
		printGrammarRule("statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$ = new symbolInfo("","statement");

		asmcodeout<<"\nIF_END_"<<conditionLabelStack.top()<<": ;Line "<<totalLine<<" conditional block end";
		conditionLabelStack.pop();


		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$->setRoot(prseMessage);
		
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());

		 
		 
		

		

	}
	| WHILE LPAREN{
		asmcodeout<<"\nWHILE_"<<whileLoopCount<<": ;Line "<<totalLine<<" : While loop begins";
		whileLabelStack.push(whileLoopCount);
		whileLoopCount++;

		} 
		expression RPAREN{
		asmcodeout<<"\nPUSH CX";
		asmcodeout<<"\nPOP AX";
		asmcodeout<<"\nCMP AX,0\nJE WHILE_BREAK_"<<whileLabelStack.top()<<": ;Line "<<totalLine<<" while loop ends";


		} 
		statement {
		printGrammarRule("statement","WHILE LPAREN expression RPAREN statement");
		$$ = new symbolInfo("","statement");

		asmcodeout<<"\nJMP WHILE_"<<whileLabelStack.top()<<" ;Line "<<totalLine<<" : goto while loop begin";
		asmcodeout<<"\nWHILE_BREAK_"<<whileLabelStack.top()<<": ; Line "<<totalLine<<" : while loop exits";
		whileLabelStack.pop();

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","WHILE LPAREN expression RPAREN statement");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($4->getRoot());
		insertTerminal($$,$5);
		$$->getRoot()->nodeList.push_back($7->getRoot());

		 
		 
		 
		
		

	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON {
		printGrammarRule("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = new symbolInfo("","statement");
		if(!symblTable->lookup($3->getName())) {
			printError("Undeclared variable",$3->getName());
		}
		else{
			auto lookedSymbol = symblTable->lookup($3->getName());
			$$->setStackOffset(lookedSymbol->getStackOffset());
			if($$->getStackOffset() != 0) $$->variableName = to_string($$->getStackOffset())+"[BP]";
			else $$->variableName = $3->getName(); //global var
			asmcodeout<<"\nMOV AX, "<<-(lookedSymbol->getStackOffset())<<"[BP]";
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

		asmcodeout<<"\nADD SP, "<<decrementStack;
		asmcodeout<<"\nPOP BP\nRET "<<memsize*2;
		asmcodeout<<"\n ; Line "<<totalLine<<" : Return back to caller function";
		memsize = 0;

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","RETURN expression SEMICOLON");
		$$->setRoot(prseMessage);
		insertTerminal($$,$1);
		$$->getRoot()->nodeList.push_back($2->getRoot());
		insertTerminal($$,$3);

		 
		  
		
		

	}
	;
IF_ : IF LPAREN expression RPAREN{
		conditionLabelStack.push(conditionCount);
		conditionCount++;
		asmcodeout<<"\nPUSH CX";
		asmcodeout<<"\nPOP AX";
		asmcodeout<<"\nCMP AX,1\nJNE IF_FALSE_"<<conditionLabelStack.top()<<"; Line "<<totalLine<<" : Branch Condition checked and jumped";


		} 
		statement{
		asmcodeout<<"\nJMP IF_END_"<<conditionLabelStack.top()<<" ;Line "<<totalLine<<" End of If Label";
		asmcodeout<<"\nIF_FALSE_"<<conditionLabelStack.top()<<": ;Line "<<totalLine<<" : Condition is false of If Label";

		$$ = new symbolInfo("","IF_");
		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"statement","IF LPAREN expression RPAREN statement ELSE statement");
		$$->setRoot(prseMessage);
		
		insertTerminal($$,$1);
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($3->getRoot());
		insertTerminal($$,$4);
		$$->getRoot()->nodeList.push_back($6->getRoot());
		} 
	  
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
			$$->setStackOffset(lookSymbol->getStackOffset());
			if($$->getStackOffset() != 0) $$->variableName = to_string($$->getStackOffset())+"[BP]";
			else $$->variableName = $1->getName();
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
	| variable{
		if($1->getName().find('[') != std::string::npos){
			asmcodeout<<"\nPUSH CX"<<"\n";
		}

		} 
		ASSIGNOP logic_expression {
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
		if($1->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString($1->getName(),splitterCh);
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
			auto lookSymbol = symblTable->lookup($1->getName());
			if(lookSymbol != nullptr)
				asmcodeout<<"\nMOV "<<lookSymbol->getStackOffset()<<"[BP],CX"<<" ; Line "<<totalLine<<" : Assign value to "<<$1->getName();
			else{
				int found = 0;
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == $1->getName()){
						found = 1;
						asmcodeout<<"\nMOV "<<$1->getName()<<" ,CX";
					}
				}
				
			}
		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"expression","variable ASSIGNOP logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$3);
		$$->getRoot()->nodeList.push_back($4->getRoot());

		 


		

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
	| rel_expression LOGICOP{
		asmcodeout<<"\nPUSH CX";

		} 
		rel_expression {
		printGrammarRule("logic_expression","rel_expression LOGICOP rel_expression");
		$$ = new symbolInfo("","logic_expression");
		$$->setTypeSpecifier("INT");

		if($2->getName() == "&&"){
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

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"logic_expression","rel_expression LOGICOP rel_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($4->getRoot());

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
	| simple_expression RELOP{
		asmcodeout<<"\nPUSH CX";

		} 
		simple_expression {
		printGrammarRule("rel_expression","simple_expression RELOP simple_expression");
		$$ = new symbolInfo("","rel_expression");

		if($1->getTypeSpecifier() == "VOID" or $4->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
			$$->setTypeSpecifier("error");
		}
		else{
			$$->setTypeSpecifier("INT");
		}

		if($2->getName() == "<"){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a < b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJL RELOP_LESS_THAN_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_LESS_THAN_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;
		}
		else if($2->getName() == "<="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a <= b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJLE RELOP_LESS_THAN_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_LESS_THAN_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if($2->getName() == ">"){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a > b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJG RELOP_GREATER_THAN_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_GREATER_THAN_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if($2->getName() == ">="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a >= b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJGE RELOP_GREATER_THAN_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_GREATER_THAN_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if($2->getName() == "=="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a == b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJE RELOP_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}
		else if($2->getName() == "!="){
			asmcodeout<<"; Line "<<totalLine<<"Whether (a != b)";
			asmcodeout<<"\nPOP AX";
			asmcodeout<<"\nCMP AX,CX";
			asmcodeout<<"\nJNE RELOP_NOT_EQUAL_"<<internalLabelCount;
			asmcodeout<<"\nMOV CX,0\nJMP RELOP_EXIT_"<<internalLabelCount;
			asmcodeout<<"\nRELOP_NOT_EQUAL_"<<internalLabelCount<<":\n";
			asmcodeout<<"\nMOV CX,1\nRELOP_EXIT_"<<internalLabelCount<<":\n";
			internalLabelCount++;

		}

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"rel_expression","simple_expression RELOP simple_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($4->getRoot());

		 
		

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
	| simple_expression ADDOP{
		asmcodeout<<"\nPUSH CX";

		} 
		term {
		printGrammarRule("simple_expression","simple_expression ADDOP term");
		$$ = new symbolInfo("","simple_expression");
		$$->setTypeSpecifier(typeCast($1,$4));
		if($4->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}

		if($2->getName() == "+"){
			asmcodeout<<"\nPOP AX\nADD AX,CX\nMOV CX,AX";
		}
		else if($2->getName() == "-"){
			asmcodeout<<"\nPOP AX\nSUB AX,CX\nMOV CX,AX";
		}



		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"simple_expression","simple_expression ADDOP term");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($4->getRoot());

		 
		  

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
    |  term MULOP{
		asmcodeout<<"\nPUSH CX";

		} 
		unary_expression {
		printGrammarRule("term","term MULOP unary_expression");
		$$ = new symbolInfo("","term");
		$$->setTypeSpecifier(typeCast($1,$4));

		if($4->getTypeSpecifier() == "VOID"){
			printSyntaxError("Void cannot be used in expression");
		}
		else if($2->getName() == "%" and $4->getName() == "0"){
			printSyntaxError("Warning: division by zero");
			$$->setTypeSpecifier("error");
		}
		else if($2->getName() == "%" and ($1->getTypeSpecifier() != "INT" or $4->getTypeSpecifier() != "INT") ){
			printSyntaxError("Operands of modulus must be integers");
			$$->setTypeSpecifier("error");
		}

		if($2->getName() == "*"){
			asmcodeout<<"\nPOP AX\nIMUL CX\nMOV CX,AX";
		}
		else if($2->getName() == "%"){
			asmcodeout<<"\nPOP AX\nCWD\nIDIV CX\n MOV CX,DX";
		}



		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"term","term MULOP unary_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$2);
		$$->getRoot()->nodeList.push_back($4->getRoot());

		 

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

		if($1->getName() == "-"){
			asmcodeout<<"\nPOP CX\nNEG CX\nPUSH CX"<<" ; Line "<<totalLine<<" : Negate the value of CX register";
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

		if($1->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString($1->getName(),splitterCh);
			string arrName = stringArr[0];
			symbolInfo* lookedSymbol = symblTable->lookup(arrName);
			
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookedSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV CX,PTR WORD[BP]\nPOP BP";
		}
		else{
			int found = 0;
			symbolInfo* lookedSymbol = symblTable->lookup($1->getName());
			if(lookedSymbol == nullptr){
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == $1->getName()){
						asmcodeout<<"\nMOV CX,"<<$1->getName();
						found = 1;

					}
				}
				
			}
			else{
				asmcodeout<<"\nMOV CX,"<<-(lookedSymbol->getStackOffset())<<"[BP]"<<" ; Line "<<totalLine<<" : Mov the value of "<<$1->getName()<<" to CX register";

			}
		}

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
				// printError("Undeclared function",$1->getName());
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

		asmcodeout<<"\nMOV AX,CX\nCALL "<<$1->getName()<<" ; Line "<<totalLine<<" : Call function "<<$1->getName();
		in_main_func++;


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

		asmcodeout<<"\nMOV CX,"<<$1->getName();

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

		asmcodeout<<"\nMOV CX,"<<$1->getName();

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

		if($1->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString($1->getName(),splitterCh);
			string arrName = stringArr[0];
			auto lookSymbol = symblTable->lookup(arrName);
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV CX,PTR WORD[BP]";
			asmcodeout<<"\nMOV AX,CX\nADD AX,1\nMOV PTR WORD [BP],AX\nPOP BP";
		}
		else{
			auto lookSymbol = symblTable->lookup($1->getName());
			int found = 0;
			if(lookSymbol == nullptr){
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == $1->getName()){
						asmcodeout<<"\nMOV CX,"<<$1->getName();
						asmcodeout<<"\nADD CX,1\nMOV "<<$1->getName()<<",CX";
					}
				}
			}
			else{
				asmcodeout<<"\nMOV CX,"<<-(lookSymbol->getStackOffset())<<"[BP]";
				asmcodeout<<"\nMOV AX,CX\nADD AX,1\nMOV "<<-(lookSymbol->getStackOffset())<<",AX";
			}
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

		if($1->getName().find('[') != std::string::npos){
			char splitterCh = '[';
			int counter = separateString($1->getName(),splitterCh);
			string arrName = stringArr[0];
			auto lookSymbol = symblTable->lookup(arrName);
			asmcodeout<<"\nPUSH BP";
			asmcodeout<<"\nSAL CX,1";
			asmcodeout<<"\nADD CX,"<<-(lookSymbol->getStackOffset());
			asmcodeout<<"\nADD BP,CX\nMOV CX,PTR WORD[BP]";
			asmcodeout<<"\nMOV AX,CX\nSUB AX,1\nMOV PTR WORD [BP],AX\nPOP BP";
		}
		else{
			auto lookSymbol = symblTable->lookup($1->getName());
			int found = 0;
			if(lookSymbol == nullptr){
				for(int i=0; i<globalVar.size(); ++i){
					if(globalVar[i].first == $1->getName()){
						asmcodeout<<"\nMOV CX,"<<$1->getName();
						asmcodeout<<"\nSUB CX,1\nMOV "<<$1->getName()<<",CX";
					}
				}
			}
			else{
				asmcodeout<<"\nMOV CX,"<<-(lookSymbol->getStackOffset())<<"[BP]";
				asmcodeout<<"\nMOV AX,CX\nSUB AX,1\nMOV "<<-(lookSymbol->getStackOffset())<<",AX";
			}
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

		asmcodeout<<"\nPUSH CX";
		$$->setStackOffset($1->getStackOffset());

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
	
arguments : arguments{
		asmcodeout<<"\nPUSH CX";

		} 
		COMMA logic_expression {
		printGrammarRule("arguments","arguments COMMA logic_expression");
		$$ = new symbolInfo("","arguments");
		$$->setParamList($1->getParamList());
		$$->insertParameter($3);

		$$->setStackOffset($1->getStackOffset()+2);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"arguments","arguments COMMA logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());
		insertTerminal($$,$3);
		$$->getRoot()->nodeList.push_back($4->getRoot());

		 
		

	}
	| logic_expression {
		printGrammarRule("arguments","logic_expression");
		$$ = new symbolInfo("","arguments");
		$$->setName(setupName({$1}));
		$$->insertParameter($1);
		$$->setStackOffset(2);

		$$->setLineCount($1->getLineCount());
		string prseMessage = getReduceMessage($$->getLineCount(),totalLine,"arguments","logic_expression");
		$$->setRoot(prseMessage);
		$$->getRoot()->nodeList.push_back($1->getRoot());

		
		

	}
	;

LCURL_ : LCURL {
	$$ = $1;
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