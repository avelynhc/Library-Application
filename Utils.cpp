/***********************************************************************
// Final Project Milestone 5
// OOP244 Utils Module
// File	Utils.cpp
// Version 1.0
// Date 2021-12-02
// Author 
// Description
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//Hyunjeong Choi   2021.11.16      added alloCopy function
//Hyunjeong Choi   2021.11.18      updated isValidInt() using static
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
using namespace std;
namespace sdds {
	int Utils::isValidInt(int& num) {
		bool ok = false;
		char newline = 'x';
		do {
			ok = true;
			cin >> num;
			newline = cin.get();
			if (!cin || newline != '\n') {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "Invalid Selection, try again: ";
				ok = false;
			}
			else {
				ok = true;
			}
		} while (!ok);
		return num;
	}
	void Utils::alloCopy(char*& des, const char* src) {
		delete[] des;
		des = new char[strlen(src) + 1];
		strcpy(des, src);
	}
}