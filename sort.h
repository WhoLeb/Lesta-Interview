#pragma once

#include <utility>
/*
* Один из самых быстрых, в общем случае, алгоритмов для сортировки - quick sort, работает в среднем за θ(nlog n)
* Каждая итерация вхождения в рекурсию режет массив примерно вдвое, поэтому и получается n log n
* 
* Однако, он не очень полезен для маленьких массивов, а так же, если будет выбрана не медиана, то может работать за O(n^2)
*/
void quickSort(int* arr, int l, int r)
{
	int i = l;
	int j = r;
	int median = arr[(i + j) / 2];

	while (i <= j)
	{
		while (arr[i] < median)
			i++;
		while (arr[j] > median)
			j--;
		if (i <= j)
		{
			std::swap<int>(arr[i], arr[j]);
			i++;
			j--;
		}
		if (j > l)
			quickSort(arr, l, j);
		if (i < r)
			quickSort(arr, i, r);
	}
}
