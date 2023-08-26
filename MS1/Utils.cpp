/***********************************************************************
// OOP244 Utils Module:
// File  utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
using namespace std;
#include "Utils.h"

namespace sdds {
    void clearInputBuffer(void)
    {   
        while (getchar() != '\n')
        {
            ; // do nothing!
        }
    }

    int inputIntRange(int lowerBound, int upperBound)
    {
        int userInput = -1;
        bool valid;

        do
        {
            valid = true;
            cin >> userInput;

            if (userInput > upperBound || userInput < lowerBound || !cin)
            {
                valid = 0;
                cout << "Invalid Selection, try again: ";
                cin.clear();
                clearInputBuffer();
            }

        } while (!valid);

        return userInput;
    }
}