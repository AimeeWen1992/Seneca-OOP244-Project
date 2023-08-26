///////////////////////////////////////////////////
// Milestone 2  : Menu.h
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#include <iostream>

namespace sdds {
    const unsigned int  MAX_MENU_ITEMS = 20;

    class MenuItem {
    private:
        char* menuContent;

        MenuItem();
        MenuItem(const char* textContent);
        ~MenuItem();

        // Sets a MenuItem object to safe empty
        void setEmpty();

        // Return true, if it is not empty and it should return false if it is empty
        operator bool() const;

        // Should return the address of the content Cstring.
        operator const char* () const;

        // Display the content of the MenuItem on ostream
        std::ostream& display(std::ostream& os = std::cout);

        //Copy constructorand Copy assignment are deleted
        MenuItem(const MenuItem& menuItem) = delete;
        void operator=(const MenuItem& MI) = delete;

        friend class Menu;
    };

    class Menu : public MenuItem {
    private:
        MenuItem menuTitle{};
        MenuItem* menuItems[MAX_MENU_ITEMS]{};
        unsigned int pointerCount = 0;

    public:
        Menu();
        Menu(const char* title);
        ~Menu();

        // Function to display the title of the menu
        std::ostream& displayMenuTitle(std::ostream& os);

        // Display the content of Menu on ostream
        std::ostream& displayMenu(std::ostream& os = std::cout);

        // Return the number of MenuItems on the Menu.
        operator int();

        // Return the number of MenuItems on the Menu.
        operator unsigned int();

        // Return true if the Menu has one or more MenuItems otherwise, false;
        operator bool();

        // Displays the Menu and gets the user selection.
        int run();

        // Overload operator~ to do exactly what the run function does (two different ways to run the menu)
        int operator~();

        // Overload a member insertion operator (operator<<) to add a MenuItem to the Menu.
        Menu& operator<<(const char* menuitemContent);

        // If the index passes the number of MenuItems in the Menu, loop back to the beginning.
        const char* operator[](unsigned int index) const;

        //Copy constructorand Copy assignment are deleted
        Menu(const Menu& M) = delete;
        void operator=(const Menu& M) = delete;

    };
    // Overloading the insertion operator
    std::ostream& operator<<(std::ostream& os, Menu& menu);
}

#endif