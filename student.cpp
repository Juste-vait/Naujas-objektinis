#include "student.h"
#include <fstream>
#include <sstream>


// Konstruktorius be parametrų
Studentas::Studentas() : egzaminas_(0), galutinisVid_(0), galutinisMed_(0) {}

// Konstruktorius su įvedimu
Studentas::Studentas(istream& is) {
    readStudent(is);
}

// Įvedimo funkcija
istream& Studentas::readStudent(istream& is) {
    is >> vardas_ >> pavarde_;

    namuDarbai_.clear();

    int pazymys;

    while (is >> pazymys) {
        namuDarbai_.push_back(pazymys);
    }
    is.clear();

    if (!namuDarbai_.empty()) {
        egzaminas_ = namuDarbai_.back();
        namuDarbai_.pop_back();
    }

    skaiciuotiGalutinius();

    return is;
}

// Galutinio balo skaičiavimas
void Studentas::skaiciuotiGalutinius() {
    galutinisVid_ = 0.4 * skaiciuotiVidurki(namuDarbai_) + 0.6 * egzaminas_;
    galutinisMed_ = 0.4 * skaiciuotiMediana(namuDarbai_) + 0.6 * egzaminas_;
}

double Studentas::skaiciuotiVidurki(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    double suma = accumulate(pazymiai.begin(), pazymiai.end(), 0);
    return suma / pazymiai.size();
}

double Studentas::skaiciuotiMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    sort(pazymiai.begin(), pazymiai.end());
    size_t n = pazymiai.size();
    return (n % 2 == 0) ? (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0 : pazymiai[n / 2];
}

// Output operatorius
ostream& operator<<(ostream& os, const Studentas& s) {
    os << left << setw(20) << s.pavarde_ << setw(20) << s.vardas_ << fixed << setprecision(2) << setw(20) << s.galutinisVid_ << setw(20) << s.galutinisMed_;
    return os;
}

// Input operatorius
istream& operator>>(istream& is, Studentas& s) {
    return s.readStudent(is);
}   

// Palyginimo funkcijos
bool comparePagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalVid(const Studentas& a, const Studentas& b) {
    return a.galutinisVid() < b.galutinisVid(); 
}

bool comparePagalMed(const Studentas& a, const Studentas& b) {
    return a.galutinisMed() < b.galutinisMed(); 
}