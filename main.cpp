// kompiliuot:  g++ -std=c++17 -O1 -o main_O1 main.cpp student.cpp
//              g++ -std=c++17 -O2 -o main_O2 main.cpp student.cpp
//              g++ -std=c++17 -O3 -o main_O3 main.cpp student.cpp

#include <iostream>
#include <fstream>
#include "student.h"
#include <vector>
#include "utils.h"
#include "vector.h"

int main() {
    Vector<Studentas> studentai;
    Vector<Studentas> nuskriaustukai;
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
        cout << "7 - input operator testavimas\n";
        cout << "8 - output operator testavimas\n";
        cout << "9 - studentų grupaviams ir išvedimas į failus\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimasK;
        cout << endl;

        if (cin.fail()) { 
            cout << "Neteisinga įvestis! Įveskite skaičių 1 - 9.\n" << endl;
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
            testInputOperator();
        } 
        else if (pasirinkimasK == 8) {
            testOutputOperator();
        } 
        else if (pasirinkimasK == 9) {
            while (true) {
                int choise;
                cout << "Pasirinkite kaip įvesti studentų duomenis:\n";
                cout << "1 - ranka\n";
                cout << "2 - generuoti\n";
                cout << "3 - iš failo\n";
                cout << "Pasirinkimas: ";
                cin >> choise;
                cout << endl;
            
                if (cin.fail()) { 
                    cout << "Neteisinga įvestis! Įveskite skaičių 1 - 3.\n" << endl;
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    continue; 
                }

                if (choise == 1) {
                    ivestiStudenta(studentai);
                    break;
                }
                else if (choise == 2) {
                    generuotiStudentus(studentai);
                    break;
                }
                else if (choise == 3){
                    nuskaitytiIsFailo(studentai);
                    break;
                }
                else {
                    cout << "Neteisingas pasirinkimas! Įveskite skaičių 1 - 3.\n" << endl;
                }
            }
            
            rusiuotiStudentus(studentai);

            strategija_3(studentai, nuskriaustukai);
            break;
            }
            else {
            cout << "Neteisingas pasirinkimas! Įveskite skaičių 1 - 9.\n" << endl;
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

