#include "leet.hpp"

using namespace std;

vector<int> Solution::twoSum(const vector<int> &nums, const int target)
{
  vector<int> sol(2);

  for (unsigned indexA = 0; indexA < nums.size(); indexA++)
  {
    if (nums[indexA] < target)
    {
      for (unsigned indexB = indexA + 1; indexB < nums.size(); indexB++)
      {
        if (nums[indexB] < target)
        {
          int sum = nums[indexA] + nums[indexB];
          if (sum == target)
          {
            sol[0] = indexA;
            sol[1] = indexB;
            return sol;
          }
        }
      }
    }
  }
  return sol;
}
