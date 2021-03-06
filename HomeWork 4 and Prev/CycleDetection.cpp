//Homework 2 bonus task
//Cycle Detection

struct Node {
	int data;
	struct Node* next;
};

bool has_cycle(Node* head) {
	Node* check = head;
	while (check && check->next)
	{
		head = head->next;
		check = check->next->next;
		if (head == check) return true;
	}
	return false;
}


