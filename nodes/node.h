#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Node{
	struct Node *prev;
    char* user;
    struct Node *next;
};


struct Node* getNode(char *name);
void removeFromLinkedList(struct Node *del);
void addToLinkedList(struct Node *insert);
int inLinkedList(char *name);