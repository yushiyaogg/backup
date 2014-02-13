#include <iostream>
using namespace std;

struct _2By2Matrix
{
    int v00;
    int v01;
    int v10;
    int v11;
};

_2By2Matrix Multi_Matrix(struct _2By2Matrix m1, struct _2By2Matrix m2)
{
    struct _2By2Matrix temp;
    temp.v00 = m1.v00 * m2.v00 + m1.v01 * m2.v10;
    temp.v01 = m1.v00 * m2.v01 + m1.v01 * m2.v11;
    temp.v10 = m1.v10 * m2.v00 + m1.v11 * m2.v01;
    temp.v11 = m1.v10 * m2.v01 + m1.v11 * m2.v11;
    return temp;
}

_2By2Matrix MatrixPower(int n)
{
    struct _2By2Matrix element;
    element.v00 = element.v01 = element.v10 = 1;
    element.v11 = 0;
    struct _2By2Matrix zero_element;
    zero_element.v00 = zero_element.v01 = zero_element.v10 =zero_element.v11 = 0;
    struct _2By2Matrix result;

    if (n == 0)
        return element;
    if(n == 1)
        return element;

    if(n % 2 == 0)
    {
        result = MatrixPower(n/2);
        return(Multi_Matrix(result,result));
    }
    if(n % 2 == 1)
    {
        result = MatrixPower((n-1)/2);
        result = Multi_Matrix(result,result);
        result = Multi_Matrix(result,element);
        return result;
    }
}
int main()
{
    struct _2By2Matrix F;
    F = MatrixPower(0);
    cout<<F.v00<<endl;
    F = MatrixPower(1);
    cout<<F.v00<<endl;
    F = MatrixPower(2);
    cout<<F.v00<<endl;
    F = MatrixPower(3);
    cout<<F.v00<<endl;
    F = MatrixPower(4);
    cout<<F.v00<<endl;
    F = MatrixPower(5);
    cout<<F.v00<<endl;
    F = MatrixPower(6);
    cout<<F.v00<<endl;
    F = MatrixPower(7);
    cout<<F.v00<<endl;
}
