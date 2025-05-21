#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../vector.h"

TEST_CASE("Tuščias konstruktorius sukuria tuščią vektorių", "[constructor]") {
    Vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("Konstruktorius su dydžiu sukuria vektorių su n reikšmių", "[constructor]") {
    Vector<int> v(5);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 5);
}

TEST_CASE("Inicializavimo sąrašo konstruktorius priskiria teisingas reikšmes", "[initializer_list]") {
    Vector<int> v{1, 2, 3};
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("Kopijavimo konstruktorius sukuria identišką kopiją", "[copy_constructor]") {
    Vector<int> a{1, 2, 3};
    Vector<int> b = a;
    REQUIRE(b == a);
}

TEST_CASE("Perkėlimo konstruktorius perkelia duomenis", "[move_constructor]") {
    Vector<int> a{1, 2, 3};
    Vector<int> b = std::move(a);
    REQUIRE(b.size() == 3);
    REQUIRE(a.size() == 0);
}

TEST_CASE("Kopijavimo priskyrimo operatorius perrašo teisingai", "[copy_assignment]") {
    Vector<int> a{4, 5, 6};
    Vector<int> b;
    b = a;
    REQUIRE(b == a);
}

TEST_CASE("Perkėlimo priskyrimo operatorius perkelia duomenis", "[move_assignment]") {
    Vector<int> a{7, 8};
    Vector<int> b;
    b = std::move(a);
    REQUIRE(b.size() == 2);
    REQUIRE(a.size() == 0);
}

TEST_CASE("erase pašalina elementą vienoje pozicijoje", "[erase]") {
    Vector<int> v{1, 2, 3};
    v.erase(v.begin() + 1);
    REQUIRE(v.size() == 2);
    REQUIRE(v[1] == 3);
}

TEST_CASE("erase su dviem iteratoriais pašalina intervalą", "[erase_range]") {
    Vector<int> v{1, 2, 3, 4, 5};
    v.erase(v.begin() + 1, v.begin() + 4);
    REQUIRE(v.size() == 2);
    REQUIRE(v[1] == 5);
}

TEST_CASE("shrink_to_fit sumažina capacity iki size", "[shrink_to_fit]") {
    Vector<int> v{1, 2, 3};
    v.reserve(10);
    REQUIRE(v.capacity() == 10);
    v.shrink_to_fit();
    REQUIRE(v.capacity() == 3);
}

TEST_CASE("swap sukeičia dviejų vektorių turinį", "[swap]") {
    Vector<int> a{1, 2}, b{3, 4, 5};
    a.swap(b);
    REQUIRE(a.size() == 3);
    REQUIRE(b.size() == 2);
    REQUIRE(a[0] == 3);
}

TEST_CASE("operator[] ir at grąžina teisingas reikšmes ir tikrina ribas", "[element_access]") {
    Vector<int> v{9, 8, 7};
    REQUIRE(v[1] == 8);
    REQUIRE(v.at(2) == 7);
    REQUIRE_THROWS_AS(v.at(10), std::out_of_range);
}

TEST_CASE("front ir back grąžina teisingus elementus", "[front_back]") {
    Vector<int> v{100, 200, 300};
    REQUIRE(v.front() == 100);
    REQUIRE(v.back() == 300);
}

TEST_CASE("reserve padidina capacity", "[reserve]") {
    Vector<int> v;
    v.reserve(20);
    REQUIRE(v.capacity() >= 20);
}

TEST_CASE("resize padidina arba sumažina dydį", "[resize]") {
    Vector<int> v{1, 2};
    v.resize(5);
    REQUIRE(v.size() == 5);
    v.resize(2);
    REQUIRE(v.size() == 2);
}

TEST_CASE("push_back prideda elementą į galą", "[push_back]") {
    Vector<int> v;
    v.push_back(10);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 10);
}

TEST_CASE("pop_back pašalina paskutinį elementą", "[pop_back]") {
    Vector<int> v{1, 2, 3};
    v.pop_back();
    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 2);
}

TEST_CASE("clear ištuština vektorių", "[clear]") {
    Vector<int> v{1, 2, 3};
    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
}

TEST_CASE("assign priskiria naujas reikšmes iš masyvo", "[assign]") {
    int arr[] = {5, 6, 7};
    Vector<int> v;
    v.assign(arr, arr + 3);
    REQUIRE(v.size() == 3);
    REQUIRE(v[1] == 6);
}

TEST_CASE("operator== ir operator!= veikia teisingai", "[comparison]") {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};
    Vector<int> c{1, 2};
    REQUIRE(a == b);
    REQUIRE(a != c);
}

TEST_CASE("begin ir end grąžina teisingus iteratorius", "[iterators]") {
    Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    REQUIRE(sum == 6);
}
