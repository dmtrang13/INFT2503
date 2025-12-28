#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Set {
    vector<int> data;

    bool contains(int x) const {
        return find(data.begin(), data.end(), x) != data.end();
    }

public:
    //  lage en ny tom liste
    Set() = default;
    Set(initializer_list<int> init) : data(init) {
        for (int x : init) if (!contains(x)) data.push_back(x);
    }

    //  union av to mengder
    Set& operator|=(const Set& a) {
        for (int x : a.data) if (!contains(x)) data.push_back(x);
        return *this;
    }

    Set operator|(const Set& a) const {
        Set r = *this;
        r |= a;
        return r;
    }

    //  legge til nytt tall i en mengde
    Set& operator+=(int x) {
        if (!contains(x)) data.push_back(x);
        return *this;
    }
    
    Set operator+(int x) const { Set r = *this; r += x; return r;}

    // skrive ut listene 
    friend ostream& operator<<(ostream& os, const Set& s) {
        os << '{';
        for (size_t i = 0; i < s.data.size(); i++) {
            if (i) os << ", ";
            os << s.data[i];
        }
        return os << '}';
    }

};


int main() {
    Set z;
    Set a{1,4,3};
    Set b{4,7};

    cout << "z = " << z << "\n";
    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";

    a += 7;
    a += 3;
    auto c = a + 9;
    cout << "a after +=7, +=3: " << a << "\n";
    cout << "c = a + 9: " << c << "\n";

    auto u = a | b;
    cout << "u = a | b: " << u << "\n";
    z |= c;
    cout << "z |= c: " << z << "\n";

    a = b;
    cout << "a = b: " << a << "\n";

    return 0;
}