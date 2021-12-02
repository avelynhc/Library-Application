/***********************************************************************
// Final Project Milestone 5
// OOP244 LibApp Module
// File	LibApp.h
// Version 1.0
// Date	2021-11-
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
#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
namespace sdds {
    class LibApp{
        bool m_changed{};
        Menu m_mainMenu{};
        Menu m_exitMenu{};

        char m_fileName[256]{};
        Publication* m_publicPointerArray[SDDS_LIBRARY_CAPACITY]{};//PPA
        int m_NumOfLoadedPublic{};//NOLP
        int m_lastLibRefNum{};//LLRN
        Menu m_pubTypeMenu{};
        bool confirm(const char* message);
        void load();
        void save();
        int search(int userInput, bool onLoan, bool showAll = false);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();
    public:
        LibApp(bool changed = false, Menu mainMenu = "Seneca Libray Application", Menu pubTypeMenu = "Choose the type of publication:", Menu exitMenu = "Changes have been made to the data, what would you like to do?");
        void run();
        Publication* getPub(int libRef);
        LibApp(const char* filename, bool changed = false, Menu mainMenu = "Seneca Libray Application", Menu pubTypeMenu = "Choose the type of publication:", Menu exitMenu = "Changes have been made to the data, what would you like to do?");
    };
}
#endif // !SDDS_LIBAPP_H




