#include<stdio.h>
#include <stdlib.h>

typedef struct MinHeap {
	int* arr;
	int capacity;
	int size;
} MinHeap;

void SwapElement(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


MinHeap* CreateMinHeap(int capacity) {
	MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
	if (heap == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

	heap->arr = (int*)calloc(capacity + 1, sizeof(int));
	if (heap->arr == NULL) {
		printf("Memory allocation failed");
		free(heap);
		exit(1);
	}

	heap->capacity = capacity;
	heap->size = 0;

	return heap;
}

void MinHeapifyDown(MinHeap* heap, int idx) {
	int smallest = idx;
	int left_child_idx = idx * 2;
	int right_child_idx = idx * 2 + 1;

	if (left_child_idx <= heap->size && heap->arr[left_child_idx] < heap->arr[smallest]) {
		smallest = left_child_idx;
	}

	if (right_child_idx <= heap->size && heap->arr[right_child_idx] < heap->arr[smallest]) {
		smallest = right_child_idx;
	}

	if (smallest != idx) {
		SwapElement(&heap->arr[idx], &heap->arr[smallest]);
		MinHeapifyDown(heap, smallest);
	}
}

void MinHeapifyUp(MinHeap* heap, int idx) {
	while (idx > 1 && heap->arr[idx] < heap->arr[idx / 2]) {
		SwapElement(&heap->arr[idx], &heap->arr[idx / 2]);
		idx = idx / 2;
	}
}

void MinHeapInsert(MinHeap* heap, int k) {
	if (heap->size == heap->capacity) {
		return;
	}

	heap->arr[++heap->size] = k;

	MinHeapifyUp(heap, heap->size);
}

int MinHeapExtration(MinHeap* heap) {
	if (heap->size < 1) {
		return;
	}

	int root = heap->arr[1];

	heap->arr[1] = heap->arr[heap->size];
	heap->size--;
	
	MinHeapifyDown(heap, 1);

	return root;
}

void FreeMinHeap(MinHeap* heap) {
	if (heap == NULL) {
		return;
	}
	if (heap->arr != NULL) {
		free(heap->arr);
	}
	free(heap);
}

int main() {
	int N;
	scanf("%d", &N);

	MinHeap* heap = CreateMinHeap(N);

	for (int i = 0; i < N; i++) {
		int card_size;
		scanf("%d", &card_size);
		MinHeapInsert(heap, card_size);
	}

	int total_comparison = 0;

	while (heap->size > 1) {
		int first_smallest = MinHeapExtration(heap);
		int second_smallest = MinHeapExtration(heap);

		int current_sum = first_smallest + second_smallest;
		total_comparison += current_sum;

		MinHeapInsert(heap, current_sum);
	}

	printf("%d\n", total_comparison);

	FreeMinHeap(heap);

	return 0;
}
