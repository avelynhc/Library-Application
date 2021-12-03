/***********************************************************************
// Final Project Milestone 5
// OOP244 Book Module
// File	Book.cpp
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
#include "Book.h"
using namespace std;
namespace sdds {
	Book::Book() {
	}
	Book::Book(const Book& B) : Publication(B) {
		operator=(B);
		//Utils::alloCopy(m_authorName, B.m_authorName);
	}
	Book& Book::operator=(const Book& B) {
		Publication::operator=(B);
		if (this != &B) {
			if (B.m_authorName) {
				Utils::alloCopy(m_authorName, B.m_authorName);
			}
		}
		return *this;
	}
	Book::~Book() {
		delete[] m_authorName;
	}
	char Book::type() const {
		return 'B';
	}
	std::ostream& Book::write(std::ostream& ostr, bool showFileFormat) const {
		Publication::write(ostr, showFileFormat);
		if (conIO(ostr) && !showFileFormat) {
			ostr << " ";
			ostr.setf(ios::left);
			if (strlen(m_authorName) > SDDS_AUTHOR_WIDTH) {
				for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
					ostr << m_authorName[i];
				}
				ostr << " |";
			}
			else {
				ostr.width(SDDS_AUTHOR_WIDTH);
				ostr << m_authorName << " |";
			}
			ostr.unsetf(ios::left);
		}
		else {
			ostr << "\t" << m_authorName;
		}
		return ostr;
	}
	std::istream& Book::read(std::istream& istr) {
		Publication::read(istr);
		m_authorName = nullptr;
		char authorName[256];
		istr.setf(ios::left);
		istr.ignore();
		if (conIO(istr)) {
			cout << "Author: ";
			istr.getline(authorName, 256);
		}
		else {
			istr.get(authorName, 256);
		}
		istr.unsetf(ios::left);
		if (istr) {
			Utils::alloCopy(m_authorName, authorName);
		}
		return istr;
	}
	void Book::set(int member_id) {
		Publication::set(member_id);
		resetDate();
	}
	Book::operator bool() const {
		bool res = false;
		if (Publication::operator bool() && m_authorName && m_authorName[0]) {
			res = true;
		}
		return res;
	}
}
