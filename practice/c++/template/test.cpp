#include <iostream>
using namespace std;

template <int a>
void func(void)
{

#if size > 5
     int j = 1;
#else
      double j = 2.4;
#endif

       std::cout<< j <<std::endl;

}

main()
{
    func<4>();
    func<7>();
}
