//Fulkerson.h header file
//Standard Ford-Fulkerson Algorithm
//Author: Fengdong

#include <stack>
#include <list>

using namespace std;

typedef pair<int,int> flowPair;


typedef struct _node
{
    int number;
    int C;
    int F;
    struct _node* next;
    _node(int _number,int _C)
    {
        number = _number;
        C = _C;
        F = 0;
        next = NULL;
    }
}Node;


typedef struct _headNode
{
    Node* next;

    _headNode()
    {
        next = NULL;
    }
}headNode;

class FordFulkerson
{
public:
    FordFulkerson();
    ~FordFulkerson();
    void getMaxFlow();
    void displayInfo();
private:
    void mark();
    void init();
    void constructAdjList(); //construct adjacent table
    void pop(int number);    // pop stack
    void adjustFlow();        // adjust flow if target node marked

    Node* findNode(Node* _current); //which node should be pushed into the stack
    Node* getAdjustedNode(int number,int _target); //change F value when adjust flow
   
   
private:
    static const int headCount = 7;
    flowPair currentState[headCount];
    int Qs;              // how many flow increased
    int augmentingPath ; // how many "augmenting path"
    headNode nodes[headCount];
    stack<Node*>* nodeStack;
    int current;
    int source ;
    int target;

};
