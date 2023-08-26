///////////////////////////////////////////////////
// Milestone 2  : Menu.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace sdds {
    // MenuItem Class
    MenuItem::MenuItem() {
        setEmpty();
    }

    MenuItem::MenuItem(const char* textContent) {
        if (textContent && textContent[0]) {
            menuContent = new char[strlen(textContent) + 1];
            strcpy(menuContent, textContent);
        }
        else {
            setEmpty();
        }
    }

    MenuItem::~MenuItem() {
        delete[] menuContent;
    }

    void MenuItem::setEmpty() {
        menuContent = nullptr;
    }

    MenuItem::operator bool() const {
        return (menuContent != nullptr && menuContent[0] != '\0');
    };

    MenuItem::operator const char* () const {
        return menuContent;
    }

    std::ostream& MenuItem::display(std::ostream& os) {
        if (*this) {
            os << menuContent;
        }
        return os;
    }

    // Menu Class

    Menu::Menu() {
        pointerCount = 0;
    };

    Menu::Menu(const char* title) : menuTitle(title) {};

    Menu::~Menu() {
        unsigned int i;
        for (i = 0; i < MAX_MENU_ITEMS; i++)
        {
            delete menuItems[i];
        }
    };

    std::ostream& Menu::displayMenuTitle(std::ostream& os) {
        if (menuTitle) {
            menuTitle.display();
        }

        return os;
    }

    std::ostream& Menu::displayMenu(std::ostream& os) {
        if (menuTitle)
        {
            menuTitle.display();
            os << endl;
        }

        unsigned int i;
        for (i = 0; i < pointerCount; i++)
        {

            os << setw(2) << right << i + 1 << "- ";
            menuItems[i]->display(os) << endl;
        }
        os << " 0- Exit" << endl;
        os << "> ";
        return os;
    }

    Menu::operator int() {
        return pointerCount;
    }

    Menu::operator unsigned int() {
        return pointerCount;
    }

    Menu::operator bool() {
        return (pointerCount > 0);
    }

    std::ostream& operator<<(std::ostream& os, Menu& menu) {
        return (menu.displayMenuTitle(os));
    }

    int Menu::run() {
        displayMenu();
        int userInput = inputIntRange(0, pointerCount);
        return userInput;
    }


    int Menu::operator~() {
        return run();
    }

    Menu& Menu::operator<<(const char* menuitemContent) {
        if (pointerCount < MAX_MENU_ITEMS)
        {
            MenuItem* newMenuItem = new MenuItem(menuitemContent);
            menuItems[pointerCount] = newMenuItem;
            pointerCount++;
        }

        return *this;
    }

    const char* Menu::operator[](unsigned int index) const {
        if (index > pointerCount)
        {
            return menuItems[index %= pointerCount]->menuContent;
        }
        else
        {
            return menuItems[index]->menuContent;
        }
    }
};