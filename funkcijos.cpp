#include "funkcijos.h"

double skaiciuotiVidurki(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    int suma = 0;
    for (int paz : pazymiai) suma += paz;
    return static_cast<double>(suma) / pazymiai.size();
}

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
/*
void ivestiStudenta(vector<Studentas>& studentai, char pasirinkimas) {
    Studentas stud;
    while (true) {  
        try {
            cout << "Ar norite pridėti studentą? (T/N): ";
            char tesiame;
            cin >> tesiame;

            if (cin.fail()) {
                throw invalid_argument("Neteisinga įvestis! Įveskite tik simbolius T arba N.");
            }

            if (tesiame == 'N' || tesiame == 'n') break;

            if (tesiame != 'T' && tesiame != 't') {
                throw invalid_argument("Neteisingas pasirinkimas! Pasirinkite T arba N.");
            }

        cout << "\nĮveskite studento vardą: ";
        cin >> stud.vardas;
        cout << "Įveskite studento pavardę: ";
        cin >> stud.pavarde;
    
    cout << "Įveskite namų darbų rezultatus (baigti -1):\n";
    while (true) {
            int rezultatas;
            try {
                cout << "Įveskite pažymį: ";
                cin >> rezultatas;

                if (cin.fail()) throw invalid_argument("Neteisinga įvestis! Įveskite tik skaičių.");
                if (rezultatas < -1 || rezultatas > 10) throw out_of_range("Klaida: Skaičius turi būti tarp 1-10.");

                if (rezultatas == -1) break;
                stud.namuDarbai.push_back(rezultatas);
            }
            catch (const exception& e) {
                cout << e.what() << " Bandykite dar kartą.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
    while (true){
            try{
                cout << "Įveskite egzamino rezultatą: ";
                cin >> stud.egzaminas;

                if (cin.fail ()) throw invalid_argument("Neteisinga įvestis! Įveskite tik skaičių.");
                if (stud.egzaminas < 1 || stud.egzaminas > 10) throw out_of_range("Klaida: Skaičius turi būti tarp 1-10.");

                break;
            }
            catch (const exception& e) {
                cout << e.what() << " Bandykite dar kartą.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }


        if (pasirinkimas == 'V' || pasirinkimas == 'v') {
        double vidurkis = skaiciuotiVidurki(stud.namuDarbai);
        stud.galutinis = 0.4 * vidurkis + 0.6 * stud.egzaminas;
        } else {
        double mediana = skaiciuotiMediana(stud.namuDarbai);
        stud.galutinis = 0.4 * mediana + 0.6 * stud.egzaminas;
        }
    studentai.push_back(stud);
    }
    catch (const exception& e) {
        cout << e.what() << " Bandykite dar kartą.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    }   
}

void generuotiPazymius(Studentas& stud, char pasirinkimas) {
    
    int kiekis = rand() % 5 + 3;  

    
    for (int i = 0; i < kiekis; ++i) {
        stud.namuDarbai.push_back(rand() % 10 + 1);  
    }

    stud.egzaminas = rand() % 10 + 1; 
    
    if (pasirinkimas == 'V' || pasirinkimas == 'v') {
        double vidurkis = skaiciuotiVidurki(stud.namuDarbai);
        stud.galutinis = 0.4 * vidurkis + 0.6 * stud.egzaminas;
    } else {
        double mediana = skaiciuotiMediana(stud.namuDarbai);
        stud.galutinis = 0.4 * mediana + 0.6 * stud.egzaminas;
    }

    
}

void generuotiStudentus(vector<Studentas>& studentai, char pasirinkimas) {
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
        stud.vardas = vardai[rand() % vardai.size()];
        stud.pavarde = pavardes[rand() % pavardes.size()];
        generuotiPazymius(stud, pasirinkimas);

        if (pasirinkimas == 'V' || pasirinkimas == 'v') {
            double vidurkis = skaiciuotiVidurki(stud.namuDarbai);
            stud.galutinis = 0.4 * vidurkis + 0.6 * stud.egzaminas;
        } else {
            double mediana = skaiciuotiMediana(stud.namuDarbai);
            stud.galutinis = 0.4 * mediana + 0.6 * stud.egzaminas;
        }

        studentai.push_back(stud);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << "Bandykite dar kartą.\n"<<endl;
    }
    }
}
*/

/*
void isvestiDuomenis(vector<Studentas>& studentai) {
    string pasirinkimasIsvesti;

    while (true) {
        try {
            cout << "Ar norite išvesti duomenis į failą ar į ekraną? (F/E): ";
            cin >> pasirinkimasIsvesti;

            if (pasirinkimasIsvesti != "F" && pasirinkimasIsvesti != "f" && 
                pasirinkimasIsvesti != "E" && pasirinkimasIsvesti != "e") {
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
    
    ostream* out;
    ofstream outFile;
    
    if (pasirinkimasIsvesti == "F" || pasirinkimasIsvesti == "f") {
        string failoPavadinimas;
        cout << "Įveskite failo pavadinimą: ";
        cin >> failoPavadinimas;
        outFile.open(failoPavadinimas);
        
        if (!outFile) {
            cout << "Nepavyko atidaryti failo!" << endl;
            return;
        }
        out = &outFile;
    } else {
        out = &cout;
    }

    auto start2 = steady_clock::now();

    *out << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    *out << string(70, '-') << endl;
    
    for (auto& stud : studentai) {
        double vidurkis = skaiciuotiVidurki(stud.namuDarbai);
        double mediana = skaiciuotiMediana(stud.namuDarbai);
        double galutinisVid = 0.4 * vidurkis + 0.6 * stud.egzaminas;
        double galutinisMed = 0.4 * mediana + 0.6 * stud.egzaminas;

        *out << left << setw(15) << stud.pavarde << setw(15) << stud.vardas << fixed << setprecision(2) << setw(20) << galutinisVid << setw(20) << galutinisMed << endl;
    }

    if (outFile.is_open()) {
        outFile.close();
        cout << "Duomenys sėkmingai išsaugoti į failą!" << endl;
    }

    auto end2 = steady_clock::now();  
    cout << "Duomenų išvedimas užtruko: " << duration_cast<milliseconds>(end2 - start2).count() << " ms" << endl;
}

void generuotiFailus(vector<int>& dydziai) {
    while (true) {
        cout << "\nPasirinkite, kokį failą norite sugeneruoti:\n";
        for (size_t i = 0; i < dydziai.size(); ++i) {
            cout << i + 1 << " - studentai" << dydziai[i] << ".txt\n";
        }
        cout << "0 - Baigti\nJūsų pasirinkimas: ";
        
        int pasirinkimas;
        cin >> pasirinkimas;

        if (cin.fail() || pasirinkimas < 0 || pasirinkimas > dydziai.size()) {
            cout << "Neteisinga įvestis! Bandykite dar kartą.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (pasirinkimas == 0) break;  

        int studentuSkaicius = dydziai[pasirinkimas - 1];  
        string failoPavadinimas = "studentai" + to_string(studentuSkaicius) + ".txt";
        
        auto start = chrono::steady_clock::now(); 
        
        ofstream failas(failoPavadinimas);
        if (!failas) {
            cerr << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
            continue;
        }

        failas << left << setw(25) << "Vardas" << setw(25) << "Pavarde";
        for (int i = 1; i <= 15; ++i) failas << setw(5) << "ND" + to_string(i);
        failas << setw(5) << "Egz." << endl;

        for (int i = 1; i <= studentuSkaicius; ++i) {
            failas << left << setw(25) << "VardasNR" + to_string(i) << setw(25) << "PavardeNR" + to_string(i);
            for (int j = 0; j < 15; ++j) failas << setw(5) << (rand() % 10 + 1);
            failas << setw(5) << (rand() % 10 + 1) << endl;
        }

        failas.close();
        
        auto end = chrono::steady_clock::now();  
        cout << "Failas " << failoPavadinimas << " sukurtas sėkmingai!\n";
        cout << "Generavimas užtruko: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
    }
}
*/

/*
void testavimoFunkcija_1(vector<int> dydziai){
    auto start = steady_clock::now();
    generuotiFailus(dydziai);
    auto end = steady_clock::now();  
    cout << "Failų generavimas užtruko: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
}

void testavimoFunkcija_2(vector<Studentas>& studentai, vector<Studentas>& kietekai, vector<Studentas>& nuskriaustukai){
    auto start = steady_clock::now();

    nuskaitytiIsFailo(studentai);

    grupuotiStudentus(studentai, kietekai, nuskriaustukai);

    auto start3 = steady_clock::now();
    isvestiIDuFailus(kietekai, nuskriaustukai);
    auto end3 = steady_clock::now();
    cout << "Išvedimas į failus užtruko: " << duration_cast<milliseconds>(end3 - start3).count() << " ms" << endl;

    auto end = steady_clock::now();
    cout << "Visos funkcijos veikimo laikas: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
}
*/