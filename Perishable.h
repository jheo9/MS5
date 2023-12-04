/***********************************************************************
// Final project Milestone 4
// Module: Perishable Test
// File: main.cpp
// Version 1.1
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
// jaehyuk Heo         23-11-25
***********************************************************************/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include <iostream>

#include "Date.h"
#include "Item.h"

using namespace std;

namespace sdds
{
	class Perishable : public Item 
	{
		Date m_expiry_date;
		const char* m_handling_instructions = nullptr;  
	public:
		Perishable();
		Perishable(const Perishable& other);

		const Date& expiry();

		Perishable& operator=(const Perishable& other);
		operator bool() const override;  

		~Perishable() override;

		int readSku(std::istream& istr) override; 

		std::ofstream& save(std::ofstream& ofstr) const override;
		std::ostream& display(std::ostream& ostr) const override;
		std::ifstream& load(std::ifstream& ifstr) override;
		std::istream& read(std::istream& istr) override;

	};
	std::ostream& operator<<(std::ostream& ostr, const Perishable& perishable_item);
	std::istream& operator>>(std::istream& istr, Perishable& perishable_item);
}

#endif //SDDS_PERISHABLE_H