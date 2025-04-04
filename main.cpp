#include <iostream>
#include <fstream>
#include "student.h"
#include <vector>

int main() {
    vector<Studentas> studentai;
    vector<Studentas> nuskriaustukai;
    Studentas s;
    /*
    while (in >> s) {
        studentai.push_back(s);
    }
    */

    nuskaitytiIsFailo(studentai);

    strategija_3(studentai, nuskriaustukai);

    //rusiuotiStudentus(studentai);

    cout << "Nuskriaustukai:\n";
    for (const auto& studentas : nuskriaustukai) {
        cout << studentas << '\n';
    } 

    cout << "Kietekai:\n";
    for (const auto& studentas : studentai) {
        cout << studentas << '\n';
    } 

    return 0;
}

