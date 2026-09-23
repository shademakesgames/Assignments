/*
    Name: Evan Garcia, 5007529509, 1002, #1
    Description: Bubble sort for a linked list
    Input: a list of intergers
    Output: a sorted list of intergers
*/
#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
double comparisons = 0;

LL<int> bubbleSort(LL<int> unsorted)
{
	auto tail = unsorted.end();

	//check if list is size 1
	if (unsorted.begin() == unsorted.end()){
		return unsorted;
	}
	
	//bool to control the loop
	bool swap = true;
	int count = 0;
	while (swap)
	{
		swap = false;
		auto i = unsorted.begin();
		auto j = unsorted.begin();
		++j;
		//compare j to a null iterator
		while (j != LL<int>::Iterator())
		{
			//if i greater than j, swap
			comparisons++;
			if (*i > *j)
			{
				unsorted.swap(i,j);
				swap = true;
			}
			i++;
			j++;
		}
		if (tail != unsorted.begin())
		{
			tail--;
		}

	}

	return unsorted;
	
}

int main()
{
	LL<int> list;
	int x;

	while (cin >> x)
		list.push_back(x);

	list = bubbleSort(list);

	auto i = list.begin();
	while (i != nullptr)
	{
		//cout << *i << endl;
		i++;
	}
	//cout << comparisons;

	return 0;
}