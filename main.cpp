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
    int rusiavimoPasirinkimas;

    testDefaultConstructor();
    testCopyConstructor();
    testCopyAssignment();
    testMoveConstructor();
    testMoveAssignment();

    //nuskaitytiIsFailo(studentai);

    //rusiuotiStudentus(studentai, rusiavimoPasirinkimas);

    //strategija_3(studentai, nuskriaustukai);

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

