#include <iostream>
using namespace std;



int count_number_k(int k, int n)
{
  int base_scale = 1;
  int passed = 0;
  int answer = 0;
  while(n)
  {
    int current = n % 10;
    n = n / 10;
    if (k < current)
      answer += (n + 1) * base_scale;
    else if (k == current)
      answer += n * base_scale + passed + 1;
    else
      answer += n * base_scale;
    passed += current * base_scale;
    base_scale *= 10;
  }
  return answer;
}

int main()
{
    cout << count_number_k(1,21345)<<endl;
}
