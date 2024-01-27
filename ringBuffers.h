#pragma once

#include <memory>

/**
* Первый вариант - я использую массив фиксированной величины в качестве буфера. Это классическая реализация кольцевого буфера.
*
* Плюсы: 
* Данные хранятся рядом друг с другом, очень быстрый доступ. 
* Кроме того, в отличие от второго решения, размер буфера примерно совпадает с размером sizeof(T) * sz.
*
* Минусы:
* Нo все данные хранятся в небольшом, по сравнению с кучей, стеке.
* Кроме того если вдруг при использовании необходимо менять размер кольцевого буфера, в данной реализации это было бы невозможно.
*/
template<class T, size_t sz>
class RingBuffer1
{
public:
	RingBuffer1() :
		m_head (0),
		m_tail(0) 
	{}
	~RingBuffer1() = default;

	inline size_t size() const { return sz; }
	inline bool isEmpty() const { return b_isEmpty; }
	inline T top() const { return m_buffer[m_head]; }

	void push(T val)
	{
		m_buffer[m_tail] = val;
		if (b_full)
			m_head = (m_head + 1) % sz;
		m_tail++;
		m_tail %= sz;
		b_full = m_head == m_tail;
		b_isEmpty = false;
	}

	T pop()
	{
		T val = m_buffer[m_head];
		m_head--;
		m_head = m_head < 0 ? sz - 1 : m_head;
		if (m_head == m_tail) b_isEmpty = true;
		return val;
	}

private:
	T m_buffer[sz];
	int m_head; // read from head
	int m_tail; // write to tail
	bool b_isEmpty = true;
	bool b_full = false;
};

/**
* Второй вариант - структура в основе буфера - двунаправленный связный список.
* 
* Плюсы:
* Основной плюс этой реализации, который я вижу - возможность изменения размера буфера, при добавлении необходимых функций, как в классическом связном списке.
* 
* Минусы:
* Данные хранятся разрозненно в куче, поэтому может произойти так, что они будут находиться в совершенно разных блоках памяти и их придется подгружать довольно долго.
* Кроме того, теперь для хранения каждого значения используется не только размер структуры элемента T, 
* но и дополнительная информация - указатели на предыдущий и следующий блоки и, так как я пользуюсь умными указателями, их контрольные блоки.
*/

template<class T, size_t sz>
class RingBuffer2
{
public:
	RingBuffer2()
	{
		m_head = std::make_shared<Node>();
		m_tail = m_head;
		std::shared_ptr<Node> tmpNode = m_head;
		for (int i = 0; i < sz; i++)
		{
			if (i == sz - 1)
			{
				tmpNode->next = m_head;
				m_head->prev = tmpNode;
				break;
			}
			tmpNode->next = std::make_shared<Node>();
			tmpNode->next->prev = tmpNode;
			tmpNode = tmpNode->next;
		}
	}

	~RingBuffer2() = default;

	size_t size() const { return sz; }
	bool isEmpty() const { return b_empty; }
	T top() const { return m_head->value; }

	void push(T val)
	{
		b_empty = false;
		m_tail->value = val;
		m_tail = m_tail->next;
		if (b_full)
			m_head = m_head->next;
		b_full = m_tail == m_head;
	}

	T pop()
	{
		if (b_empty) 
			throw 404;
		T val = m_head->value;
		m_head = m_head->prev;
		b_empty = m_head == m_tail;
		return val;
	}

private:
	class Node
	{
	public:
		~Node() { std::cout << "Deleted node \n"; }
		T value;
		std::shared_ptr<Node> prev;
		std::shared_ptr<Node> next;
	};

	std::shared_ptr<Node> m_head;
	std::shared_ptr<Node> m_tail;

	bool b_full = false;
	bool b_empty = true;
};

