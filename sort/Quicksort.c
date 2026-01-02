#include <stdio.h>

void Partition_first(int arr[], int left, int right) {
	int pivot = arr[left];
	int low = left + 1;
	int high = right;

	while (low <= high) {
		while (low <= right && arr[low] <= pivot) low++;
		while (arr[high] > pivot) high--;

		if (low < high) 
			swap(&arr[low], &arr[high]);
	}

	swap(&arr[left], &arr[high]);
	return high;
}

void QuickSort_first(int arr[], int left, int right) {
	if (left < right) {
		int p = Partition_first(arr, left, right);
		QuickSort_first(arr, left, p - 1);
		QuickSort_first(arr, p + 1, right);
	}
}
