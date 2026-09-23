#include "priorityQ.h"

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ()
{
	//set the capacity and size
	capacity = 5;
	size = 0;
	//initialize the heapArray
	heapArray = new priorityType[capacity + 1];
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
	//resize if needed
	if (size == capacity)
	{
		capacity *= 2;
		priorityType* newArray = new priorityType[capacity + 1];
		for (std::size_t i = 1; i <= size; i++)
		{
			newArray[i] = heapArray[i];
		}
		delete[] heapArray;
		heapArray = newArray;
	}
	//push back
	size++;
	heapArray[size] = priorityType(key, priority);
	itemToPQ[key] = size;
	bubbleUp(size);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
	//if it is empty, return
	if (isEmpty()) return;

	//pop the front
	itemToPQ.erase(heapArray[1].key);
	if (size > 1)
	{
		heapArray[1] = heapArray[size];
		itemToPQ[heapArray[1].key] = 1;
		size--;
		bubbleDown(1);
	} else {
		size--;
	}
}

template <class t1, class t2>
void priorityQ<t1, t2>::update_element(const t1& key, const t2& priority)
{
    //variables
	std::size_t index = itemToPQ[key];
	t2 oldPriority = heapArray[index].priority;
	heapArray[index].priority = priority;
	//use the operator in lander class to find which priority is greater
	if (priority < oldPriority)
		bubbleUp(index);
	else
		bubbleDown(index);
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
	//return priority at index 1
	return heapArray[1].priority;
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
	//return key at index 1
	return heapArray[1].key;
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_element(t1 key)
{
	//get the element
	std::size_t index = itemToPQ[key];
	return heapArray[index].priority;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
	//if size == 0, return
	if (size == 0)
		return true;
	return false;
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
	//loop while index greater than 1
	while (index > 1)
	{
		//get the parent
		std::size_t parent = index / 2;
		//if priority < parent priority, swap
		if (heapArray[index].priority < heapArray[parent].priority)
		{
            //swap logic
			priorityType temp = heapArray[index];
			heapArray[index] = heapArray[parent];
			heapArray[parent] = temp;
			itemToPQ[heapArray[index].key] = index;
			itemToPQ[heapArray[parent].key] = parent;
			index = parent;
		}
		else
		{
			break;
		}
	}
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
	while (true)
	{
		//get left and right child indexes
		std::size_t left = 2 * index;
		std::size_t right = 2 * index + 1;
		//get the smallest possible index
		std::size_t smallest = index;

        //checks if its the left child
		if (left <= size && heapArray[left].priority < heapArray[smallest].priority)
			smallest = left;
        //checks if its the right child
		if (right <= size && heapArray[right].priority < heapArray[smallest].priority)
			smallest = right;

        //if smallest != the index, swap
		if (smallest != index)
		{
			priorityType temp = heapArray[index];
			heapArray[index] = heapArray[smallest];
			heapArray[smallest] = temp;
			itemToPQ[heapArray[index].key] = index;
			itemToPQ[heapArray[smallest].key] = smallest;
			index = smallest;
		} else {
            //end if smallest == index
			break;
		}
	}
}

template class priorityQ<std::string, int>;
template class priorityQ<std::string, lander>;