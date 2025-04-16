#include "student.h"
#include <fstream>
#include <sstream>

Studentas::Studentas() : vardas_(""), pavarde_(""), namuDarbai_(), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0) {
    cout << "Knstruktorius suveikė" << endl;
}

Studentas::~Studentas() {
    namuDarbai_.clear();
}

Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_), namuDarbai_(other.namuDarbai_), egzaminas_(other.egzaminas_), galutinisVid_(other.galutinisVid_), galutinisMed_(other.galutinisMed_) {
        cout << "Copy konstruktorius suveikė" << endl;
    }

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        namuDarbai_ = other.namuDarbai_;
        egzaminas_ = other.egzaminas_;
        galutinisVid_ = other.galutinisVid_;
        galutinisMed_ = other.galutinisMed_;
    }

    cout << "Kopijavimo priskyrimo operatorius suveikė" << endl;
    return *this;
} 

Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(move(other.vardas_)), pavarde_(move(other.pavarde_)), namuDarbai_(move(other.namuDarbai_)), egzaminas_(other.egzaminas_), galutinisVid_(other.galutinisVid_), galutinisMed_(other.galutinisMed_) {
        cout << "Move konstruktorius suveikė" << endl;
    }
      
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = move(other.vardas_);
        pavarde_ = move(other.pavarde_);
        namuDarbai_ = move(other.namuDarbai_);
        egzaminas_ = move(other.egzaminas_);
        galutinisVid_ = move(other.galutinisVid_);
        galutinisMed_ = move(other.galutinisMed_);
    }

    cout << "Move assignment operatorius suveikė" << endl;
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
    os << left << setw(20) << s.pavarde_ << setw(20) << s.vardas_ << fixed << setprecision(2) << setw(20) << s.galutinisVid_ << setw(20) << s.galutinisMed_;
    return os;
}

istream& operator>>(istream& is, Studentas& s) {
    return s.readStudent(is);
}   

void testDefaultConstructor() {
    cout << "Testuojamas: Default konstruktorius" << endl;
    Studentas s;
    cout << s << "\n" << endl;
}

void testCopyConstructor() {
    cout << "Testuojamas: Kopijavimo konstruktorius" << endl;

    istringstream iss("Michael Jackson 8 9 10 10 9 9");
    Studentas original;
    original.readStudent(iss);
    Studentas kopija(original); 

    cout << "Originalas: " << original << endl;
    cout << "Kopija:     " << kopija << "\n" << endl;
}

void testCopyAssignment() {
    cout << "Testuojamas: Kopijavimo priskyrimo operatorius" << endl;
    istringstream iss("Freddie Mercury 10 10 9 8 10 10");
    Studentas b;
    b.readStudent(iss);
    Studentas a;
    a = b; 

    cout << "Šaltinis:   " << b << endl;
    cout << "Gavėjas:    " << a << "\n" << endl;
}

void testMoveConstructor() {
    cout << "Testuojamas: Move konstruktorius" << endl;
    istringstream iss("Britney Spears 7 8 9 10 9 10");
    Studentas laikinas;
    laikinas.readStudent(iss);
    Studentas perkeltas(std::move(laikinas)); 
    cout << "Perkeltas:  " << perkeltas << "\n" << endl;
}

void testMoveAssignment() {
    cout << "Testuojamas: Move priskyrimo operatorius" << endl;
    istringstream iss("Lady Gaga 9 9 9 10 10 10");
    Studentas b;
    b.readStudent(iss);

    Studentas a;
    a = std::move(b); 
    cout << "Gavėjas po move: " << a << "\n" << endl;
}