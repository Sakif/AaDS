#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main(int const argc, char const **argv) {
  srand(time(0));
  auto arg_index = 0;
  auto no_to_gen = 100;
  auto max = INT_MAX;
  auto rand_nums = ofstream("rand.txt");

  cout << argv[arg_index] << " created on " << __DATE__ << " at " << __TIME__ << endl;

  if (argc > 1) {
    no_to_gen = atoi(argv[++arg_index]);
  }

  if (argc > 2) {
    max = atoi(argv[++arg_index]);
  }

  for (auto i = 0; i < no_to_gen; i++) {
    rand_nums << rand() % max << endl;
  }

  rand_nums.close();
  return EXIT_SUCCESS;
}
