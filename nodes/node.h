#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct Node* getNode(char *name);
void removeFromLinkedList(struct Node *del);
void addToLinkedList(struct Node *insert);
int inLinkedList(char *name);