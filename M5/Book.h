///////////////////////////////////////////////////
// Milestone 5 : Book.h
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include "Publication.h"

namespace sdds {
    class Book : public Publication {
    private:
        char* m_authorName;
    public:
        Book();
        ~Book();
        Book(const Book& book);
        Book& operator=(const Book& book);

        // Returns the character "B".
        char type() const;

        // Write into an ostream object
        std::ostream& write(std::ostream& os) const;

        // Read from an istream object.
        std::istream& read(std::istream& is);

        // Sets the membership attribute to either zero or a five-digit integer.
        virtual void set(int member_id);

        // Overloads of this method will return if the Streamable object is in a valid state or not
        operator bool() const override;
    };
}

#endif // SDDS_BOOK_H
