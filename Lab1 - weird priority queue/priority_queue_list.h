typedef struct Node Node;
struct Node {
	int data;
	Node*next;
};

void qinsert(Node **phead, Node *data);

void qlist(Node* head);

void qremove(Node **head);

void deletequeue(Node** head);