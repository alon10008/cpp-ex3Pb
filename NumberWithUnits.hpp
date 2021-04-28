#include <iostream>
#include <string>
#include <stdexcept>
#include <map>

using namespace std;


namespace ariel{


    class NumberWithUnits{
    
        public:
            static map<string, map<string, double>> units;
            static void read_units(ifstream& file);
            NumberWithUnits(double size, string unit) {
                if(units[unit].size() == 0)
                {
                    throw invalid_argument("wrong input!!!\n");
                }
                this->size = size; 
                this->unit = unit;
            }
            NumberWithUnits(const NumberWithUnits& n) {
                this->size = n.get_size(); 
                this->unit = n.get_unit();
            }
            double get_size()const {return this->size;}
            string get_unit()const {return this->unit;}
            NumberWithUnits operator+(const NumberWithUnits& nwu);
            NumberWithUnits& operator++();
            NumberWithUnits operator++(int);
            NumberWithUnits operator+(const double& d);
            NumberWithUnits& operator+=(const NumberWithUnits& nwu);
            NumberWithUnits& operator+=(const double& d);
            NumberWithUnits operator+();
            NumberWithUnits operator-(const NumberWithUnits& nwu);
            NumberWithUnits& operator--();
            NumberWithUnits operator--(int);
            NumberWithUnits operator-(const double& d);
            NumberWithUnits& operator-=(const NumberWithUnits& nwu);
            NumberWithUnits& operator-=(const double& d);
            NumberWithUnits operator-();
            NumberWithUnits operator*(const double& d);
            friend NumberWithUnits operator*(const double& d, const NumberWithUnits& nwu);
            bool operator<(const NumberWithUnits& nwu)const;
            bool operator<=(const NumberWithUnits& nwu)const;
            bool operator>(const NumberWithUnits& nwu)const;
            bool operator>=(const NumberWithUnits& nwu)const;
            bool operator==(const NumberWithUnits& nwu)const;
            bool operator!=(const NumberWithUnits& nwu)const;
            friend ostream& operator<<(ostream& os, const NumberWithUnits& nwu);
            friend istream& operator>>(istream& is, NumberWithUnits& nwu);
        private:
            string unit;
            double size;
    };

}
