///////////////////////////////////////////////////
// Milestone 5 : Publication.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
namespace sdds {
    Publication::Publication() {
        setDefault();
    }

    Publication::Publication(const Publication& publication) {
        *this = publication;
    }

    Publication& Publication::operator=(const Publication& publication) {
        set(publication.m_membership);
        setRef(publication.m_libRef);
        strcpy(m_shelfId, publication.m_shelfId);
        m_date = publication.m_date;

        if (m_title)
        {
            delete[] m_title;
            m_title = nullptr;
        }

        // Deep Copying
        if (publication.m_title != nullptr) {
            m_title = new char[strlen(publication.m_title) + 1];
            strcpy(m_title, publication.m_title);
        }
        else {
            m_title = nullptr;
        }

        return *this;
    }

    Publication::~Publication() {
        delete[] m_title;
    }

    void Publication::setDefault() {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        resetDate();
    }

    void Publication::set(int member_id) {
        m_membership = member_id;
    }

    void Publication::setRef(int value) {
        m_libRef = value;
    }

    void Publication::resetDate() {
        m_date = Date();
    }

    char Publication::type() const {
        return 'P';
    }

    bool Publication::onLoan() const {
        return m_membership != 0 ? true : false;
    }

    Date Publication::checkoutDate() const {
        return m_date;
    }

    bool Publication::operator==(const char* title) const {
        return strstr(m_title, title) != nullptr ? true : false;
    }

    Publication::operator const char* () const {
        return m_title;
    }

    int Publication::getRef() const {
        return m_libRef;
    }

    bool Publication::conIO(std::ios& io) const {
        return (&io == &cin || &io == &cout) ? true : false;
    }

    std::ostream& Publication::write(std::ostream& os) const {
        char title[SDDS_TITLE_WIDTH + 1] = { '\0' };
        strncpy(title, m_title, SDDS_TITLE_WIDTH);

        if (conIO(os)) {
            os << "| " << m_shelfId << " | " << setw(30) << left << setfill('.') << title << " | " ;
            if (m_membership)
            {
                os << m_membership;
            }
            else
            {
                os << " N/A ";
            }
            os << " | " << m_date << " |";
        }
        else {
            os << type();
            os << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t";
            os << m_membership;
            os << "\t" << m_date;
        }

        return os;
    }

    std::istream& Publication::read(std::istream& is) {
        char tempTitle[256] = { '\0' }, tempShelfId[SDDS_SHELF_ID_LEN + 1] = { '\0' };
        int tempLibRef = -1, tempMembership = 0;
        Date tempDate;

        if (m_title) {
            delete[] m_title;
            m_title = nullptr;
        }
        setDefault();

        if (conIO(is)) {
            cout << "Shelf No: ";
            is.getline(tempShelfId, SDDS_SHELF_ID_LEN + 1);

            if (strlen(tempShelfId) != SDDS_SHELF_ID_LEN) {
                is.setstate(ios::failbit);
            }

            cout << "Title: ";
            is.getline(tempTitle, 256);

            cout << "Date: ";
            is >> tempDate;
        }
        else {
            is >> tempLibRef;
            is.ignore();
            is.getline(tempShelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            is.getline(tempTitle, 256, '\t');
            is >> tempMembership;
            is.ignore();
            is >> tempDate;
        }

        if (!tempDate) {
            is.setstate(ios::failbit);
        }

        if (is) {
            m_title = new char[strlen(tempTitle) + 1];
            strcpy(m_title, tempTitle);
            strcpy(m_shelfId, tempShelfId);
            m_membership = tempMembership;
            m_date = tempDate;
            m_libRef = tempLibRef;
        }

        return is;
    }

    Publication::operator bool() const {
        return (m_title && m_shelfId[0]) ? true : false;
    }
}