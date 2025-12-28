#include <iostream>
#include <vector>

using namespace std;

int main() {

    const int length = 5;

    vector<double> temps;
    temps.reserve(length);

    cout << "Du skal skrive inn 5 temperaturer\n";
    for (int i = 0; i < length; i++) {
        cout << "Temperatur nr " << i+1 << ": ";
        double t;
        cin >> t;
        temps.push_back(t);
    }

    double under10;
    double mellomt;
    double over20;
    for (double t : temps) {
            if (t < 10) { ++under10;}
            else if (t <= 20) { ++mellomt;}
            else ++over20; }

    cout << "Antall under 10 er: " << under10 << "\n";
    cout << "Antall mellom 10 og 20 er: " << mellomt << "\n";
    cout << "Antall over 20 er: " << over20;

    return 0;

}
    



