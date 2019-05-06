#pragma once
#include <iostream>
#include "RPQ.h"

template <typename T, typename Comparator> class Heap
{
public:
	Heap(std::vector<T> data, int dataSize);
	void showTop();
	void push(T val);
	bool empty();
	T pop();
	T Top();

private:
	void restoreHeap(int parent);
	int _size;
	std::vector<T> _data;
	int left(int iterator);
	int right(int iterator);
	Comparator comparator;
};
//  5 5 3 1

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(std::vector<T> data, int dataSize)
{
	_size = dataSize;
	_data = data;
	for (int i = _size / 2; i >= 0; --i)
		restoreHeap(i);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(T val)
{
	_size++;
	_data.push_back(val);

	for (int i = _size / 2; i >= 0; --i)
		restoreHeap(i);
}

template <typename T, typename Comparator>
T Heap<T, Comparator>::Top()
{
	return _data[0];
}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty()
{
	return _size;
}
template <typename T, typename Comparator>
void Heap<T, Comparator>::showTop()
{
	std::cout << "On top is: " << Top() << std::endl;
}
template <typename T, typename Comparator>
T Heap<T, Comparator>::pop()
{
	T toReturn = _data[0];
	_data[0] = _data[--_size];
	_data.erase(_data.end() -1);
	restoreHeap(0);
	return toReturn;
}
template <typename T, typename Comparator>
int Heap<T, Comparator>::left(int iterator)
{
	return (iterator * 2 + 1);
}
template <typename T, typename Comparator>
int Heap<T, Comparator>::right(int iterator)
{
	return (iterator * 2 + 2);
}
template <typename T, typename Comparator>
void Heap<T, Comparator>::restoreHeap(int parent)  //przywracam kopiec
{
	int largest = parent;
	// Porz¹dkujê i szukam najwiêkszego
	if ((left(parent) < _size) && comparator(_data[left(parent)], _data[largest]))
		largest = left(parent);
	if (right(parent) < _size && comparator(_data[right(parent)], _data[largest]))
		largest = right(parent);

	if (largest != parent)
	{
		std::swap(_data[parent], _data[largest]);
		restoreHeap(largest);
	}
}
