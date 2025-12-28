#include <iostream>
using namespace std;


template<typename t1, typename t2>
struct Pair {
    t1 first;
    t2 second;
    
    Pair(const t1& a, const t2& b) : first(a), second(b) {}

    auto operator+(const Pair& other) const -> Pair<decltype(first + other.first), decltype(second + other.second)> 
        {
        return {first + other.first, second + other.second};
    }
    
    bool operator>(const Pair& other) const {
        return (first + second) > (other.first + other.second);
    }
    
};


int main() {
  Pair<double, int> p1(3.5, 14);
  Pair<double, int> p2(2.1, 7);
  cout << "p1: " << p1.first << ", " << p1.second << endl;
  cout << "p2: " << p2.first << ", " << p2.second << endl;

  if (p1 > p2)
    cout << "p1 er størst" << endl;
  else
    cout << "p2 er størst" << endl;

  auto sum = p1 + p2;
  cout << "Sum: " << sum.first << ", " << sum.second << endl;
}

/* Utskrift:
p1: 3.5, 14
p2: 2.1, 7
p1 er størst
Sum: 5.6, 21
*/