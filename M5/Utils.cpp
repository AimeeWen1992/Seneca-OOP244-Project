///////////////////////////////////////////////////
// Milestone 5 : Utils.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#include <iostream>
using namespace std;
#include "Utils.h"

namespace sdds {
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
                valid = false;
                cout << "Invalid Selection, try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

        } while (!valid);

        return userInput;
    }
    int inputIntRange(int lowerBound, int upperBound, const char* warning)
    {
        int userInput = -1;
        bool valid;
        do
        {
            valid = true;
            cin >> userInput;
            if (userInput > upperBound || userInput < lowerBound || !cin)
            {
                valid = false;
                cout << warning;
                cin.clear();
                cin.ignore(1000, '\n');
            }

        } while (!valid);
        return userInput;
    }
}