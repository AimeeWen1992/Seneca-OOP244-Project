///////////////////////////////////////////////////
// Milestone 5 : Stramable.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////

#include "Streamable.h"

namespace sdds {
    Streamable::~Streamable(){};

    std::ostream& operator<<(std::ostream& os, const Streamable& streamable) {
        if (streamable) {
            streamable.write(os);
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Streamable& streamable) {
        return (streamable.read(is));
    }
}