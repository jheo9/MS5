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
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Menu.h"

namespace sdds
{
	Menu::Menu(const char* menu_string)
	{
		if (menu_string == nullptr || count_tabs(menu_string) > 14) 
		{
			m_menu_content = nullptr;
			m_option_count = 0;
		}
		else
		{
			m_menu_content = new char[strlen(menu_string) + 1];
			strcpy(m_menu_content, menu_string);
			m_option_count = count_tabs(menu_string) + 1;
		}
	}

	Menu::~Menu()
	{
		delete[] m_menu_content;
	}

	void Menu::print_menu() const
	{
		const char* current = m_menu_content;
		int i = 1;

		while (*current != '\0') 
		{
			const char* start = current;
			while (*current != '\t' && *current != '\0') 
			{
				++current;
			}

			cout << i++ << "- ";
			while (start < current) 
			{
				cout << *start++;
			}
			cout << endl;

			if (*current == '\t')
			{
				++current;
			}
		}
		cout << "0- Exit" << endl;
		cout << "> ";
		//cout << "---------------------------------" << endl;
		//cout << "0- Exit\n> ";
	}


	int Menu::count_tabs(const char* menu_string) 
	{
		int count = 0;

		while (*menu_string)
		{
			if (*menu_string == '\t')
				count++;
			menu_string++;
		}

		return count;
	}

	unsigned int Menu::run() const
	{
		
		if (m_menu_content == nullptr) 
		{ // I want this to be in the private function section but whatever
			cout << "Invalid Menu!\n";
			return 0;

		}

		
		print_menu();

		return ut.get_int(0, m_option_count);
	}
}