#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Studentas {
    string vardas, pavarde;
    vector<int> namuDarbai;
    int egzaminas;
    double galutinis;
};

// Funkcija apskaičiuoti vidurkį
double skaiciuotiVidurki(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    int suma = 0;
    for (int paz : pazymiai) suma += paz;
    return static_cast<double>(suma) / pazymiai.size();
}

// Funkcija apskaičiuoti medianą
double skaiciuotiMediana(vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    sort(pazymiai.begin(), pazymiai.end());
    size_t n = pazymiai.size();
    if (n % 2 == 0) {
        return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0;
    } else {
        return pazymiai[n / 2];
    }
}

// Funkcija apskaičiuoti galutinį balą pagal vidurkį
double skaiciuotiGalutiniVidurkis(const vector<int>& namuDarbai, int egzaminas) {
    double vidurkis = skaiciuotiVidurki(namuDarbai);
    return 0.4 * vidurkis + 0.6 * static_cast<double>(egzaminas);
}

// Funkcija apskaičiuoti galutinį balą pagal medianą
double skaiciuotiGalutiniMediana(vector<int>& namuDarbai, int egzaminas) {
    double mediana = skaiciuotiMediana(namuDarbai);
    return 0.4 * mediana + 0.6 * static_cast<double>(egzaminas);
}

int main() {
    int n;
    cout << "Iveskite studentu skaiciu: ";
    cin >> n;

    vector<Studentas> studentai(n);
    char pasirinkimas;
    
    cout << "Pasirinkite galutinio balo skaiciavima (V - vidurkis, M - mediana): ";
    cin >> pasirinkimas;

    for (int i = 0; i < n; i++) {
        cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        cin >> studentai[i].pavarde;
        cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        cin >> studentai[i].vardas;

        cout << "Iveskite 5 namu darbu pazymius: ";
        studentai[i].namuDarbai.clear();

        int pazymys;
        while (studentai[i].namuDarbai.size() < 5) {
            if (cin >> pazymys) {
                studentai[i].namuDarbai.push_back(pazymys);
            } else {
                cout << "Neteisinga ivestis! Iveskite skaiciu: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Iveskite egzamino rezultata: ";
        while (!(cin >> studentai[i].egzaminas)) {
            cout << "Neteisinga ivestis! Iveskite skaiciu: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Apskaičiuojame galutinį balą pagal pasirinkimą
        if (pasirinkimas == 'V' || pasirinkimas == 'v') {
            studentai[i].galutinis = skaiciuotiGalutiniVidurkis(studentai[i].namuDarbai, studentai[i].egzaminas);
        } else if (pasirinkimas == 'M' || pasirinkimas == 'm') {
            studentai[i].galutinis = skaiciuotiGalutiniMediana(studentai[i].namuDarbai, studentai[i].egzaminas);
        } else {
            cout << "Neteisingas pasirinkimas, naudojamas vidurkis.\n";
            studentai[i].galutinis = skaiciuotiGalutiniVidurkis(studentai[i].namuDarbai, studentai[i].egzaminas);
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
        cout << left << setw(15) << stud.pavarde << setw(15) << stud.vardas
             << fixed << setprecision(2) << setw(15) << stud.galutinis << endl;
    }

    return 0;
}
