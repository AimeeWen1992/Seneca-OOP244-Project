///////////////////////////////////////////////////
// Milestone 4 : Book.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
namespace sdds {
    Book::Book() : Publication()
    {
        authorName = nullptr;
    }

    Book::~Book() 
    {
        delete[] authorName;
    }

    Book::Book(const Book& book) : Publication(book)
    {
        if (authorName) 
        {
            delete[] authorName;
            authorName = nullptr;
        }

        authorName = new char[strlen(book.authorName) + 1];
        strcpy(authorName, book.authorName);
    }

    Book& Book::operator=(const Book& book)
    {
        Publication::operator=(book);

        if (authorName)
        {
            delete[] authorName;
            authorName = nullptr;
        }

        if (book.authorName) 
        {
            authorName = new char[strlen(book.authorName) + 1];
            strcpy(authorName, book.authorName);
        }
        else
        {
            authorName = nullptr;
        }

        return *this;
    }


    char Book::type() const 
    {
        return 'B';
    };

    std::ostream& Book::write(std::ostream& os) const 
    {
        Publication::write(os);
        if (conIO(os))
        {
            char author[SDDS_AUTHOR_WIDTH + 1] = { 0 };
            strncpy(author, authorName, SDDS_AUTHOR_WIDTH);
            os << " ";
            os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author << " |";
        }
        else 
        {
            os << "\t" << authorName;
        }

        return os;
    }

    std::istream& Book::read(istream& is) 
    {
        char authName[256] = { '0' };

        Publication::read(is);

        if (authorName) 
        {
            delete[] authorName;
            authorName = nullptr;
        }

        if (conIO(is)) 
        {
            is.ignore();
            cout << "Author: ";
        }
        else 
        {
            is.ignore(1000, '\t');
        }

        is.get(authName, 256);

        if (is)
        {
            authorName = new char[strlen(authName) + 1];
            strcpy(authorName, authName);
        }

        return is;
    }

    void Book::set(int member_id) 
    {
        Publication::set(member_id);
        Publication::resetDate();
    }

    Book::operator bool() const 
    {
        return (authorName && Publication::operator bool()) ? true : false;
    }
}