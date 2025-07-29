#include <stdio.h>
#include <stdlib.h>

#define kMaxStackSize 100000

struct Stack {
	int data[kMaxStackSize];
	int top;
};

void InitStack(struct Stack* stack) {
	stack->top = -1;
}

void Push(struct Stack* stack, int x) {
	stack->data[++stack->top] = x;
}

int Pop(struct Stack* stack) {
	if (stack->top == -1) {
		return -1;
	}
	return stack->data[stack->top--];
}

int IsEmpty(struct Stack* stack) {
	return stack->top == -1 ? 1 : 0;
}

int Size(struct Stack* stack) {
	return stack->top + 1;
}

int main() {
	int k;
	scanf("%d", &k);

	struct Stack ledger;
	InitStack(&ledger);

	for (int i = 0; i < k; i++) {
		int m;
		scanf("%d", &m);
			
		if (m == 0)
			Pop(&ledger);
		else
			Push(&ledger, m);
	}

	int sum = 0;

	while (!IsEmpty(&ledger)) {
		sum += Pop(&ledger);
	}

	printf("%d", sum);
}
