/***********************************************************************
// Final Project Milestone 5
// OOP244 Utils Module
// File	Utils.h
// Version 1.0
// Date	2021-12-02
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
#ifndef SDDS_UTILS_H__
#define SDDS_UTILS_H__
#include <iostream>
#include <cstring>
#include "Publication.h"
namespace sdds {
	class Utils {
	public:
		static int isValidInt(int& num);
		static void alloCopy(char*& des, const char* src);
	};
}
#endif // SDDS_UTILS_H_

