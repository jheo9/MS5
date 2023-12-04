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
#include "iProduct.h"

namespace sdds {
	std::istream& operator>>(std::istream& istr, iProduct& p)
	{
		return p.read(istr);
	}
	std::ostream& operator<<(std::ostream& ostr, iProduct& p) 
	{
		return p.display(ostr);
	}
}