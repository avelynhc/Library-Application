/***********************************************************************
// Final Project Milestone 5
// OOP244 Pulication Module
// File	Publication.h
// Version 1.0
// Date 2021-11-23
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
#ifndef SDDS_PUBLICATION_H_
#define SDDS_PUBLICATION_H_
#include <iostream>
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"
#include "Utils.h"
namespace sdds {
	class Publication : public Streamable {
		char* m_title{};
		char m_shelfId[SDDS_SHELF_ID_LEN + 1]{};
		int m_membership = 0; // hold a 5 digit membership number
		int m_libRef = -1;
		Date m_date{};
	public:
		Publication();
		// rule of three
		Publication(const Publication& p);
		Publication& operator=(const Publication& p);
		virtual ~Publication();

		virtual void set(int member_id);
		void setRef(int value);
		void resetDate();
		virtual char type()const;
		bool onLoan()const;
		Date checkoutDate()const;
		bool operator==(const char* title)const;
		operator const char* ()const;
		int getRef()const;

		// Streamable pure virtual function implementations
		bool conIO(std::ios& io)const;
		virtual std::ostream& write(std::ostream& ostr, bool showFileFormat = false)const;
		virtual std::istream& read(std::istream& istr);
		virtual operator bool()const;
	};
}
#endif // !SDDS_PUBLICATION_H_
