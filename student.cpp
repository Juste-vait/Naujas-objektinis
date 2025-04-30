#include "student.h"
#include <fstream>
#include <sstream>

Studentas::Studentas() : Zmogus("", ""), namuDarbai_(), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0) {}

Studentas::~Studentas() {
    namuDarbai_.clear();
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
    : Zmogus(move(other.vardas_), move(other.pavarde_)), namuDarbai_(move(other.namuDarbai_)), egzaminas_(move(other.egzaminas_)), galutinisVid_(move(other.galutinisVid_)), galutinisMed_(move(other.galutinisMed_)) {}

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

void testDestructor() {
    cout << "Testuojamas: Destruktorius" << endl;

        istringstream iss("Leonardo DiCaprio 9 9 9 10 10 10");
        Studentas s;
        s.readStudent(iss);
        cout << "Objektas sukurtas: " << s << endl;
        cout << "Studentas prieš destruktorių: " << s << endl;
        s.~Studentas();
        cout << "Studentas po destruktoriaus: " << s << "\n" << endl;

    cout << "Blokas baigtas, objektas sunaikintas\n" << endl;
}

void testConstructor() {
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
    cout << "Laikinas: " << laikinas << "\n" << endl;
}

void testMoveAssignment() {
    cout << "Testuojamas: Move priskyrimo operatorius" << endl;
    istringstream iss("Lady Gaga 9 9 9 10 10 10");
    Studentas b;
    b.readStudent(iss);

    Studentas a;
    a = std::move(b); 
    cout << "Gavėjas po move: " << a << "\n" << endl;
    cout << "Šaltinis po move: " << b << "\n" << endl;
}

void ivestiStudenta(vector<Studentas>& studentai) {
    char pasirinkimas;

    while (true) {
        try {
            cout << "Ar norite pridėti studentą? (T/N): ";
            cin >> pasirinkimas;

            if (cin.fail()) throw invalid_argument("Neteisinga įvestis! Įveskite tik simbolius T arba N.");
            if (pasirinkimas == 'N' || pasirinkimas == 'n') break;
            if (pasirinkimas != 'T' && pasirinkimas != 't') throw invalid_argument("Neteisingas pasirinkimas! Pasirinkite T arba N.");

            string vardas, pavarde;
            vector<int> namuDarbai;
            int egzaminas;

            cout << "\nĮveskite studento vardą: ";
            cin >> vardas;
            cout << "Įveskite studento pavardę: ";
            cin >> pavarde;

            cout << "Įveskite namų darbų rezultatus (baigti -1):\n";
            while (true) {
                try {
                    int rezultatas;
                    cout << "Įveskite pažymį: ";
                    cin >> rezultatas;

                    if (cin.fail()) throw invalid_argument("Neteisinga įvestis! Įveskite tik skaičių.");
                    if (rezultatas == -1) break;
                    if (rezultatas < 1 || rezultatas > 10) throw out_of_range("Pažymys turi būti tarp 1 ir 10.");

                    namuDarbai.push_back(rezultatas);
                }
                catch (const exception& e) {
                    cout << e.what() << " Bandykite dar kartą.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                try {
                    cout << "Įveskite egzamino rezultatą: ";
                    cin >> egzaminas;

                    if (cin.fail()) throw invalid_argument("Neteisinga įvestis! Įveskite tik skaičių.");
                    if (egzaminas < 1 || egzaminas > 10) throw out_of_range("Egzamino pažymys turi būti tarp 1 ir 10.");
                    break;
                }
                catch (const exception& e) {
                    cout << e.what() << " Bandykite dar kartą.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            Studentas stud;
            stud.setVardas(vardas);
            stud.setPavarde(pavarde);
            stud.setNamuDarbai(namuDarbai);
            stud.setEgzaminas(egzaminas);
            stud.skaiciuotiGalutinius(); 

            studentai.push_back(std::move(stud));
        }
        catch (const exception& e) {
            cout << e.what() << " Bandykite dar kartą.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void generuotiStudentus(vector<Studentas>& studentai) {
    vector<string> vardai = {"Jonas", "Petras", "Antanas", "Nojus", "Lukas"};
    vector<string> pavardes = {"Kazlauskas", "Petraitis", "Jonaitis", "Biliūnas", "Lukauskis"};

    while (true) {
        try {
            cout << "Ar norite pridėti studentą? (T/N): ";
            char tesiame;
            cin >> tesiame;

            if (tesiame == 'N' || tesiame == 'n') break;

            if (tesiame != 'T' && tesiame != 't') {
                throw invalid_argument("Neteisinga įvestis! Pasirinkite T arba N. ");
            }

        Studentas stud;

        stud.setVardas(vardai[rand() % vardai.size()]);
        stud.setPavarde(pavardes[rand() % pavardes.size()]);

        
        int kiekis = rand() % 5 + 3;  

        vector<int> naujiNamuDarbai;
        for (int i = 0; i < kiekis; ++i) {
            naujiNamuDarbai.push_back(rand() % 10 + 1); 
        }

        stud.setNamuDarbai(naujiNamuDarbai);

        stud.setEgzaminas(rand() % 10 + 1); 

        stud.skaiciuotiGalutinius();

        studentai.push_back(stud);
        
    }
    catch (const invalid_argument& e) {
        cout << e.what() << "Bandykite dar kartą.\n"<<endl;
    }
    }
}

void testInputOperator() {
    istringstream input("Jonas Jonaitis 8 9 10 7");

    Studentas s;
    input >> s;

    cout << "Test input operator:\n";
    cout << "Vardas: " << s.vardas() << "\n";
    cout << "Pavarde: " << s.pavarde() << "\n";
    cout << "Namu darbai: ";
    for (int nd : s.getNamuDarbai()) std::cout << nd << " ";
    cout << "\nEgzaminas: " << s.getEgzaminas() << "\n";
    cout << "Galutinis (vid): " << s.galutinisVid() << "\n";
    cout << "Galutinis (med): " << s.galutinisMed() << "\n\n";
}

void testOutputOperator() {
    Studentas s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNamuDarbai({8, 9, 10});
    s.setEgzaminas(9);
    s.skaiciuotiGalutinius();

    ostringstream output;
    output << s;

    cout << "Test output operator:\n";
    cout << output.str() << "\n" << endl;
}