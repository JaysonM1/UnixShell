#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


struct Node* head = NULL;

struct Node* getNode(char *name){
	struct Node *temp = head;
	while(temp){
		if(strcmp(temp->user,name) == 0){
			return temp;
		}
	}
}



void removeFromLinkedList(struct Node *del){
	if (head == del){ 
        	head = head->next;
	}
	if(del->next != NULL)
		    del->next->prev = del->prev;

	if(del->prev != NULL)
    		del->prev->next = del->next;

 	free(del); //delete the node
}


void addToLinkedList(struct Node *insert){
	if(head == NULL){
		head = insert;
	}
	else{
		struct Node* end =head;
		insert->next = NULL;
		while (end->next != NULL) 
       	 		end = end->next;
	       end->next = insert;
  	       insert->prev = end; 	
	}
	
}

int inLinkedList(char *name){
	struct Node* temp = head;
	while(temp){
		if(strcmp(temp->user,name) == 0){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}




