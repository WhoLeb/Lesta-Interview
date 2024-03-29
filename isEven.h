#pragma once

// Этот способ определяет последний бит в числе (делит по модулю на 2) и затем проверяет, равен ли он нулю
bool isEven(int value) { return value % 2 == 0; }

// Мой способ похож на тот что был приведен вами, но он вместо логического сравнения и деления по остатку делает побитовое И для определения последнего бита
bool myIsEven(int value) { return !(value & 1); }

// Странный способ, неэффективный, непрактичный, но сделает свою работу... Это как в мемах "жаль, что нет способа сделать это проще"
bool weirdIsEven(int value) 
{
	value = std::abs(value);
	while (value > 1)
		value -= 2;
	return value == 0;
}

/**
* Первая реализация более привычна, и, для большинства, наверное, более логична, мы определяем остаток от деления на 2, что по определению и есть определение четности
* второй вариант может быть более привычен тем, кто часто работал с битами и он менее читаем, но можно определять нечетность числа за меньшее количество операций в asm
* Последний вариант это прикол, он будет работать медленее в зависимости от размера числа, но вы просили чего-то отличного по сути, а я не уверен что второй прям ОТЛИЧАЕТСЯ по сути...
*/
