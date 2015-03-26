
/*
Warehouse Inventory Management System

Cody Carlson 3/11/15 5:30pm - Created the basic main menu structure.


*/

//Includes go here:
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include<istream>
#include<fstream>
#include<sstream>


using namespace std;

struct CatalogItem{
	string ID;
	string itemName;
	string itemSize;
	string itemPrice;
	string itemDesc;
};

void loadCatalog(){
	vector<CatalogItem> Catalog;
	CatalogItem A;
	ifstream cat;
	string sLine;
	cat.open("Catalog.txt");
	getline(cat,sLine);
	//for (unsigned i = 0; i < sLine.length(); i=i+1) {
    cout << sLine.substr(0, 1) << endl;
//}
	getline(cat,sLine);

	while (sLine.length()>11)
	{
		A.ID = sLine.substr(0, 10);
		cout<<A.ID<<endl;
		A.itemName = sLine.substr(10,30);
		cout<<A.itemName<<endl;
		A.itemSize = sLine.substr(40,1);
		cout<<A.itemSize<<endl;
		A.itemPrice = sLine.substr(41,8);
		cout<<A.itemPrice<<endl;
		A.itemDesc = sLine.substr(49);//.substr(45);
		cout<<A.itemDesc<<endl;
		system("pause");
		Catalog.push_back(A);
		getline(cat,sLine);
	}

	for(int x=0;x<Catalog.size();x++)
	{
		cout<<Catalog[x].ID<<endl;
		cout<<Catalog[x].itemName<<endl;
		cout<<Catalog[x].itemPrice<<endl;
		cout<<Catalog[x].itemSize<<endl;
		cout<<Catalog[x].itemDesc<<endl;
	}


}


class Item{
	string iD;
	string iName;
	int iQuantity;
	double iCost;
	char iSize;



};


//Prototypes of functions go here:
void displayMainMenu();
void logOut();
void availableSpaceRemaining();
void inventoryValue();
void searchHistoryLog();
void searchWarehouse();
void searchItem();
void editCatalog();
void addUser();


bool login(){
    string username, password;
	string User[] = {"ADMIN", };
	string Pass[] = {"ADMIN", };

cout<<"Username:"<<endl;
cin>>username;
cout<<"Password:"<<endl;
cin>>password;
int arrayLength = end(User) - begin(User);

for(int x=0; x<arrayLength;x++){
if(User[x]==username)
{
    if(Pass[x]==password)
    {
     return true;
    }
    else return false;
    }
return false;
}
return 0;
}

void programStartUp(){
	bool L=login();
	while(L!=true)
    {
        cout<<"Incorrect Username or Password.\nPlease try again.\n";
        L=login();
    }
}

//Main goes here:
int main () {
    cout << "Welcome to the Gold Star's Warehouse Inventory Management System!" << endl << endl;//Main start up message
	programStartUp();
	loadCatalog();
	cout<<"here";

	//Initialize Catalog
	//Initialize Warehouse
	//Order Processing
	//Shipment Processing


	displayMainMenu();// call the main menu function

	return 0;
}


//Program functions go here:
void displayMainMenu() {//main menu willdisplay to the user which options they have to choose from
	int menuResponse;

	cout << "\nYou are in the Main Menu, select an option to continue:" << endl;//notify user they are in the main menu.

	//Display the menu options
	cout << "0. Save and Log out" <<endl;
	cout << "1. Available Space Remaining" <<endl;
	cout << "2. Inventory Value" <<endl;
	cout << "3. Search History Log" <<endl;
	cout << "4. Search Warehouse" <<endl;
	cout << "5. Search Item" <<endl;
	cout << "6. Edit Catalog" <<endl;
	cout << "7. Add User" <<endl<<endl;

	//if the user enters a character value it will continously loop without this While loop
	while(!(cin>>menuResponse)){//so this clears the current input value and ignores the character value. It will display an error message and enables us to return to the main menu and enter in another value.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error: Invalid input, please try again."<<endl<<endl;
		displayMainMenu();
	}

	//if the input is actally one of the inputs then do that functionality
		if (menuResponse == 0){
			logOut();
		}

		else if (menuResponse == 1){
			availableSpaceRemaining();
		}

		else if (menuResponse == 2){
			inventoryValue();
		}

		else if (menuResponse == 3){
			searchHistoryLog();
		}
		else if (menuResponse == 4){
			searchWarehouse();
		}
		else if (menuResponse == 5){
			searchItem();
		}
		else if (menuResponse == 6){
			editCatalog();
		}
		else if (menuResponse == 7){
			addUser();
		}
		else//Any other number input will be invalid.
			cout<<"Error: Invalid input, please try again."<<endl<<endl;
			displayMainMenu();

}

void logOut(){//(BASE FUNCTIONALITY)if the user decides to log out, it will save the current warehouse inventory and catalog to the file then close the program
	cout << "TEST: Save everything to the files functions go here, then close the program."<<endl<<endl;
	exit(0);//exit point of the program
}

void availableSpaceRemaining(){//(EXTRA FUNCTIONALITY:CODY) displays the remaining location in the designated warehouse


	cout << "TEST: Available Space Remaining functions go here."<<endl<<endl;
	displayMainMenu();
}

void inventoryValue(){//(EXTRA FUNCTIONALITY:FERIQUE) displays the total value of all the items in the warehouses


	cout << "TEST: Inventory Value functions go here."<<endl<<endl;
	displayMainMenu();
}

void searchHistoryLog(){//(EXTRA FUNCTIONALITY:ZACH) Search the History log for all transactions of the item ID


	cout << "TEST: Search History Log functions go here."<<endl<<endl;
	displayMainMenu();
}

void searchWarehouse(){//(BASE FUNCTIONALITY) Search a warehouse for an item. Can decide to change the quantity of the item in that location


	cout << "TEST: Search Warehouse functions go here."<<endl<<endl;
	displayMainMenu();
}

void searchItem(){//(BASE FUNCTIONALITY) Search the catalog based on the item ID and display its contents. Can edit the values of the item. Editing values will change the values in the warehouse.


	cout << "TEST: Search Item functions go here."<<endl<<endl;
	displayMainMenu();
}

void editCatalog(){//(EXTRA FUNCTIONALITY: GROUP) Able to Add or Delete an item from the catalog.


	cout << "TEST: Search Warehouse functions go here."<<endl<<endl;
	displayMainMenu();
}

void addUser(){// (EXTRA FUNCTIONALITY: ANNA) To add a new user they must contact the Gold Stars.


	cout << "\nTo add a new user, contact Gold Stars."<<endl;
	displayMainMenu();
}
