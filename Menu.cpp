/***********************************************************************
// Final Project Milestone 3
// OOP244 Menu Module
// File	Menu.cpp
// Version 1.0
// Date 2021-11-16
// Author 
// Description
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//Hyunjeong Choi   2021.11.18	   Updated menu() using static
//									Utils::isValidInt()
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	void MenuItem::setEmpty() {
		m_content = nullptr;
	}
	bool MenuItem::isEmpty()const {
		return m_content == nullptr;
	}
	MenuItem::MenuItem() {
		setEmpty();
	}
	MenuItem::MenuItem(const char* title) {
		if (title) {
			m_content = new char[strlen(title) + 1];
			strcpy(m_content, title);
		}
		else {
			setEmpty();
		}
	}
	MenuItem::~MenuItem() {
		delete[] m_content;
		m_content = nullptr;

	}
	MenuItem::operator bool() {
		return !isEmpty();
	}
	MenuItem::operator const char* () {
		return m_content;
	}
	ostream& MenuItem::display(ostream& ostr) const {
		if (!isEmpty()) {
			ostr << m_content;
		}
		return ostr;
	}
	void Menu::setEmpty() {
		m_title[0] = 0;
		m_arrayOfMenuItem[0] = nullptr;
		m_numOfItems = 0;
	}
	bool Menu::isEmpty() {
		return m_title == nullptr;
	}
	Menu::Menu() {
		setEmpty();
	}
	Menu::Menu(const char* title) {
		if (m_title) {
			strcpy(m_title, title);
		}
		else {
			setEmpty();
		}
	}
	Menu::~Menu() {
		for (int i = 0; i < m_numOfItems; i++) {
			delete m_arrayOfMenuItem[i];
			m_arrayOfMenuItem[i] = nullptr;
		}
	}
	std::ostream& Menu::display(std::ostream& ostr) const {
		if (m_title) {
			ostr << m_title;
		}
		return ostr;
	}
	std::ostream& Menu::fullDisplay(std::ostream& ostr) const{
		if (m_title[0]) {
			ostr << m_title << endl;
		}
		for (int i = 0; i < m_numOfItems; i++) {
			ostr.width(2);
			ostr << i + 1 << "- " << m_arrayOfMenuItem[i]->m_content << endl;
		}
		ostr << " 0- Exit" << endl;
		ostr << "> ";
		return ostr;
	}
	unsigned int Menu::run() {
		int a;
		fullDisplay();
		return Utils::isValidInt(a);
	}
	unsigned int Menu::operator~() const {
		int a;
		fullDisplay();
		return Utils::isValidInt(a);
	}
	Menu& Menu::operator<<(const char* menuitemContent) {
		if (m_numOfItems < MAX_MENU_ITEMS) {
			m_arrayOfMenuItem[m_numOfItems] = new MenuItem(menuitemContent);
			m_numOfItems++;
		}
		return *this;
	}
	Menu::operator int() {
		return m_numOfItems;
	}
	Menu::operator unsigned int() {
		return m_numOfItems;
	}
	Menu::operator bool() {
		return m_numOfItems >= 1;
	}
	const char* Menu::operator[](int index) const {
		return *m_arrayOfMenuItem[index % m_numOfItems];
	}
	std::ostream& operator<<(std::ostream& ostr, const Menu& Ro) {
		return Ro.display(ostr);
	}
}