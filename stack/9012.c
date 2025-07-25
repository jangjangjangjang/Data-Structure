#include <stdio.h>
#include <string.h>

#define kMaxString 50

struct Stack {
	char data[kMaxString];
	int top;
};

void InitStack(struct Stack* stack) {
	stack->top = -1;
}

void Push(struct Stack* stack, char c) {
	stack->data[++stack->top] = c;
}

char Pop(struct Stack* stack) {
	return stack->data[stack->top--];
}

char Peek(struct Stack* stack) {
	if (stack->top == -1) return '\0';
	return stack->data[stack->top];
}

int IsEmpty(struct Stack* stack) {
	return stack->top == -1;
}

int IsVPS(const char* str) {
	struct Stack s;

	InitStack(&s);

	for (int i = 0; str[i] != '\0'; i++) {
		char c = str[i];

		if (c == '(') {
			Push(&s, c);
		}
		else if (c == ')') {
			if (Peek(&s) == '(') {
				Pop(&s);
			}
			else
				return 0;
		}
	}

	return IsEmpty(&s);
}

int main() {
	int n;
	scanf("%d", &n);

	char input[kMaxString + 2];

	for (int i = 0; i < n; i++) {
		scanf("%s", input);
		if (IsVPS(input)) {
			printf("YES\n");
		}
		else 
			printf("NO\n");
	}
}
