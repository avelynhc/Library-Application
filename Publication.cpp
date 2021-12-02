/***********************************************************************
// Final Project Milestone 5
// OOP244 Pulication Module
// File	Publication.cpp
// Version 1.0
// Date 2021-11-23
// Author 
// Description
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
// Revision History
// ----------------------------------------------------------------------------
// Name            Date            Reason
//Hyunjeong Choi   2021-11-23      change write() so it can cover long title
///////////////////////////////////////////////////////////////////////////////
******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Publication.h"
#include "Date.h"
#include <cstring>
#include <string>
using namespace std;
namespace sdds {
	Publication::Publication() {
		// set attributes to default values
	}
	Publication::Publication(const Publication& p) {
		strcpy(m_shelfId, p.m_shelfId);
		m_membership = p.m_membership;
		m_date = p.m_date;
		m_libRef = p.m_libRef;
		if (p) {
			Utils::alloCopy(m_title, p.m_title);
		}
	}
	Publication& Publication::operator=(const Publication& p) {
		if (this != &p) {
			if (p) {
				Utils::alloCopy(m_title, p.m_title);
				strcpy(m_shelfId, p.m_shelfId);
				m_membership = p.m_membership;
				m_date = p.m_date;
				m_libRef = p.m_libRef;
			}
		}
		return *this;
	}
	Publication::~Publication() {
		delete[] m_title;
	}
	void Publication::set(int member_id) {
		if (member_id >= 0) {
			m_membership = member_id;
		}
	}
	void Publication::setRef(int value) {
		if (value>=0) {
			m_libRef = value;
		}
	}
	void Publication::resetDate() {
		m_date.setToToday();
	}
	char Publication::type() const {
		return 'P';
	}
	bool Publication::onLoan() const {
		return m_membership != 0;
	}
	Date Publication::checkoutDate()const {
		return m_date;
	}
	bool Publication::operator==(const char* title)const {
		return strstr(m_title, title);
	}
	Publication::operator const char* ()const {
		return m_title;
	}
	int Publication::getRef()const {
		return m_libRef;
	}
	bool sdds::Publication::conIO(ios& io) const {
		return &io == &cin || &io == &cout;
	}
	std::ostream& Publication::write(std::ostream& ostr, bool showFileFormat) const {
		if (conIO(ostr) && !showFileFormat) {
			ostr << "| " << m_shelfId << " | ";
			ostr.setf(ios::left);
			if (strlen(m_title) > SDDS_TITLE_WIDTH) {
				for (int i = 0; i < SDDS_TITLE_WIDTH; i++) {
					ostr << m_title[i];
				}
				ostr << " | ";
			}
			else {
				ostr.width(SDDS_TITLE_WIDTH);
				ostr.fill('.');
				ostr << m_title << " | ";
				ostr.fill(' ');
			}
			ostr.width(SDDS_MEMBERSHIP_NUMBER_DIGIT);
			if (m_membership == 0) {
				ostr << " N/A " << " | " << m_date << " |";
			}
			else {
				ostr << m_membership << " | " << m_date << " |";
			}
			ostr.unsetf(ios::left);
		}
		else {
			ostr << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
		}
		//ostr << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
		return ostr;
	}
	std::istream& Publication::read(std::istream& istr) {
		m_title = nullptr;
		m_shelfId[0] = 0;
		m_membership = 0;
		m_libRef = 0;

		char title[255];
		char shelfId[SDDS_SHELF_ID_LEN + 1];
		int membership = 0;
		int libRef = 0;
		Date date{};
		if (conIO(istr)) {
			cout << "Shelf No: ";
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1);
			if (!cin) {
				istr.setstate(ios::failbit);
			}
			cout << "Title: ";
			istr.getline(title, 255);
			cout << "Date: ";
			istr >> date;
		}
		else {
			istr >> libRef;
			istr.ignore(100, '\t');
			istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
			istr.getline(title, 255, '\t');
			istr >> membership;
			istr.ignore(100, '\t');
			istr >> date;
		}
		if (!date) {
			istr.setstate(ios::failbit);
		}
		if (istr) {
			Utils::alloCopy(m_title, title);
			strcpy(m_shelfId, shelfId);
			m_membership = membership;
			m_date = date;
			m_libRef = libRef;
		}
		return istr;
	}
	Publication::operator bool() const {
		return m_title && m_title[0] && m_shelfId && m_shelfId[0];
	}
}