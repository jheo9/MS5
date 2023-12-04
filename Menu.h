/***********************************************************************
// Final project Milestone 51
//
// File: main51.cpp
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name: JaehyukHeo            Date: 2023-12-01            Reason
***********************************************************************/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H


#include "Utils.h"

namespace sdds {
	class Menu {
		char* m_menu_content;
		int m_option_count;

		void print_menu() const;
		int count_tabs(const char* menu_string);
	public:
		Menu(const char* menu_string);
		~Menu();

		Menu(const Menu& other) = delete;
		Menu& operator=(const Menu& other) = delete;

		unsigned int run() const;
	};
}

#endif 