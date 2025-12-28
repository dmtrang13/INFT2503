#include <iostream>
#include <string>

using namespace std;

int main() {
    // a)
    string word1, word2, word3;
    cout << "Skriv inn tre ord: ";
    cin >> word1 >> word2 >> word3;

    // b)
    string sentence = word1 + " " + word2 + " " + word3 + ".";
    cout << "Setning: " << sentence;

    // c)

    cout << "\nLengder: \n"
         << "word1: " << word1.size() << "\n"
         << "word2: " << word2.size() << "\n"
         << "word3: " << word3.size() << "\n"
         << "sentence: " << sentence.size() << "\n";

    // d)
    string sentence2 = sentence;

    // e)
    if (sentence2.size() >= 13) {
        sentence2.replace(10,3,"xxx");
    } else {
        cout << "Setningen er for kort til å bytte tegn 10-12.\n";
    }

    cout << "sentence: " << sentence << "\n";
    cout << "sentence2: " << sentence2 << "\n";
    
    // f)
    string sentence_start = sentence.substr(0, sentence.size() >= 5 ? 5 : sentence.size());
    cout << "sentence: " << sentence << "\n";
    cout << "sentence_start: " << sentence_start << "\n";

    // g)
    bool contains_hallo = (sentence.find("hallo") != string::npos);
    cout << "Inneholder hallo?: " << (contains_hallo ? "ja" : "nei") << "\n";

    // h) 
    cout << "Forekomster av 'er' på posisjoner: ";
    bool found_any = false;
    for (size_t pos = sentence.find("er"); 
        pos != string::npos; 
        pos = sentence.find("er" , pos +1)) {
        cout << pos << " ";
        found_any = true;
    }
    if (!found_any) cout << "ingen\n";

    return 0;
}