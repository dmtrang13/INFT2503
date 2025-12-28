// Programmet skriver toerpotenser til fil.
// Alle toerpotenser mindre enn halvparten av
// maksimalverdien til "long int" skrives ut.

#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
  const char filename[] = "toerpot.dat";
  ofstream file;
  file.open(filename);
  if (!file) {
    cout << "Feil ved åpning av utfil." << endl;
    exit(EXIT_FAILURE);
  }

  long int product = 1L;
  int exponent = 0;
  while (product <= LONG_MAX / 2L) {
    exponent++;
    product *= 2L;
    file << "2 opphøyd i " << setw(4) << exponent << " er "
         << product << endl;
  }
  file.close();
}

/* Filen ser slik ut:
2 opphøyd i    1 er 2
2 opphøyd i    2 er 4
2 opphøyd i    3 er 8
2 opphøyd i    4 er 16
2 opphøyd i    5 er 32
2 opphøyd i    6 er 64
2 opphøyd i    7 er 128
2 opphøyd i    8 er 256
2 opphøyd i    9 er 512
2 opphøyd i   10 er 1024
2 opphøyd i   11 er 2048
2 opphøyd i   12 er 4096
2 opphøyd i   13 er 8192
2 opphøyd i   14 er 16384
2 opphøyd i   15 er 32768
2 opphøyd i   16 er 65536
2 opphøyd i   17 er 131072
2 opphøyd i   18 er 262144
2 opphøyd i   19 er 524288
2 opphøyd i   20 er 1048576
2 opphøyd i   21 er 2097152
2 opphøyd i   22 er 4194304
2 opphøyd i   23 er 8388608
2 opphøyd i   24 er 16777216
2 opphøyd i   25 er 33554432
2 opphøyd i   26 er 67108864
2 opphøyd i   27 er 134217728
2 opphøyd i   28 er 268435456
2 opphøyd i   29 er 536870912
2 opphøyd i   30 er 1073741824
2 opphøyd i   31 er 2147483648
2 opphøyd i   32 er 4294967296
2 opphøyd i   33 er 8589934592
2 opphøyd i   34 er 17179869184
2 opphøyd i   35 er 34359738368
2 opphøyd i   36 er 68719476736
2 opphøyd i   37 er 137438953472
2 opphøyd i   38 er 274877906944
2 opphøyd i   39 er 549755813888
2 opphøyd i   40 er 1099511627776
2 opphøyd i   41 er 2199023255552
2 opphøyd i   42 er 4398046511104
2 opphøyd i   43 er 8796093022208
2 opphøyd i   44 er 17592186044416
2 opphøyd i   45 er 35184372088832
2 opphøyd i   46 er 70368744177664
2 opphøyd i   47 er 140737488355328
2 opphøyd i   48 er 281474976710656
2 opphøyd i   49 er 562949953421312
2 opphøyd i   50 er 1125899906842624
2 opphøyd i   51 er 2251799813685248
2 opphøyd i   52 er 4503599627370496
2 opphøyd i   53 er 9007199254740992
2 opphøyd i   54 er 18014398509481984
2 opphøyd i   55 er 36028797018963968
2 opphøyd i   56 er 72057594037927936
2 opphøyd i   57 er 144115188075855872
2 opphøyd i   58 er 288230376151711744
2 opphøyd i   59 er 576460752303423488
2 opphøyd i   60 er 1152921504606846976
2 opphøyd i   61 er 2305843009213693952
2 opphøyd i   62 er 4611686018427387904
*/
