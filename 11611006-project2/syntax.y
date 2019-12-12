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
	int loop_flag = 0;
	char errmsg[100];
	
	// temporary store child node
	struct treeNode* childNodeList[10];
	
	// temporarily store a list of variable
	struct FieldList* tmpList;
	
	// global
	struct FieldList* globalVariableList;
	struct FieldList* globalStructList;
	
	// funcList is already global
	struct FieldList* funcList;
	
	// store all variable in {  }
	// each member is a List 
	// use '->vars' to get all variables
	struct FieldList* allTmpVarList;
	struct FieldList* structList;
	
	struct FieldList* retList;
	struct FieldList* funcArgs;
	
	struct FieldList* curFunc;
	
	char *varName; // record variable name when it is defined
	
	Type *baseType;
	Type *arrayType; 
	Type *funcRetType;
	
	void yyerror(char*);
	
	FieldList* validDecDefVar(char *name);
	FieldList* validUseVar(char *name);
	
	FieldList* varExist(char *name);
	
	// return 0 if variable add successfully
	// return 1 means error
	int addVar(FieldList*, struct treeNode*, int);
	int addFuncStruct(FieldList* head, struct treeNode* node, Type *type, int lineno);
	
	Type* isValidAssign(struct treeNode *a, struct treeNode *b, int lineno);
	Type* isValidOperation(struct treeNode *a, struct treeNode *b, char *operation, int lineno);
	Type* getExpTypePtr(struct treeNode* node, int lineno);
	Type* parseSpecifier(struct treeNode* node);
%}
%token TYPE ID CHAR FLOAT INT VOID
%token STRUCT IF ELSE WHILE FOR RETURN BREAK
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
		list_link(globalVariableList, tmpList);
		//list_link(globalStructList, structList);
	}
    | Specifier SEMI { childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "ExtDef", @$.first_line); }
    | Specifier FunDec CompSt { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "ExtDef", @$.first_line); 
		funcRetType = parseSpecifier($1);
		list_getLast(funcList)->type = funcRetType;
		FieldList* ret = retList->next;
		// delete member after checking
		while (ret != NULL){
			if (!isSameType(ret->type, funcRetType)){
				printf("Error type 8 at Line %d: Function’s return value type mismatches the declared type\n", ret->lineno);
			}
			ret = ret->next;
		}
		list_clear(retList);
	}
    | Specifier ExtDecList error { printf("Error type B at Line %d: Missing ';'\n", @$.first_line); error_flag = 1; }
	;
ExtDecList: VarDec { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "ExtDecList", @$.first_line);
		addVar(tmpList, $1, @$.first_line);
	}
    | VarDec COMMA ExtDecList { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "ExtDecList", @$.first_line); 
		addVar(tmpList, $1, @$.first_line);
	}
    ;
Specifier: TYPE { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Specifier", @$.first_line); 
		// "TYPE :"
		switch (*($1->value+6)){
			case 'i':
				baseType = &INT_TYPE;
				break;
			case 'f':
				baseType = &FLOAT_TYPE;
				break;
			case 'c':
				baseType = &CHAR_TYPE;
				break;
		}
		//printf("INT %d FLOAT %d CHAR %d: %d %s\n", INT, FLOAT, CHAR, baseType.primitive, baseType.name);
	}
    | StructSpecifier { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Specifier", @$.first_line); 
	}
    ;
StructSpecifier: STRUCT ID LC DefList RC { 
		childNum = 5; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; $$=createNode(childNum, childNodeList, "StructSpecifier", @$.first_line); 
		baseType = (Type*)malloc(sizeof(Type)); memset(baseType, 0, sizeof(Type));
		baseType->category = STRUCTURE;
		baseType->structure = (FieldList*)malloc(sizeof(FieldList)); memset(baseType->structure, 0, sizeof(FieldList));
		list_link(baseType->structure, list_getLast(allTmpVarList)->vars);
		list_deleteLast(allTmpVarList);
		addFuncStruct(structList, $2, baseType, @2.first_line);
	}
    | STRUCT ID { 
		childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "StructSpecifier", @$.first_line); 
		FieldList *structType;
		//"ID: "
		if ((structType = list_findByName(structList, $2->value+4)) != NULL){
			baseType = structType->type;
		}
		else{
			error_flag = 1;
			printf("Semantic Error at line %d: Struct '%s' is used without definition.\n", @2.first_line, $2->value+4);
		}
	}
    ;
VarDec: ID { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "VarDec", @$.first_line); 
		varName = $1->value+4; //"ID: ";
		//printf(varName);
	}
    | VarDec LB INT RB { 
		childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "VarDec", @$.first_line); 
		Type *lastArrayType = arrayType;
		arrayType = (Type*)malloc(sizeof(Type)); memset(arrayType, 0, sizeof(Type));
		Array *array = (Array*)malloc(sizeof(Array)); memset(array, 0, sizeof(Array));
		if (lastArrayType == NULL){ // first dimension
			array->base = baseType;
		}
		else{
			array->base = lastArrayType;
		}
		array->size = strToInt($3->value+5); // "INT: "
		arrayType->category = ARRAY;
		arrayType->array = array;
	}
    ;
FunDec: ID LP VarList RP { 
		childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "FunDec", @$.first_line); 
		// we do not need to know function return type in here
		// return type check will be done after FunDec be recognized
		addFuncStruct(funcList, $1, NULL, @1.first_line);
		curFunc = list_getLast(funcList);
		curFunc->args = (FieldList*)malloc(sizeof(FieldList)); memset(curFunc->args, 0, sizeof(FieldList));
		list_link(curFunc->args, tmpList);
		//printf("FunDec -> ID LP VarList RP\n");
		//FieldListToString(curFunc->args);
	}
    | ID LP RP { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "FunDec", @$.first_line); 
		addFuncStruct(funcList, $1, NULL, @1.first_line);
		//printf("FunDec -> ID LP RP\n");
		curFunc = list_getLast(funcList);
		curFunc->args = NULL;
	}
    | ID LP error { printf("Error type B at Line %d: Missing \")\"\n", @$.first_line); error_flag = 1; }
	;
VarList: ParamDec COMMA VarList { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "VarList", @$.first_line); }
    | ParamDec { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "VarList", @$.first_line); }
    ;
ParamDec: Specifier VarDec { 
		childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "ParamDec", @$.first_line); 
		addVar(tmpList, $2, @$.first_line);
	}
    ;
CompSt: LC DefList StmtList RC { 
		childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "CompSt", @$.first_line); 
		list_deleteLast(allTmpVarList);
	}
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
    | CompSt { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
	}
    | RETURN Exp SEMI { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		FieldList *ret = (FieldList*)malloc(sizeof(FieldList)); memset(ret, 0, sizeof(FieldList));
		ret->lineno = @2.first_line;
		ret->type = getExpTypePtr($2, @2.first_line);
		list_pushBack(retList, ret);
	}
    | IF LP Exp RP Stmt { 
		childNum = 5; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		Type *typePtr = getExpTypePtr($3, @3.first_line);
		if (!(typePtr->category == PRIMITIVE && typePtr->primitive == INT)){
			error_flag = 1;
			printf("Semantic Error at line %d: Use non-int type variable as condition.\n", @3.first_line);
		}
	}
    | IF LP Exp RP Stmt ELSE Stmt { 
		childNum = 7; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; childNodeList[5]=$6; childNodeList[6]=$7; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		Type *typePtr = getExpTypePtr($3, @3.first_line);
		if (!(typePtr->category == PRIMITIVE && typePtr->primitive == INT)){
			error_flag = 1;
			printf("Semantic Error at line %d: Use non-int type variable as condition.\n", @3.first_line);
		}
	}
    | WHILE LP Exp RP Stmt { 
		childNum = 5; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		loop_flag--;
		Type *typePtr = getExpTypePtr($3, @3.first_line);
		if (!(typePtr->category == PRIMITIVE && typePtr->primitive == INT)){
			error_flag = 1;
			printf("Semantic Error at line %d: Use non-int type variable as condition.\n", @3.first_line);
		}
	}
//	| Exp error { printf("Error type B at Line %d: Exp error\n", @$.first_line); error_flag = 1; }
	| RETURN Exp error { printf("Error type B at Line %d: Missing \";\"\n", @$.first_line); error_flag = 1; } 
//	| RETURN error SEMI { printf("Error type B at Line %d: RETURN error SEMI\n", @$.first_line); error_flag = 1; } 
	| FOR LP Def ExpListEx SEMI ExpListEx RP Stmt { 
		childNum = 8; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; childNodeList[5]=$6; childNodeList[6]=$7; childNodeList[7]=$8; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		loop_flag--;
	}
	| FOR LP ExpListEx SEMI ExpListEx SEMI ExpListEx RP Stmt { 
		childNum = 9; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; childNodeList[4]=$5; childNodeList[5]=$6; childNodeList[6]=$7; childNodeList[7]=$8; childNodeList[8]=$9; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		loop_flag--;
	}
	| BREAK SEMI { 
		childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "Stmt", @$.first_line); 
		//printf("loop flag = %d\n", loop_flag);
		if (!loop_flag) {
			printf("Semantic Error at line %d: 'break' should be used in loop.\n", @1.first_line);
		}
	}
	;
DefList: Def DefList { 
		childNum = 2; childNodeList[0]=$1; childNodeList[1]=$2; $$=createNode(childNum, childNodeList, "DefList", @$.first_line); 
	}
    |  { 
		$$=createEmpty(); 
		FieldList* varDefList = (FieldList*)malloc(sizeof(FieldList)); memset(varDefList, 0, sizeof(FieldList));
		varDefList->vars = (FieldList*)malloc(sizeof(FieldList)); memset(varDefList->vars, 0, sizeof(FieldList));
		list_link(varDefList->vars, tmpList);
		list_pushBack(allTmpVarList, varDefList);
	}
    ;
Def: Specifier DecList SEMI { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Def", @$.first_line); 
	}
    | Specifier DecList error { printf("Error type B at Line %d: Missing \";\"\n", @$.first_line); error_flag = 1; }
	;
DecList: Dec { childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "DecList", @$.first_line); }
    | Dec COMMA DecList { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "DecList", @$.first_line); }
    ;
Dec: VarDec { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Dec", @$.first_line); 
		addVar(tmpList, $1, @$.first_line);
	}
    | VarDec ASSIGN Exp { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Dec", @$.first_line); 
		if (addVar(tmpList, $1, @$.first_line) == 0){
			Type *typePtr = getExpTypePtr($3, @2.first_line);
			//printf("%s Exp category = %d\n", $1->child[0]->value, typePtr->category);
			if (!isSameType(typePtr, list_getLast(tmpList)->type)){
				error_flag = 1;
				printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", @2.first_line);
			}
		}
	}
//	| VarDec ASSIGN error { printf("Error type B at Line %d: VarDec ASSIGN error\n", @$.first_line); error_flag = 1; }
	;
Exp: Exp ASSIGN Exp { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); 
		Type *typePtr = isValidAssign($1, $3, @2.first_line);
		if (typePtr->category == DIFFERENT) {
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
    | ID LP Args RP { 
		childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); 
		//printf("Size = %d %s\n", list_size(funcList), $1->value+4);
		FieldList* func;
		if ((func = list_findByName(funcList, $1->value+4)) == NULL) { // "ID: "
			error_flag = 1;
			if (validUseVar($1->value+4)){
				printf("Error type 11 at Line %d: Applying function invocation operator '()' on non-function names '%s'\n", @1.first_line, $1->value+4);
			}
			else{
				printf("Error type 2 at Line %d: Function '%s' is invoked without definition\n", @1.first_line, $1->value+4);
			}
		}
		else{
			FieldList *cur1 = func->args->next, *cur2 = funcArgs->next;
			int ok = 1;
			FieldList *p1 = cur1, *p2 = cur2;
			/*int cnt1 = 0, cnt2 = 0;
			while (p1 != NULL) cnt1 ++, p1 = p1->next;
			while (p2 != NULL) cnt2 ++, p2 = p2->next;
			printf("len1 = %d len2 = %d\n", cnt1, cnt2);*/
			//printf("Size %d %d\n", list_size(func->args), list_size(funcArgs));
			while (cur1 != NULL && cur2 != NULL){
				if (!isSameType(cur1->type, cur2->type)){
					ok = 0;
					break;
				}
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
			if (!ok || (cur1 == NULL && cur2 != NULL) || (cur1 != NULL && cur2 == NULL)){
				printf("Error type 9 at Line %d: Function’s arguments mismatch the declared parameters\n", @3.first_line);
			}
		}
		list_clear(funcArgs);
	}
    | ID LP RP { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); 
		if (list_findByName(funcList, $1->value+4) == NULL) { // "ID: "
			error_flag = 1;
			if (validUseVar($1->value+4)){
				printf("Error type 11 at Line %d: Applying function invocation operator '()' on non-function names '%s'\n", @1.first_line, $1->value+4);
			}
			else{
				printf("Error type 2 at Line %d: Function '%s' is invoked without definition\n", @1.first_line, $1->value+4);
			}
		}
	}
    | Exp LB Exp RB { childNum = 4; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; childNodeList[3]=$4; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | Exp DOT ID { childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); }
    | ID { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Exp", @$.first_line); 
		if (validUseVar($1->value+4) == NULL) { //"ID: "
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
Args: Exp COMMA Args { 
		childNum = 3; childNodeList[0]=$1; childNodeList[1]=$2; childNodeList[2]=$3; $$=createNode(childNum, childNodeList, "Args", @$.first_line); 
		FieldList* arg = (FieldList*)malloc(sizeof(FieldList)); memset(arg, 0, sizeof(FieldList));
		arg->type = getExpTypePtr($1, @1.first_line);
		//printf("type %s", TypeToString(arg->type));
		list_pushBack(funcArgs, arg);
	}
    | Exp { 
		childNum = 1; childNodeList[0]=$1; $$=createNode(childNum, childNodeList, "Args", @$.first_line); 
		FieldList* arg = (FieldList*)malloc(sizeof(FieldList)); memset(arg, 0, sizeof(FieldList));
		arg->type = getExpTypePtr($1, @1.first_line);
		//printf("type %d %d %s\n", type.category, type.primitive, TypeToString(&type));
		list_pushBack(funcArgs, arg);
	}
    ;
%%

void yyerror(char* s){
	//printf("%s\n", s);
}

char* TypeToString(Type *type){
	switch (type->category){
		case PRIMITIVE:
			//res = (char*)malloc(sizeof(char)*256);
			if (type->primitive == INT) return "INT";
			if (type->primitive == CHAR) return "CHAR";
			if (type->primitive == FLOAT) return "FLOAT";
			//sprintf(res, "%s", type->name);
			//return res;
			break;
		case ARRAY:
			return ArrayToString(type->array);
			break;
		case STRUCTURE:
			printf("FieldList in Struct: %d\n", list_size(type->structure));
			FieldListToString(type->structure);
			return "struct";
			break;
	}
	return NULL;
}

char* ArrayToString(Array *array){
	char *res = (char*)malloc(sizeof(char)*256);
	sprintf(res, "array baseTypeName=%s size=%d", array->base->name, array->size);
	return res;
}

char *FieldListToString(FieldList* head){
	FieldList* cur = head->next;
	while (cur != NULL){
		printf("Name:%s Type:%s\n", cur->name, TypeToString(cur->type));
		cur = cur->next;
	}
	return NULL;
}

FieldList* validDecDefVar(char *name){
	// Just check current field
	FieldList* var;
	//var = list_findByName(list_getLast(allTmpVarList)->vars, name);
	//if (var != NULL) return var;
	var = list_findByName(tmpList, name);
	if (var != NULL) 
		return var;
	/*
	var = list_getLast(funcList);
	if (var != NULL){
		return list_findByName(var->args, name);
	}
	else 
		return NULL;
	*/
	return NULL;
}

FieldList* validUseVar(char *name){
	// check all fields
	FieldList* var;
	
	var = list_findByName(globalVariableList, name);
	if (var != NULL)
		return var;
	FieldList* cur = allTmpVarList->next;
	while (cur != NULL){
		var = list_findByName(cur->vars, name);
		if (var != NULL) 
			return var;
		cur = cur->next;
	}
	var = list_findByName(tmpList, name);
	if (var != NULL) 
		return var;
	var = list_getLast(funcList);
	if (var != NULL)
		return list_findByName(var->args, name);
	return NULL;
}

FieldList* varExist(char *name){
	FieldList* var;
	var = list_findByName(list_getLast(allTmpVarList)->vars, name);
	if (var != NULL) 
		return var;
	var = list_findByName(tmpList, name);
	if (var != NULL) 
		return var;
	var = list_getLast(funcList);
	if (var != NULL)
		return list_findByName(var->args, name);
	return NULL;
}

int addVar(FieldList* head, struct treeNode* node, int lineno){
	// "ID: "
	if (validDecDefVar(varName) != NULL)
	{
		error_flag = 1;
		printf("Error type 3 at Line %d: Variable '%s' is redefined\n", lineno, node->child[0]->value+4);
		return 1;
	}
	FieldList* newVar = (FieldList*)malloc(sizeof(FieldList)); memset(newVar, 0, sizeof(FieldList));
	strcpy(newVar->name, varName);
	//newVar->type = baseType;
	newVar->type = (arrayType != NULL) ? arrayType : baseType ;
	list_pushBack(head, newVar);
	arrayType = NULL; // reset it
	return 0;
}

int addFuncStruct(FieldList* head, struct treeNode* node, Type *typePtr, int lineno){
	// "ID: "
	if (list_findByName(head, node->value+4) != NULL){
		error_flag = 1;
		if (!strcmp(head->name, "function"))
			printf("Error type 4 at Line %d: Function '%s' is redefined\n", lineno, node->value+4);
		if (!strcmp(head->name, "struct"))
			printf("Error type 15 at Line %d: Redefine the same structure type(same name).\n", lineno, node->value+4);
		return 1;
	}
	
	FieldList* newItem = (FieldList*)malloc(sizeof(FieldList)); memset(newItem, 0, sizeof(FieldList));
	
	newItem->type = typePtr;
	strcpy(newItem->name, node->value+4); // "ID: "
	
	list_pushBack(head, newItem);
	
	return 0;
}

Type* isValidAssign(struct treeNode *a, struct treeNode *b, int lineno){
	Type *typePtr_a, *typePtr_b;
	typePtr_a = getExpTypePtr(a, lineno);
	typePtr_b = getExpTypePtr(b, lineno);
	if (isSameType(typePtr_a, typePtr_b)){
		return typePtr_a;
	}
	else {
		return &DIFFERENT_TYPE;
	}
}

Type* isValidOperation(struct treeNode *a, struct treeNode *b, char* operation, int lineno){
	Type *typePtr_a, *typePtr_b;
	typePtr_a = getExpTypePtr(a, lineno);
	typePtr_b = getExpTypePtr(b, lineno);
	//printf("%s %s %d\n", TypeToString(typePtr_a), TypeToString(typePtr_b), isSameType(typePtr_a, typePtr_b));
	if (typePtr_a->category == IGNORE || typePtr_b->category == IGNORE) 
		return &IGNORE_TYPE;
	if (typePtr_a->category == PRIMITIVE && (typePtr_a->primitive == INT || typePtr_a->primitive == FLOAT) && isSameType(typePtr_a, typePtr_b)){
		return typePtr_a;
	}
	else {
		error_flag = 1;
		printf("Error type 7 at Line %d: Invalid operation '%s' on non-number variables\n", lineno, operation);
		return &DIFFERENT_TYPE;
	}
}

Type* getExpTypePtr(struct treeNode* node, int lineno){
	switch (node->childNum){
		case 1: // ID INT CHAR FLOAT
			//printf("node value = %s\n", node->child[0]->value);
			switch (node->child[0]->value[0]){
				case 'I': // INT or ID
					if (node->child[0]->value[1] == 'D'){ // ID
						FieldList* var;
						if ((var = validUseVar(node->child[0]->value+4)) != NULL){ //"ID: "
							return var->type;
						}
						else{ // not find this variable, just ignore it
							//printf("Ignore it!\n");
							//printf("node value = %s\n", node->value);
							return &IGNORE_TYPE;
						}
					}
					else { // INT
						return &INT_TYPE;
					}
					break;
				case 'C': // CHAR
					return &CHAR_TYPE;
					break;
				case 'F': // FLOAT
					return &FLOAT_TYPE;
					break;
			}
			break;
		case 2: // only 'MINUS Exp' or 'NOT Exp'
			return getExpTypePtr(node->child[1], lineno);
			break;
		case 3:
			// LP Exp RP
			if (!strcmp(node->child[0]->value, "LP") && !strcmp(node->child[2]->value, "RP")){
				return getExpTypePtr(node->child[1], lineno);
			}
			// ID LP RP
			if (!strcmp(node->child[1]->value, "LP") && !strcmp(node->child[2]->value, "RP")){
				FieldList *func = list_findByName(funcList, node->child[0]->value+4); // "ID: "
				//char *res = TypeToString(func->type);
				//printf("function return type: %s\n", res);
				return func->type;
			}
			if (!strcmp(node->child[1]->value, "ASSIGN")){ // for ASSIGN operation, just ensure two Exp has same type
				return isValidAssign(node->child[0], node->child[2], lineno);
			}
			else{
				// Exp DOT ID
				//printf("Operation: %s\n", node->child[1]->value);
				if (!strcmp("DOT", node->child[1]->value)){
					Type *typePtr = getExpTypePtr(node->child[0], lineno);
					if (typePtr->category != STRUCTURE){
						error_flag = 1;
						printf("Error type 13 at Line %d: Accessing member of non-structure variable\n", lineno);
						return &IGNORE_TYPE;
					}
					else{
						//printf("StructList: %d %d %d\n", type.category, type.structure, list_size(type.structure));
						//FieldListToString(type.structure);
						FieldList* var = list_findByName(typePtr->structure, node->child[2]->value+4);
						if (var == NULL){
							error_flag = 1;
							printf("Error type 14 at Line %d: Accessing an undefined structure member '%s'\n", lineno, node->child[2]->value+4);
							return &IGNORE_TYPE;
						}
						else {
							return (var->type);
						}
					}
				}
				else{ // Exp Op Exp
					return isValidOperation(node->child[0], node->child[2], node->child[1]->value, lineno);
				}
			}
			break;
		case 4: 
			// ID LP Args RP
			if (!strcmp(node->child[1]->value, "LP") && !strcmp(node->child[3]->value, "RP")){
				FieldList *func = list_findByName(funcList, node->child[0]->value+4); // "ID: "
				if (func != NULL) return (func->type);
				else return &IGNORE_TYPE;
			}
			//Exp LB Exp RB
			if (!strcmp(node->child[1]->value, "LB") && !strcmp(node->child[3]->value, "RB")){
				Type *typePtr = getExpTypePtr(node->child[2], lineno);
				//printf("Type category: %d primitive %d INT %d BOOL %d childNum %d\n", 
				//	type.category, type.primitive, INT, (type.category == PRIMITIVE && type.primitive == INT), node->child[2]->childNum);
				if (!(typePtr->category == PRIMITIVE && typePtr->primitive == INT)){
					error_flag = 1;
					printf("Error type 12 at Line %d: Array indexing with non-integer type expression\n", lineno);
					return &IGNORE_TYPE;
				}
				typePtr = getExpTypePtr(node->child[0], lineno);
				if (typePtr->category != ARRAY){
					error_flag = 1;
					printf("Error type 10 at Line %d: Applying indexing operator '[]' on non-array type variabless\n", lineno);
					return &IGNORE_TYPE;
				}
				return (typePtr->array->base);
			}
			break;
	}
	return NULL;
}

Type* parseSpecifier(struct treeNode* node){
	node = node->child[0];
	if (!memcmp(node->value, "TYPE", 4)){
		// "TYPE :"
		switch (*(node->value+6)){
			case 'i':
				return &INT_TYPE;
				break;
			case 'f':
				return &FLOAT_TYPE;
				break;
			case 'c':
				return &CHAR_TYPE;
				break;
		}
	}
	return NULL;
}

int main(int argc, char** args){
	//for (int i = 0 ; i < argc ; i ++)
	//	printf("%d %s\n", i, args[i]);
	
	// input
	freopen(args[1], "r", stdin);
	
	// output
	char outputPath[256];
	strcpy(outputPath, args[1]);
	strcpy(outputPath+strlen(outputPath)-3, "out");
	//printf("OutputPath = %s\n", outputPath);
	freopen(outputPath, "w", stdout);
	
	globalVariableList = list_init();
	globalStructList = list_init();
	
	tmpList = list_init();
	allTmpVarList = list_init();
	
	funcList = list_init(); strcpy(funcList->name, "function");
	
	retList = list_init(); strcpy(retList->name, "return");
	funcArgs = list_init(); strcpy(funcArgs->name, "functionArguments");
	
	structList = list_init(); strcpy(structList->name, "struct");
	
	//printf("Parsing...\n");
    yyparse();
	//#define DEBUG
	#ifdef DEBUG
	printf("Variable List\n");
	//FieldListToString();
	printf("Function List\n");
	FieldListToString(funcList);
	printf("Struct List\n");
	FieldListToString(structList);
	#endif
	
	fclose(stdin);
	fclose(stdout);
}