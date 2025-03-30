//kompiliuot: g++ -std=c++11 -o main masyvas.cpp

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    int* namuDarbai;
    int namuDarbaiKiekis;
    int egzaminas;
    double galutinis;

    Studentas() : namuDarbai(nullptr), namuDarbaiKiekis(0) {}
    ~Studentas() { delete[] namuDarbai; }
    
    Studentas(const Studentas& other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
        egzaminas = other.egzaminas;
        galutinis = other.galutinis;
        namuDarbaiKiekis = other.namuDarbaiKiekis;
        
        if (other.namuDarbai) {
            namuDarbai = new int[namuDarbaiKiekis];
            copy(other.namuDarbai, other.namuDarbai + namuDarbaiKiekis, namuDarbai);
        } else {
            namuDarbai = nullptr;
        }
    }
};

double skaiciuotiVidurki(int* pazymiai, int kiekis) {
    if (kiekis == 0) return 0.0;
    int suma = 0;
    for (int i = 0; i < kiekis; ++i) suma += pazymiai[i];
    return static_cast<double>(suma) / kiekis;
}

double skaiciuotiMediana(int* pazymiai, int kiekis) {
    if (kiekis == 0) return 0.0;
    sort(pazymiai, pazymiai + kiekis);
    if (kiekis % 2 == 0) {
        return (pazymiai[kiekis / 2 - 1] + pazymiai[kiekis / 2]) / 2.0;
    } else {
        return pazymiai[kiekis / 2];
    }
}

void ivestiStudenta(vector<Studentas>& studentai, char pasirinkimas) {
    Studentas stud;
    while (true) {  
    cout << "Ar norite pridėti studentą? (T/N): ";
    char tesiame;
    cin >> tesiame;
    if (tesiame == 'N' || tesiame == 'n') break;

    Studentas stud;
    cout << "\nĮveskite studento vardą: ";
    cin >> stud.vardas;
    cout << "Įveskite studento pavardę: ";
    cin >> stud.pavarde;
    
    cout << "Įveskite namų darbų rezultatus (baigti -1):\n";
    int* laikinas = new int[100]; 
    int kiekis = 0;
    while (true) {
        int rezultatas;
        if (!(cin >> rezultatas)) {
            cout << "Klaida! Įveskite tik skaičius.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (rezultatas == -1) break;
        laikinas[kiekis++] = rezultatas;
    }
    
    stud.namuDarbai = new int[kiekis];
    copy(laikinas, laikinas + kiekis, stud.namuDarbai);
    stud.namuDarbaiKiekis = kiekis;

        
        cout << "Įveskite egzamino rezultatą: ";
        while (!(cin >> stud.egzaminas)) {
        cout << "Klaida! Įveskite tik skaičius.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pasirinkimas == 'V' || pasirinkimas == 'v') {
        double vidurkis = skaiciuotiVidurki(stud.namuDarbai, stud.namuDarbaiKiekis);
        stud.galutinis = 0.4 * vidurkis + 0.6 * stud.egzaminas;
        } else {
        double mediana = skaiciuotiMediana(stud.namuDarbai, stud.namuDarbaiKiekis);
        stud.galutinis = 0.4 * mediana + 0.6 * stud.egzaminas;
        }
    studentai.push_back(stud);
    }
    
}

void generuotiPazymius(Studentas& stud, char pasirinkimas) {
    stud.namuDarbaiKiekis = rand() % 5 + 3;

    stud.namuDarbai = new int[stud.namuDarbaiKiekis]; 

    for (int i = 0; i < stud.namuDarbaiKiekis; ++i) {
        stud.namuDarbai[i] = rand() % 10 + 1; 
    }

    stud.egzaminas = rand() % 10 + 1; 
    
    if (pasirinkimas == 'V' || pasirinkimas == 'v') {
        double vidurkis = skaiciuotiVidurki(stud.namuDarbai, stud.namuDarbaiKiekis);
        stud.galutinis = 0.4 * vidurkis + 0.6 * stud.egzaminas;
    } else {
        double mediana = skaiciuotiMediana(stud.namuDarbai, stud.namuDarbaiKiekis);
        stud.galutinis = 0.4 * mediana + 0.6 * stud.egzaminas;
    }

}

void generuotiStudentus(vector<Studentas>& studentai, char pasirinkimas) {
    vector<string> vardai = {"Jonas", "Petras", "Antanas", "Nojus", "Lukas"};
    vector<string> pavardes = {"Kazlauskas", "Petraitis", "Jonaitis", "Biliūnas", "Lukauskis"};

    while (true) {
        cout << "Ar norite pridėti studentą? (T/N): ";
        char tesiame;
        cin >> tesiame;
        if (tesiame == 'N' || tesiame == 'n') break;

        Studentas stud;
        stud.vardas = vardai[rand() % vardai.size()];
        stud.pavarde = pavardes[rand() % pavardes.size()];
        generuotiPazymius(stud, pasirinkimas);

        if (pasirinkimas == 'V' || pasirinkimas == 'v') {
            double vidurkis = skaiciuotiVidurki(stud.namuDarbai, stud.namuDarbaiKiekis);
            stud.galutinis = 0.4 * vidurkis + 0.6 * stud.egzaminas;
        } else {
            double mediana = skaiciuotiMediana(stud.namuDarbai, stud.namuDarbaiKiekis);
            stud.galutinis = 0.4 * mediana + 0.6 * stud.egzaminas;
        }

        studentai.push_back(stud);
    }
}


int main() {
    srand(time(0));  
    vector<Studentas> studentai;
    char pasirinkimas;
    int pasirinkimasMeniu;

    while (true) {
        cout << "Pasirinkite galutinio balo skaičiavimą (V - vidurkis, M - mediana): ";
        cin >> pasirinkimas;

        if (pasirinkimas == 'V' || pasirinkimas == 'v' || pasirinkimas == 'M' || pasirinkimas == 'm') {
            break; 
        } else {
            cout << "Neteisinga įvestis! Pasirinkite V arba M.\n";
        }
    }
    
    while (true) {
        cout << "\nPasirinkite veiksmą:\n";
        cout << "1 - Rankiniu būdu įvesti duomenis\n";
        cout << "2 - Generuoti pažymius\n";
        cout << "3 - Generuoti ir pažymius, ir vardus/pavardes\n";
        cout << "4 - Baigti darbą\n";
        cout << "Jūsų pasirinkimas: ";
        cin >> pasirinkimasMeniu;

        if (pasirinkimasMeniu == 4) {
            break;
        } else if (pasirinkimasMeniu == 1) {
            ivestiStudenta(studentai, pasirinkimas);
        } else if (pasirinkimasMeniu == 2) {
            while (true) {  
                cout << "Ar norite pridėti studentą? (T/N): ";
                char tesiame;
                cin >> tesiame;
                if (tesiame == 'N' || tesiame == 'n') break;

                Studentas stud;
                cout << "\nĮveskite studento vardą: ";
                cin >> stud.vardas;
                cout << "Įveskite studento pavardę: ";
                cin >> stud.pavarde;
                generuotiPazymius(stud, pasirinkimas);
                studentai.push_back(stud);
            }
        } else if (pasirinkimasMeniu == 3) {
            generuotiStudentus(studentai, pasirinkimas);
        } else {
            cout << "Neteisingas pasirinkimas! Bandykite dar kartą.\n";
        }
    }

    cout << "\n---------------------------------------------------\n";
    cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (";
    if (pasirinkimas == 'V' || pasirinkimas == 'v') {
        cout << "Vid.)";
    } else {
        cout << "Med.)";
    }
    cout << endl;
    cout << "---------------------------------------------------\n";

    for (const auto& stud : studentai) {
        cout << left << setw(15) << stud.pavarde << setw(15) << stud.vardas << fixed << setprecision(2) << setw(15) << stud.galutinis << endl;
    }

    return 0;
}