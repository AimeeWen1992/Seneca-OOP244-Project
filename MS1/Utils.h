/***********************************************************************
// OOP244 Utils Module
// File  utils.h
// Version
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>

namespace sdds {
    // Discard all remaining char's from the standard input buffer:
    void clearInputBuffer(void);
    int inputIntRange(int lowerBound, int upperBound);
}

#endif