#include <iostream>

using namespace std;

int test(int **a)
{
    cout <<a[0][0]<<endl;
    return -1;
}
int main()
{
//    int a[] ={1,2,3,4,5};
//    int *ptr = a;
//    cout <<ptr[0]<<endl;

    int a2[3][2] = {{1,2},{3,4},{5,6}};
 //   int ** ptr2 =(int **) a2;
    int ** ptr2 =(int **)new int[12];
    cout <<ptr2[1][1]<<endl;
   // test(ptr2);
   //
   int **LCS_length;
   int length1 =3;
   int length2 =3;
   LCS_length = (int**)(new int[length1]);
   for(int i = 0; i < length1; ++ i)
       LCS_length[i] = (int*)new int[length2];

   for(int i = 0; i < length1; ++ i)
       for(int j = 0; j < length2; ++ j)
           LCS_length[i][j] = 0;
   test(LCS_length);
    return 0;
}

