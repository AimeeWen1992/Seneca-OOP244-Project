///////////////////////////////////////////////////
// Milestone 2  : LibApp.cpp
// Student Name: Rong-Yuan, Wen
// Student ID  : 114556228
// Email       : rwen1@myseneca.ca
// Section     : NGG
///////////////////////////////////////////////////
#include<iostream>
#include "LibApp.h"
using namespace std;

namespace sdds {
	bool LibApp::confirm(const char* message)
	{
		Menu menu(message);
		menu << "Yes";
		return (menu.run() == 1) ? true : false;
	}

	void LibApp::load()
	{
		cout << "Loading Data" << endl;
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
	}

	void LibApp::search()
	{
		cout << "Searching for publication" << endl;
	}

	void LibApp::returnPub()
	{
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl;
		m_changed = true;
	}
	
	void LibApp::newPublication()
	{
		cout << "Adding new publication to library" << endl;
		if (confirm("Add this publication to library?")) {
			m_changed = true;
			cout << "Publication added" << endl;
		};
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		search();
		if (confirm("Remove this publication from the library?")) {
			m_changed = true;
			cout << "Publication removed" << endl;
		}

	}

	void LibApp::checkOutPub()
	{
		search();
		if (confirm("Check out publication?")) {
			m_changed = true;
			cout << "Publication checked out" << endl;
		}
	}

//Public------------------------------------------------------------------------------------

	LibApp::LibApp() : m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_changed = false;
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		load();
	}

	void LibApp::run()
	{
		int menuSelect, exitSelect;
		do
		{
			menuSelect = m_mainMenu.run();
			switch (menuSelect)
			{
			case 0:
				if (m_changed == true) {
					exitSelect = m_exitMenu.run();

					if (exitSelect == 0)
					{
						if (confirm("This will discard all the changes are you sure?")) {
							m_changed = false;
						}
					}
					else if (exitSelect == 1)
					{
						save();
					}
					else if (exitSelect == 2)
					{
						menuSelect = 1;
					}
				}
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
			cout << endl;
		} while (menuSelect);

		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
	}
}
