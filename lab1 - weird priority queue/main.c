#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue_list.h"

int
main(int argc, char **argv) {
	
	Node *queue = NULL;
	Node *n1, *n2, *n3;
	n1 = (Node *) malloc(sizeof(Node));
	n2 = (Node *) malloc(sizeof(Node));
	n3 = (Node *) malloc(sizeof(Node));
	n1->data = 5;
	n2->data = 10; 
	n3->data = 1;
	qinsert(&queue, n1);
	qinsert(&queue, n2);
	qinsert(&queue, n3);
	qlist(queue);
	
	printf("\n");
	qremove(&queue);
	qlist(queue);
	
	printf("\n");
	Node* n4 = (Node*)malloc(sizeof(Node));
	n4->data = 7;
	qinsert(&queue, n4);
	qlist(queue);
	
	printf("\n");
	qremove(&queue);
	qlist(queue);
	
	printf("\n");
	qremove(&queue);
	qlist(queue);
	
	deletequeue(&queue);
		
	return 0;
}