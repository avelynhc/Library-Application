/***********************************************************************
// Final Project Milestone 5
// OOP244 Menu Module
// File	Menu.h
// Version 1.0
// Date 2021-11-
// Author 
// Description
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
#include <iostream>
namespace sdds {
	const int MAX_MENU_ITEMS = 20;
	class Menu;
	class MenuItem {
		char* m_content{};
		void setEmpty();
		bool isEmpty()const;
		MenuItem();
		MenuItem(const char* title);
		~MenuItem();// destructor
		MenuItem(const MenuItem& menuitem) = delete;// copy constructor
		MenuItem& operator=(const MenuItem& menuitem) = delete;// assignment constructor
		operator bool();
		operator const char* ();
		std::ostream& display(std::ostream& ostr = std::cout)const;
		friend class Menu;
	};
	class Menu {
		char m_title[100];
		MenuItem* m_arrayOfMenuItem[MAX_MENU_ITEMS]{};
		int m_numOfItems{};
		void setEmpty();
		bool isEmpty();
	public:
		Menu();
		Menu(const char* title);
		~Menu();
		std::ostream& display(std::ostream& ostr = std::cout)const;
		std::ostream& fullDisplay(std::ostream& ostr = std::cout)const;
		unsigned int run();
		unsigned int operator~()const;
		Menu& operator<<(const char* menuitemContent);
		operator int();
		operator unsigned int();
		operator bool();
		const char* operator[](int index)const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Menu& Ro);
}
#endif // !SDDS_MENU_H_

