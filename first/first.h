#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef _HEADER_H
#define _HEADER_H

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

typedef struct node{
	char data;
	struct node *child[26];
	int isword, occur, prefix, numChild;

}node;

node* root;
FILE *outputFile;
int count;

node *makeNode(char c);
void traverse(node*temp, char word[200], int size);
void insertword(char *temparr, node *root);
void matchStr(char*temparr);
void readDict(FILE *dict);
void readData(FILE *data);
void printResult();


#endif