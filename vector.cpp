//kompiliuot: g++ -std=c++17 -o main vector.cpp funkcijos.cpp

#include "funkcijos.h"

int main() {
    srand(time(0));  
    char pasirinkimas;
    int pasirinkimasMeniu;
    bool duomenysIsvesti = false;
    //vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    
    while (true) {
        int pasirinkimasK;
        cout << "Pasirinkite konteinerį: \n";
        cout << "1 - vector\n";
        cout << "2 - deque\n";
        cout << "3 - list\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimasK;

        if (cin.fail()) { 
            cout << "Neteisinga įvestis! Įveskite skaičių 1, 2 arba 3.\n" << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue; 
        }

        if (pasirinkimasK == 1) {
            vector<Studentas> studentai, kietekai, nuskriaustukai;
            testavimoFunkcija_3(studentai, kietekai, nuskriaustukai);
            break;
        } 
        else if (pasirinkimasK == 2) {
            deque<Studentas> studentai, kietekai, nuskriaustukai;
            testavimoFunkcija_3(studentai, kietekai, nuskriaustukai);
            break;
        } 
        else if (pasirinkimasK == 3) {
            list<Studentas> studentai, kietekai, nuskriaustukai;
            testavimoFunkcija_3(studentai, kietekai, nuskriaustukai);
            break;
        } 
        else {
            cout << "Neteisingas pasirinkimas! Įveskite skaičių 1, 2 arba 3.\n" << endl;
        }
    }

    /*
    while (true) {
        try {
        cout << "\nPasirinkite veiksmą:\n";
        cout << "1 - Rankiniu būdu įvesti duomenis\n";
        cout << "2 - Generuoti pažymius\n";
        cout << "3 - Generuoti ir pažymius, ir vardus/pavardes\n";
        cout << "4 - Baigti darbą\n";
        cout << "5 - Nuskaityti duomenis iš failo\n";
        cout << "6 - Generuoti failus\n";
        cout << "7 - Paskirstyti studentus į galvočius ir nuskriaustukus\n";
        cout << "8 - testavimo funkcija 1\n";
        cout << "9 - testavimo funkcija 2\n";
        cout << "10 - testavimo funkcija 2\n";
        cout << "Jūsų pasirinkimas: ";
        cin >> pasirinkimasMeniu;
        
        if (cin.fail()) throw invalid_argument("Neteisinga įvestis! Įveskite tik skaičių.");
        if (pasirinkimasMeniu < 1 || pasirinkimasMeniu > 10) throw out_of_range("Klaida: Skaičius turi būti tarp 1-10.");

        if (pasirinkimasMeniu == 4) {
            break;
        } else if (pasirinkimasMeniu == 1) {
            while (true) {
                cout << "Pasirinkite galutinio balo skaičiavimą (V - vidurkis, M - mediana): ";
                cin >> pasirinkimas;
        
                if (pasirinkimas == 'V' || pasirinkimas == 'v' || pasirinkimas == 'M' || pasirinkimas == 'm') {
                    break; 
                } else {
                    cout << "Neteisinga įvestis! Pasirinkite V arba M.\n";
                }
            }
            visit([&](auto& konteineris) {
                if constexpr (is_same_v<decay_t<decltype(konteineris)>, vector<Studentas>>) {
                    ivestiStudenta(konteineris, pasirinkimas);
                } else {
                    cerr << "Klaida: Funkcija ivestiStudenta veikia tik su vector<Studentas>!" << endl;
                }
            }, studentai);    
        } else if (pasirinkimasMeniu == 2) {
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
                cout << "Ar norite pridėti studentą? (T/N): ";
                char tesiame;
                cin >> tesiame;

                if (tesiame == 'T' || tesiame == 't') {
                    
                    Studentas stud;
                    cout << "\nĮveskite studento vardą: ";
                    cin >> stud.vardas;
                    cout << "Įveskite studento pavardę: ";
                    cin >> stud.pavarde;
                    generuotiPazymius(stud, pasirinkimas);
                    std::visit([&](auto& konteineris) {
                        konteineris.push_back(stud); 
                    }, studentai);
                } 
                else if (tesiame == 'N' || tesiame == 'n') {
                    break;
                } 
                else {
                    cout << "Neteisinga įvestis! Pasirinkite T arba N.\n";
                }
            }
        } else if (pasirinkimasMeniu == 3) {
            while (true) {
                cout << "Pasirinkite galutinio balo skaičiavimą (V - vidurkis, M - mediana): ";
                cin >> pasirinkimas;
        
                if (pasirinkimas == 'V' || pasirinkimas == 'v' || pasirinkimas == 'M' || pasirinkimas == 'm') {
                    break; 
                } else {
                    cout << "Neteisinga įvestis! Pasirinkite V arba M.\n";
                }
            }
            visit([&](auto& konteineris) {
                if constexpr (is_same_v<decay_t<decltype(konteineris)>, vector<Studentas>>) {
                    generuotiStudentus(konteineris, pasirinkimas);
                } else {
                    cerr << "Klaida: generuotiStudentus() veikia tik su vector<Studentas>!" << endl;
                }
            }, studentai);
        } else if (pasirinkimasMeniu == 5) {
            nuskaitytiIsFailo(studentai);
            rusiuotiStudentus(studentai);
            visit([&](auto& konteineris) {
                if constexpr (is_same_v<decay_t<decltype(konteineris)>, vector<Studentas>>) {
                    isvestiDuomenis(konteineris);
                } else {
                    cerr << "Klaida: generuotiStudentus() veikia tik su vector<Studentas>!" << endl;
                }
            }, studentai);
            duomenysIsvesti = true;
            break;
        } else if (pasirinkimasMeniu == 6) {
            generuotiFailus(dydziai);
        } else if (pasirinkimasMeniu == 7) {
            nuskaitytiIsFailo(studentai);
            grupuotiStudentus(studentai, kietekai, nuskriaustukai);
            isvestiIDuFailus(kietekai, nuskriaustukai);
        } else if (pasirinkimasMeniu == 8) {
            testavimoFunkcija_1(dydziai);
        } else if (pasirinkimasMeniu == 9) {
            testavimoFunkcija_2(studentai, kietekai, nuskriaustukai);
            duomenysIsvesti = true;
            break;
        } else if (pasirinkimasMeniu == 10) {
            testavimoFunkcija_3(studentai, kietekai, nuskriaustukai);
            break;
        } else {
            cout << "Neteisingas pasirinkimas! Bandykite dar kartą.\n";
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    catch (const exception& e) {
        cout << e.what() << "\nBandykite dar kartą.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    }
    

    if (!duomenysIsvesti) {
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

        visit([](auto &konteineris) {
            for (const auto& stud : konteineris) {
                cout << left << setw(15) << stud.pavarde << setw(15) << stud.vardas << fixed << setprecision(2) << setw(15) << stud.galutinis << endl;
            }
        }, studentai);
    
    }
    */
    return 0;
}