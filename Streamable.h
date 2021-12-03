/***********************************************************************
// Final Project Milestone 5
// OOP244 Streamable Module
// File	Streamable.h
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
#ifndef SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_
#include <iostream>
namespace sdds {
	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& ostr, bool showFileFormat = false)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual bool conIO(std::ios& io)const = 0;
		virtual operator bool()const = 0;
		virtual ~Streamable() {
		}
	};
	std::ostream& operator<<(std::ostream& ostr, const Streamable& st);
	std::istream& operator>>(std::istream& istr, Streamable& st);
}
#endif // !SDDS_STREAMABLE_H_
