#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../student.h"

// 1. Default konstruktorius
TEST_CASE("Konstruktorius inicijuoja teisingas pradinias reikšmes") {
    Studentas s;
    REQUIRE(s.vardas() == "");
    REQUIRE(s.pavarde() == "");
    REQUIRE(s.getNamuDarbai().empty());
    REQUIRE(s.getEgzaminas() == 0);
    REQUIRE(s.galutinisVid() == 0.0);
    REQUIRE(s.galutinisMed() == 0.0); 
}

// 2. Copy konstruktorius
TEST_CASE("Kopijavimo konstruktorius sukuria kopiją") {
    Studentas s1;
    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    s1.setNamuDarbai({9, 10});
    s1.setEgzaminas(9);
    s1.skaiciuotiGalutinius();

    Studentas s2 = s1;

    REQUIRE(s2.vardas() == "Jonas");
    REQUIRE(s2.pavarde() == "Jonaitis");
    REQUIRE(s2.getEgzaminas() == 9);
    REQUIRE(s2.getNamuDarbai() == vector<int>({9, 10}));
    REQUIRE(s2.galutinisVid() == s1.galutinisVid());
    REQUIRE(s2.galutinisMed() == s1.galutinisMed()); 
}

// 3. Copy assignment operator
TEST_CASE("Kopijavimo priskyrimo operatorius sukuria kopiją") {
    Studentas s1, s2;
    s1.setVardas("A");
    s1.setPavarde("B");
    s1.setEgzaminas(8);
    s1.setNamuDarbai({8, 9});
    s1.skaiciuotiGalutinius();

    s2 = s1;

    REQUIRE(s2.vardas() == "A");
    REQUIRE(s2.pavarde() == "B");
    REQUIRE(s2.getEgzaminas() == 8);
    REQUIRE(s2.getNamuDarbai() == vector<int>({8, 9}));
    REQUIRE(s2.galutinisVid() == s1.galutinisVid());
    REQUIRE(s2.galutinisMed() == s1.galutinisMed());
}

// 4. Move konstruktorius
TEST_CASE("Perdavimo konstruktorius perkelia duomenis") {
    Studentas s1;
    s1.setVardas("X");
    s1.setEgzaminas(10);
    s1.setNamuDarbai({10, 10});
    s1.skaiciuotiGalutinius();

    Studentas s2 = std::move(s1);

    REQUIRE(s2.vardas() == "X");
    REQUIRE(s2.getEgzaminas() == 10);
    REQUIRE(s2.getNamuDarbai() == vector<int>({10, 10}));

    REQUIRE(s1.vardas() == "");
    REQUIRE(s1.getEgzaminas() == 0);
    REQUIRE(s1.getNamuDarbai().empty());
    REQUIRE(s1.galutinisVid() == 0.0);
    REQUIRE(s1.galutinisMed() == 0.0);
}

// 5. Move assignment operator
TEST_CASE("Move assignment operator perkelia duomenis") {
    Studentas s1;
    s1.setVardas("Move");
    s1.setPavarde("Operator");
    s1.setNamuDarbai({7, 8});
    s1.setEgzaminas(9);
    s1.skaiciuotiGalutinius();

    Studentas s2;
    s2 = std::move(s1);
    
    REQUIRE(s2.vardas() == "Move");
    REQUIRE(s2.pavarde() == "Operator");
    REQUIRE(s2.getNamuDarbai() == vector<int>({7, 8}));
    REQUIRE(s2.getEgzaminas() == 9);
    REQUIRE(s2.galutinisVid() > 0.0);
    REQUIRE(s2.galutinisMed() > 0.0);

    REQUIRE(s1.vardas() == "");
    REQUIRE(s1.pavarde() == "");
    REQUIRE(s1.getNamuDarbai().empty());
    REQUIRE(s1.getEgzaminas() == 0);
    REQUIRE(s1.galutinisVid() == 0.0);
    REQUIRE(s1.galutinisMed() == 0.0);
}

// 6. readStudent() testas
TEST_CASE("readStudent() nuskaitymas veikia korektiškai") {
    std::istringstream iss("Vardenis Pavardenis 8 9 10");
    Studentas s;
    iss >> s;

    REQUIRE(s.vardas() == "Vardenis");
    REQUIRE(s.pavarde() == "Pavardenis");
    REQUIRE(s.getNamuDarbai() == std::vector<int>({8, 9}));
    REQUIRE(s.getEgzaminas() == 10);
    REQUIRE(s.galutinisVid() > 0.0);
    REQUIRE(s.galutinisMed() > 0.0);
}

// 7. skaiciuotiGalutinius() testas
TEST_CASE("skaiciuotiVidurki ir skaiciuotiMediana veikia korektiškai") {
    Studentas s;
    std::vector<int> pazymiai = {8, 9, 10};

    double vid = s.skaiciuotiVidurki(pazymiai);
    double med = s.skaiciuotiMediana(pazymiai);

    REQUIRE(vid == (9.0));
    REQUIRE(med == (9.0));

    pazymiai = {7, 9, 10, 8};
    med = s.skaiciuotiMediana(pazymiai);

    REQUIRE(med == (8 + 9) / 2.0);
}


