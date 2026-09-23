#include "hashMap.h"
#include <cstdlib>
#include <string>
#include <cmath>
using std::string;
using std::size_t;

template <class t1, class t2>
hashMap<t1, t2>::hashMap(size_t initCapacity)
{
    //set variables
    capacity = initCapacity;
    items1 = 0;
    items2 = 0;
    //allocate an array node*[capacity] to table 1 and table 2
    table1 = new node*[capacity];
    table2 = new node*[capacity];
    //set each element of table 1 and table 2 with nullptr
    for (int i = 0; i < capacity; i++)
    {
        table1[i] = nullptr;
        table2[i] = nullptr;
    }
}

template <class t1, class t2>
hashMap<t1, t2>::~hashMap()
{
    //destructor, go through each table and delete each element
    //then delete the tables
    for (int i = 0; i < capacity; i++)
    {
        if (table1[i] != nullptr)
        {
            delete table1[i];
        }
        if (table2[i] != nullptr)
        {
            delete table2[i];
        }
    }
    delete[] table1;
    delete[] table2;

}

template <class t1, class t2>
size_t hashMap<t1, t2>::hash1(string k)
{
    //get the sum of ki  x 10^i from i = 0 to kLen-1
    size_t sum = 0;
    for (int i = 0; i <= k.length()-1; i++)
    {
        sum += k[i] * std::pow(10, i);
    }
    return sum;
}

template <class t1, class t2>
size_t hashMap<t1, t2>::hash2(string k)
{
    //get the sum of ki  x 10^(kLen-i-1) from i = 0 to kLen-1
    size_t sum = 0;
    for (int i = 0; i <= k.length()-1; i++)
    {
        sum += k[i] * std::pow(10, k.length()-i-1);
    }
    return sum;
}

template <class t1, class t2>
void hashMap<t1, t2>::resize(size_t amount)
{
    //save the old capacity
    size_t oldCapacity = capacity;
    capacity *= amount;
    //create a copy of the arrays and set
    node ** oldTable1 = table1;
    node ** oldTable2 = table2;
    //create a new larger array, then set table1 and table 2 to them
    table1 = new node*[capacity];
    table2 = new node*[capacity];
    //fill with nullptrs and rehash
    for (int i = 0; i < capacity; i++)
    {
        table1[i] = nullptr;
        table2[i] = nullptr;
    }
    for (int i = 0; i < oldCapacity; i++)
    {
        if (oldTable1[i] != nullptr)
        {
            table1[lookup(oldTable1[i]->key)] = new node(oldTable1[i]->key, oldTable1[i]->value);
        }
        if (oldTable2[i]!= nullptr)
        {
            table2[lookup(oldTable2[i]->key)] = new node(oldTable2[i]->key, oldTable2[i]->value);
        }
    }
    //deallocate the old arrays
    for (int i = 0; i < oldCapacity; i++)
    {
        delete oldTable1[i];
        delete oldTable2[i];
    }
    delete[] oldTable1;
    delete[] oldTable2;

}

template <class t1, class t2>
size_t hashMap<t1, t2>::lookup(t1 k)
{
    //safeguard just in case the hash maps goes out of bounds, probably never will
    bool out_of_bounds = false;
    int i = 0;
    for (int i = 0; i < capacity; i++)
    {
        //hashing formula
        size_t index = (hash1(k) + i * hash2 ( k )) % capacity;
        //if found or and empty space in table 1
        if (table1[index] != nullptr && table1[index]->key == k)
        {
            return index;
        }
        //if found on table 2 or empty space in table 2
        if (table2[index] != nullptr && table2[index]->key == k)
        {
            return index;
        }
        //if not found in table 1 or table 2
        if (table1[index] == nullptr || table2[index] == nullptr)
        {
            return index;
        }
    }
    //return capacity if not found at all
    return capacity;
}

template <class t1, class t2>
bool hashMap<t1, t2>::find(t1 k)
{
    size_t index = lookup(k);
    if (lookup(k) == capacity)
        return false;
    //lookup in both tables, and if it is nullptr return false, if something is found, return true.
    //also check if the key matches
    return (table1[index] != nullptr && table1[index]->key == k) || (table2[index] != nullptr && table2[index]->key == k);
}

template <class t1, class t2>
void hashMap<t1, t2>::insert(t1 k, t2 v)
{
    size_t index = lookup(k);
    if (index == capacity)
        return;
    //if not found in table 1, insert in table 1, else, insert in table 2
    if (table1[index] == nullptr)
    {
        table1[index] = new node(k,v);
        items1++;
    } else {
        if (table2[index] == nullptr)
        {
            table2[index] = new node(k,v);
            items2++;
        }   
    }

    //resize if capacity is at 20%
    if ((items1 > capacity*0.2)||(items2 > capacity*0.2))
    {
        resize(2);
    }
}

template <class t1, class t2>
void hashMap<t1, t2>::update(t1 k, t2 v)
{
    size_t index = lookup(k);
    if (index == capacity)
        return;
    //check if it even exists
    if (find(k))
    {
        //check for nullptr and if the key matches!
        if (table1[index] != nullptr && table1[index]->key == k){
            table1[index]->value = v;
        } else  if (table2[index] != nullptr && table2[index]->key == k){
            table2[index]->value = v;
        }
    }
}

template <class t1, class t2>
t2 hashMap<t1, t2>::getValue(t1 k)
{
	size_t index = lookup(k);
    if (index == capacity)
        return t2();
    //check if it even exists
    if (find(k))
    {
        //check for nullptr and if the key matches!
        if (table1[index] != nullptr && table1[index]->key == k){
            return table1[index]->value;
        } else  if (table2[index] != nullptr && table2[index]->key == k){
            return table2[index]->value;
        }
    }
    return t2();
}


template class hashMap<string, int>;
template class hashMap<string, string>;
template class hashMap<string, bool>;
template class hashMap<string, menuType>;
