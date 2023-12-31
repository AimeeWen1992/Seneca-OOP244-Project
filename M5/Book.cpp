///////////////////////////////////////////////////
// Milestone 5 : Book.cpp
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
    Book::Book() : Publication() {
        m_authorName = nullptr;
    }

    Book::~Book() {
        delete[] m_authorName;
    }

    Book::Book(const Book& book) : Publication(book) {
        if (m_authorName) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        m_authorName = new char[strlen(book.m_authorName) + 1];
        strcpy(m_authorName, book.m_authorName);
    }

    Book& Book::operator=(const Book& book) {
        Publication::operator=(book);

        if (m_authorName) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        if (book.m_authorName) {
            m_authorName = new char[strlen(book.m_authorName) + 1];
            strcpy(m_authorName, book.m_authorName);
        }

        return *this;
    }

    char Book::type() const {
        return 'B';
    };

    std::ostream& Book::write(std::ostream& os) const {
        Publication::write(os);
        if (conIO(os)) {
            char author[SDDS_AUTHOR_WIDTH + 1] = { '0' };
            strncpy(author, m_authorName, SDDS_AUTHOR_WIDTH);
            os << " ";
            os << setw(SDDS_AUTHOR_WIDTH) << left << setfill(' ') << author << " |";
        }
        else {
            os << "\t" << m_authorName;
        }

        return os;
    }

    std::istream& Book::read(std::istream& is) {
        char tempAuthName[256] = { '0' };

        Publication::read(is);

        if (m_authorName) {
            delete[] m_authorName;
            m_authorName = nullptr;
        }

        if (conIO(is)) {
            is.ignore();
            std::cout << "Author: ";
        }
        else {
            is.ignore(1000, '\t');
        }

        is.get(tempAuthName, 256);

        if (is) {
            m_authorName = new char[strlen(tempAuthName) + 1];
            strcpy(m_authorName, tempAuthName);
        }

        return is;
    }

    void Book::set(int member_id) {
        Publication::set(member_id);
        Publication::resetDate();
    }


    Book::operator bool() const {
        return (m_authorName && Publication::operator bool()) ? true : false;
    }
}