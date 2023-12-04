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
#include "AidMan.h"
#include "Perishable.h"
#include <iostream>
#include<string.h> 
#include <chrono>
#include<fstream>
#include<limits>
#include <ctime>
#include <iomanip>

using namespace std; 

namespace sdds
{

	int AidMan::search(int sku) const
	{
		for (int i = 0; i < numProducts; i++)
		{
			if (products[i]->operator==(sku))
			{
				return i; 
			}
		}
		return -1;
	}

	void AidMan::add() //: Menu_Obj("1- Perishable\n2- Non-Perishable\n-----------------\n")     
	{
		if (products[numProducts - 1] != nullptr)
		{
			products[numProducts - 1]->read(cin);
		}

		save();

		itemdel();
		
	}
	void AidMan::remove(int index)
	{
		iProduct* temp = products[index];

		for (int i = index; i < numProducts - 1; i++)
		{  
			products[i] = products[i+1];
		}

		delete temp;
		numProducts--;
		save();

	}

	void AidMan::itemdel()
	{
		for (int i = 0; i < numProducts; i++)
		{
			delete products[i];  
			products[i] = nullptr;
		}

		numProducts = 0;
	}
	unsigned int AidMan::menu() const 
	{


		cout << "Aid Management System" << endl; 
		cout << "Date: " << m_date<< endl;


		cout << "Data file: " << ((m_file) ? m_file : "No file");
		cout << endl << "---------------------------------" << endl;


		return Menu_Obj.run();
	}

	AidMan::AidMan(const char* file) : Menu_Obj("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database\n---------------------------------")
	{
		if (file != nullptr) 
		{
			m_file = new char[strlen(file) + 1];
			strcpy(m_file, file);
		}
		else 
		{
			m_file = nullptr;
		}
	}

	void AidMan::run()
	{
		ifstream ifstr;
		int n;

		do
		{
			n = menu();

			if (n != 0 && !m_file && n != 7) 
			{
				//cout << "Database not loaded! Redirecting to Open Database menu..." << endl;
				n = 7;

			}
			switch (n)
			{
			case 1:
				if (!m_file)
				{
					//cout << "****New/Open Aid Database****" << endl;
					n = 7;
					
				}
				else
				{
					cout << endl << "****List Items****" << endl;
					list("list");
					break;
				}
			case 2:
				cout << endl << "****Add Item****" << endl;

				if (numProducts > sdds_max_num_items)
				{
					cout << "Database full!";
				}
				else
				{
					int choice = 0;
					int item_count = 0;
					Menu tempMenu("Perishable\tNon-Perishable\n-----------------");
					choice = tempMenu.run();

					if (choice == 0)
					{
						cout << "Aborted\n";
						return;
					}
					if (choice == 1)
					{

						products[numProducts] = new Perishable();
						item_count = products[numProducts]->readSku(cin);
						save();
					}
					else if (choice == 2)
					{

						products[numProducts] = new Item();
						
						item_count = products[numProducts]->readSku(cin);
						save();
					}

					if (search(item_count) != -1)
					{
						cout << "Sku: " << item_count << " is already in the system, try updating quantity instead.\n\n";
						//delete products[numProducts];


					}
					else
					{

						numProducts++;


						add();
						

						load("data.dat");
						save();

						cout << "\n";

					}

				}
				break;
			case 3:

				cout << endl << "****Remove Item****" << endl;
				cout << "Item description: ";
				char str[10];
				cin.ignore();
				cin.getline(str, '\n');

				list(str);

				if (true) 
				{
					int choice = 0;
					int sku;
					cout << "Enter SKU: ";
					cin >> sku;
					int i = search(sku);
					cout << "Following item will be removed: "; //<< endl;
					//cout << std::setw(10) << setfill(' ') << "";

					products[i]->linear(false);
					cout << *products[i] << endl;

					cout << "Are you sure" << endl;
					Menu tempMe("Yes!");
					choice = tempMe.run();

					if (choice == 1)
					{
						remove(i);
						cout << "Item removed!\n\n";
					}
				}
				break;
			case 4:
				cout << endl << "****Update Quantity****" << endl << endl;

				cout << "Item description: ";
				char strst[10];
				cin.ignore();
				cin.getline(strst, '\n');

				list(strst);

				if (true)
				{
					int cho = 0;
					int sku2;
					cout << "Enter SKU: ";
					cin >> sku2;
					int i = search(sku2);

					Menu tempMeu("Add\tReduce");
					cho = tempMeu.run();

					if (cho == 1) {
						int quantityToAdd = ut.get_int(1, sdds_max_num_items - products[i]->qty(), "Quantity to add: ", "Invalid quantity, retry: ");
						products[i]->operator+=(quantityToAdd);
						cout << quantityToAdd << " items added!\n";
					}
					else if (cho == 2) {
						int quantityToReduce = ut.get_int(1, products[i]->qty(), "Quantity to Reduce: ", "Invalid quantity, retry: ");
						if (quantityToReduce == products[i]->qty()) {
							remove(i);
							cout << quantityToReduce << " items removed!\n";
						}
						else {
							products[i]->operator-=(quantityToReduce);
							cout << quantityToReduce << " items removed!\n";
						}
					}
					else {
						cout << "Aborted!\n";
					}
				}

				break;
			case 5:
				cout << endl << "****Sort****" << endl << endl;
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl << endl;
				break;
			case 7:
				cout << endl << "****New/Open Aid Database****" << endl;

				m_file = new char[50];

				cout << "Enter file name: ";

				cin.ignore(1000, '\n');

				cin.getline(m_file, 50, '\n');

				load("data.dat");

				cout << numProducts << " records loaded!\n\n";
				break;
			case 0:
				cout << "Exiting Program!" << endl;
				break;
			}


		} while (n != 0);
	}

	void AidMan::save() const
	{
		if (m_file)
		{
			std::ofstream outfile(m_file);


			if (outfile.is_open())
			{

				for (int i = 0; i < numProducts; ++i)
				{

					products[i]->save(outfile);
					outfile << '\n';
				}

				outfile.close();
			}
		}

	}
	void AidMan::deallocate()
	{

		for (size_t i = numProducts; i > 0;)
		{
			--i;
			delete products[i];
			products[i] = nullptr;
		}
		numProducts = 0;
	}

	bool AidMan::load(const char* File)
	{
		if (File)
		{
			delete[] m_file;
			m_file = nullptr;
		}

		if (File != nullptr && File[0] != '\0') {
			m_file = new char[strlen(File) + 1];
			strcpy(m_file, File);
		}

		std::ifstream ifstr(m_file);
		if (!ifstr.is_open()) {
			// 파일 열기 실패 처리
			// ...
			return false;
		}

		//deallocate();
		numProducts = 0;

		while (numProducts < sdds_max_num_items && ifstr.peek() != EOF) {
			char type = ifstr.peek(); 
			if (type >= '1' && type <= '3')
			{
				products[numProducts] = new Perishable();
			}
			else if (type >= '4' && type <= '9') 
			{
				products[numProducts] = new Item();
			}
			else 
			{
				ifstr.clear();
				ifstr.ignore(1000, '\n');
				continue;
			}

			if (products[numProducts]->load(ifstr))
			{
				numProducts++;
			}
			else
			{
				delete products[numProducts]; 
			}
		}

		ifstr.close();

		// 파일 로드 후 메시지 출력
		//cout << "Enter file name: " << m_file << endl;
		//cout << numProducts << " records loaded!\n" << endl;
		save();
		if (numProducts > 0)
		{
			return true;

		}
		return false;
	}

	int AidMan::list(const char* sub_desc)
	{
			if (numProducts < 1)
			{
				cout << "The list is emtpy!\n";
			}
			else
			{
				cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

				for (int i = 0; i < numProducts; i++) 
					{
						if (strstr(sub_desc, "list") || *products[i] == sub_desc)
						{
							cout.fill(' ');
							cout.setf(ios::right);
							cout.width(4);
							cout << i + 1 << " ";
							cout << "| ";
							products[i]->linear(true);
							cout << *products[i];
							cout << endl;
						}
					}

				cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

				if (strstr(sub_desc, "list"))
				{
					char choice;
					cout << "Enter row number to display details or <ENTER> to continue:\n";
					cout << "> "; //<< endl;
					cout << endl;
					cin.ignore();
					choice = getchar();

					if (isdigit(choice))
					{
						int op = (choice - '0') - 1;

						products[op]->linear(false);
						cout << *products[op] << endl;
					}

					//cout << "\n";

				}
				// else 
				// {
				//     int sku;
				//     cout << "Enter SKU:\n";
				//     cout << "> ";
				//     cin>>sku;
				//     cout<<"\n";      
				// }

			}

			return numProducts;

		}
	

		/*do
		{
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;
			cout << "> ";
			cin.ignore();
			if (cin.peek() == '\n')
			{

				cout << "\n";
				break;
			}
			cin >> number;
			if (number >= 1 && number <= rowNum)
			{
				products[number - 1]->linear(false);
				products[number - 1]->display(cout);
				cout << '\n' << '\n';


			}
			else
			{
				cout << "Invalid input. Please enter a valid row number." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cin.get(); // Consume the newline character

		} while (!validInput);


		return rowNum; 
	}*/
	
	
	/*void AidMan::addProduct(iProduct* product)
	{
		if (numProducts < sdds_max_num_items)
		{
			products[numProducts] = product; 
			numProducts++; 
		}
	}*/

	AidMan::operator bool() const  
	{ 
		return m_file && numProducts;
	}


	

	/*AidMan::AidMan(const char* filename) : File(nullptr)
	{
		if (filename) {

			File = new char[std::strlen(filename) + 1];
			std::strcpy(File, filename);
		}
		else {
			File = nullptr;
		}
		// Menu_Obj 멤버 변수 초기화
		Menu_Obj.setMenu("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n", 7);
	}*/

	AidMan::~AidMan()
	{
		delete[] m_file;
		m_file = nullptr;
		deallocate();
	}
	
	}        