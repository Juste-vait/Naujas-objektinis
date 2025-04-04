#include <iostream>
#include <fstream>
#include "student.h"
#include <vector>

int main() {
    vector<Studentas> studentai;
    Studentas s;
    /*
    while (in >> s) {
        studentai.push_back(s);
    }
    */

    nuskaitytiIsFailo(studentai);

    cout << "Rezultatai:\n";
    for (const auto& studentas : studentai) {
        cout << studentas << '\n';
    } 

    return 0;
}

