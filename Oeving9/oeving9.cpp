#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, const vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

bool bigger (int i) { return i>15; }

int main() {
  vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};
  cout << "v1: " << v1 << endl;

  vector<int> v2 = {2, 3, 12, 14, 24};
  cout << "v2: " << v2 << endl;

  // a)
  auto pos = find_if(v1.begin(), v1.end(), bigger);
  if (pos != v1.end()) {
    cout << "The first number bigger than 15 in v1 is: " << *pos << "\n";
  } else {
    cout << "v1 doesnt contain any number bigger than 15\n";
  }

  // b)
  auto approx = [](const auto& a, const auto& b) {return abs(a-b)<=2; };
  bool eq5 = equal(v1.begin(), v1.begin() + 5, v2.begin(), approx);
  bool eq4 = equal(v1.begin(), v1.begin() + 4, v2.begin(), approx);
  cout << boolalpha;
  cout << "[v1[0..5> vs v2] " << eq5 << "\n";
  cout << "[v1[0..4> vs v2] " << eq4 << "\n";

  // c)
  vector<int> dst(v1.size());
  replace_copy_if(v1.cbegin(), v1.cend(), dst.begin(), [](int n){return n&1; }, 100);
  cout << "dst: " << dst << endl;

  return 0;
}
