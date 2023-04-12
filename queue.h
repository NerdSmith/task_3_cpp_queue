#pragma once

using namespace std;

class EmptyQueueException
{
};

template <typename T>
class Queue
{
private:
	T *qPtr;
	int frontIdx = -1;
	int size = 0;
	int capacity = 5;

public:
	class iterator
	{
	public:
		typedef iterator self_type;
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		iterator(
			pointer ptr,
			int cIdxPos,
			int *frontIdx,
			int *size,
			int *capacity) : ptr_(ptr),
							 currIdxPos(cIdxPos),
							 frontIdx_(frontIdx),
							 size_(size),
							 capacity_(capacity)
		{
			end_ = &(ptr_[*capacity]);
		}

		self_type operator++()
		{
			if (currIdxPos <= *size_)
			{
				currIdxPos++;
			}
			return *this;
		}

		self_type operator++(int junk)
		{
			self_type i = *this;
			if (currIdxPos <= *size_)
			{
				currIdxPos++;
			}
			return i;
		}

		pointer get_ptr() const
		{
			if (currIdxPos >= *size_)
			{
				return end_;
			}
			return ptr_ + (*frontIdx_ + currIdxPos) % *capacity_;
		}

		reference operator*()
		{
			return *(this->get_ptr());
		}

		pointer operator->()
		{
			return this->get_ptr();
		}

		bool operator==(const self_type &rhs)
		{
			return get_ptr() ==
				   rhs.get_ptr();
		}

		bool operator!=(const self_type &rhs)
		{
			return get_ptr() !=
				   rhs.get_ptr();
		}

	private:
		int currIdxPos = 0;
		int *frontIdx_;
		int *size_;
		int *capacity_;
		pointer end_;
		pointer ptr_;
	};

	Queue(int initialSize);
	bool isEmpty();
	void enqueue(T item);
	T dequeue();
	T peek();
	int getSize();
	int getCapacity();
	string toString();
	iterator begin()
	{
		return iterator(qPtr, 0, &frontIdx, &size, &capacity);
	}
	iterator end()
	{
		return iterator(qPtr, capacity, &frontIdx, &size, &capacity);
	}
	~Queue();
};

#include "queue.tpp"
