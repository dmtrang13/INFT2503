#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int length = 5;

void read_temperatures(double temperatures[], int length) {
   // her plasserer du koden i funksjonen, vi sier at vi definerer funksjonen
    double under10;
    double mellomt;
    double over20;

    const char filename[] = "temperatures.dat";
    ifstream file;       // definerer filvariabel
    file.open(filename); // åpner filen
    if (!file) {         // innfil kan brukes som et logisk uttrykk
            cerr << "Feil ved åpning av innfil." << endl;
            exit(EXIT_FAILURE); // uthopp fra programmet
        }
        
    for (int i = 0; i < length; i++) {
        if (!(file >> temperatures[i])) {
            cerr << "For få/ugyldige tall i filen (stoppet ved posisjon "
                 << (i + 1) << ").\n";
            exit(EXIT_FAILURE);
        }

        double t = temperatures[i];
        cout << "Temperatur nr " << i+1 << ": " << t << "\n";
        int temps = (t < 10) ? 0 : (t <= 20 ? 1 : 2);
        switch (temps) {
            case 0: ++under10; break;
            case 1: ++mellomt; break;
            case 2: ++over20; break;
        }
    }

    cout << "Antall under 10 er: " << under10 << "\n";
    cout << "Antall mellom 10 og 20 er: " << mellomt << "\n";
    cout << "Antall over 20 er: " << over20;

}


int main() {
    double temperatures[length];
    read_temperatures(temperatures, length);

    
    return 0;
}