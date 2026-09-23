#include "bst.h"
using std::string;

template <class t1, class t2>
void bst<t1, t2>::deallocateTree(binTreeNode * r)
{
    //recursive post order binary search
    if (r == nullptr) //base case
        return;
    
    deallocateTree(r->left); //recursive calls
    deallocateTree(r->right);
    

    delete r; //deallocate

}

template <class t1, class t2>
typename bst<t1, t2>::binTreeNode* bst<t1, t2>::insert(binTreeNode * r, t1 k, t2 v)
{
    //recursive binary tree insert
    //base case
    if (r == nullptr)
        return new binTreeNode(k,v);
    
    //compare, then decide to traverse left or right
    if (k < r->key)
        r->left = insert(r->left, k, v);
    else
        r->right = insert(r->right, k, v);
    return r;

}

template <class t1, class t2>
void bst<t1, t2>::update(binTreeNode * r, t1 k, t2 v)
{
    //search for key, then replace the value
    //base case
    if (r == nullptr)
        return;

    //if key found, replace value
    if (r->key == k)
    {
        r->value = v;
        return;
    }
    //compare, then decide to traverse left or right
    if (k < r->key)
        update(r->left, k, v);
    else
        update(r->right, k, v);
}

template <class t1, class t2>
t2 bst<t1, t2>::getValue(binTreeNode * r, t1 k)
{
     //search for key, then replace the value
     //base case
    if (r == nullptr)
        return t2{};
    //if key found, return value
    if (r->key == k)
    {
        return r->value;
    }
    //compare, then decide to traverse left or right
    if (k < r->key)
        return getValue(r->left, k);
    else
        return getValue(r->right, k);
}

template <class t1, class t2>
string bst<t1, t2>::getPath(t1 k)
{
    //not recursive
    if (root == nullptr)
    {
        return "";
    }
    //S case
    if (root->key == k)
    {
        return "S";
    }

    //non recursive traversal of binary tree, saving direction into a string
    string path = "";
    binTreeNode * tmp = root;
    while (tmp->key != k)
    {
        if (k < tmp->key)
        {
            path += "L";
            tmp = tmp->left;
        }
        else {
            path += "R";
            tmp = tmp->right;
        }
    }
    if (tmp == nullptr)
        return "";


    return path;
}

template class bst<char, std::string>;
template class bst<std::string, char>;
