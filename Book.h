/***********************************************************************
// Final Project Milestone 5
// OOP244 Book Module
// File	Book.h
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
#ifndef SDDS_BOOK_H_
#define SDDS_BOOK_H_
#include <iostream>
#include "Publication.h"
#include "Utils.h"
namespace sdds {
	class Book : public Publication {
		char* m_authorName{};
	public:
		Book();
		Book(const Book& B);
		Book& operator=(const Book& B);
		~Book();

		virtual char type()const;
		std::ostream& write(std::ostream& ostr, bool showFileFormat = false)const;
		std::istream& read(std::istream& istr);
		virtual void set(int member_id);
		operator bool()const;
	};
}
#endif // !SDDS_BOOK_H_
