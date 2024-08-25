#include "leet.hpp"
#include <iostream>
using namespace std;

int main()
{
  vector<int> numbers({2, 7, 11, 15});
  auto sol = Solution::twoSum(numbers, 9);

  auto num1 = numbers[sol[0]];
  auto num2 = numbers[sol[1]];
  auto sum = num1 + num2;
  cout << num1 << " + " << num2 << " = " << sum << endl;

  numbers = vector<int>({3, 2, 4});
  sol = Solution::twoSum(numbers, 6);
  num1 = numbers[sol[0]];
  num2 = numbers[sol[1]];
  sum = num1 + num2;
  cout << num1 << " + " << num2 << " = " << sum << endl;

  numbers = vector<int>({3, 3});
  sol = Solution::twoSum(numbers, 6);
  num1 = numbers[sol[0]];
  num2 = numbers[sol[1]];
  sum = num1 + num2;
  cout << num1 << " + " << num2 << " = " << sum << endl;

  return EXIT_SUCCESS;
}
