#include "map.hpp"
// clang-format off
int main() 
{

  Map<int, int> m;
  m.insert(pair<int, int>::make_pair(3, 4));
  m.insert(pair<int, int>::make_pair(5, 4));
  m.insert(pair<int, int>::make_pair(1, 2));
  m.insert(pair<int, int>::make_pair(1, 245));

  std::cout << m.size() << "\t" << m.empty() << "\n";

  m.print_map();

  m[6] = 98;
  m[2] = 45;

  m.print_map();
  return 0;
}