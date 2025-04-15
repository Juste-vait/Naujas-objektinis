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
    string pavarde_;;
    vector<int> namuDarbai_;
    int egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

public:

    Studentas();
    ~Studentas();

    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;

    string vardas() const { return vardas_; }
    string pavarde() const { return pavarde_; }
    double galutinisVid() const { return galutinisVid_; }
    double galutinisMed() const { return galutinisMed_; }

    istream& readStudent(istream& is);

    void skaiciuotiGalutinius();

    static double skaiciuotiVidurki(const vector<int>& pazymiai);
    static double skaiciuotiMediana(vector<int> pazymiai);

    friend ostream& operator<<(ostream& os, const Studentas& s);
    friend istream& operator>>(istream& is, Studentas& s);

};


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
    getline(failas, eilute);  

    while (getline(failas, eilute)) {
        istringstream line(eilute);
        Studentas stud;
        

        stud.readStudent(line);
        
        studentai.push_back(stud); 
    }

    failas.close();

    auto end = steady_clock::now();
    cout << "Duomenų nuskaitymas užtruko: " << duration_cast<seconds>(end - start).count() << " s\n" << endl;
}

template <typename konteineris>
void rusiuotiStudentus(konteineris &studentai, int rusiavimoPasirinkimas){

    while (true) {
        try {
            cout << "Pasirinkite rikiavimo būdą:\n";
            cout << "1 - Pagal vardą (A-Z)\n";
            cout << "2 - Pagal pavardę (A-Z)\n";
            cout << "3 - Pagal galutinį vidurkį\n";
            cout << "4 - Pagal galutinę medianą\n";
            cout << "Jūsų pasirinkimas: ";
            cin >> rusiavimoPasirinkimas;

            if (cin.fail()) {
                throw invalid_argument("Neteisinga įvestis! Įveskite tik skaičių.");
            }
            if (rusiavimoPasirinkimas < 1 || rusiavimoPasirinkimas > 4) {
                throw out_of_range("Pasirinkimas turi būti nuo 1 iki 4.");
            }
            break;
        }
        catch (const exception &e) {
            cout << e.what() << " Bandykite dar kartą.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    auto start1 = steady_clock::now();

    switch (rusiavimoPasirinkimas) {
        case 1:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.vardas() < b.vardas();
            });
            break;
        case 2:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.pavarde() < b.pavarde();
            });
            break;
        case 3:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.galutinisVid() < b.galutinisVid();
            });
            break;
        case 4:
            std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
                return a.galutinisMed() < b.galutinisMed();
            });
            break;
    }
    
    auto end1 = steady_clock::now();
    cout << "Rikiavimas užtruko: " << duration_cast<seconds>(end1 - start1).count() << " s\n" << endl;
}

template <typename konteineris>
void strategija_3(konteineris& studentai, konteineris& nuskriaustukai) {

    char grupavimoPasirinkimas;
    Studentas stud;

    while (true) {
        try {
            cout << "Pasirinkite pagal ką bus sugrupuoti studentai (V - pagal vidurkį, M - pagal medianą): ";
            cin >> grupavimoPasirinkimas;

            if (grupavimoPasirinkimas != 'V' && grupavimoPasirinkimas != 'v' && grupavimoPasirinkimas != 'M' && grupavimoPasirinkimas != 'm') {
                throw invalid_argument("Neteisinga įvestis! Pasirinkite V arba M.");
            }

            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Bandykite dar kartą.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
        }

    auto start = steady_clock::now();
    
    auto it = stable_partition(studentai.begin(), studentai.end(), [grupavimoPasirinkimas](const Studentas& stud) {
        if (grupavimoPasirinkimas == 'V' || grupavimoPasirinkimas == 'v') {
            return stud.galutinisVid() >= 5; 
        } else {
            return stud.galutinisMed() >= 5;
        }
    });
    
    nuskriaustukai.assign(it, studentai.end()); 
    studentai.erase(it, studentai.end());
    
    auto end = steady_clock::now();

    if constexpr (is_same_v<konteineris, vector<Studentas>> || is_same_v<konteineris, deque<Studentas>>) {
        studentai.shrink_to_fit();
    }

    cout << "3 strategija: " << duration_cast<seconds>(end - start).count() << " s\n" << endl;
}

template <typename konteineris>
void isvestiIDuFailus(konteineris& nuskriaustukai, konteineris& studentai){
    
    ofstream outNuskriaustukai("nuskriaustukai.txt"), outKietekai("kietekai.txt");
    if (!outNuskriaustukai || !outKietekai) {
        cerr << "Nepavyko sukurti rezultatų failų!" << endl;
        return;
    }

    outNuskriaustukai << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    outNuskriaustukai << string(70, '-') << endl;
    outKietekai << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    outKietekai << string(70, '-') << endl;

    for (const auto& stud : nuskriaustukai) {
        outNuskriaustukai << left << setw(20) << stud.pavarde() << setw(20) << stud.vardas() << fixed << setprecision(2) << setw(20) << stud.galutinisVid() << setw(20) << stud.galutinisMed() << endl;
    }
    for (const auto& stud : studentai) {        
        outKietekai << left << setw(20) << stud.pavarde() << setw(20) << stud.vardas() << fixed << setprecision(2) << setw(20) << stud.galutinisVid() << setw(20) << stud.galutinisMed() << endl;
    }

    cout << "Failai \"nuskriaustukai.txt\" ir \"kietekai.txt\" sukurti!" << endl;
}

#endif
