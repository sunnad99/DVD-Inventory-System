#include "DVD_Inventory_System.h"

unsigned int DVDInventorySystem::listSize = 0;

DVDInventorySystem::DVDInventorySystem()
{

}

void DVDInventorySystem::loadDVDFromFile()
{
	string fileName("DVDs.csv");
	ifstream inFile;
	
	inFile.open(fileName);

	if (inFile.is_open())
	{
		DVDRecord tempRecord;
		string title, year, author;
		double price;

		while (inFile)
		{
			getline(inFile, title, ',');
			getline(inFile, year, ',');
			getline(inFile, author, ',');
			inFile >> price;
			inFile >> ws;

			if (!inFile)
			{
				break;
			}

			tempRecord.title = title;
			tempRecord.year = year;
			tempRecord.author = author;
			tempRecord.price = price;
			
			dvdRecords[listSize] = tempRecord;
			listSize += 1;
		}

		inFile.close();
	}


}

void DVDInventorySystem::saveDVDToFile()
{
	string fileName("DVDs.csv");
	ofstream outFile;
	DVDRecord tempRecord;
	
	outFile.open(fileName);

	if (outFile.is_open())
	{

		for (unsigned int i = 0; i < listSize; i++)
		{
			tempRecord = dvdRecords[i];
			outFile << tempRecord.title << "," << tempRecord.year << "," << tempRecord.author << "," << tempRecord.price << endl;
		}

		outFile.close();

	}

	else
	{
		cout << "Could not save the current DVDs to the inventory, exiting..." << endl;
	}
}

void DVDInventorySystem::login()
{

	cout << "--------------------------- Welcome to the DVD Inventory System. ---------------------------" << endl << endl;
	string password;

	cout << "---------------------------------------- LOGIN MENU ----------------------------------------" << endl << endl;

	cout << "Password: ";
	cin >> password;
	cout << endl;

	if (password == SYSTEM_PASSWORD)
	{
		cout << "Successfully logged in to the system!!!" << endl;
		menu();
	}
	else
	{
		cout << "Incorrect Password, exiting..." << endl;
	}

}

void DVDInventorySystem::menu()
{
	loadDVDFromFile();

	bool isRunning = true;
	int option;
	while (isRunning)
	{
		cout << endl << "--------------------------------------------- MAIN MENU -----------------------------------------------------" << endl << endl;

		cout << "Please choose one of the following options." << endl;

		cout << "1. Add a DVD" << endl;
		cout << "2. Remove a DVD" << endl;
		cout << "3. Search for a DVD" << endl;
		cout << "4. Display all DVDs" << endl;
		cout << "Any other number: Exit program" << endl;
	
		cout << "Enter a number: ";
		cin >> option;
		cin.ignore();

		switch (option)
		{
			case 1:
				addDVD();
				break;
			case 2:
				removeDVD();
				break;
			case 3:
				search();
				break;
			case 4:
				displayDVD();
				break;
			default:
				cout << "No options from the ones shown above were given, exiting..." << endl;
				saveDVDToFile();
				isRunning = false;
				break;
		}
	}
}

void DVDInventorySystem::addDVD()
{
	DVDRecord tempRecord;

	cout << "Enter the title of the DVD: ";
	getline(cin,tempRecord.title);

	cout << "Enter the author of the DVD: ";
	getline(cin, tempRecord.author);

	cout << "Enter the year when the DVD was released: ";
	getline(cin, tempRecord.year);

	cout << "Enter the price of the DVD: ";
	cin >> tempRecord.price;
	cin.ignore();

	dvdRecords[listSize] = tempRecord;
	listSize += 1;
}

void DVDInventorySystem::removeDVD()
{
	if (listSize == 0)
	{
		cout << "Currently, there are no DVDs that exist within our inventory!" << endl;
	}

	else
	{
		unsigned int dvdToRemove;
		cout << "Which DVD do you want to remove?" << endl << endl;
		
		for (unsigned int i = 0; i < listSize; i++)
		{
			cout << i + 1 << ". " << dvdRecords[i].title << endl;
		}

		cout << "Enter a number: ";
		cin >> dvdToRemove;
		cin.ignore();

		if (dvdToRemove < listSize)
		{

			for (unsigned int j = dvdToRemove; j < listSize; j++)
			{
				dvdRecords[j - 1] = dvdRecords[j];
			}
		}
		
		listSize -= 1;
		cout << "DVD has been removed successfully!" << endl;
	}
}

void DVDInventorySystem::displayDVD()
{
	if (listSize == 0)
	{
		cout << "Currently, there are no DVDs that exist within our inventory!" << endl;
	}

	else
	{
		cout << "--------------------------------------------- Current Inventory ---------------------------------------------" << endl << endl;

		DVDRecord tempRecord;
		for (unsigned int i = 0; i < listSize; i++)
		{
			tempRecord = dvdRecords[i];
			cout << i + 1 << "." << " Name: " << tempRecord.title << " --" <<" Author: " << tempRecord.author << " --" <<  " Year of Release: " << tempRecord.year << " --" << " Price of DVD: " << tempRecord.price << endl << endl;
		}
	}
}

void DVDInventorySystem::searchByTitle()
{
	string DVDTitle;
	DVDRecord tempRecord;
	cout << "--------------------------------------------- SEARCH BY TITLE ---------------------------------------------" << endl << endl;

	cout << "Enter the title of the DVD you wish to search: ";
	getline(cin, DVDTitle);

	cout << endl << "Showing DVDs by title..." << endl << endl;
	for (unsigned int i = 0; i < listSize; i++)
	{
		tempRecord = dvdRecords[i];

		if (tempRecord.title == DVDTitle)
		{
			cout << i + 1 << "." << " Name: " << tempRecord.title << " --" << " Author: " << tempRecord.author << " --" << " Year of Release: " << tempRecord.year << " --" << " Price of DVD: " << tempRecord.price << endl;
		}
	}

}

void DVDInventorySystem::searchByAuthor()
{
	string DVDAuthor;
	DVDRecord tempRecord;
	cout << "--------------------------------------------- SEARCH BY AUTHOR ---------------------------------------------" << endl << endl;

	cout << "Enter the author of the DVD you wish to search: ";
	getline(cin, DVDAuthor);
	

	cout << endl << "Showing all DVDs by author..." << endl << endl;
	for (unsigned int i = 0; i < listSize; i++)
	{
		tempRecord = dvdRecords[i];

		if (tempRecord.author == DVDAuthor)
		{
			cout << i + 1 << "." << " Name: " << tempRecord.title << " --" << " Author: " << tempRecord.author << " --" << " Year of Release: " << tempRecord.year << " --" << " Price of DVD: " << tempRecord.price << endl;
		}
	}
}

void DVDInventorySystem::searchByYear()
{
	string DVDYear;
	DVDRecord tempRecord;
	cout << "--------------------------------------------- SEARCH BY YEAR ---------------------------------------------" << endl << endl;

	cout << "Enter the year of the DVD you wish to search: ";
	getline(cin, DVDYear);
	

	cout << endl << "Showing all DVDs by year..." << endl << endl;
	for (unsigned int i = 0; i < listSize; i++)
	{
		tempRecord = dvdRecords[i];

		if (tempRecord.year == DVDYear)
		{
			cout << i + 1 << "." << " Name: " << tempRecord.title << " --" << " Author: " << tempRecord.author << " --" << " Year of Release: " << tempRecord.year << " --" << " Price of DVD: " << tempRecord.price << endl;
		}
	}
}

void DVDInventorySystem::searchByPrice()
{
	double DVDPrice;
	DVDRecord tempRecord;
	cout << "--------------------------------------------- SEARCH BY PRICE ---------------------------------------------" << endl << endl;

	cout << "Enter maximum cost of DVD: ";
	cin >> DVDPrice;


	cout << endl << "Showing all DVDs that at most have the cost of " << DVDPrice <<endl << endl;
	for (unsigned int i = 0; i < listSize; i++)
	{
		tempRecord = dvdRecords[i];

		if (tempRecord.price <= DVDPrice)
		{
			cout << i + 1 << "." << " Name: " << tempRecord.title << " --" << " Author: " << tempRecord.author << " --" << " Year of Release: " << tempRecord.year << " --" << " Price of DVD: " << tempRecord.price << endl;
		}
	}
}

void DVDInventorySystem::search()
{
	if (listSize == 0)
	{
		cout << "Currently, there are no DVDs that exist within our inventory!" << endl;
	}

	else
	{
		int searchSelection;
		cout << "--------------------------------------------- SEARCH MENU -------------------------------------------------" << endl << endl;

		cout << "Select which way you want to search by." << endl;
		cout << "1. Search by Title" << endl;
		cout << "2. Search by Author" << endl;
		cout << "3. Search by Year" << endl;
		cout << "4. Search by Price" << endl;

		cout << "Enter a number: ";
		cin >> searchSelection;
		cin.ignore();

		switch (searchSelection)
		{
		case 1:
			searchByTitle();
			break;
		case 2:
			searchByAuthor();
			break;
		case 3:
			searchByYear();
			break;
		case 4:
			searchByPrice();
			break;
		default:
			cout << "Option doesn't exist...please try again!" << endl;
			break;
		}
	}
}
