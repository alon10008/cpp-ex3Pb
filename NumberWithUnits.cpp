#include <iostream>
#include "NumberWithUnits.hpp"
#include <string>
#include <fstream>
#include <cstring>

#define EPSILON 0.000001

using namespace ariel;
using namespace std;

map<string, map<string, double>> NumberWithUnits::units = map<string, map<string, double>>();
void ariel::NumberWithUnits::read_units(ifstream& file) {

    string s;
    string line[5];
    int counter = 0;
    while(file >> s)
    {
        line[counter%5] = s;
        counter++;
        if(counter%5 == 0)
        {
            NumberWithUnits::units[line[1]][line[4]] = stod(line[3]);
            NumberWithUnits::units[line[4]][line[1]] = 1/stod(line[3]);
            for(map<string, double>::iterator it = NumberWithUnits::units[line[4]].begin() ; it != NumberWithUnits::units[line[4]].end() ; it++)
            {
                if(NumberWithUnits::units[line[1]][it->first] == 0)
                {
                    NumberWithUnits::units[line[1]][it->first] = stod(line[3]) * NumberWithUnits::units[line[4]][it->first];
                }
                if(NumberWithUnits::units[it->first][line[1]] == 0)
                {
                    NumberWithUnits::units[it->first][line[1]] = 1/(stod(line[3])*NumberWithUnits::units[line[4]][it->first]);
                }
            }
        }
    }
    for(map<string, map<string, double>>::iterator it = NumberWithUnits::units.begin() ; it != NumberWithUnits::units.end() ; it++)
    {
        for(map<string, double>::iterator iter = NumberWithUnits::units[it->first].begin() ; iter != NumberWithUnits::units[it->first].end() ; iter++)
        {
            for(map<string, double>::iterator iterat = NumberWithUnits::units[it->first].begin() ; iterat != NumberWithUnits::units[it->first].end() ; iterat++)
            {
                if(NumberWithUnits::units[iter->first][iterat->first] == 0)
                {
                    NumberWithUnits::units[iter->first][iterat->first] = NumberWithUnits::units[it->first][iterat->first] / NumberWithUnits::units[it->first][iter->first];
                }
            }
        }
    } 
    file.close();
}
NumberWithUnits ariel::NumberWithUnits::operator+(const NumberWithUnits& nwu){

    NumberWithUnits n(*this);
    double convert = NumberWithUnits::units[n.get_unit()][nwu.get_unit()];
    if(convert == 0)
    {
        throw invalid_argument("diffrenet type!\n");
    }
    n.size += nwu.size/convert;
    return n;

}
NumberWithUnits& ariel::NumberWithUnits::operator++(){

    ++this->size;
    return *this;

}
NumberWithUnits ariel::NumberWithUnits::operator++(int){

    NumberWithUnits n(*this);
    this->size++;
    return n;

}
NumberWithUnits ariel::NumberWithUnits::operator+(const double& d){

    NumberWithUnits nwu(*this);
    nwu.size += d;
    return nwu;

}
NumberWithUnits& ariel::NumberWithUnits::operator+=(const NumberWithUnits& nwu){
    
    double convert = NumberWithUnits::units[this->unit][nwu.get_unit()];
    if(convert == 0)
    {
        throw invalid_argument("diffrenet type!\n");
    }
    this->size += nwu.size/convert;
    return *this;

}
NumberWithUnits& ariel::NumberWithUnits::operator+=(const double& d){

    this->size += d;
    return *this;

}
NumberWithUnits ariel::NumberWithUnits::operator+(){

    return NumberWithUnits(*this);

}
NumberWithUnits ariel::NumberWithUnits::operator-(const NumberWithUnits& nwu){

    NumberWithUnits n(*this);
    double convert = -1;
    convert = NumberWithUnits::units[n.get_unit()][nwu.get_unit()];
    if(convert == 0)
    {
        throw invalid_argument("diffrenet type!\n");
    }
    n.size -= nwu.size/convert;
    return n;

}
NumberWithUnits& ariel::NumberWithUnits::operator--(){

    --this->size;
    return *this;

}
NumberWithUnits ariel::NumberWithUnits::operator--(int){

    
    NumberWithUnits n(*this);
    this->size--;
    return n;

}
NumberWithUnits ariel::NumberWithUnits::operator-(const double& d){

    NumberWithUnits n(*this);
    n.size -= d;
    return n;

}
NumberWithUnits& ariel::NumberWithUnits::operator-=(const NumberWithUnits& nwu){

    double convert = -1;
    convert = NumberWithUnits::units[this->unit][nwu.get_unit()];
    if(convert == 0)
    {
        throw invalid_argument("diffrenet type!\n");
    }
    this->size -= nwu.size/convert;
    return *this;

}
NumberWithUnits& ariel::NumberWithUnits::operator-=(const double& d){

    this->size -= d;
    return *this;

}
NumberWithUnits ariel::NumberWithUnits::operator-(){

    NumberWithUnits n(*this);
    n.size *= -1;
    return n;

}
NumberWithUnits ariel::NumberWithUnits::operator*(const double& d){

    NumberWithUnits nwu(*this);
    nwu.size *= d;
    return nwu;

}
NumberWithUnits ariel::operator*(const double& d, const NumberWithUnits& nwu){
 
    NumberWithUnits n(nwu);
    n.size *= d;
    return n;

}
bool ariel::NumberWithUnits::operator<(const NumberWithUnits& nwu)const{

    if(NumberWithUnits::units[this->unit][nwu.get_unit()] == 0)
    {
        throw invalid_argument("NOT the same type!\n");
    }
    double convert = nwu.get_size()/NumberWithUnits::units[this->unit][nwu.get_unit()];
    return this->get_size()<convert;

}
bool ariel::NumberWithUnits::operator<=(const NumberWithUnits& nwu)const{

    if(NumberWithUnits::units[this->unit][nwu.get_unit()] == 0)
    {
        throw invalid_argument("NOT the same type!\n");
    }
    double convert = nwu.get_size()/NumberWithUnits::units[this->unit][nwu.get_unit()];
    return this->size<=convert;

}
bool ariel::NumberWithUnits::operator>(const NumberWithUnits& nwu)const{

    if(NumberWithUnits::units[this->unit][nwu.get_unit()] == 0)
    {
        throw invalid_argument("NOT the same type!\n");
    }
    double convert = nwu.get_size()/NumberWithUnits::units[this->unit][nwu.get_unit()];
    return this->size>convert;

}
bool ariel::NumberWithUnits::operator>=(const NumberWithUnits& nwu)const{

    if(NumberWithUnits::units[this->unit][nwu.get_unit()] == 0)
    {
        throw invalid_argument("NOT the same type!\n");
    }
    double convert = nwu.get_size()/NumberWithUnits::units[this->unit][nwu.get_unit()];
    return this->size>=convert;

}
bool ariel::NumberWithUnits::operator==(const NumberWithUnits& nwu)const{

    if(NumberWithUnits::units[this->unit][nwu.get_unit()] == 0)
    {
        throw invalid_argument("NOT the same type!\n");
    }
    double convert = nwu.get_size()/NumberWithUnits::units[this->unit][nwu.get_unit()];
    double d = this->size-convert;
    return (d<EPSILON) && (-d<EPSILON);

}
bool ariel::NumberWithUnits::operator!=(const NumberWithUnits& nwu)const{

    if(NumberWithUnits::units[this->unit][nwu.get_unit()] == 0)
    {
        throw invalid_argument("NOT the same type!\n");
    }
    double convert = nwu.get_size()/NumberWithUnits::units[this->unit][nwu.get_unit()];
    return this->size!=convert;

}
ostream& ariel::operator<<(ostream& os, const NumberWithUnits& nwu){

    os << nwu.size << "[" << nwu.unit << "]"; 
    return os;

}
istream& ariel::operator>>(istream& is, NumberWithUnits& nwu){

    string s;
    string u;
    while(is >> s)
    {
        u += s;
        if(u[u.length()-1] == ']')
        {
            break;
        }
    }
    int ind;
    char str[u.size() + 1];
    strcpy(str, &u[0]);
    for(int i=0 ; i<u.length() ; i++)
    {
        if(str[i] == '[')
        {
            ind = i;
            break;
        }
    } 
    string ssize, unit;
    for(int i=0 ; i<u.length() ; i++)
    {
        if(str[i]==']')
        {
            break;
        }
        if(i<ind)
        {
            ssize += str[i];
        }
        if(i>ind)
        {
            unit += str[i];
        }
    }
    double size = stod(ssize);
    nwu = NumberWithUnits(size, unit);
    return is;

}
