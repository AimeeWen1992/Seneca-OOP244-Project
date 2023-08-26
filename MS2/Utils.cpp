///////////////////////////////////////////////////
// Milestone 2  : Utils.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
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