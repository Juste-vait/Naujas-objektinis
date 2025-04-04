#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<int> namuDarbai_;
    int egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

public:
    // Konstruktoriai
    Studentas();
    Studentas(std::istream& is);

    // Getteriai (const funkcijos)
    string vardas() const { return vardas_; }
    string pavarde() const { return pavarde_; }
    double galutinisVid() const { return galutinisVid_; }
    double galutinisMed() const { return galutinisMed_; }

    // Įvedimo funkcija
    istream& readStudent(std::istream& is);

    // Galutinio pažymio skaičiavimas
    void skaiciuotiGalutinius();

    // Pagalbinės funkcijos
    static double skaiciuotiVidurki(const std::vector<int>& pazymiai);
    static double skaiciuotiMediana(std::vector<int> pazymiai);

    // Operatoriai
    friend ostream& operator<<(std::ostream& os, const Studentas& s);
    friend istream& operator>>(std::istream& is, Studentas& s);

};



// Palyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalEgza(const Studentas& a, const Studentas& b);

template <typename konteineris>
void nuskaitytiIsFailo(konteineris &studentai);

template <typename konteineris>
void nuskaitytiIsFailo(konteineris &studentai) {
    string failoPavadinimas;
    ifstream failas;

    while (true) {
        try {
            cout << "\nĮveskite failo pavadinimą: ";
            cin >> failoPavadinimas;
            
            failas.open(failoPavadinimas);
            if (!failas) throw runtime_error("Nepavyko atidaryti failo!");

            break; 
        }
        catch (const exception& e) {
            cout << e.what() << " Bandykite dar kartą.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    auto start = steady_clock::now();

    string eilute;
    getline(failas, eilute);  // Nuskaitome pirmąją eilutę (antraštę), bet jos nenaudojame

    while (getline(failas, eilute)) {
        istringstream line(eilute);
        Studentas stud;
        
        // Naudojame klasės metodą nuskaitymui
        stud.readStudent(line);
        
        studentai.push_back(stud); 
    }

    failas.close();

    auto end = steady_clock::now();
    cout << "Duomenų nuskaitymas užtruko: " 
         << duration_cast<seconds>(end - start).count() << " s\n" << endl;
}

#endif
