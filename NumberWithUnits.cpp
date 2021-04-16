#include "NumberWithUnits.hpp"
#include <iostream>
#include <map>
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <algorithm> // remove_if
using namespace std;

namespace ariel {
    //////////////////////////////////////////////////////////////////////////
    /////////////////////////// Read_units method ////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    void NumberWithUnits::read_units(ifstream &infile) {
        double first_unit_num = 1;
        double second_unit_num = 0;
        string first_unit;
        string second_unit;
        string line;
        while (getline(infile, line)) {
            /* remove white spaces */
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            /* get first unit */
            size_t i = 0;
            size_t j = 0;
            for (j=1; j < line.length(); j++) {if(line[j]=='=') {break;}}
            first_unit = line.substr(1, j-1);
            /* get second unit number */
            i=j+1;
            for (j=line.length()-1; j >= 0; j--) {if(isdigit(line[j])!=0) {break;}}
            second_unit_num = stod(line.substr(i,j));
            /* get second unit */
            second_unit = line.substr(j+1,line.length()-1);
            /* link the first unit to the parentss and childs of the second unit */
            for (const auto &myPair : get_unit[second_unit]) {
                NumberWithUnits::get_unit[first_unit][myPair.first] = second_unit_num*myPair.second;
                NumberWithUnits::get_unit[myPair.first][first_unit] = (first_unit_num/second_unit_num)/myPair.second;
            }
            /* link the second unit to the parentss and childs of the first unit */
            for (const auto &myPair : get_unit[first_unit]) {
                NumberWithUnits::get_unit[second_unit][myPair.first] = (first_unit_num/second_unit_num)*myPair.second;
                NumberWithUnits::get_unit[myPair.first][second_unit] = second_unit_num/myPair.second;
            }
            /* link the first unit to the second unit */
            NumberWithUnits::get_unit[first_unit][second_unit]=second_unit_num;
            NumberWithUnits::get_unit[second_unit][first_unit]=first_unit_num/second_unit_num;
            /* link each unit to itself */
            if (NumberWithUnits::get_unit[first_unit].count(first_unit)==0) {get_unit[first_unit][first_unit]=1;}
            if (NumberWithUnits::get_unit[second_unit].count(second_unit)==0) {get_unit[second_unit][second_unit]=1;}
        }
    };

    //////////////////////////////////////////////////////////////////////////
    ///////////////////////// Arithmetic operators ///////////////////////////
    //////////////////////////////////////////////////////////////////////////
    NumberWithUnits operator-(const NumberWithUnits& a) {
        return NumberWithUnits(-a.amount, a.unit);
    }

    NumberWithUnits operator+(const NumberWithUnits& a) {
        return a;
    }

    NumberWithUnits operator+(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return NumberWithUnits(a1.amount+a2_new_amount, a1.unit);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    NumberWithUnits operator-(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return NumberWithUnits(a1.amount-a2_new_amount, a1.unit);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    //////////////////////////////////////////////////////////////////////////
    /////////////////////////// Boolean operators ////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    bool operator<(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return (a1.amount<a2_new_amount);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    bool operator>(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return (a1.amount>a2_new_amount);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    bool operator>=(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return (a1.amount>=a2_new_amount);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    bool operator<=(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return (a1.amount<=a2_new_amount);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    bool operator==(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (NumberWithUnits::get_unit.count(a1.unit)!=0&&NumberWithUnits::get_unit[a1.unit].count(a2.unit)!=0) {
            double a2_new_amount = a2.amount*NumberWithUnits::get_unit[a2.unit][a1.unit];
            return (a1.amount==a2_new_amount);
        }
        stringstream ss;
        ss << "Units do not match - [" << a1.unit << "] cannot be converted to [" << a2.unit <<"]";
        throw invalid_argument(ss.str());
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////// ++/-- operators /////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    /* (The implementation of this operators is in the hpp file) */

    //////////////////////////////////////////////////////////////////////////
    ///////////////// Multiplication by real number operators ////////////////
    //////////////////////////////////////////////////////////////////////////
    NumberWithUnits operator*(double d, const NumberWithUnits& a) {
        return NumberWithUnits(d*a.amount, a.unit);
    }

    NumberWithUnits operator*(const NumberWithUnits& a, double d) {
        return NumberWithUnits(d*a.amount, a.unit);
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////// Input/Output operators //////////////////////////
    //////////////////////////////////////////////////////////////////////////
    ostream& operator<<(ostream& os, const NumberWithUnits& a) {
        os << a.amount << "[" << a.unit << "]";
        return os;
    }

    static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
    char actualChar = 0;
    input >> actualChar;
    if (!input) {return input;}

    if (actualChar!=expectedChar) 
        // failbit is for format error
        {input.setstate(ios::failbit);}
    return input;
    }

    istream& operator>>(istream& input, NumberWithUnits& a) {
    double new_amount = 0;
    string new_unit;
    // remember place for rewinding
    ios::pos_type startPosition = input.tellg();
    if ( (!(input >> new_amount))                 ||
         (!getAndCheckNextCharIs(input,'['))  ||
         (!(input >> new_unit))                 ||
         (!(getAndCheckNextCharIs(input,']'))) ) {

        // rewind on error
        auto errorState = input.rdstate(); // remember error state
        input.clear(); // clear error so seekg will work
        input.seekg(startPosition); // rewind
        input.clear(errorState); // set back the error flag
    } else {
        a.amount = new_amount;
        a.unit = new_unit;
    }
    return input;
    }
}