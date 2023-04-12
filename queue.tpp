#include "queue.h"
#include <sstream>

template <typename T>
Queue<T>::Queue(int initialSize)
{
	this->qPtr = new T[initialSize];
	this->frontIdx = 0;
}

template <typename T>
bool Queue<T>::isEmpty()
{
	return !(this->size);
}

template <typename T>
int Queue<T>::getSize()
{
	return this->size;
}

template <typename T>
int Queue<T>::getCapacity()
{
	return this->capacity;
}

template <typename T>
void Queue<T>::enqueue(T item)
{
	if (this->capacity == this->size)
	{
		int newCapacity = this->capacity * 2;
		T *newQPtr = new T[newCapacity];
		for (int i = 0; i < this->size; i++)
		{
			newQPtr[i] = qPtr[frontIdx++ % capacity];
		}
		capacity = newCapacity;
		delete[] qPtr;
		frontIdx = 0;
		qPtr = newQPtr;
		newQPtr = nullptr;
	}
	qPtr[(frontIdx + size) % capacity] = item;
	size++;
}

template <typename T>
T Queue<T>::dequeue()
{
	if (this->isEmpty())
	{
		throw EmptyQueueException();
	}

	int takePos = frontIdx;
	frontIdx = (frontIdx + 1) % capacity;
	size--;

	return qPtr[takePos];
}

template <typename T>
string Queue<T>::toString()
{
	stringstream ss;
	ss << "queue: ";
	for (int i = 0; i < this->size; i++)
	{
		ss << qPtr[(frontIdx + i) % capacity] << " ";
	}
	return ss.str();
}

template <typename T>
T Queue<T>::peek()
{
	return qPtr[frontIdx];
}

template <typename T>
Queue<T>::~Queue()
{
	delete[] this->qPtr;
}
