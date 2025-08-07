#include <stdio.h>
#include <stdlib.h>

struct Node {
	char c;
	struct Node* next;
	struct Node* prev;
};

int main() {
	char str[100002];
	scanf("%s", &str);

	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->next = NULL;
	head->prev = NULL;

	struct Node* cursor = head;

	for (int i = 0; str[i] != '\0'; i++) {
		struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));

		if (new_Node == NULL) {
			printf("Memory allocation failed");
			exit(1);
		}

		new_Node->c = str[i];
		cursor->next = new_Node;
		new_Node->prev = cursor;
		new_Node->next = NULL;
		cursor = new_Node;
	}

	int m;
	scanf("%d", &m);

	char command;

	for (int i = 0; i < m; i++) {
		scanf(" %c", &command);

		if (command == 'L') {
			if (cursor->prev != NULL) {
				cursor = cursor->prev;
			}
		}
		else if (command == 'D') {
			if (cursor->next != NULL) {
				cursor = cursor->next;
			}
		}
		else if (command == 'B') {
			if (cursor != head) {
				struct Node* to_delete = cursor;
				cursor = cursor->prev;
				cursor->next = to_delete->next;
				if (to_delete->next != NULL) {
					to_delete->next->prev = cursor;
				}
				free(to_delete);
			}
		}
		else if (command == 'P') {
			char ch;
			scanf(" %c", &ch);

			struct Node* ins_Node = (struct Node*)malloc(sizeof(struct Node));
			ins_Node->c = ch;

			ins_Node->prev = cursor;
			ins_Node->next = cursor->next;
			if (cursor->next != NULL) {
				cursor->next->prev = ins_Node;
			}
			cursor->next = ins_Node;
			cursor = ins_Node;

		}
	}

	for (cursor = head->next; cursor != NULL; cursor = cursor->next) {
		printf("%c", cursor->c);
	}

	cursor = head;
	while (cursor != NULL) {
		struct Node* tmp = cursor;
		cursor = cursor->next;
		free(tmp);
	}
	
	return 0;
}
