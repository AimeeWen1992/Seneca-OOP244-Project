///////////////////////////////////////////////////
// Milestone 2  : Utils.h
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>

namespace sdds {
    // Discard all remaining char's from the standard input buffer:
    void clearInputBuffer(void);
    int inputIntRange(int lowerBound, int upperBound);
}

#endif