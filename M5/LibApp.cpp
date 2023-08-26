///////////////////////////////////////////////////
// Milestone 5 : LibApp.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Book.h"
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Utils.h"

using namespace std;

namespace sdds {
    LibApp::LibApp(const char* filename): m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicationType("Choose the type of publication:") {
     
        if (filename)
        {
            strcpy(m_filename, filename);
        }

        m_changed = false;
        m_NOLP = 0;
        m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
        m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
        m_publicationType << "Book" << "Publication";

        load();
    }

    LibApp::~LibApp() {
        for (int i = 0; i < m_NOLP; i++) {
            delete m_PPA[i];
        }
    }

    Publication* LibApp::getPub(int libRef) {
        Publication* result = nullptr;
        for (int i = 0; i < m_NOLP; i++)
        {
            if (m_PPA[i]->getRef() == libRef) {
                result = m_PPA[i];
            }
        }

        return result;
    }

    bool LibApp::confirm(const char* message) {
        bool result = false;
        Menu menu(message);
        menu << "Yes";

        int returnedValue = menu.run();
        if (returnedValue == 1) {
            result = true;
        }

        return result;
    }

    void LibApp::load() {
        char type{};
        cout << "Loading Data" << endl;
        ifstream infile(m_filename);

        for (int i = 0; infile && i < SDDS_LIBRARY_CAPACITY; i++) {
            infile >> type;

            infile.ignore();
            if (infile) {
                if (type == 'P')
                    m_PPA[i] = new Publication;

                else if (type == 'B')
                    m_PPA[i] = new Book;

                if (m_PPA[i]) {
                    infile >> *m_PPA[i];
                    m_NOLP++;
                    m_LLRN = m_PPA[i]->getRef();
                }
            }
        }
    };

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream out_file(m_filename);
        int i;
        for (i = 0; i < m_NOLP; i++) {
            if (m_PPA[i]->getRef() != 0)
            {
                out_file << *m_PPA[i] << endl;
            }
        }

        out_file.close();
    }

    int LibApp::search(int searchType) {
        char title[256] = { '\0' };
        int selectedType = 0, i = 0, libRef = 0;
        char typeChar = '\0';
        PublicationSelector pubSel("Select one of the following found matches:", 15);

        selectedType = m_publicationType.run();
        switch (selectedType)
        {
        case 1:
            typeChar = 'B';
            break;
        case 2:
            typeChar = 'P';
            break;
        }

        cin.ignore(1000, '\n');
        cout << "Publication Title: ";
        cin.getline(title, 256);

        switch (searchType)
        {
        case 1:
            for (i = 0; i < m_NOLP; i++) {
                if (m_PPA[i]->operator==(title) && typeChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
                    pubSel << m_PPA[i];
                }
            }
            break;
        case 2:
            for (i = 0; i < m_NOLP; i++) {
                if (m_PPA[i]->operator==(title) && m_PPA[i]->onLoan() && typeChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
                    pubSel << m_PPA[i];
                }
            }
            break;
        case 3:
            for (i = 0; i < m_NOLP; i++) {
                if (m_PPA[i]->operator==(title) && !m_PPA[i]->onLoan() && typeChar == m_PPA[i]->type() && m_PPA[i]->getRef() != 0) {
                    pubSel << m_PPA[i];
                }
            }
            break;
        }

        if (pubSel) {
            pubSel.sort();
            libRef = pubSel.run();

            if (libRef > 0)
            {
                cout << *getPub(libRef) << endl;
            }
            else {
                cout << "Aborted!" << endl;
            }
        }
        else {
            cout << "No matches found!" << endl;
        }

        return libRef;
    }

    void LibApp::returnPub() {
        bool aborted = false;
        cout << "Return publication to the library" << endl;
        int libRef = search(2); 
        if (!(libRef > 0)) {
            aborted = true;
        }

        if (!aborted) {
            bool confirmed = confirm("Return Publication?");

            if (confirmed) {
                int daysLoaned = Date() - getPub(libRef)->checkoutDate();

                if (daysLoaned > SDDS_MAX_LOAN_DAYS) {
                    double penalty = (daysLoaned - SDDS_MAX_LOAN_DAYS) * 0.5;
                    cout << fixed << setprecision(2);
                    cout << "Please pay $" << penalty << " penalty for being " << (daysLoaned - SDDS_MAX_LOAN_DAYS) << " days late!" << endl;
                }
                getPub(libRef)->set(0);
                m_changed = true;
            }

            cout << "Publication returned" << endl;
        }

        cout << endl;
    }

    void LibApp::newPublication() {
        bool aborted = false;

        if (m_NOLP >= SDDS_LIBRARY_CAPACITY)
        {
            cout << "Library is at its maximum capacity!" << endl;
        }
        else{
            cout << "Adding new publication to the library" << endl;
            Publication* p = nullptr;
            int pubType = m_publicationType.run();
            cin.ignore(1000, '\n');

            switch (pubType)
            {
            case 0:
                cout << "Aborted!" << endl;
                aborted = true;
                break;
            case 1:
                p = new Book;
                cin >> *p;
                break;
            case 2:
                p = new Publication;
                cin >> *p;
                break;
            }

            if (cin.fail())
            {
                cin.ignore(1000, '\n');
                cin.clear();
                cout << "Aborted!" << endl;
                exit(0);
            }
            else {
                if (!aborted && confirm("Add this publication to the library?")) {
                    if (*p)
                    {
                        m_LLRN++;
                        p->setRef(m_LLRN);
                        m_PPA[m_NOLP] = p;
                        m_NOLP++;
                        m_changed = true;

                        cout << "Publication added" << endl;
                    }
                    else
                    {
                        cout << "Failed to add publication!" << endl;
                        delete p;
                    }
                }
            }
        }
        cout << endl;
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library" << endl;
        int libRef = search(1); 

        if (libRef) {
            bool confirmed = confirm("Remove this publication from the library?");
            if (confirmed) {
                getPub(libRef)->setRef(0);
                m_changed = true;
                cout << "Publication removed" << endl;
            }
        }
        cout << endl;
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library" << endl;
        int libRef = search(3);

        if (libRef > 0) {
            bool confirmed = confirm("Check out publication?");
            if (confirmed) {
                cout << "Enter Membership number: ";
                int inputMembership = inputIntRange(10000, 99999,"Invalid membership number, try again: ");
                getPub(libRef)->set(inputMembership);
                m_changed = true;
                cout << "Publication checked out"<< endl;
            }
        }
        cout << endl;
    }

    void LibApp::run() {
        int userInputMenu, userInputExit;
        do {
            userInputMenu = m_mainMenu.run();
            switch (userInputMenu) {
                case 0:
                    if (m_changed) {
                        userInputExit = m_exitMenu.run();

                        switch (userInputExit) {
                            case 0:
                                if (confirm("This will discard all the changes are you sure?"))
                                    m_changed = false;
                                break;
                            case 1:
                                save();
                                break;
                            case 2:
                                userInputMenu = 1;
                                break;
                        }
                    }
                    cout << endl;
                    break;
                case 1:
                    newPublication();
                    break;
                case 2:
                    removePublication();
                    break;
                case 3:
                    checkOutPub();
                    break;
                case 4:
                    returnPub();
                    break;
            }
        }
        while (userInputMenu);

        cout << "-------------------------------------------" << endl;
        cout << "Thanks for using Seneca Library Application" << endl;
    }
}