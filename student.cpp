#include "student.h"
#include <fstream>
#include <sstream>


Studentas::Studentas() : egzaminas_(0), galutinisVid_(0), galutinisMed_(0) {}

Studentas::~Studentas() {}

Studentas::Studentas(istream& is) {
    readStudent(is);
}

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

ostream& operator<<(ostream& os, const Studentas& s) {
    os << left << setw(20) << s.pavarde_ << setw(20) << s.vardas_ << fixed << setprecision(2) << setw(20) << s.galutinisVid_ << setw(20) << s.galutinisMed_;
    return os;
}

istream& operator>>(istream& is, Studentas& s) {
    return s.readStudent(is);
}   