#include <stdio.h>
#include <stdlib.h>

typedef struct Lecture {
	int start, end;
} Lecture;

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

void MinHeapifyUp(MinHeap* heap, int idx) {
	while (idx > 1 && heap->arr[idx] < heap->arr[idx / 2]) {
		SwapElement(&heap->arr[idx], &heap->arr[idx / 2]);
		idx = idx / 2;
	}
}

void MinHeapifyDown(MinHeap* heap, int idx) {
	int smallest = idx;
	int right_idx = 2 * idx + 1;
	int left_idx = 2 * idx;

	if (right_idx <= heap->size && heap->arr[smallest] > heap->arr[right_idx]) {
		smallest = right_idx;
	}
	if (left_idx <= heap->size && heap->arr[smallest] > heap->arr[left_idx]) {
		smallest = left_idx;
	}

	if (smallest != idx) {
		SwapElement(&heap->arr[smallest], &heap->arr[idx]);
		MinHeapifyDown(heap, smallest);
	}
	
}

void MinHeap_Insert(MinHeap* heap, int k) {
	if (heap->size >= heap->capacity) {
		return;
	}


	heap->arr[++heap->size] = k;
	MinHeapifyUp(heap, heap->size);
}

int MinHeap_Extraction(MinHeap* heap) {
	if (heap->size < 1) {
		return;
	}

	int root = heap->arr[1];

	heap->arr[1] = heap->arr[heap->size--];
	
	MinHeapifyDown(heap, 1);

	return root;
}


int Compare(const void* a, const void* b) {
	Lecture* l1 = (Lecture*)a;
	Lecture* l2 = (Lecture*)b;
	if (l1->start == l2->start) return l1->end - l2->end;
	return l1->start - l2->start;
}

int MinHeap_Top(MinHeap* heap) {
	if (heap->size == 0) 
		return -1;

	return heap->arr[1];
}

int main() {
	int N;
	scanf("%d", &N);

	MinHeap* T_Heap = CreateMinHeap(N);

	Lecture* arr = (Lecture*)calloc(N, sizeof(Lecture));

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &arr[i].start, &arr[i].end);
	}

	qsort(arr, N, sizeof(Lecture), Compare);

	MinHeap_Insert(T_Heap, arr[0].end);

	for (int i = 1; i < N; i++) {
		if (arr[i].start >= MinHeap_Top(T_Heap)) {
			MinHeap_Extraction(T_Heap);
		}
		MinHeap_Insert(T_Heap, arr[i].end);
	}

	printf("%d\n", T_Heap->size);

	free(arr);
	free(T_Heap->arr);
	free(T_Heap);

}
