#include "heap.h"
/*int Heap::Heap()
{
    this -> size = 0;
    this -> ptr = NULL;
    this -> top = NULL;
    this -> type = 0;
}*/

Heap::Heap(int size)
{
    
    int* temp_ptr = ptr;
    this -> max_size = size;
    this -> size = 0;
    this -> top = NULL;
    this -> ptr = new int[size];
    this -> type = 1;

}

int Heap::swap(int* a,int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}

int Heap::show()
{
    for(int i = 0 ; i <size;i++)
    {
        cout << *(ptr + i)<<endl;
        
    }
    return 0;
}
int Heap::Max_Heapify()
{
    if(size < 2)
        return 0;
    int mark = size / 2;
    if(size == mark * 2)
    {
        if(*(ptr + mark - 1 ) < *(ptr + 2 * mark -1))
            swap(ptr+mark-1,ptr+2*mark-1);
    }
    if(size == mark * 2 + 1)
    {
        if(*(ptr + mark - 1) < *(ptr + mark * 2 -1) || *(ptr + mark -1 ) < * (ptr + mark * 2 ) )
        {
            if(*(ptr + mark * 2 - 1) > *(ptr + mark *2))
            {
                swap(ptr+mark-1,ptr+mark*2-1);
            }
            else
            {
                swap(ptr+mark-1,ptr+mark*2);
            }
                    
        }
    }
    if(size == 2||size ==3)
        return 0;
    for(int i = size / 2 -1 ; i > 0 ;i--)
    {
      int mark = i ; 
            while(*(ptr + mark - 1) < *(ptr + mark * 2 -1) || *(ptr + mark -1 ) < * (ptr + mark * 2 ) )
            {
                if(*(ptr + mark * 2 - 1) > *(ptr + mark *2))
                {
                    swap(ptr+mark-1,ptr+mark*2-1);
                    mark = mark * 2;
                }
                else
                {
                    swap(ptr+mark-1,ptr+mark*2);
                    mark = mark *2 +1;
                }
                if(mark > size /2)
                    break;
                if(mark == size / 2)
                {
                    
                    if(*(ptr + mark * 2 - 1) > *(ptr + mark *2))
                    {
                        int temp = *(ptr + mark -1);
                        *(ptr + mark -1) = *(ptr + mark * 2 - 1);
                        *(ptr + mark * 2 - 1) = temp;
                        mark = mark * 2;
                        break;
                    }
                    break;
                }
                    

            }
    }
    return 0;
}

int Heap::Min_Heapify()
{
    return 0;
}

int Heap::Max_Heap_Insert(int num)
{
    if(this -> size < this -> max_size)
    {
        *(this -> ptr + size) = num;
        this -> size += 1;
        
        if(this -> size == this -> max_size)
            Max_Heapify();
    }
    else
    {
        if(num >= *ptr)
            return 0;
        else
        {
            *ptr = num;
            Max_Heap_Sort();
        }
    }

    return 0;
}

int Heap::Max_Heap_Sort()
{

        int mark = 1;
        if(size > 2)
        {
            while(*(ptr + mark - 1) < *(ptr + mark * 2 -1) || *(ptr + mark -1 ) < * (ptr + mark * 2 ) )
            {
                if(*(ptr + mark * 2 - 1) > *(ptr + mark *2))
                {
                    int temp = *(ptr + mark -1);
                    *(ptr + mark -1) = *(ptr + mark * 2 - 1);
                    *(ptr + mark * 2 - 1) = temp;
                    mark = mark * 2;
                }
                else
                {
                    int temp = *(ptr + mark -1);
                    *(ptr + mark -1) = *(ptr + mark * 2 );
                    *(ptr + mark * 2 ) = temp;
                    mark = mark *2 +1;
                }
                if(mark > size /2)
                    return 0;
                if(mark == size / 2)
                {
                    
                    if(*(ptr + mark * 2 - 1) > *(ptr + mark *2))
                    {
                        int temp = *(ptr + mark -1);
                        *(ptr + mark -1) = *(ptr + mark * 2 - 1);
                        *(ptr + mark * 2 - 1) = temp;
                        mark = mark * 2;
                        return 0;
                    }
                    return 0;
                }
                    

            }
        }
            if (size == 1)
                return 0;
            if(size == 2)
            {
                if(*ptr < *(ptr +1))
                {
                    int temp = *ptr;
                    *ptr = * (ptr + 1);
                    *(ptr) = temp;
                    return 0;
                }
                return 0;
            }
}

int Heap::Min_Heap_Insert(int num)
{
    if(this -> size == 0)
    {
        
    }

    return 0;
}
