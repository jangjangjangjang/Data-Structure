#include <stdio.h>

#define kMaxStackSize 1000

struct Stack {
	int top;
	int data[kMaxStackSize];
};

void InitStack(struct Stack* stack) {
	stack->top = -1;
}

void Push(struct Stack* stack, int n) {
	stack->data[++stack->top] = n;
}

int Pop(struct Stack* stack) {
	if (stack->top == -1) return -1;
	return stack->data[stack->top--];
}

int Peek(struct Stack* stack) {
	if (stack->top == -1) return -1;
	return stack->data[stack->top];
}

int Size(struct Stack* stack) {
	return stack->top + 1;
}

int main() {
	int n;
	scanf("%d", &n);

	struct Stack s;
	struct Stack w;

	InitStack(&s);
	InitStack(&w);

	int arr[kMaxStackSize];

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = n - 1; i >= 0; i--) {
		Push(&s, arr[i]);
	}

	int a = 1;

	while(Size(&s) > 0 || Size(&w) > 0) {
		if (Peek(&s) == a) {
			Pop(&s);
			a += 1;
		}
		else if (Peek(&w) == a) {
			Pop(&w);
			a += 1;
		}
		else if (Size(&s) > 0) {
			int b = Pop(&s);
			Push(&w, b);
		}
		else
			break;
		
	}

	if (Size(&w) == 0) {
		printf("%s", "Nice\n");
	}
	else
		printf("%s", "Sad\n");

}
