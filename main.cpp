#include <iostream>
#include <fstream>
#include "student.h"
#include <vector>

int main() {
    vector<Studentas> studentai;
    vector<Studentas> nuskriaustukai;
    Studentas s;
    string pasirinkimasIsvesti;
    /*
    while (in >> s) {
        studentai.push_back(s);
    }
    */

    nuskaitytiIsFailo(studentai);

    rusiuotiStudentus(studentai);

    strategija_3(studentai, nuskriaustukai);

    while (true) {
        try {
            cout << "Ar norite išvesti duomenis į failą ar į ekraną? (F/E): ";
            cin >> pasirinkimasIsvesti;

            if (pasirinkimasIsvesti != "F" && pasirinkimasIsvesti != "f" && pasirinkimasIsvesti != "E" && pasirinkimasIsvesti != "e") {
                throw invalid_argument("Neteisinga įvestis! Įveskite 'F' arba 'E'.");
            }
            break;
        }
        catch (const exception& e) {
            cout << e.what() << " Bandykite dar kartą.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (pasirinkimasIsvesti == "F" || pasirinkimasIsvesti == "f") {
        isvestiIDuFailus(nuskriaustukai, studentai);
    }
    else {
        cout << "Nuskriaustukai:\n";
        for (const auto& studentas : nuskriaustukai) {
            cout << studentas << '\n';
        } 
    
        cout << endl;
    
        cout << "Kietekai:\n";
        for (const auto& studentas : studentai) {
            cout << studentas << '\n';
        }
    }

    /*

    // Isvedimas i ekrana
    cout << "Nuskriaustukai:\n";
    for (const auto& studentas : nuskriaustukai) {
        cout << studentas << '\n';
    } 

    cout << endl;

    cout << "Kietekai:\n";
    for (const auto& studentas : studentai) {
        cout << studentas << '\n';
    }

    // Isvedimas į failus
    ofstream failasNuskriaustukai("nuskriaustukai.txt");
    ofstream failasKietekai("kietekai.txt");

    if (!failasNuskriaustukai || !failasKietekai) {
        cerr << "Klaida atidarant išvesties failus!" << endl;
        return 1;
    }

    failasNuskriaustukai << left << setw(20) << "Pavardė" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    failasNuskriaustukai << string(80, '-') << endl;

    for (const auto& studentas : nuskriaustukai) {
        failasNuskriaustukai << studentas << '\n';
    }

    failasKietekai << left << setw(20) << "Pavardė" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    failasKietekai << string(80, '-') << endl;

    for (const auto& studentas : studentai) {
        failasKietekai << studentas << '\n';
    }

    failasNuskriaustukai.close();
    failasKietekai.close();

    */
    
    return 0;
}

