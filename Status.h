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
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <ostream>

using namespace std;

namespace sdds
{
	class Status 
	{
		char* m_description = nullptr;
		int m_code = 0;
	public:
		Status(const char* description = nullptr, int code = 0);
		Status(const Status& other);
		~Status();

		Status& operator=(const Status& other);
		Status& operator=(const char* description);
		Status& operator=(int status);

		Status& clear();

		operator int() const;

		operator const char* () const;
		
		operator bool() const;
		

		friend std::ostream& operator<<(std::ostream& os, const Status& status);
	};
}

#endif 