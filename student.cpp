#include "student.h"
#include <fstream>
#include <sstream>

Studentas::Studentas() : Zmogus("", ""), namuDarbai_(), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0) {}

Studentas::~Studentas() {
    vardas_ = "";
    pavarde_ = "";
    namuDarbai_.clear();
    egzaminas_ = 0;
    galutinisVid_ = 0.0;
    galutinisMed_ = 0.0;
}

Studentas::Studentas(const Studentas& other)
    : Zmogus(other.vardas_, other.pavarde_), namuDarbai_(other.namuDarbai_), egzaminas_(other.egzaminas_), galutinisVid_(other.galutinisVid_), galutinisMed_(other.galutinisMed_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        namuDarbai_ = other.namuDarbai_;
        egzaminas_ = other.egzaminas_;
        galutinisVid_ = other.galutinisVid_;
        galutinisMed_ = other.galutinisMed_;
    }
    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : Zmogus(move(other.vardas_), move(other.pavarde_)), namuDarbai_(move(other.namuDarbai_)), egzaminas_(move(other.egzaminas_)), galutinisVid_(move(other.galutinisVid_)), galutinisMed_(move(other.galutinisMed_)) {
        other.vardas_.clear();
        other.pavarde_.clear();
        other.namuDarbai_.clear();
        other.egzaminas_ = 0;
        other.galutinisVid_ = 0.0;
        other.galutinisMed_ = 0.0;
    }

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = move(other.vardas_);
        pavarde_ = move(other.pavarde_);
        namuDarbai_ = move(other.namuDarbai_);
        egzaminas_ = move(other.egzaminas_);
        galutinisVid_ = move(other.galutinisVid_);
        galutinisMed_ = move(other.galutinisMed_);

        other.egzaminas_ = 0;
        other.galutinisVid_ = 0.0;
        other.galutinisMed_ = 0.0;
    }
    return *this;
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
    os << left << setw(20) << s.pavarde() << setw(20) << s.vardas() << fixed << setprecision(2) << setw(20) << s.galutinisVid() << setw(20) << s.galutinisMed();
    return os;
}

istream& operator>>(istream& is, Studentas& s) {
    return s.readStudent(is);
}   