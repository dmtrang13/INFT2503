#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


int find_sum(const int *table, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) sum += table[i];
    return sum;
}


int main() {

// 6)
    const int length = 20;

    int table[length];
    for (int i = 0; i < length; i++) table[i] = i + 1;

    int first10 = find_sum(table, 10);
    int next5 = find_sum(table + 10, 5);
    int last5 = find_sum(table + 15, 5);


    cout << "Sum første 10 elementene er: " << first10 << "\n";
    cout << "Sum neste 5 elementene er: " << next5 << "\n";
    cout << "Sum siste 5 elementene er: " << last5;
    return 0;
    
}