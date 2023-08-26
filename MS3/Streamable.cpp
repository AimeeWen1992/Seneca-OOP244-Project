///////////////////////////////////////////////////
// Milestone 3 : Streamable.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#include "Streamable.h"

namespace sdds {

    Streamable::~Streamable() {};

    std::ostream& operator<<(std::ostream& os, const Streamable& s) {
        if (s) {
            s.write(os);
        }
        return os;
    }
    std::istream& operator>>(std::istream& is, Streamable& s) {
        return (s.read(is));
    }
}