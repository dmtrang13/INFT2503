#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    vector<double> numbers = {1.2, 2.3, 3.4, 4.5, 5.6};
    for (double i : numbers) {
        cout << i << " ";
    }
    cout << "\nFørste tall i rekka: " << numbers.front() << "\n";
    cout << "Siste tall i rekka: " << numbers.back() << "\n";

    // Setter 6.7 i indeks 1
    numbers.emplace(numbers.begin() + 1, 6.7);
    cout << "Lista etter emplace(): ";
    for (double i : numbers) {
        cout << i << " ";
    }

    cout << "\nEtter emplace() er første tallet fortsatt: " << numbers.front() << "\n";

    auto it = find(numbers.begin(), numbers.end(), 6.7);

    if (it != numbers.end()) {
        cout << "Fant nummeret 6.7 i lista: " << *it;
    } else {
    cout << "Fant ikke nummeret 6.7 i lista.";
    }

    return 0;
}