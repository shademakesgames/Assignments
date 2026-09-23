/*
    Name: Evan Garcia, 5007529509, 1002, #1
    Description: Merge sort for a linked list
    Input: a list of intergers
    Output: a sorted list of intergers
*/
#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

int comparisons = 0;

LL<int> merge(const LL<int>& left_list, const LL<int>& right_list){
	//create a new list to house the merged list
	LL<int> merged;
	auto i = left_list.begin();
	auto j = right_list.begin();
	//merge the two lists
	while (i != LL<int>::Iterator() && j != LL<int>::Iterator())
	{
		comparisons++;
		if (*i <= *j)
		{
			merged.push_back(*i);
			i++;
		} 
		else
		{
			merged.push_back(*j);
			j++;
		}
	}

	//handle edge cases
	while (i != LL<int>::Iterator())
	{
		merged.push_back(*i);
		i++;
	}
	while (j != LL<int>::Iterator())
	{
		merged.push_back(*j);
		j++;
	}
	return merged;

}

LL<int> mergeSort(const LL<int>& unsorted, LL<int>::Iterator left, LL<int>::Iterator right)
{
	//base case
	if (left == right)
	{
		LL<int> single;
		single.push_back(*left);
		return single;
	}
	//compute midpoint
	auto i = left;
	int count = 1;
	//while i does not equal the right iterator
	while(i != right)
	{
		i++;
		count++;
		
	}
	auto mid = left;
	//move mid to the midpoint
	for(int n = 0; n < count/2-1; n++)
	{
		mid++;
	}


	//recursive call
	LL<int> left_list = mergeSort(unsorted, left, mid);
	mid++; //increment the midpoint
	LL<int> right_list = mergeSort(unsorted, mid, right);
	LL<int> merged = merge(left_list, right_list);
	return merged;


}

int main()
{
	LL<int> list;
	int x;

	while (cin >> x)
		list.push_back(x);


	list = mergeSort(list, list.begin(), list.end());

	auto i = list.begin();
	while (i != nullptr)
	{
		//cout << *i << endl;
		i++;
	}
	//cout << comparisons;

	return 0;
}
