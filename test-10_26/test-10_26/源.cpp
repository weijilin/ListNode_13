#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <stdio.h>

void printArray(int a[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}

	printf("\n");
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// 插入排序
void insertSort(int a[], int size) {
	for (int i = 0; i < size; i++) {
		int k = a[i];
		int j;
		for (j = i - 1; j >= 0 && a[j] < k; j--) {
			a[j + 1] = a[j];
		}

		a[j + 1] = k;
	}
}

// 希尔排序
void shellSort(int a[], int size) {
	int gap = size;

	while (1) {
		gap = gap / 3 + 1;

		for (int i = 0; i < size; i++) {
			int k = a[i];
			int j;
			for (j = i - gap; j >= 0 && a[j] < k; j -= gap) {
				a[j + gap] = a[j];
			}
			a[j + gap] = k;
		}

		if (gap == 1) {
			break;
		}
	}
}

// 选择排序（直接选择）
void selectSort(int a[], int size) {
	int left = 0;
	int right = size - 1;
	while (left < right) {
		int min = left;
		int max = left;
		for (int i = left + 1; i <= right; i++) {
			if (a[i] < a[min]) {
				min = i;
			}
			if (a[i] > a[max]) {
				max = i;
			}
		}
		swap(&a[min], &a[left]);
		if (max == left) {
			max = min;
		}
		swap(a + max, a + right);
		left++;
		right--;
	}
}

// 堆排序
void heapify(int a[], int size, int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left >= size) {
		return;
	}
	int max = left;
	if (right < size && a[right] > a[left]) {
		max = right;
	}
	if (a[index] >= a[max]) {
		return;
	}
	swap(a + index, a + max);
	heapify(a, size, max);
}
void createHeap(int a[], int size) {
	for (int i = (size - 2) / 2; i >= 0; i--) {
		heapify(a, size, i);
	}
}
void heapSort(int a[], int size) {
	createHeap(a, size);
	for (int i = 0; i < size; i++) {
		// 无序 [0, size - i)
		swap(a, a + size - i - 1);
		// 无序 [0, size - i - 1)
		heapify(a, size - i - 1, 0);
	}
}

/*
时间复杂度:
最好：	O(n)		有序
平均：	O(n^2)
最坏：	O(n^2)		逆序
空间复杂度：	O(1)
稳定性：稳定
*/
void bubbleSort(int a[], int size) {
	// 把最大的数冒泡到最后去
	for (int i = 0; i < size; i++) {
		int sorted = 1;

		// 无序 [0, size - i)
		// 有序 [size - i, size)
		// 冒泡 无序区间
		for (int j = 0; j < size - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				swap(a + j, a + j + 1);
				sorted = 0;
			}
		}

		if (sorted == 1) {
			break;
		}
	}
}

// 快速排序
int partition1(int a[], int left, int right) {
	int begin = left;
	int end = right;
	int pivot = a[right];
	while (begin < end) {
		while (begin < end && a[begin] <= pivot) {
			begin++;
		}
		while (begin < end && a[end] >= pivot) {
			end--;
		}
		swap(a + begin, a + end);
	}
	swap(a + begin, a + right);
	return begin;
}

int partition2(int a[], int left, int right) {
	int begin = left;
	int end = right;
	int pivot = a[right];
	while (begin < end) {
		while (begin < end && a[begin] <= pivot) {
			begin++;
		}

		a[end] = a[begin];

		while (begin < end && a[end] >= pivot) {
			end--;
		}

		a[begin] = a[end];
	}

	a[begin] = pivot;
	return begin;
}

int partition3(int a[], int left, int right) {
	// [left, div) 比基准小
	// [div, i) 比基准值大于等于
	int div = left;
	int i = left;
	for (; i < right; i++) {
		if (a[i] < a[right]) {
			swap(a + i, a + div);
			div++;
		}
	}

	swap(a + div, a + right);

	return div;
}

// [left, right]
void quickSortInternal(int a[], int left, int right) {
	if (left >= right) {
		// [left, right] 区间内只剩 1 或者 0 个数
		return;
	}
	// 1. 确定基准值，最右边	a[right]
	// 2. 做 partition，小的左，大的右，返回基准值最终的下标
	int pivotIndex = partition3(a, left, right);
	// 3. 分治处理左右两个小区间
	quickSortInternal(a, left, pivotIndex - 1);
	quickSortInternal(a, pivotIndex + 1, right);
}

#include <stack>

void quickSortNoR(int a[], int left, int right) {
	std::stack<int>	s;
	s.push(left);
	s.push(right);

	while (!s.empty()) {
		int high = s.top();	s.pop();
		int low = s.top(); s.pop();

		if (low >= high) {
			continue;
		}

		int pivotIndex = partition1(a, low, high);
		// [low, pivotIndex - 1]
		// [pivotIndex + 1, high]
		s.push(pivotIndex + 1);
		s.push(high);

		s.push(low);
		s.push(pivotIndex - 1);
	}
}

/*
时间复杂度：
最好		O(n * log(n))
平均		O(n * log(n))
最坏		O(n^2)

空间复杂度：
最好		O(log(n))
平均		O(log(n))
最坏		O(n)

稳定		不稳定
*/
void quickSort(int a[], int size) {
	quickSortNoR(a, 0, size - 1);
}

// 归并排序
void mergeSortInternal(int a[], int low, int high) {
	if (low >= high - 1) {
		return;
	}
	int mid = (low + high) / 2;
	// [low, mid)
	// [mid, high)
	mergeSortInternal(a, low, mid);
	mergeSortInternal(a, mid, high);
	// 3. 合并两个有序区间
	// [low, mid)		[mid, high)
	merge(a, low, mid, high);
}

void mergeSort(int a[], int size) {

}

void test() {
	int a[] = { 9, 3, 5, 4, 9, 2, 7, 9, 3, 6, 8, 8 };
	int size = sizeof(a) / sizeof(int);

	quickSort(a, size);

	printArray(a, size);
}