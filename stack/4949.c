#include <stdio.h>
#include <string.h>

#define kMaxStackSize 100

struct Stack {
	char data[kMaxStackSize];
	int top;
};

void InitStack(struct Stack* stack) {
	stack->top = -1;
}

void Push(struct Stack* stack, char key) {
	stack->data[++stack->top] = key;
}

char Pop(struct Stack* stack) {
	if (stack->top == -1) {
		return '\0';
	}
	return stack->data[stack->top--];
}

char Peek(struct Stack* stack) {
	if (stack->top == -1) return '\0';
	return stack->data[stack->top];
}

int IsEmpty(struct Stack* stack) {
	return stack->top == -1 ? 1 : 0;
}

int IsBalanced(const char* str) {
	struct Stack s;

	InitStack(&s);

	for (int i = 0; str[i] != '\0'; i++) {
		char c = str[i];

		if (c == '(' || c == '[') {
			Push(&s, c);
		}
		else if (c == ')') {
			if (IsEmpty(&s) || Peek(&s) != '(') {
				return 0;
			}
			Pop(&s);
		}
		else if (c == ']') {
			if (IsEmpty(&s) || Peek(&s) != '[') {
				return 0;
			}
			Pop(&s);
		}
	}
	return IsEmpty(&s);

}

int main() {
	char input[102];

	while (1) {
		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, ".") == 0)
			break;

		if (IsBalanced(input))
			printf("yes\n");
		else
			printf("no\n");
	}
}
