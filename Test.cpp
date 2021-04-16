/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Please write your names here>
 * 
 * Date: 2020-02
 */

#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace ariel;
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <string>
using namespace std;


TEST_CASE("Read_units test") {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    /* valid units - km, m, cm, ton, kg, g, hour, min, sec, USD, ILS */
    /* Valid conversion check (different units) */
    CHECK(NumberWithUnits(1,"km") == NumberWithUnits(1000,"m"));
    CHECK(NumberWithUnits(1,"km") == NumberWithUnits(100000,"cm"));
    CHECK(NumberWithUnits(1,"m") == NumberWithUnits(100,"cm"));
    CHECK(NumberWithUnits(1,"ton") == NumberWithUnits(1000,"kg"));
    CHECK(NumberWithUnits(1,"ton") == NumberWithUnits(1000000,"g"));
    CHECK(NumberWithUnits(1,"kg") == NumberWithUnits(1000,"g"));
    CHECK(NumberWithUnits(1,"hour") == NumberWithUnits(60,"min"));
    CHECK(NumberWithUnits(1,"hour") == NumberWithUnits(60*60,"sec"));
    CHECK(NumberWithUnits(1,"min") == NumberWithUnits(60,"sec"));
    CHECK(NumberWithUnits(1,"USD") == NumberWithUnits(3.33,"ILS"));
    /* Valid conversion check (self-conversion) */
    CHECK(NumberWithUnits(1,"km") == NumberWithUnits(1,"km"));
    CHECK(NumberWithUnits(1,"m") == NumberWithUnits(1,"m"));
    CHECK(NumberWithUnits(1,"cm") == NumberWithUnits(1,"cm"));
    CHECK(NumberWithUnits(1,"ton") == NumberWithUnits(1,"ton"));
    CHECK(NumberWithUnits(1,"kg") == NumberWithUnits(1,"kg"));
    CHECK(NumberWithUnits(1,"g") == NumberWithUnits(1,"g"));
    CHECK(NumberWithUnits(1,"hour") == NumberWithUnits(1,"hour"));
    CHECK(NumberWithUnits(1,"min") == NumberWithUnits(1,"min"));
    CHECK(NumberWithUnits(1,"sec") == NumberWithUnits(1,"sec"));
    CHECK(NumberWithUnits(1,"USD") == NumberWithUnits(1,"USD"));
    CHECK(NumberWithUnits(1,"ILS") == NumberWithUnits(1,"ILS"));
    /* Invalid conversion check (foreign units) */
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"kg"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"g"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"ton"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"hour"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"min"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"sec"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"km") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"kg"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"g"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"ton"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"hour"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"min"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"sec"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"kg"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"g"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"ton"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"hour"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"min"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"sec"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"cm") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"ton") + NumberWithUnits(1,"hour"));
    CHECK_THROWS(NumberWithUnits(1,"ton") + NumberWithUnits(1,"min"));
    CHECK_THROWS(NumberWithUnits(1,"ton") + NumberWithUnits(1,"sec"));
    CHECK_THROWS(NumberWithUnits(1,"ton") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"ton") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"kg") + NumberWithUnits(1,"hour"));
    CHECK_THROWS(NumberWithUnits(1,"kg") + NumberWithUnits(1,"min"));
    CHECK_THROWS(NumberWithUnits(1,"kg") + NumberWithUnits(1,"sec"));
    CHECK_THROWS(NumberWithUnits(1,"kg") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"kg") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"g") + NumberWithUnits(1,"hour"));
    CHECK_THROWS(NumberWithUnits(1,"g") + NumberWithUnits(1,"min"));
    CHECK_THROWS(NumberWithUnits(1,"g") + NumberWithUnits(1,"sec"));
    CHECK_THROWS(NumberWithUnits(1,"g") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"g") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"hour") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"hour") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"min") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"min") + NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"sec") + NumberWithUnits(1,"USD"));
    CHECK_THROWS(NumberWithUnits(1,"sec") + NumberWithUnits(1,"ILS"));
    /* Invalid conversion check (illegal units) */
    CHECK_THROWS(NumberWithUnits(1,"illegal_unit") + NumberWithUnits(1,"illegal_unit"));
    CHECK_THROWS(NumberWithUnits(1,"illegal_unit1") + NumberWithUnits(1,"illegal_unit2"));
    CHECK_THROWS(NumberWithUnits(1,"m") + NumberWithUnits(1,"illegal_unit2"));
    CHECK_THROWS(NumberWithUnits(1,"illegal_unit1") + NumberWithUnits(1,"m"));
}

TEST_CASE("Constructor test") {
    CHECK_THROWS(NumberWithUnits(1,"illegal_unit"));
    CHECK_THROWS(NumberWithUnits(1,"KM"));
    CHECK_THROWS(NumberWithUnits(1,"Km"));
    CHECK_THROWS(NumberWithUnits(1,"kM"));
    CHECK_THROWS(NumberWithUnits(1,"TON"));
    CHECK_THROWS(NumberWithUnits(1,"tON"));
    CHECK_THROWS(NumberWithUnits(1,"ToN"));
    CHECK_THROWS(NumberWithUnits(1,"TOn"));
    CHECK_THROWS(NumberWithUnits(1,"toN"));
    CHECK_THROWS(NumberWithUnits(1,"tOn"));
    CHECK_THROWS(NumberWithUnits(1,"Ton"));
    CHECK_THROWS(NumberWithUnits(1,"ils"));
    CHECK_THROWS(NumberWithUnits(1,"ilS"));
    CHECK_THROWS(NumberWithUnits(1,"iLs"));
    CHECK_THROWS(NumberWithUnits(1,"Ils"));
    CHECK_THROWS(NumberWithUnits(1,"ILs"));
    CHECK_THROWS(NumberWithUnits(1,"IlS"));
    CHECK_THROWS(NumberWithUnits(1,"iLS"));
}

TEST_CASE("Arithmetic operators") {
    stringstream result;
    result << +NumberWithUnits(1000,"m");
    CHECK(result.str() == string("1000[m]"));
    result.str("");
    result << -NumberWithUnits(1000,"m");
    CHECK(result.str() == string("-1000[m]"));
    result.str("");
    result << NumberWithUnits(1,"km") + NumberWithUnits(1000,"m");
    CHECK(result.str() == string("2[km]"));
    result.str("");
    result << NumberWithUnits(1000,"m") + NumberWithUnits(1,"km");
    CHECK(result.str() == string("2000[m]"));
    result.str("");
    result << NumberWithUnits(1000,"km") - NumberWithUnits(1,"km");
    CHECK(result.str() == string("999[km]"));
    result.str("");
    result << NumberWithUnits(1000,"m") - NumberWithUnits(1,"km");
    CHECK(result.str() == string("0[m]"));
    result.str("");
    NumberWithUnits a(1,"km");
    a += NumberWithUnits(1000,"m");
    result << a;
    CHECK(result.str() == string("2[km]"));
    result.str("");
    NumberWithUnits b(1000,"m");
    b += NumberWithUnits(1,"km");
    result << b;
    CHECK(result.str() == string("2000[m]"));
    result.str("");
    NumberWithUnits c(1000,"km");
    c -= NumberWithUnits(1,"km");
    result << c;
    CHECK(result.str() == string("999[km]"));
    result.str("");
    NumberWithUnits d(1000,"m");
    d -= NumberWithUnits(1,"km");
    result << d;
    CHECK(result.str() == string("0[m]"));
}

TEST_CASE("Boolean operators") {
    CHECK(NumberWithUnits(1,"ton") < NumberWithUnits(1001,"kg"));
    CHECK(NumberWithUnits(1,"ton") < NumberWithUnits(1000001,"g"));
    CHECK(NumberWithUnits(1,"ton") > NumberWithUnits(999,"kg"));
    CHECK(NumberWithUnits(1,"ton") > NumberWithUnits(999999,"g"));
    CHECK(NumberWithUnits(1,"ton") >= NumberWithUnits(999,"kg"));
    CHECK(NumberWithUnits(1,"ton") >= NumberWithUnits(999999,"g"));
    CHECK(NumberWithUnits(1,"ton") <= NumberWithUnits(1001,"kg"));
    CHECK(NumberWithUnits(1,"ton") <= NumberWithUnits(1000001,"g"));
    CHECK(NumberWithUnits(1,"ton") >= NumberWithUnits(1000,"kg"));
    CHECK(NumberWithUnits(1,"ton") >= NumberWithUnits(1000000,"g"));
    CHECK(NumberWithUnits(1,"ton") <= NumberWithUnits(1000,"kg"));
    CHECK(NumberWithUnits(1,"ton") <= NumberWithUnits(1000000,"g"));
    CHECK(NumberWithUnits(1,"ton") == NumberWithUnits(1000,"kg"));
    CHECK(NumberWithUnits(1,"ton") == NumberWithUnits(1000000,"g"));
}

TEST_CASE("++/-- operators") {
    /* prefix increment */
    CHECK(++NumberWithUnits(1000,"m") == NumberWithUnits(1001,"m"));
    CHECK(++NumberWithUnits(1,"km") == NumberWithUnits(2000,"m"));
    CHECK(++NumberWithUnits(1,"km") == NumberWithUnits(200000,"cm"));
    CHECK(--NumberWithUnits(1000,"m") == NumberWithUnits(999,"m"));
    CHECK(--NumberWithUnits(2,"km") == NumberWithUnits(1000,"m"));
    CHECK(--NumberWithUnits(2,"km") == NumberWithUnits(100000,"cm"));
    /* postfix increment */
    CHECK(NumberWithUnits(1000,"m")++ == NumberWithUnits(1000,"m"));
    CHECK(NumberWithUnits(1,"km")++ == NumberWithUnits(1000,"m"));
    CHECK(NumberWithUnits(1,"km")++ == NumberWithUnits(100000,"cm"));
    CHECK(NumberWithUnits(1000,"m")-- == NumberWithUnits(1000,"m"));
    CHECK(NumberWithUnits(2,"km")-- == NumberWithUnits(2000,"m"));
    CHECK(NumberWithUnits(2,"km")-- == NumberWithUnits(200000,"cm"));
}

TEST_CASE("Multiplication by real number operators") {
    CHECK((NumberWithUnits(1000,"m")*7) == NumberWithUnits(7000,"m"));
    CHECK((7*NumberWithUnits(1000,"m")) == NumberWithUnits(7000,"m"));
    CHECK((NumberWithUnits(1000,"km")*7) == NumberWithUnits(7000000,"m"));
    CHECK((7*NumberWithUnits(1000,"km")) == NumberWithUnits(7000000,"m"));
}

TEST_CASE("Input/Output operators") {
    NumberWithUnits a{1,"ILS"};
    istringstream first_num{"2 [ ton ]"};
    first_num >> a;
    stringstream result;
    result << a;
    CHECK(result.str() == string("2[ton]"));
    NumberWithUnits b{1,"ILS"};
    istringstream second_num{"2[ton ] "};
    second_num >> b;
    CHECK(a == b);
}