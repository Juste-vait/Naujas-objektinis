// kompikiuot:  g++ -std=c++17 -O1 -o main_O1 main.cpp student.cpp
//              g++ -std=c++17 -O2 -o main_O2 main.cpp student.cpp
//              g++ -std=c++17 -O3 -o main_O3 main.cpp student.cpp

#include <iostream>
#include <fstream>
#include "student.h"
#include <vector>

int main() {
    vector<Studentas> studentai;
    vector<Studentas> nuskriaustukai;
    Studentas s;
    string pasirinkimasIsvesti;



    while (true) {
        int pasirinkimasK;
        cout << "Pasirinkite: \n";
        cout << "1 - konstruktoriaus testavimas\n";
        cout << "2 - destruktoriaus testavimas\n";
        cout << "3 - copy constructor testavimas\n";
        cout << "4 - copy assignment operator testavimas\n";
        cout << "5 - move constructor testavimas\n";
        cout << "6 - move assignment operator testavimas\n";
        cout << "7 - studentų grupaviams ir išvedimas į failus\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimasK;
        cout << endl;

        if (cin.fail()) { 
            cout << "Neteisinga įvestis! Įveskite skaičių 1 - 6.\n" << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue; 
        }

        if (pasirinkimasK == 1) {
            testConstructor();
        } 
        else if (pasirinkimasK == 2) {
            testDestructor();
        } 
        else if (pasirinkimasK == 3) {
            testCopyConstructor();
        } 
        else if (pasirinkimasK == 4) {
            testCopyAssignment();
        } 
        else if (pasirinkimasK == 5) {
            testMoveConstructor();
        } 
        else if (pasirinkimasK == 6) {
            testMoveAssignment();
        } 
        else if (pasirinkimasK == 7) {
            nuskaitytiIsFailo(studentai);

            rusiuotiStudentus(studentai);

            strategija_3(studentai, nuskriaustukai);
            break;
        }
        else {
            cout << "Neteisingas pasirinkimas! Įveskite skaičių 1 - 6.\n" << endl;
        }
    }

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
    
    return 0;
}

