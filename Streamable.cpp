/***********************************************************************
// Final Project Milestone 5
// OOP244 Streamable Module
// File	Streamable.cpp
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
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include "Streamable.h"
using namespace std;
namespace sdds {
	std::ostream& operator<<(std::ostream& ostr, const Streamable& st) {
		if (st) {
			st.write(ostr);
		}
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, Streamable& st) {
		st.read(istr);
		return istr;
	}
}