/////////////////////////////////////////////
//level travesal of a binary tree
/////////////////////////////////////////////////

#include <iostream>
#include "binary_search_tree.h"
using namespace std;

int main()
{
    //class Queue queue(100);
    Binary_Search_Tree binary_search_tree;
    binary_search_tree.insert_node(8);
    binary_search_tree.insert_node(6);
    binary_search_tree.insert_node(5);
    binary_search_tree.insert_node(7);
    binary_search_tree.insert_node(10);
    binary_search_tree.insert_node(9);
    binary_search_tree.insert_node(11);
    binary_search_tree.level_traversal();
}
