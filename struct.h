#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <string>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namuDarbai;
    int egzaminas;
    double galutinis;
    double galutinisVid;
    double galutinisMed;
};

#endif
