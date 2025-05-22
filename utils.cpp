#include "student.h"
#include "utils.h"
#include "vector.h"
#include <fstream>
#include <sstream>

void testDestructor() {
    cout << "Testuojamas: Destruktorius" << endl;

        Studentas* s = new Studentas();
        s->setVardas("Bruno");
        s->setPavarde("Mars");
        s->setNamuDarbai({10, 9, 8});
        s->setEgzaminas(9);
        s->setGalutinisVid(9);
        s->setGalutinisMed(9);

        s->~Studentas();

        if (s->getNamuDarbai().empty() && s->getEgzaminas() == 0) {
            cout << left << setw(31) << "Destruktorius iškviestas" << "\n";
        } else {
            cout << left << setw(31) << "Destruktorius neiškviestas" << " \n";
        }
        cout << endl;

        operator delete(s);
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
    cout << "Perkeltas:  " << perkeltas << "\n";
    cout << "Laikinas: " << laikinas << "\n" << endl;
}

void testMoveAssignment() {
    cout << "Testuojamas: Move priskyrimo operatorius" << endl;
    istringstream iss("Lady Gaga 9 9 9 10 10 10");
    Studentas b;
    b.readStudent(iss);

    Studentas a;
    a = std::move(b); 
    cout << "Gavėjas po move: " << a << "\n";
    cout << "Šaltinis po move: " << b << "\n" << endl;
}

void ivestiStudenta(Vector<Studentas>& studentai) {
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

void generuotiStudentus(Vector<Studentas>& studentai) {
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

void test_vector_push_back(unsigned int sz) {
    cout << "Testavimas su " << sz << " elementų:\n";

    // std::vector testas
    {
        std::vector<int> v1;
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int i = 1; i <= sz; ++i) v1.push_back(i);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << "std::vector užtruko: " << duration.count() << " s\n";
    }

    // klasės Vector testas
    {
        Vector<int> v2;
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int i = 1; i <= sz; ++i) v2.push_back(i);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << "klasė Vector užtruko: " << duration.count() << " s\n";
    }

    cout << "----------------------------------------\n";
}