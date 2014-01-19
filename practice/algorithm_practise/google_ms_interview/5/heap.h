///////////////////////////////////
// Heap
/////////////////////////////////


#include <iostream>
using namespace std;

class Heap{
    public:
    int size;
    int max_size;
    int* ptr;
    int* top;
    bool type;//0 - small top; 1 - big top

//    int Heap();
    Heap(int);
    int Max_Heap_Insert(int);
    int Min_Heap_Insert(int);
    int show(); 
    private:

    int Max_Heapify();
    int Min_Heapify();
    int Max_Heap_Sort();
    int swap(int*,int*);

};
