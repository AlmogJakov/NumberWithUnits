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


TEST_CASE("just a test") {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};
    stringstream ss;
    string result;
    ss << a;
    CHECK(ss.str() == string("2[km]"));
}
/* Add more test cases here */
