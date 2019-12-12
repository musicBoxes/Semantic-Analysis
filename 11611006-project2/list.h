#ifndef MYLIST
#define MYLIST

#include<stdio.h>
#include<stdlib.h>
#define INT_MIN -0x80000000

#include"syntax.tab.h"

typedef struct Type {
	char name[32];
	enum { PRIMITIVE, ARRAY, STRUCTURE, DIFFERENT, IGNORE } category;
	union { 
		int primitive;
		struct Array *array;
		struct FieldList *structure;
	};
} Type;

const Type INT_TYPE = {
	.category = PRIMITIVE,
	.primitive = INT
};
const Type CHAR_TYPE = {
	.category = PRIMITIVE,
	.primitive = CHAR
};
const Type FLOAT_TYPE = {
	.category = PRIMITIVE,
	.primitive = FLOAT
};
const Type DIFFERENT_TYPE = {
	.category = DIFFERENT
};
const Type IGNORE_TYPE = {
	.category = IGNORE
};

typedef struct Array {
	struct Type *base;
	int size;
} Array;

typedef struct FieldList {
	char name[32];
	union{
		int lineno;
		struct FieldList* args;
		struct FieldList* vars;
	};
	struct Type *type;
	struct FieldList *next;
} FieldList;

char* TypeToString(Type *type);
char* ArrayToString(Array *array);
char *FieldListToString(FieldList* head);

int isSameType(const Type *a, const Type *b){
	if (a == NULL || b == NULL) return 0;
	if (a->category == IGNORE || b->category == IGNORE) return 1;
	if (a->category != b->category) return 0;
	switch (a->category){
		struct FieldList *aFiledList, *bFiledList;
		case PRIMITIVE:
			return a->primitive == b->primitive;
		break;
		
		case ARRAY:
			return a->array->size == b->array->size && isSameType(a->array->base, b->array->base);
		break;
		
		case STRUCTURE:{
			aFiledList = a->structure->next;
			bFiledList = b->structure->next;
			while (1){
				if (aFiledList == NULL || bFiledList == NULL) break;
				if (!isSameType(aFiledList->type, bFiledList->type))
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

int list_size(FieldList* head){
	if (head == NULL) return 0;
	FieldList* cur = head->next;
	int cnt = 0;
	while (cur != NULL) {
		cur = cur->next;
		cnt ++;
	}
	return cnt;
}

void list_pushBack(FieldList *head, FieldList *value){
	if (head == NULL) return;
	FieldList* cur = head;
	while (cur->next != NULL) cur = cur->next;
	cur->next = value;
}

FieldList* list_getLast(FieldList *head){
	if (head == NULL) return NULL;
	FieldList* cur = head;
	while (cur->next != NULL) cur = cur->next;
	return cur;
}

void list_deleteLast(FieldList *head){
	FieldList* cur = head;
	FieldList* curLast;
	while (cur->next != NULL) {
		curLast = cur;
		cur = cur->next;
	}
	curLast->next = NULL;
}

void list_link(FieldList *firstHead, FieldList *secondHead){
	//printf("%d %d\n", list_getLast(firstHead)->next == NULL, list_getLast(firstHead));
	list_getLast(firstHead)->next = secondHead->next;
	secondHead->next = NULL;
}

FieldList* list_findByName(FieldList *head, char *name){
	if (head == NULL) return NULL;
	FieldList* cur = head->next;
	while (cur != NULL){
		if (!strcmp(cur->name, name))
			return cur;
		cur = cur->next;
	}
	return NULL;
}

void list_clear(FieldList* head){
	FieldList* cur = head->next;
	head->next = NULL;
	/*while (cur != NULL){
		cur = cur->next;
	}*/
	FieldList* next;
	if (strcmp(head->name, "return") || // retList just record lineno, not FieldList*
		strcmp(head->name, "functionArguments")){ // funcArgs do not use this union field
		while (cur != NULL){
			next = cur->next;
			free(cur);
			cur = next;
		}
	}
}
#endif