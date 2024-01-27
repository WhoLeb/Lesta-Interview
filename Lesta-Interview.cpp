#include <iostream>
#include <random>

#include "isEven.h"
#include "ringBuffers.h"
#include "sort.h"

int main()
{
	int num = -121;
	std::cout << isEven(num) << ' ' << myIsEven(num) << ' ' << weirdIsEven(num) << '\n';

	RingBuffer1<int, 10> buffer1;

	for (int i = 0; i < 15; i++)
		buffer1.push(i);
	while (!buffer1.isEmpty())
		std::cout << buffer1.pop() << ' ';
	std::cout << '\n';

	RingBuffer2<int, 10> buffer2;
	for (int i = 0; i < 15; i++)
		buffer2.push(i);
	while (!buffer2.isEmpty())
		std::cout << buffer2.pop() << ' ';

	std::cout << '\n';
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = std::rand();
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
	quickSort(arr, 0, 9);
	for (int i = 0; i < 10; i++)
		std::cout << arr[i] << ' ';

	return 0;
}