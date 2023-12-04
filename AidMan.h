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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include <cstring>
#include <iostream>
#include "Menu.h"
#include "iProduct.h"
#include "Date.h"
#include "Item.h"
#include "Utils.h"

const int sdds_max_num_items = 100;

using namespace std; 

namespace sdds
{
	class AidMan //: public iProduct 
	{
	private:
		char* m_file;
		Menu Menu_Obj;
		iProduct* products[sdds_max_num_items];
		int numProducts;
		Date m_date;


		unsigned int menu() const;
	public:
		//Admin();
		AidMan(const char* file = nullptr);
		AidMan(const AidMan& other) = delete;
		AidMan& operator=(const AidMan& other) = delete;
		//AidMan(const char* file);
		~AidMan();
		void run();
		void save() const;
		bool load(const char* File);
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void add();
		void add_count();
		void itemdel();
		void remove(int index);

		operator bool() const;
		void deallocate();
		//void addProduct(iProduct* product);

	};
}
#endif // !SDDS_AIDMAN_H 