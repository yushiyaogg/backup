#include <iostream>
using namespace std;

template <class type>
class sort_tree
{
    public:
    class node
    {
        type number;
        node* left_child;
        node* right_child;
    };
    node *root;
    int insert_node(type );
    int delete_node(type);

};
