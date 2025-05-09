#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "student.h"

// 1. Default konstruktorius
TEST_CASE("Default constructor initializes correct defaults") {
    Studentas s;
    REQUIRE(s.vardas() == "");
    REQUIRE(s.pavarde() == "");
    REQUIRE(s.getNamuDarbai().empty());
    REQUIRE(s.getEgzaminas() == 0);
}

// 2. Copy konstruktorius
TEST_CASE("Copy constructor creates exact copy") {
    Studentas s1;
    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    s1.setNamuDarbai({9, 10});
    s1.setEgzaminas(9);
    s1.skaiciuotiGalutinius();

    Studentas s2 = s1;

    REQUIRE(s2.vardas() == "Jonas");
    REQUIRE(s2.getEgzaminas() == 9);
    REQUIRE(s2.getNamuDarbai() == vector<int>({9, 10}));
}

// 3. Copy assignment operator
TEST_CASE("Copy assignment works correctly") {
    Studentas s1, s2;
    s1.setVardas("A");
    s1.setPavarde("B");
    s1.setEgzaminas(8);
    s1.setNamuDarbai({8, 9});
    s1.skaiciuotiGalutinius();

    s2 = s1;

    REQUIRE(s2.vardas() == "A");
    REQUIRE(s2.getEgzaminas() == 8);
    REQUIRE(s2.getNamuDarbai() == vector<int>({8, 9}));
}


