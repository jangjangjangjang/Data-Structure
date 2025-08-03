#include <stdio.h>
#include <stdlib.h>

#define kMaxBallons 1000

struct Node {
	int number;
	int value;
	struct Node* next;
	struct Node* prev;
};

int main() {
	int N;
	scanf("%d", &N);

	struct Node* head = NULL;
	struct Node* tail = NULL;

	int value;

	for (int i = 1; i <= N; i++) {
		scanf("%d", &value);

		struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
		if (new_Node == NULL) {
			printf("Memory allocation failed\n");
			exit(1);
		}

		new_Node->number = i;
		new_Node->value = value;

		if (head == NULL) {
			head = new_Node;
			tail = new_Node;
			new_Node->next = new_Node;
			new_Node->prev = new_Node;
		}
		else {
			new_Node->next = head;
			new_Node->prev = tail;
			tail->next = new_Node;
			head->prev = new_Node;
			tail = new_Node;
		}
	}

	struct Node* current = head;

	for (int i = 0; i < N; i++) {
		printf("%d ", current->number);

		if (i == N - 1) {
			break;
		}

		int move_steps = current->value;
		struct Node* next_Node = current->next;
		struct Node* prev_Node = current->prev;

		next_Node->prev = prev_Node;
		prev_Node->next = next_Node;

		if (current == head) {
			head = next_Node;
		}

		struct Node* to_delete = current;

		if (move_steps > 0) {
			current = next_Node;
			for (int j = 1; j < move_steps; j++) {
				current = current->next;
			}
		}

		else {
			current = prev_Node;
			for (int j = 1; j < -move_steps; j++) {
				current = current->prev;
			}
		}

		free(to_delete);
	}
	if (head != NULL) {
		free(head);
	}
	return 0;
}
