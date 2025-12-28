#include <iostream>
#include <vector>
using namespace std;

template <class T>
auto times_two(T a) -> decltype(a*2) {
    return a * 2;
}

string times_two(const char* s) {
    return string(s) + s;
}

template <class T>
vector<T> times_two(vector<T> v) {
    for (auto& x : v) x *= 2;
    return v;
}

template <class T> 
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "{ ";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) os << ", ";
        os << v[i];
    };
    return os << " }";
}

int main() { 
    cout << times_two(2) << endl;
    cout << times_two(2.25) << endl;
    cout << times_two("test") << endl;
    cout << times_two(vector<int>{1, 2, 3}) << endl;

    return 0;
}