#include <stdio.h>
#include <stdlib.h>

#define kMaxString 100000
#define kMaxCommand 500000

struct Node {
	char c;
	struct Node* next;
	struct Node* prev;
};

int main() {
	int N;
	scanf("%d", &N);

	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	head->prev = NULL;
	head->next = NULL;

	struct Node* cursor = head;

	char str[100001];
	scanf("%s", str);

	for (int i = 0; str[i] != '\0'; i++) {
	
		struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
		if (new_Node == NULL) {
			printf("Memory allocation failed\n");
			exit(1);
		}

		new_Node->c = str[i];

		if (head->next == NULL) {
			head->next = new_Node;
			new_Node->prev = head;
			new_Node->next = NULL;
			cursor = new_Node;
		}
		else {
			new_Node->prev = cursor;
			new_Node->next = NULL;
			cursor->next = new_Node;
			cursor = new_Node;
		}
	}

	int a;
	scanf("%d", &a);

	char command;
	for (int i = 0; i < a; i++) {

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
			struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
			new_Node->c = ch;

			new_Node->prev = cursor;
			new_Node->next = cursor->next;
			if (cursor->next != NULL) {
				cursor->next->prev = new_Node;
			}
			
			cursor->next = new_Node;
			cursor = new_Node;
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
