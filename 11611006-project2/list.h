#include<stdio.h>
#include<stdlib.h>
#define INT_MIN -0x80000000

#ifndef LEX
#define LEX
#include "lex.yy.c"
#endif

typedef struct Type {
	char name[32];
	enum { PRIMITIVE, ARRAY, STRUCTURE } category;
	union { 
		int primitive;
		struct Array *array;
		struct FieldList *structure;
	};
} Type;

typedef struct Array {
	struct Type *base;
	int size;
} Array;

typedef struct FieldList {
	char name[32];
	struct Type *type;
	struct FieldList *next;
} FieldList;

char* TypeToString(Type *type);
char* ArrayToString(Array *array);
char *FieldListToString(FieldList* head);

char* TypeToString(Type *type){
	char* res;
	switch (type->category){
		case PRIMITIVE:
			res = (char*)malloc(sizeof(char)*256);
			switch (type->primitive){
				case INT: sprintf(res, "INT %s", type->name); break;
				case FLOAT: sprintf(res, "FLOAT %s", type->name); break;
				case CHAR: sprintf(res, "CHAR %s", type->name); break;
			}
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
		printf("%s\n", cur->name);
		//printf("%s %s\n", cur->name, TypeToString(cur->type));
		cur = cur->next;
	}
}

int isSameType(const Type *a, const Type *b){
	if (a->category != b->category) return 0;
	switch (a->category){
		struct FieldList *aFiledList, *bFiledList;
		case PRIMITIVE:
			return a->primitive == b->primitive;
		break;
		
		case ARRAY:
			return a->array->base == b->array->base;
		break;
		
		case STRUCTURE:{
			aFiledList = a->structure;
			bFiledList = b->structure;
			while (1){
				if (aFiledList == NULL || bFiledList == NULL) break;
				if (!strcmp(aFiledList->name, bFiledList->name) || !isSameType(aFiledList->type, bFiledList->type))
					return 0;
				aFiledList = aFiledList->next;
				bFiledList = bFiledList->next;
			}
			return aFiledList == NULL && bFiledList == NULL;
		}
		break;
	}
	return 0;
}

FieldList* list_init(){
	FieldList* head = (FieldList*)malloc(sizeof(FieldList));
	memset(head, 0, sizeof(FieldList));
	return head;
}

void list_pushBack(FieldList *head, FieldList *value){
	FieldList* cur = head;
	while (cur->next != NULL) cur = cur->next;
	cur->next = value;
}

FieldList* list_getLast(FieldList *head){
	FieldList* cur = head;
	while (cur->next != NULL) cur = cur->next;
	return cur;
}

void list_link(FieldList *firstHead, FieldList *secondHead){
	list_getLast(firstHead)->next = secondHead->next;
	secondHead->next = NULL;
}