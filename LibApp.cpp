/***********************************************************************
// Final Project Milestone 5
// OOP244 LibApp Module
// File	LibApp.cpp
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
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Menu.h"
#include "Book.h"
using namespace std;
namespace sdds {
	bool LibApp::confirm(const char* message) {
		Menu M(message);
		M << "Yes";
		return M.run();
	}
	void LibApp::load() {
		cout << "Loading Data" << endl;
		ifstream infile("LibRecs.txt");
		char type{};
		for (int i = 0; infile; i++) {
			infile >> type;
			infile.ignore();
			if (infile) {
				if (type == 'P')
					m_publicPointerArray[i] = new Publication;
				else if (type == 'B')
					m_publicPointerArray[i] = new Book;
				if (m_publicPointerArray[i]) {
					infile >> *m_publicPointerArray[i];
					m_NumOfLoadedPublic++;
					m_lastLibRefNum = m_publicPointerArray[i]->getRef();
				}
			}
		}
	}
	void LibApp::save() {
		cout << "Saving Data" << endl;
		cout << endl;
		ofstream fileout("LibRecs.txt", ios::trunc);
		for (int i = 0; i < m_NumOfLoadedPublic; i++) {
			if (fileout && m_publicPointerArray[i]) {
				if (m_publicPointerArray[i]->getRef()) { // when reference number is not zero, save it
					fileout << *m_publicPointerArray[i] << endl;
				}
			}
		}
		fileout.close();
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;
		for (int i = 0; i < m_NumOfLoadedPublic; i++) {
			if (m_publicPointerArray[i] && m_publicPointerArray[i]->getRef()) {
				m_publicPointerArray[i]->write(cout, true) << endl;
			}
		}
	}
	int LibApp::search(int userInput, bool onLoan, bool showAll) {
		char title[256];
		int ref = 0;
		cout << "Publication Title: ";
		cin.getline(title, 256);
		PublicationSelector ps("Select one of the following found matches:");
		for (int i = 0; i < m_NumOfLoadedPublic; i++) {
			// when book 
			if (m_publicPointerArray[i] && userInput == 1 && strstr(*m_publicPointerArray[i], title) && m_publicPointerArray[i]->type() == 'B') {
				if (showAll) { // when user select showAll
					ps << m_publicPointerArray[i];
				}
				else if (onLoan) { // show onLoan only
					if (m_publicPointerArray[i]->onLoan()) {
						ps << m_publicPointerArray[i];
					}
				}
				else if (!onLoan) { // show notOnLoan only
					if (!m_publicPointerArray[i]->onLoan()) {
						ps << m_publicPointerArray[i];
					}
				}
			}
			// when publication
			else if (m_publicPointerArray[i] && userInput == 2 && strstr(*m_publicPointerArray[i], title) && m_publicPointerArray[i]->type() == 'P') {
				if (showAll) { // when user select showAll
					ps << m_publicPointerArray[i];
				}
				else if (onLoan) { // show onLoan only
					if (m_publicPointerArray[i]->onLoan()) {
						ps << m_publicPointerArray[i];
					}
				}
				else if (!onLoan) { // show notOnLoan only
					if (!m_publicPointerArray[i]->onLoan()) {
						ps << m_publicPointerArray[i];
					}
				}
			}
		}
		if (ps) {
			ps.sort();
			int ref = ps.run();
			if (ref) {
				for (int i = 0; i < m_NumOfLoadedPublic && m_publicPointerArray[i]; i++) {
					if (ref == m_publicPointerArray[i]->getRef()) {
						cout << *m_publicPointerArray[i] << endl;
						i = m_NumOfLoadedPublic;
						return ref;
					}
				}
			}
			else {
				cout << "Aborted!" << endl;
			}
		}
		else {
			cout << "No matches found!" << endl;
		}
		return ref;
	}
	void LibApp::returnPub() {
		PublicationSelector ps;
		Date D1(2021, 12, 10);
		cout << "Return publication to the library" << endl;
		int userInput = m_pubTypeMenu.run();
		int selectedRef = search(userInput, true);
		if (selectedRef && userInput && confirm("Return Publication?")) {
			for (int i = 0; i < m_NumOfLoadedPublic && m_publicPointerArray[i]; i++) {
				if (selectedRef == m_publicPointerArray[i]->getRef()) {
					int dayPassed = D1 - m_publicPointerArray[i]->checkoutDate();
					int overDue = dayPassed - SDDS_MAX_LOAN_DAYS;
					if (dayPassed > SDDS_MAX_LOAN_DAYS) {
						double penalty = overDue * 0.50;
						cout << "Please pay $";
						cout.setf(ios::fixed);
						cout.precision(2);
						cout << penalty;
						cout << " penalty for being " << overDue << " days late!" << endl;
					}
					m_publicPointerArray[i]->set(0);// set membership num of publication to 0
					m_changed = true;
				}
			}
			cout << "Publication returned" << endl;
		}
	}
	void LibApp::newPublication() {
		if (m_NumOfLoadedPublic == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
		}
		else {
			Publication* P{};
			cout << "Adding new publication to the library" << endl;
			int userInput = m_pubTypeMenu.run();
			if (userInput == 1) {// when user's choice = Book
				P = new Book;
				P->read(cin);
				if (!cin) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Aborted!" << endl;
				}
				else {
					if (confirm("Add this publication to the library?")) {
						if (P) {
							P->setRef(++m_lastLibRefNum);
							m_publicPointerArray[m_NumOfLoadedPublic++] = P;
							m_changed = true;
							cout << "Publication added" << endl;
						}
						else {
							cout << "Failed to add publication!" << endl;
							for (int i = 0; P[i]; i++) {
								delete P[i];
							}
						}
					}
					else {
						cout << "Aborted!" << endl;
					}
				}
			}
			else if (userInput == 2) {// when user's choice = Publication
				P = new Publication;
				P->read(cin);
				if (!cin) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Aborted!" << endl;
				}
				else {
					if (confirm("Add this publication to the library?")) {
						if (P) {
							//set the library reference number to the value
							P->setRef(++m_lastLibRefNum);
							m_publicPointerArray[m_NumOfLoadedPublic++] = P;
							m_changed = true;
							cout << "Publication added" << endl;
						}
						else {
							cout << "Failed to add publication!" << endl;
							for (int i = 0; P[i]; i++) {
								delete P[i];
							}
						}
					}
					else {
						cout << "Aborted!" << endl;
					}
				}
			}
			else if (userInput == 0) {
				cout << "Aborted!" << endl;
			}
		}
	}
	void LibApp::removePublication() {
		cout << "Removing publication from the library" << endl;
		int userInput = m_pubTypeMenu.run();
		int seletecdRef = search(userInput, true, true); // search all publication
		if (seletecdRef) {
			if (confirm("Remove this publication from the library?")) {
				//Set the library reference of the selected publication to 0 (zero) -- deleting it
				getPub(seletecdRef)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
	}
	void LibApp::checkOutPub() {
		int membershipNum;
		cout << "Checkout publication from the library" << endl;
		int userInput = m_pubTypeMenu.run();
		int seletecdRef = search(userInput, false);
		if (seletecdRef) {
			if (userInput && confirm("Check out publication?")) {
				bool flag = false;
				cout << "Enter Membership number: ";
				cin >> membershipNum;
				flag = membershipNum > 99999;
				while (flag) {
					cout << "Invalid membership number, try again: ";
					cin >> membershipNum;
					flag = membershipNum > 99999;
				}
				getPub(seletecdRef)->set(membershipNum);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
	}
	void LibApp::run() {
		bool res = false;
		do {
			int choice = m_mainMenu.run();
			if (choice == 0) {
				if (!m_changed) {
					res = true;
					cout << endl;
				}
				else {
					int option = m_exitMenu.run();
					if (option == 0) {
						if (confirm("This will discard all the changes are you sure?")) {
							res = true;
							cout << endl;
							cout << "-------------------------------------------" << endl;
							cout << "Thanks for using Seneca Library Application" << endl;
							ifstream file("LibRecs.txt");
							if (file.is_open()) {
								cout << file.rdbuf();
							}
						}
					}
					else if (option == 1) {
						save();
						res = true;
					}
					else {
						cout << endl;
					}
				}
			}
			else if (choice == 1) {
				newPublication();
				cout << endl;
			}
			else if (choice == 2) {
				removePublication();
				cout << endl;
			}
			else if (choice == 3) {
				checkOutPub();
				cout << endl;
			}
			else if (choice == 4) {
				returnPub();
				cout << endl;
			}
		} while (!res);
	}
	Publication* LibApp::getPub(int libRef) {
		for (int i = 0; i < m_NumOfLoadedPublic; i++) {
			if (m_publicPointerArray[i]->getRef() == libRef) {
				return m_publicPointerArray[i];
			}
		}
		return NULL;
	}
	LibApp::LibApp(const char* filename, bool changed, Menu mainMenu, Menu pubTypeMenu, Menu exitMenu) : m_changed(changed), m_mainMenu(mainMenu), m_pubTypeMenu(pubTypeMenu), m_exitMenu(exitMenu) {
		if (filename) {
			strcpy(m_fileName, filename);
		}
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_pubTypeMenu << "Book" << "Publication";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		load();
	}
	LibApp::~LibApp() {
		for (int i = 0; i < SDDS_LIBRARY_CAPACITY; i++) {
			delete m_publicPointerArray[i];
		}
	}
}