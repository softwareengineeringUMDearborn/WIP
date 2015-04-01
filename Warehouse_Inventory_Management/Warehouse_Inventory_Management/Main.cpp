/*
Warehouse Inventory Management System

Cody Carlson 3/11/15 5:30pm - Created the basic main menu structure.
			 3/27/15 3:30pm - Edited the main menu based on use case changes.
			 3/31/15 6:30pm - Added Anna's Basis to the main.
			 4/1/15  3:30pm - Added parameters to main menu and worked on item inventory display and update. Made warehouse vector sizes 20/60/20 (See main, Starts at Warehouse1[0].resize(20);)
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

struct ItemsOrdered{
string ItemID;
string Warehouse;
string Count;//Quantity Ordered
};

struct ItemsShipped{
string ItemID;
string Warehouse;
string Count;//Quantity Ordered less than 9
};

//left off here
struct Orders{
	vector<ItemsOrdered> ItemsOrderedVector;
	string CustomerType;
	string Cusomer_OR_EntityName;
	string CustomerStreetAddress;
	string CustomerCity;
	string CustomerState_OR_Province;
	string CustomerPostalCode;
	string CustomerCountry;
	string OrderDate;
	string OrderItemCount;//must be less than 7
	string CustomerID;
	string CustomerOrderID;
	string CustomerPaymentType;
	string CustomerDiscount;
};

struct Shipments{
	string VendorName;
	string VendorShippingDate;
	string ItemCount;
	vector <ItemsShipped> ItemsShippedVector;
};

vector<Shipments> loadShipments()
{
	//vector<Orders> StoredDailyOrders;
	Shipments A;
	ItemsShipped B;
	vector<Shipments> StoredDailyShipments;
	ifstream cat;
	string sLine;
	cat.open("Vendor.txt");
	//getting the header

	cout<<"here";

	getline(cat,sLine);
	//for (unsigned i = 0; i < sLine.length(); i=i+1) {
    cout << sLine.substr(0, 1) << endl;
//}
	getline(cat,sLine);

	while (sLine.length()!=4)
	{
		//get vendor name, shipping date and item count
		A.VendorName= sLine.substr(0, 50);
		cout<<A.VendorName<<endl;
		A.VendorShippingDate = sLine.substr(50,10);
		cout<<A.VendorShippingDate<<endl;
		A.ItemCount= sLine.substr(60,1);
		cout<<A.ItemCount<<endl;
		
		//read in items ordered
		for(int x=0;x!= atoi(A.ItemCount.c_str()); x++){

		getline(cat,sLine);
		B.ItemID = sLine.substr(0,10);
		cout<<B.ItemID<<endl;
		B.Warehouse = sLine.substr(11,1);
		cout<<B.Warehouse<<endl;
		B.Count = sLine.substr(13);
		cout<<B.Count<<endl;
		A.ItemsShippedVector.push_back(B);

		}


		//system("pause");
		StoredDailyShipments.push_back(A);
		getline(cat,sLine);
	}

	//check total number of items in trailer matches what was received
	if(sLine.substr(1,1)== to_string(StoredDailyShipments.size()))
	{
		cout<<"All "<<StoredDailyShipments.size()<<" customers were processed.";
	}else cout<<"There was an error with the Catalog File. The Trailer number does not match the number of customers in the file.\n";

	return StoredDailyShipments;
}


vector<Orders> loadOrders(){
	//vector<Orders> StoredDailyOrders;
	Orders A;
	ItemsOrdered B;
	vector<Orders> StoredDailyOrders;
	ifstream cat;
	string sLine;
	cat.open("Customer.txt");
	//getting the header

	cout<<"here";

	getline(cat,sLine);
	//for (unsigned i = 0; i < sLine.length(); i=i+1) {
    cout << sLine.substr(0, 1) << endl;
//}
	getline(cat,sLine);

	while (sLine.length()!=4)
	{
		//get customer type:b/p & name
		A.CustomerType= sLine.substr(0, 1);
		cout<<A.CustomerType<<endl;
		A.Cusomer_OR_EntityName = sLine.substr(1,60);
		cout<<A.Cusomer_OR_EntityName<<endl;
		
		//get address
		//getline(cat,sLine);
		A.CustomerStreetAddress = sLine.substr(61,30);
		cout<<A.CustomerStreetAddress<<endl;
		A.CustomerCity = sLine.substr(91,20);
		cout<<A.CustomerCity<<endl;
		//include comma in the space
		A.CustomerState_OR_Province = sLine.substr(112,20);//.substr(45);
		cout<<A.CustomerState_OR_Province<<endl;
		A.CustomerPostalCode = sLine.substr(132,10);
		cout<<A.CustomerPostalCode<<endl;
		A.CustomerCountry = sLine.substr(142,40);
		cout<<A.CustomerCountry<<endl;
		//getline(cat,sLine);
		A.OrderDate = sLine.substr(182,10);
		cout<<A.OrderDate<<endl;
		A.OrderItemCount = sLine.substr(192,1);
		cout<<A.OrderItemCount<<endl;
		
		//get Customer id payment discount
		getline(cat,sLine);
		A.CustomerID = sLine.substr(0,10);
		cout<<A.CustomerID<<endl;
		A.CustomerOrderID = sLine.substr(10,10);
		cout<<A.CustomerOrderID<<endl;
		A.CustomerPaymentType = sLine.substr(20,10);
		cout<<A.CustomerPaymentType<<endl;
		A.CustomerDiscount = sLine.substr(30,3);
		cout<<A.CustomerDiscount<<endl;
		//read in items ordered
		//IMPORTANT TO DISCUSS HOW TO LOOP THROUGH ITEMS
		for(int x=0;x!= atoi(A.OrderItemCount.c_str()); x++){

		getline(cat,sLine);
		B.ItemID = sLine.substr(0,10);
		cout<<B.ItemID<<endl;
		B.Warehouse = sLine.substr(11,1);
		cout<<B.Warehouse<<endl;
		B.Count = sLine.substr(13);
		cout<<B.Count<<endl;
		A.ItemsOrderedVector.push_back(B);

		}


		//system("pause");
		StoredDailyOrders.push_back(A);
		getline(cat,sLine);
	}

	//check total number of items in trailer matches what was received
	if(sLine.substr(1,1)== to_string(StoredDailyOrders.size()))
	{
		cout<<"All "<<StoredDailyOrders.size()<<" customers were processed.";
	}else cout<<"There was an error with the Catalog File. The Trailer number does not match the number of customers in the file.\n";

	return StoredDailyOrders;
}


vector<CatalogItem> loadCatalog(){
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
		A.itemDesc = sLine.substr(49,300);//.substr(45);
		cout<<A.itemDesc<<endl;
		//system("pause");
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
	//check total number of items in trailer matches what was received
	if(sLine.substr(1)== to_string(Catalog.size()))
	{
		cout<<"All "<<Catalog.size()<<" items were processed.";
	}else cout<<"There was an error with the Catalog File. The Trailer number does not match the number of items in the file.\n";

	return Catalog;
}

struct Warehouse{
	string ItemID;
	string quantity;
};


//class Item{
//	string iD;
//	string iName;
//	int iQuantity;
//	double iCost;
//	char iSize;
//};



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


void SetUpWarehouses(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3, string& OrdersFileSequenceNumber, string& ShipmentsFileSequenceNumber)
{
	vector<Warehouse> ColumnSmall;
	vector<Warehouse> ColumnMedium;
	vector<Warehouse> ColumnLarge;
	Warehouse A;
	ifstream cat;
	string sLine;
	cat.open("WarehouseStatus.txt");
	getline(cat,sLine);
	OrdersFileSequenceNumber= sLine.substr(27, 1);

	cout<<"A: "<<OrdersFileSequenceNumber<<endl;
	getline(cat,sLine);
	ShipmentsFileSequenceNumber= sLine.substr(29, 1);
	cout<<"B: "<<ShipmentsFileSequenceNumber<<endl;
	getline(cat,sLine);
	cout<<sLine<<endl;
	cout<<"here";
	while(sLine!="Warehouse 2:")
	{
		cout<<"Igot it";
		getline(cat,sLine);
		if(sLine.substr(0, 1)=="A")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnSmall.push_back(A);
		}else if(sLine.substr(0,1)=="B")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnMedium.push_back(A);
		}else if(sLine.substr(0,1)=="C")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnLarge.push_back(A);
		}
	
	}
	Warehouse1.push_back(ColumnSmall);
	Warehouse1.push_back(ColumnMedium);
	Warehouse1.push_back(ColumnLarge);
	//Warehouse1.push_back(ColumnMedium);
	//Warehouse1.push_back(ColumnSmall);
	ColumnLarge.clear();
	ColumnMedium.clear();
	ColumnSmall.clear();

	while(sLine!="Warehouse 3:")
	{
		cout<<"Hi";
		getline(cat,sLine);
		cout<<"star";
		if(sLine.substr(0, 1)=="A")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnSmall.push_back(A);
		}else if(sLine.substr(0,1)=="B")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnMedium.push_back(A);
		}else if(sLine.substr(0,1)=="C")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnLarge.push_back(A);
		}
	}
	Warehouse2.push_back(ColumnSmall);
	Warehouse2.push_back(ColumnMedium);
	Warehouse2.push_back(ColumnLarge);
	//Warehouse2.push_back(ColumnMedium);
	//Warehouse2.push_back(ColumnSmall);

	ColumnLarge.clear();
	ColumnMedium.clear();
	ColumnSmall.clear();

	getline(cat,sLine);
	cout<<sLine<<"after warehouse3";
	//system("pause");
	while(!cat.eof())
	{
		cout<<"hi";
		//getline(cat,sLine);
		if(sLine.substr(0, 1)=="A")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnSmall.push_back(A);
		}else if(sLine.substr(0,1)=="B")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnMedium.push_back(A);
		}else if(sLine.substr(0,1)=="C")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnLarge.push_back(A);
		}
		getline(cat,sLine);
	}
	Warehouse3.push_back(ColumnSmall);
	Warehouse3.push_back(ColumnMedium);
	Warehouse3.push_back(ColumnLarge);
	/*Warehouse3.push_back(ColumnMedium);
	Warehouse3.push_back(ColumnSmall);*/
	
	cout<<Warehouse1.at(0).size();
	cout<<Warehouse1.at(1).size();
	cout<<Warehouse1.at(2).size();
	cout<<endl;
	cout<<Warehouse2.at(0).size();
	cout<<Warehouse2.at(1).size();
	cout<<Warehouse2.at(2).size();
	cout<<endl;
	cout<<Warehouse3.at(0).size();
	cout<<Warehouse3.at(1).size();
	cout<<Warehouse3.at(2).size();

	cout<<"\nWas that 2?";


	return;
}

bool SearchCatalog(vector<CatalogItem>&Catalog, string ItemId, string& ItemSize){
	for(int x=0;x<Catalog.size();x++)
	{
		if(ItemId==Catalog[x].ID)
		{ //item valid
			ItemSize=Catalog[x].itemSize;
			return true;
		}
	}
	//item not valid
	return false;
}

void ProcessOrders(vector<CatalogItem>&Catalog, vector<Orders>& StoredDailyOrders,vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3)
{
	string ItemSize;
	for(int x=0;x<StoredDailyOrders.size();x++)
	{
		cout<<"hello";
		for(int y=0; y<StoredDailyOrders[x].ItemsOrderedVector.size();y++)
		{   
			cout<<"hihi\n";
			//Check Catalog for legal item ordered
			string ID=StoredDailyOrders[x].ItemsOrderedVector[y].ItemID;
			if(SearchCatalog(Catalog,ID, ItemSize)==false)
			{
				cout<<"This item is not found in the Catalog and hence is not available at any of the Warehouses."<<endl;
			}
			string WNum=StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse;
			cout<<"minnie\n";
			if(WNum=="1")
			{
				if(ItemSize=="A")
				{
					for(int k=0;k<Warehouse1.at(0).size();k++)
					{
						if(Warehouse1[0][k].ItemID==ID)
						{
							if(Warehouse1[0][k].quantity<StoredDailyOrders[x].ItemsOrderedVector[y].Count)
							{
								cout<<"Insufficient ammount of item number "<< Warehouse1[0][k].ItemID<<" on hand for the order.";
							}else{ int OnHand=atoi(Warehouse1[0][k].quantity.c_str());
									int AmmountOrdered= atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());
								int NewQuant = OnHand - atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());;
								Warehouse1[0][k].quantity=to_string(NewQuant);
							}
								if(Warehouse1[0][k].quantity == "0") Warehouse1[0].erase(Warehouse1[0].begin() +k);
						}
				
					}
				}if(ItemSize=="B")
				{
					for(int k=0;k<Warehouse1.at(1).size();k++)
					{
						if(Warehouse1[1][k].ItemID==ID)
						{
							if(Warehouse1[1][k].quantity<StoredDailyOrders[x].ItemsOrderedVector[y].Count)
							{
								cout<<"Insufficient ammount of item number "<< Warehouse1[1][k].ItemID<<" on hand for the order.";
							}else Warehouse1[1][k].quantity = atoi(Warehouse1[1][k].quantity.c_str()); - atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());

						}
					}
				}if(ItemSize=="C")
				{
					for(int k=0;k<Warehouse1.at(2).size();k++)
					{
						if(Warehouse1[2][k].ItemID==ID)
						{
							if(Warehouse1[2][k].quantity<StoredDailyOrders[x].ItemsOrderedVector[y].Count)
							{
								cout<<"Insufficient ammount of item number "<< Warehouse1[2][k].ItemID<<" on hand for the order.";
							}else Warehouse1[2][k].quantity = atoi(Warehouse1[2][k].quantity.c_str()); - atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());

						}
					}
				}

		}else return;
	}




}
	return;
}


//Prototypes of functions go here:
void displayMainMenu(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void logOut(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void availableSpaceRemaining(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void inventoryValue(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void searchHistoryLog(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void itemInformationDisplay(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);

void itemInventoryDisplay(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void itemInformationDisplay_WarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);

void showWarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void editItemCatalog(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void addUser(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);


//Main goes here:
int main () {
	vector<vector<Warehouse>> Warehouse1;
	vector<vector<Warehouse>> Warehouse2;
	vector<vector<Warehouse>> Warehouse3;
	string OrdersFileSequenceNumber, ShipmentsFileSequenceNumber;
	//A=small=0;B=medium=1;C=large=2;
    cout << "Welcome to the Gold Star's Warehouse Inventory Management System!" << endl << endl;//Main start up message
	programStartUp();
	vector<CatalogItem> Catalog = loadCatalog();
	
	vector<Orders> StoredDailyOrders = loadOrders();
	
	vector<Shipments> StoredDailyShipments = loadShipments();

	SetUpWarehouses(Warehouse1, Warehouse2, Warehouse3, OrdersFileSequenceNumber, ShipmentsFileSequenceNumber);
	cout<<"here";
	ProcessOrders(Catalog, StoredDailyOrders, Warehouse1, Warehouse2, Warehouse3);
	cout<<Warehouse1[0][0].ItemID<<"    here    +++"<<Warehouse1[0][0].quantity;
	cout<<"Back in Main\n";
	cout<<Warehouse1.at(0).size();
	cout<<Warehouse1.at(1).size();
	cout<<Warehouse1.at(2).size();
	cout<<endl;
	cout<<Warehouse2.at(0).size();
	cout<<Warehouse2.at(1).size();
	cout<<Warehouse2.at(2).size();
	cout<<endl;
	cout<<Warehouse3.at(0).size();
	cout<<Warehouse3.at(1).size();
	cout<<Warehouse3.at(2).size();

	Warehouse1[0].resize(20);
	Warehouse1[1].resize(60);
	Warehouse1[2].resize(20);

	Warehouse2[0].resize(20);
	Warehouse2[1].resize(60);
	Warehouse2[2].resize(20);

	Warehouse3[0].resize(20);
	Warehouse3[1].resize(60);
	Warehouse3[2].resize(20);
	
	cout<<endl<<endl;

	cout<<Warehouse1.at(0).size();
	cout<<Warehouse1.at(1).size();
	cout<<Warehouse1.at(2).size();
	cout<<endl;
	cout<<Warehouse2.at(0).size();
	cout<<Warehouse2.at(1).size();
	cout<<Warehouse2.at(2).size();
	cout<<endl;
	cout<<Warehouse3.at(0).size();
	cout<<Warehouse3.at(1).size();
	cout<<Warehouse3.at(2).size();

	cout<<"here"<<endl;

	//Initialize Catalog
	//Initialize Warehouse
	//Order Processing
	//Shipment Processing


	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);// call the main menu function

	return 0;
}


//Program functions go here:
void displayMainMenu(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3) {//main menu willdisplay to the user which options they have to choose from
	int menuResponse;

	cout << "\nYou are in the Main Menu, select an option to continue:" << endl;//notify user they are in the main menu.

	//Display the menu options
	cout << "0. Save and Log out" <<endl;
	cout << "1. Available Space Remaining" <<endl;
	cout << "2. Inventory Value" <<endl;
	cout << "3. Search History Log" <<endl;
	cout << "4. Item Information Display" <<endl;
	cout << "5. Item Inventory Display" <<endl;
	cout << "6. Show Warehouse Contents" <<endl;
	cout << "7. Edit Item Catalog" <<endl;
	cout << "8. Add User" <<endl<<endl;

	//if the user enters a character value it will continously loop without this While loop
	while(!(cin>>menuResponse)){//so this clears the current input value and ignores the character value. It will display an error message and enables us to return to the main menu and enter in another value.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error: Invalid input, please try again."<<endl<<endl;
		displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
	}

	//if the input is actally one of the inputs then do that functionality
		if (menuResponse == 0){
			logOut(Warehouse1,Warehouse2,Warehouse3);
		}

		else if (menuResponse == 1){
			availableSpaceRemaining(Warehouse1,Warehouse2,Warehouse3);
		}

		else if (menuResponse == 2){
			inventoryValue(Warehouse1,Warehouse2,Warehouse3);
		}

		else if (menuResponse == 3){
			searchHistoryLog(Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 4){
			itemInformationDisplay(Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 5){
			itemInventoryDisplay(Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 6){
			showWarehouseContents(Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 7){
			editItemCatalog(Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 8){
			cout << "\nTo add a new user, contact Gold Stars."<<endl;
		}
		else//Any other number input will be invalid.
			cout<<"Error: Invalid input, please try again."<<endl<<endl;
			displayMainMenu(Warehouse1,Warehouse2,Warehouse3);

}

void logOut(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY)if the user decides to log out, it will save the current warehouse inventory and catalog to the file then close the program
	cout << "TEST: Save everything to the files functions go here, then close the program."<<endl<<endl;
	exit(0);//exit point of the program
}

void availableSpaceRemaining(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(EXTRA FUNCTIONALITY:CODY) displays the remaining location in the designated warehouse


	cout << "TEST: Available Space Remaining functions go here."<<endl<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}

void inventoryValue(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(EXTRA FUNCTIONALITY:FERIQUE) displays the total value of all the items in the warehouses. 


	cout << "TEST: Inventory Value functions go here."<<endl<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}

void searchHistoryLog(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(EXTRA FUNCTIONALITY:ZACH) Search the History log for all transactions of the item ID


	cout << "TEST: Search History Log functions go here."<<endl<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}

void itemInformationDisplay(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY) The inventory analyst is able to update the item name, id, price, stock, and size type.


	cout << "TEST: Item Information display and update functions go here."<<endl<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}

void itemInventoryDisplay(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY) Retrieves current status of all 3 warehouses' inventory, and allows inventory analyst to override any location status and update inventory
	/*
	QUESTIONS: Should we be able to manually add an item to the warehouse?
	*/
	string quantityResponse;
	string warehouseResponse;
	string sizeResponse;
	int sizeConverter; //Takes the S,M,L that the user enters and converts it to the row of the matrix
	int locationResponse;

	itemInformationDisplay_WarehouseContents(Warehouse1, Warehouse2, Warehouse3);

	do{
	cout<< "Would you like to edit a quantity (y/n)? ";
	cin>> quantityResponse;

	if(quantityResponse == "y"){
		do{
		cout<< "What warehouse number is the item located in (1,2,3)?";
		cin>> warehouseResponse;
		}while(warehouseResponse != "1" && warehouseResponse != "2" &&warehouseResponse != "3");

		cout<<endl;
		do{
		cout<< "What size type is the item (S,M,L)?";
		cin>> sizeResponse;



		}while(sizeResponse!="S" && sizeResponse!="M" && sizeResponse!="L");
	
		if(sizeResponse == "S")
			sizeConverter = 0;
		else if(sizeResponse == "M")
			sizeConverter = 1;
		else if(sizeResponse == "L")
			sizeConverter = 2;
		else
			cout<<"issue converting size to warehouse"<<endl;


		cout<<endl;
		
		cout<< "What location is the item in?";
		cin>> locationResponse;
		
		
		if(warehouseResponse =="1"){
			cout<< locationResponse; 
			cout<<" || Item ID: " + Warehouse1[sizeConverter][locationResponse].ItemID + " || Item Quantity: " + Warehouse1[sizeConverter][locationResponse].quantity<<endl;
		}
		if(warehouseResponse =="2"){
			cout<< locationResponse; 
			cout<<" || Item ID: " + Warehouse2[sizeConverter][locationResponse].ItemID + " || Item Quantity: " + Warehouse2[sizeConverter][locationResponse].quantity<<endl;
		}
		if(warehouseResponse =="3"){
			cout<< locationResponse; 
			cout<<" || Item ID: " + Warehouse3[sizeConverter][locationResponse].ItemID + " || Item Quantity: " + Warehouse3[sizeConverter][locationResponse].quantity<<endl;
		}

		

	}

	else if(quantityResponse == "n"){
		cout<< "you chose NO. ";
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
	}
	}while(quantityResponse != "y" && quantityResponse != "n");
	
	//cout << "TEST: Item Inventory display and update functions go here."<<endl<<endl;
	
}

void itemInformationDisplay_WarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY) Retrieves current status of all 3 warehouses' inventory, and allows inventory analyst to override any location status and update inventory
	
	cout<<"\nWarehouse 1 Small:"<<endl;
	for(int i = 0; i<Warehouse1.at(0).size();i++){	
		if (Warehouse1[0][i].ItemID != ""){
			cout<< i;
			cout<<" || Item ID: " + Warehouse1[0][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse1[0][i].quantity <<endl;}
	}

	cout<<"\nWarehouse 1 Medium:"<<endl;
	for(int i = 0; i<Warehouse1.at(1).size();i++){	
		if (Warehouse1[1][i].ItemID != ""){
			cout<< i;
			cout<<" || Item ID: " + Warehouse1[1][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse1[1][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 1 Large:"<<endl;
	for(int i = 0; i<Warehouse1.at(2).size();i++){	
		if (Warehouse1[2][i].ItemID != ""){
			cout<< i;
			cout<<" || Item ID: " + Warehouse1[2][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse1[2][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 2 Small:"<<endl;
	for(int i = 0; i<Warehouse2.at(0).size();i++){	
		if(Warehouse2[0][i].ItemID!=""){
			cout<<  i;
			cout<<" || Item ID: " + Warehouse2[0][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse2[0][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 2 Medium:"<<endl;
	for(int i = 0; i<Warehouse2.at(1).size();i++){	
		if(Warehouse2[1][i].ItemID!=""){
			cout<<  i;
			cout<<" || Item ID: " + Warehouse2[1][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse2[1][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 2 Large:"<<endl;
	for(int i = 0; i<Warehouse2.at(2).size();i++){	
		if(Warehouse2[2][i].ItemID!=""){
			cout<<  i;
			cout<<" || Item ID: " + Warehouse2[2][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse2[2][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 3 Small:"<<endl;
	for(int i = 0; i<Warehouse3.at(0).size();i++){	
		if(Warehouse3[0][i].ItemID!=""){
			cout<<  i;
			cout<<" || Item ID: " + Warehouse3[0][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse3[0][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 3 Medium:"<<endl;
	for(int i = 0; i<Warehouse3.at(1).size();i++){	
		if(Warehouse3[1][i].ItemID!=""){
			cout<<  i;
			cout<<" || Item ID: " + Warehouse3[1][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse3[1][i].quantity <<endl;
		}
	}

	cout<<"\nWarehouse 3 Large:"<<endl;
	for(int i = 0; i<Warehouse3.at(2).size();i++){	
		if(Warehouse3[2][i].ItemID!=""){
			cout<<  i;
			cout<<" || Item ID: " + Warehouse3[2][i].ItemID;
			cout<<" || Item Quantity: " + Warehouse3[2][i].quantity <<endl;
		}
	}

}


void showWarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY) Given a Warehouse and a location show the contents


	cout << "TEST: Show Warehouse Contents functions go here."<<endl<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}

void editItemCatalog(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(EXTRA FUNCTIONALITY: GROUP) Able to Add or Delete an item from the catalog. From SPMP, "Edits the valid item catalog, ensuring that the number of accepted items never exceeds 400."


	cout << "TEST: Adding/Deleting Catalog items functions go here."<<endl<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}

/*void addUser(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){// (EXTRA FUNCTIONALITY: ANNA) To add a new user they must contact the Gold Stars.


	cout << "\nTo add a new user, contact Gold Stars."<<endl;
	displayMainMenu(Warehouse1,Warehouse2,Warehouse3);
}*/