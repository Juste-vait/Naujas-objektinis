#include "student.h"
#include <fstream>
#include <sstream>


// Konstruktorius be parametrų
Studentas::Studentas() : egzaminas_(0), galutinisVid_(0), galutinisMed_(0) {}

// Konstruktorius su įvedimu
Studentas::Studentas(std::istream& is) {
    readStudent(is);
}

istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_ >> egzaminas_;
    namuDarbai_.clear();
    int pazymys;
    while (is >> pazymys) {
        namuDarbai_.push_back(pazymys);
    }
    is.clear(); 
    return is;
}

// Galutinio balo skaičiavimas
void Studentas::skaiciuotiGalutinius() {
    galutinisVid_ = 0.4 * skaiciuotiVidurki(namuDarbai_) + 0.6 * egzaminas_;
    galutinisMed_ = 0.4 * skaiciuotiMediana(namuDarbai_) + 0.6 * egzaminas_;
}

double Studentas::skaiciuotiVidurki(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    double suma = std::accumulate(pazymiai.begin(), pazymiai.end(), 0);
    return suma / pazymiai.size();
}

double Studentas::skaiciuotiMediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0.0;
    std::sort(pazymiai.begin(), pazymiai.end());
    size_t n = pazymiai.size();
    return (n % 2 == 0) ? (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0 : pazymiai[n / 2];
}

// Output operatorius
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(20) << s.pavarde_ << std::setw(20) << s.vardas_ << std::fixed << std::setprecision(2) << std::setw(20) << s.galutinisVid_ << std::setw(20) << s.galutinisMed_;
    return os;
}

// Palyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalEgza(const Studentas& a, const Studentas& b) {
    return a.galutinisVid() < b.galutinisVid(); 
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.readStudent(is);
}   