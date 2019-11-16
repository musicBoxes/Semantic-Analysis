#ifndef MYTREE
#define MYTREE
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "list.h"

struct treeNode
{
	char *value;
	int childNum;
	struct treeNode *child[10];
};

struct treeNode *createLeaf(char *text);
struct treeNode *createNode(int childNum, struct treeNode *a[], char *value, int lineno);
struct treeNode *createEmpty();
void treePrintLevel(struct treeNode *node, int lvl);
void treePrint(struct treeNode *node);

struct treeNode *createLeaf(char *text)
{
	struct treeNode *node = (struct treeNode*)malloc(sizeof(struct treeNode));
	node->childNum = 0;
	if (text != NULL)
	{
		node->value=(char*)malloc(sizeof(char)*strlen(text));
		strcpy(node->value, text);
	}
	else
	{
		node->value = NULL;
	}
	return node;
}
 
struct treeNode *createNode(int childNum, struct treeNode *a[], char *value, int lineno)
{
	struct treeNode *node = (struct treeNode*)malloc(sizeof(struct treeNode));
	node->childNum = childNum;
	node->value=(char*)malloc(sizeof(char)*(strlen(value)+12));
	memset(node->value, 0, sizeof(char)*(strlen(value)+12));
	sprintf(node->value, "%s (%d)", value, lineno);
	for (int i = 0; i < node->childNum; i ++)
		(node->child)[i] = a[i];
	return node;
}
 
struct treeNode *createEmpty()
{
	struct treeNode *node=(struct treeNode*)malloc(sizeof(struct treeNode));
	node->childNum=0;
	node->value=NULL;
	return node;
}
 
void treePrintLevel(struct treeNode *node, int depth)
{
	if (node == NULL 
		|| node->value==NULL 
		|| (node->childNum == 1 && (node->child)[0]->value==NULL)) return;
	
	for (int i = 0; i < 2*depth; i ++) printf(" ");
	printf("%s\n", node->value, node->childNum);
	for (int i = 0; i < node->childNum; i ++)   
		treePrintLevel((node->child)[i], depth+1);
}

int strToInt(char *str){
	int res = 0;
	while (*str != 0){
		res = res * 10 + *str - '0';
	}
}

void treeParseLevel(struct treeNode *node, Type *type, FieldList* varList)
{
	extern int arraySize_flag;
	if (node == NULL || node->value == NULL) return;
	char str[4]; memset(str, 0, sizeof(str));
	memcpy(str, node->value, sizeof(char)*3);
	// an array a[10]
	/*if (!strcmp(node->value, "LB")){
		arraySize_flag = 1;
		return;
	}
	if (arraySize_flag && !strcmp(str, "INT")){
		arraySize_flag = 0;
		FieldList *last = list_getLast(varList);
		Array *array = (Array*)malloc(sizeof(Array));
		array->base = last->type;
		array->size = strToInt(node->value+5); //"INT: "
		last->type = (Type*)malloc(sizeof(Type));
		last->type->category = ARRAY;
		last->type->array = array;
	}*/
	// memcpy(str, node->value, sizeof(char)*4);
	if (!strcmp(str, "ID:")){
		// encounter an ID
		FieldList* newItem = (FieldList*)malloc(sizeof(FieldList));
		newItem->type = (Type*)malloc(sizeof(Type));
		memcpy(newItem->type, type, sizeof(Type));
		strcpy(newItem->name, node->value+4);
		list_pushBack(varList, newItem);
	}
	for (int i = 0 ; i < node->childNum; i ++)
		treeParseLevel((node->child)[i], type, varList);
}
 
void treePrint(struct treeNode *node)
{
	treePrintLevel(node, 0);
}
#endif