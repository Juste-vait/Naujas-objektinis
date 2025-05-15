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

class Zmogus {
    protected:
        string vardas_;
        string pavarde_;
    public:
        Zmogus() = default;
        Zmogus(const string& vardas, const string& pavarde) : vardas_(vardas), pavarde_(pavarde) {}
        virtual ~Zmogus() = default;
    
        virtual string vardas() const = 0;
        virtual string pavarde() const = 0;
    
        virtual void setVardas(const string& vardas) = 0;
        virtual void setPavarde(const string& pavarde) = 0;
};

class Studentas : public Zmogus {
    private:
        vector<int> namuDarbai_;
        int egzaminas_;
        double galutinisVid_;
        double galutinisMed_;
    
    public:
        // Konstruktoriai ir destruktoriai
        Studentas();
        ~Studentas();
    
        Studentas(const Studentas& other);
        Studentas& operator=(const Studentas& other);
        Studentas(Studentas&& other) noexcept;
        Studentas& operator=(Studentas&& other) noexcept;
    
        // Getteriai
        string vardas() const override { return vardas_; }
        string pavarde() const override { return pavarde_; }
        double galutinisVid() const { return galutinisVid_; }
        double galutinisMed() const { return galutinisMed_; }
        vector<int> getNamuDarbai() const { return namuDarbai_; }
        int getEgzaminas() const { return egzaminas_; }
        size_t getNamuDarbaiSize() const { return namuDarbai_.size(); }
    
        // Setteriai
        void setVardas(const string& vardas) override { vardas_ = vardas; }
        void setPavarde(const string& pavarde) override { pavarde_ = pavarde; }
        void setEgzaminas(int egzas) { egzaminas_ = egzas; }
        void setNamuDarbai(const vector<int>& nd) { namuDarbai_ = nd; }
        void setGalutinisVid(double vid) { galutinisVid_ = vid; }
        void setGalutinisMed(double med) { galutinisMed_ = med; }
    
        // Funkcijos
        istream& readStudent(istream& is);
    
        void skaiciuotiGalutinius();
        static double skaiciuotiVidurki(const vector<int>& pazymiai);
        static double skaiciuotiMediana(vector<int> pazymiai);
    
        // Operatoriai
        friend ostream& operator<<(ostream& os, const Studentas& s);
        friend istream& operator>>(istream& is, Studentas& s);
    };

#endif
