///////////////////////////////////////////////////
// Milestone 2  : LibApp.h
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
namespace sdds {
   class LibApp {
       
       bool m_changed;
       Menu m_mainMenu;
       Menu m_exitMenu;
       bool confirm(const char* message);

       //Simple private fuctions
       void load(); 
       void save();
       void search(); 
       void returnPub();

       //Methods with confirmation
       void newPublication();
       void removePublication();
       void checkOutPub();
       
   public:
       LibApp();
       void run();
   };
}
#endif // !SDDS_LIBAPP_H



