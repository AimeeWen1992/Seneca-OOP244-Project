///////////////////////////////////////////////////
// Milestone 5 : Streamable.h
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////

#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include <iostream>

namespace sdds {
    class Streamable {
    public:

        virtual std::ostream& write(std::ostream& os) const = 0;

        virtual std::istream& read(std::istream& is) = 0;

        virtual bool conIO(std::ios& io) const = 0;

        virtual operator bool() const = 0;

        // Empty virtual destructor to this interface to guaranty that the descendants of the Streamable are removed from memory with no leak
        virtual ~Streamable();
    };
    // Insertion and Extraction operator overloads
    std::ostream& operator<<(std::ostream& os, const Streamable& streamable);
    std::istream& operator>>(std::istream& is, Streamable& streamable);
}

#endif //SDDS_STREAMABLE_H