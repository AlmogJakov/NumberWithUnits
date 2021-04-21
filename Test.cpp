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
    istringstream units("1km = 1000m\n1m=100cm\n1 kg = 1000 g\n1 ton = 1000 kg\n1 hour = 60 min\n1 min = 60 sec\n1 USD = 3.33 ILS");
    ifstream virtual_file;
    virtual_file.basic_ios<char>::rdbuf(units.rdbuf());
    NumberWithUnits::read_units(virtual_file);
    istringstream special_chars_units("1WR24^$#!&=10.01@$^@#*FF\n1T-Unit = 200.3T2-Unit\n1!@#=2.67##!\n1$!@=2.2^!@#'\\\n1^!@#'\\=56.1$@!!");
    ifstream virtual_file2;
    virtual_file2.basic_ios<char>::rdbuf(special_chars_units.rdbuf());
    NumberWithUnits::read_units(virtual_file2);
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
    /* Cases of a units containing numbers/special-characters */
    CHECK(NumberWithUnits(1,"T-Unit") == NumberWithUnits(200.3,"T2-Unit"));
    CHECK(NumberWithUnits(1,"WR24^$#!&") == NumberWithUnits(10.01,"@$^@#*FF"));
    CHECK(NumberWithUnits(1,"!@#") == NumberWithUnits(2.67,"##!"));
    CHECK(NumberWithUnits(1,"$!@") == NumberWithUnits(2.2,"^!@#'\\"));
    CHECK(NumberWithUnits(1,"^!@#'\\") == NumberWithUnits(56.1,"$@!!"));
    CHECK(NumberWithUnits(1,"$!@") == NumberWithUnits(123.42,"$@!!"));
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

TEST_CASE("Constructor throws test") {
    CHECK_THROWS(NumberWithUnits(1,"illegal_unit"));
    CHECK_THROWS(NumberWithUnits(1,"!@#$%^&*()_+"));
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
    result << +NumberWithUnits(1000.2,"m");
    CHECK(result.str() == string("1000.2[m]"));
    result.str("");
    result << -NumberWithUnits(1000.3,"m");
    CHECK(result.str() == string("-1000.3[m]"));
    result.str("");
    result << NumberWithUnits(1.0001,"km") + NumberWithUnits(1000.1,"m");
    CHECK(result.str() == string("2.0002[km]"));
    result.str("");
    result << NumberWithUnits(1000.4,"m") + NumberWithUnits(1.0001,"km");
    CHECK(result.str() == string("2000.5[m]"));
    result.str("");
    result << NumberWithUnits(1000.4,"km") - NumberWithUnits(1.001,"km");
    CHECK(result.str() == string("999.399[km]"));
    result.str("");
    result << NumberWithUnits(1000.2,"m") - NumberWithUnits(1.0001,"km");
    CHECK(result.str() == string("0.1[m]"));
    result.str("");
    NumberWithUnits a(1,"km");
    a += NumberWithUnits(1000.5,"m");
    result << a;
    CHECK(result.str() == string("2.0005[km]"));
    result.str("");
    NumberWithUnits b(1000.4,"m");
    b += NumberWithUnits(1.01,"km");
    result << b;
    CHECK(result.str() == string("2010.4[m]"));
    result.str("");
    NumberWithUnits c(1000.2,"km");
    c -= NumberWithUnits(1.001,"km");
    result << c;
    CHECK(result.str() == string("999.199[km]"));
    result.str("");
    NumberWithUnits d(1000.2,"m");
    d -= NumberWithUnits(1.0001,"km");
    result << d;
    CHECK(result.str() == string("0.1[m]"));
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