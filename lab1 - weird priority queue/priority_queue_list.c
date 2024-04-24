#include <stdio.h>
#include <stdlib.h>
#include "priority_queue_list.h"

void qlist(Node *head) {
	Node*p = head;
	
	while (p != NULL)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}

void qinsert(Node** phead, Node* data) {
    Node* current = *phead;
    Node* prev = NULL;

    while (current != NULL && data->data <= current->data) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        data->next = *phead;
        *phead = data;
    } else {
        prev->next = data;
        data->next = current;
    }
}


void qremove(Node** phead) {
    if (*phead != NULL) {
        Node* tmp = (*phead)->next;
        free(*phead);
        *phead = tmp;
    }
}


void deletequeue(Node** head) {
    Node* node = *head;
    while (node != NULL) {
        Node* tmp = node->next;
        free(node);
        node = tmp;
    }
    *head = NULL;
}
