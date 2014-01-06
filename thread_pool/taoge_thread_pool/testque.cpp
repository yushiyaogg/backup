#include "header.h"

int main()
{
 queue<int*> myqueue;
 int* num;
 num = (int*)malloc(sizeof(int));
 *num = 5;
 myqueue.push(num);
 myqueue.pop();
 cout<<"num:"<<*num<<" length:"<<sizeof(size_t)<<endl;
 return 0;
}
