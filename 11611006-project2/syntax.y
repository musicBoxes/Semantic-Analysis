%{
	#include "tree.h"
	#define YYSTYPE struct treeNode*
	#include "list.h"
	
    #ifndef LEX
	#define LEX
	#include "lex.yy.c"
	#endif
	
	int childNum;
	int error_flag = 0;
	int arraySize_flag = 0;
	char errmsg[100];
	
	// temporary store
	struct treeNode* childNodeList[10];
	// global table
	struct FieldList* globalVariableTable;
	struct FieldList* varList;
	struct FieldList* funcList;
	
	Type baseType;
	void yyerror(char*);
	
	// return 0 if variable add successfully
	// return 1 means error
	int addVar(FieldList*, struct treeNode*, int);
	
	Type isValidAssign(struct treeNode *a, struct treeNode *b, int lineno);
	Type isValidOperation(struct treeNode *a, struct treeNode *b, int lineno);
	Type getExpType(struct treeNode* node, int lineno);
%}
%token TYPE ID CHAR FLOAT INT
%token STRUCT IF ELSE WHILE FOR RETURN 
%token DOT SEMI COMMA ASSIGN LT LE GT GE NE EQ 
%token PLUS MINUS MUL DIV AND OR NOT LP RP LB RB LC RC 
%token CS CE
%right ASSIGN NOT
%left OR AND LT LE GT GE EQ NE PLUS MINUS MUL DIV DOT LB RB LP RP
%%
Program: ExtDefList { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Program", @$.first_line); 
		//if (!error_flag) treePrint($$); 
	}
    ;
ExtDefList: ExtDef ExtDefList { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "ExtDefList", @$.first_line); }
    |  { $$=createEmpty(); }
    ;
ExtDef: Specifier ExtDecList SEMI { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "ExtDef", @$.first_line); 
	}
    | Specifier SEMI { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "ExtDef", @$.first_line); }
    | Specifier FunDec CompSt { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "ExtDef", @$.first_line); }
    | Specifier ExtDecList error { printf("Error type B at Line %d: Specifier ExtDecList error\n", @$.first_line); error_flag = 1; }
	;
ExtDecList: VarDec { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "ExtDecList", @$.first_line);
		addVar(varList, $1, @$.first_line);
	}
    | VarDec COMMA ExtDecList { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "ExtDecList", @$.first_line); 
		addVar(varList, $1, @$.first_line);
	}
    ;
Specifier: TYPE { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Specifier", @$.first_line); 
		baseType.category = PRIMITIVE;
		// "TYPE :"
		strcpy(baseType.name, $1->value+6);
		switch (baseType.name[0]){
			case 'i':
				baseType.primitive = INT;
				break;
			case 'f':
				baseType.primitive = FLOAT;
				break;
			case 'c':
				baseType.primitive = CHAR;
				break;
		}
		//printf("INT %d FLOAT %d CHAR %d: %d %s\n", INT, FLOAT, CHAR, baseType.primitive, baseType.name);
	}
    | StructSpecifier { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Specifier", @$.first_line); }
    ;
StructSpecifier: STRUCT ID LC DefList RC { childNum = 5; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; $$=createNode(childNum, childNodeList, "StructSpecifier", @$.first_line); }
    | STRUCT ID { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "StructSpecifier", @$.first_line); }
    ;
VarDec: ID { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "VarDec", @$.first_line); }
    | VarDec LB INT RB { childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "VarDec", @$.first_line); }
    ;
FunDec: ID LP VarList RP { 
		childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "FunDec", @$.first_line); 
		addFunc(funcList, $1, @1.first_line);
	}
    | ID LP RP { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "FunDec", @$.first_line); 
		addFunc(funcList, $1, @1.first_line);
	}
    | ID LP error { printf("Error type B at Line %d: Missing \")\"\n", @$.first_line); error_flag = 1; }
	;
VarList: ParamDec COMMA VarList { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "VarList", @$.first_line); }
    | ParamDec { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "VarList", @$.first_line); }
    ;
ParamDec: Specifier VarDec { 
		childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "ParamDec", @$.first_line); 
		addVar(varList, $2, @$.first_line);
	}
    ;
CompSt: LC DefList StmtList RC { childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "CompSt", @$.first_line); }
	| LC DefList StmtList error { printf("Error type B at Line %d: Missing \"}\"\n", @$.first_line); error_flag = 1; }
	| LC DefList StmtList Def StmtList DefStmtList RC { printf("Error type B at Line %d: Definition must at head.\n", @4.first_line); error_flag = 1; }
	;
DefStmtList: Def StmtList
	|
	;
StmtList: Stmt StmtList { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "StmtList", @$.first_line); }
    |  { $$=createEmpty(); }
//	| Def DefList { printf("Error type B at Line %d: Definition must at head.\n", @$.first_line); error_flag = 1; }
    ;
Stmt: Exp SEMI { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
    | CompSt { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
    | RETURN Exp SEMI { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		
	}
    | IF LP Exp RP Stmt { childNum = 5; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
    | IF LP Exp RP Stmt ELSE Stmt { childNum = 7; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; childNodeList[5]=$6; childNodeList[6]=$7; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
    | WHILE LP Exp RP Stmt { childNum = 5; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
//	| Exp error { printf("Error type B at Line %d: Exp error\n", @$.first_line); error_flag = 1; }
	| RETURN Exp error { printf("Error type B at Line %d: Missing \";\"\n", @$.first_line); error_flag = 1; } 
//	| RETURN error SEMI { printf("Error type B at Line %d: RETURN error SEMI\n", @$.first_line); error_flag = 1; } 
	| FOR LP Def ExpListEx SEMI ExpListEx RP Stmt { childNum = 8; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; childNodeList[5]=$6; childNodeList[6]=$7; childNodeList[7]=$8; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
	| FOR LP ExpListEx SEMI ExpListEx SEMI ExpListEx RP Stmt { childNum = 9; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; childNodeList[5]=$6; childNodeList[6]=$7; childNodeList[7]=$8; childNodeList[8]=$9; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); }
	;
DefList: Def DefList { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "DefList", @$.first_line); }
    |  { $$=createEmpty(); }
    ;
Def: Specifier DecList SEMI { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Def", @$.first_line); }
    | Specifier DecList error { printf("Error type B at Line %d: Missing \";\"\n", @$.first_line); error_flag = 1; }
	;
DecList: Dec { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "DecList", @$.first_line); }
    | Dec COMMA DecList { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "DecList", @$.first_line); }
    ;
Dec: VarDec { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Dec", @$.first_line); 
		addVar(varList, $1, @$.first_line);
	}
    | VarDec ASSIGN Exp { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Dec", @$.first_line); 
		addVar(varList, $1, @$.first_line);
		Type tmp = getExpType($3, @2.first_line);
		//Type *last = list_getLast(varList)->type;
		//printf("tmp %d %d last %d %d\n", tmp.category, tmp.primitive, last->category, last->primitive);
		if (!isSameType(&tmp, list_getLast(varList)->type)){
			error_flag = 1;
			printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", @2.first_line);
		}
	}
//	| VarDec ASSIGN error { printf("Error type B at Line %d: VarDec ASSIGN error\n", @$.first_line); error_flag = 1; }
	;
Exp: Exp ASSIGN Exp { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); 
		Type type = isValidAssign($1, $3, @2.first_line);
		if (type.category == DIFFERENT) {
			error_flag = 1;
			printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", @2.first_line);
		}
		if ($1->childNum == 1) {
			char str[5]; memset(str, 0, sizeof(str));
			memcpy(str, $1->child[0]->value, sizeof(char)*4);
			if (!strcmp(str, "INT:") || !strcmp(str, "CHAR") || !strcmp(str, "FLOA")){
				error_flag = 1;
				printf("Error type 6 at Line %d: rvalue on the left side of assignment operator\n", @1.first_line);
			}
		}
	}
    | Exp AND Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp OR Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp LT Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp LE Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp GT Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp GE Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp NE Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp EQ Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp PLUS Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp MINUS Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp MUL Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp DIV Exp { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | LP Exp RP { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | MINUS Exp { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | NOT Exp { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | ID LP Args RP { childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | ID LP RP { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp LB Exp RB { childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp DOT ID { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | ID { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); 
		if (list_findByName(varList, $1->value+4) == NULL) { //"ID: "
			error_flag = 1;
			printf("Error type 1 at Line %d: Variable '%s' is not defined\n", @$.first_line, $1->value+4);
		}
	}
    | INT { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | FLOAT { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | CHAR { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | ID LP Args error { printf("Error type B at Line %d: Missing \")\"\n", @$.first_line); error_flag = 1; }
//	| Exp ASSIGN error { printf("Error type B at Line %d: Exp ASSIGN error\n", @$.first_line); error_flag = 1; } // 20 reduce/reduce conflicts
	| error { /*printf("error\n"); yyerrok;*/ error_flag = 1; }
	;
ExpList: Exp { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "ExpList", @$.first_line); }
	| Exp COMMA ExpList { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "ExpList", @$.first_line); }
	;
ExpListEx: ExpList { $$=$1; }
	| { $$ = createEmpty(); }
	;
Args: Exp COMMA Args { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Args", @$.first_line); }
    | Exp { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Args", @$.first_line); }
    ;
%%

void yyerror(char* s){
	//printf("%s\n", s);
}

char* TypeToString(Type *type){
	char* res;
	switch (type->category){
		case PRIMITIVE:
			res = (char*)malloc(sizeof(char)*256);
			sprintf(res, "%s", type->name);
			return res;
			break;
		case ARRAY:
			res = ArrayToString(type->array);
			return res;
			break;
		case STRUCTURE:
			break;
	}
	return res;
}

char* ArrayToString(Array *array){
	char *res = (char*)malloc(sizeof(char)*256);
	sprintf(res, "array baseTypeName=%s size=%d", array->base->name, array->size);
	return res;
}

char *FieldListToString(FieldList* head){
	FieldList* cur = head->next;
	while (cur != NULL){
		printf("%s %s\n", cur->name, TypeToString(cur->type));
		cur = cur->next;
	}
}

int addVar(FieldList* head, struct treeNode* node, int lineno){
	// "ID: "
	if (list_findByName(head, node->child[0]->value+4) != NULL){
		error_flag = 1;
		printf("Error type 3 at Line %d: Variable '%s' is redefined\n", lineno, node->child[0]->value+4);
		return 1;
	}
	if (node->childNum == 1){ // just variable, not array
		FieldList* newItem = (FieldList*)malloc(sizeof(FieldList));
		newItem->type = (Type*)malloc(sizeof(Type));
		memcpy(newItem->type, &baseType, sizeof(Type));
		strcpy(newItem->name, node->child[0]->value+4);
		//printf("INT %d FLOAT %d CHAR %d: %d %s\n", INT, FLOAT, CHAR, baseType.primitive, baseType.name);
		//printf("INT %d FLOAT %d CHAR %d: %d %s\n", INT, FLOAT, CHAR, newItem->type->primitive, newItem->type->name);
		list_pushBack(head, newItem);
	}
	return 0;
}

int addFunc(FieldList* head, struct treeNode* node, int lineno){
	// "ID: "
	if (list_findByName(head, node->value+4) != NULL){
		error_flag = 1;
		printf("Error type 4 at Line %d: Function '%s' is redefined\n", lineno, node->value+4);
		return 1;
	}
	
	FieldList* newItem = (FieldList*)malloc(sizeof(FieldList));
	newItem->type = (Type*)malloc(sizeof(Type));
	memcpy(newItem->type, &baseType, sizeof(Type));
	strcpy(newItem->name, node->value+4);
	list_pushBack(head, newItem);
	
	return 0;
}

Type isValidAssign(struct treeNode *a, struct treeNode *b, int lineno){
	Type type_a, type_b;
	type_a = getExpType(a, lineno);
	type_b = getExpType(b, lineno);
	Type type;
	if (isSameType(&type_a, &type_b)){
		return type_a;
	}
	else {
		type.category = DIFFERENT;
		return type;
	}
}

Type isValidOperation(struct treeNode *a, struct treeNode *b, int lineno){
	Type type_a, type_b;
	type_a = getExpType(a, lineno);
	type_b = getExpType(b, lineno);
	if (type_a.category == IGNORE) return type_a;
	if (type_b.category == IGNORE) return type_b;
	Type type;
	if (type_a.category == PRIMITIVE && (type_a.primitive == INT || type_a.primitive == FLOAT) && isSameType(&type_a, &type_b)){
		return type_a;
	}
	else {
		error_flag = 1;
		printf("Error type 7 at Line %d: Invalid operation on non-number variables\n", lineno);
		type.category = DIFFERENT;
		return type;
	}
}

Type getExpType(struct treeNode* node, int lineno){
	Type type;
	switch (node->childNum){
		case 1: // ID INT CHAR FLOAT
			//printf("node value = %s\n", node->child[0]->value);
			switch (node->child[0]->value[0]){
				case 'I': // INT or ID
					if (node->child[0]->value[1] == 'D'){ // ID
						FieldList* var;
						if ((var = list_findByName(varList, node->child[0]->value+4)) != NULL){ //"ID: "
							return *(var->type);
						}
						else{ // not find this variable, just ignore it
							//printf("Ignore it!\n");
							//printf("node value = %s\n", node->value);
							type.category = IGNORE;
							return type;
						}
					}
					else { // INT
						type.category = PRIMITIVE;
						type.primitive = INT;
						return type;
					}
					break;
				case 'C': // CHAR
					type.category = PRIMITIVE;
					type.primitive = CHAR;
					return type;
					break;
				case 'F': // FLOAT
					type.category = PRIMITIVE;
					type.primitive = FLOAT;
					return type;
					break;
			}
			break;
		case 2: // only 'MINUS Exp' or 'NOT Exp'
			return getExpType(node->child[1], lineno);
			break;
		case 3:
			if (!strcmp(node->child[1]->value, "ASSIGN")){ // for ASSIGN operation, just ensure two Exp has same type
				return isValidAssign(node->child[0], node->child[2], lineno);
			}
			else{
				return isValidOperation(node->child[0], node->child[2], lineno);
			}
			break;
	}
}

int main(){
	varList = list_init();
	funcList = list_init();
    yyparse();
	printf("Variable List\n");
	FieldListToString(varList);
	printf("Function List\n");
	FieldListToString(funcList);
}