#pragma once
#include<iostream>
#include<string>
#include<fstream>

#define MAX_DVD_RECORDS 100
#define SYSTEM_PASSWORD "root_password"

using namespace std;

struct DVDRecord
{
	string author, title, year;
	double price;
};

class DVDInventorySystem
{
	public:
		static unsigned int listSize;
		DVDRecord dvdRecords[MAX_DVD_RECORDS];

		DVDInventorySystem();

		void login();
		void menu(); // main menu for the entire system
		void loadDVDFromFile(); // load DVDs from file if they exist
		void saveDVDToFile(); // save DVDs to file

		void addDVD();
		void removeDVD();

		void search(); // a generic search function to act as a menu for the below mentioned search functions.
		void searchByTitle();
		void searchByAuthor();
		void searchByYear();
		void searchByPrice();

		void displayDVD();

};