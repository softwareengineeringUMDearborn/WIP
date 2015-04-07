
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

struct ItemsOrdered{
string ItemID;
string ItemName;
string ItemCost;
string Warehouse;
string Count;//Quantity Ordered
string LocationFound;//can me more than one 
vector<ItemsOrdered> MultipleLocations; //
};

struct ItemsShipped{
string ItemID;
string Warehouse;
string ItemName;
string Count;//Quantity Sent
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
	string ItemCount;//must be less than 9
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


		system("pause");
		StoredDailyShipments.push_back(A);
		A.ItemsShippedVector.clear();
		getline(cat,sLine);
	}

	//check total number of items in trailer matches what was received
	if(sLine.substr(1,1)== to_string(StoredDailyShipments.size()))
	{
		cout<<"All "<<StoredDailyShipments.size()<<" vendors were processed.";
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
		//importans fix
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


		system("pause");
		StoredDailyOrders.push_back(A);
		getline(cat,sLine);
		A.ItemsOrderedVector.clear();
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


//Prototypes of functions go here:

void displayMainMenu(vector<CatalogItem>&Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void logOut();

void availableSpaceRemaining(vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3);
void availableSpaceRemaining_WarehouseSpaces(vector<vector<Warehouse>> Warehouse, int counter, int Size);

void inventoryValue();
void searchHistoryLog();
void itemInformationDisplay();

void itemInventoryDisplay(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
void itemInformationDisplay_WarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
bool itemInformationDisplay_testCatalog(vector<CatalogItem>Catalog, string ItemId, string ItemSize);

void showWarehouseContents(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3);
void showWarehouseContents_ShowCatalogInfo(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse, string ItemID, string quantity, int location);

void editItemCatalog();
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
		if(sLine.substr(0, 1)=="S")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnSmall.push_back(A);
		}else if(sLine.substr(0,1)=="M")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnMedium.push_back(A);
		}else if(sLine.substr(0,1)=="L")
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
		if(sLine.substr(0, 1)=="S")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnSmall.push_back(A);
		}else if(sLine.substr(0,1)=="M")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnMedium.push_back(A);
		}else if(sLine.substr(0,1)=="L")
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
	system("pause");
	while(!cat.eof())
	{
		cout<<"hi";
		//getline(cat,sLine);
		if(sLine.substr(0, 1)=="S")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnSmall.push_back(A);
		}else if(sLine.substr(0,1)=="M")
		{
			A.ItemID=sLine.substr(1,10);
			A.quantity=sLine.substr(11);
			ColumnMedium.push_back(A);
		}else if(sLine.substr(0,1)=="L")
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

//for Orders
bool SearchCatalog(vector<CatalogItem>&Catalog, string ItemId, string& ItemSize, vector<Orders>&StoredDailyOrders, int k, int y){
	for(int x=0;x<Catalog.size();x++)
	{
		if(ItemId==Catalog[x].ID)
		{ //item valid
			ItemSize=Catalog[x].itemSize;
			StoredDailyOrders[k].ItemsOrderedVector[y].ItemName=Catalog[x].itemName;
			StoredDailyOrders[k].ItemsOrderedVector[y].ItemCost=Catalog[x].itemPrice;
			return true;
		}
	}
	//item not valid
	return false;
}
//for shipments
bool SearchCatalog(vector<CatalogItem>&Catalog, string ItemId, string& ItemSize,  int k, int y){
	for(int x=0;x<Catalog.size();x++)
	{
		if(ItemId==Catalog[x].ID)
		{ //item valid
			ItemSize=Catalog[x].itemSize;
			//StoredDailyShipments[k].ItemsShippedVector[y].ItemName=Catalog[x].itemName;
			return true;
		}
	}
	//item not valid
	return false;
}

void CreateInvoice(vector<Orders> &StoredDailyOrders, vector<CatalogItem> Catalog)
{
	
	//float subtotal=0;
	cout<<endl<<endl;
	for(int x=0; x<StoredDailyOrders.size();x++)
	{
		cout<<endl;
		float subtotal=0;
		cout<<StoredDailyOrders[x].CustomerID<<endl;
		cout<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
		cout<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
		cout<<StoredDailyOrders[x].CustomerCity<<" "<<StoredDailyOrders[x].CustomerState_OR_Province<<" "<<StoredDailyOrders[x].CustomerPostalCode<<endl;
		cout<<endl;
		cout<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
		cout<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
		cout<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
		cout<<"Shipping Date: WHat is this?"<<endl;
		cout<<"Payment Type:\t"<<StoredDailyOrders[x].CustomerPaymentType<<endl;
		cout<<endl;
		cout<<"Item ID\t\tItem Name\t\t\tQuantity\tPrice\tItem total"<<endl;
		cout<<"__________________________________________________________________________"<<endl;
		for(int y=0;y<StoredDailyOrders[x].ItemsOrderedVector.size();y++){
			cout<<StoredDailyOrders[x].ItemsOrderedVector[y].ItemID<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[y].ItemName<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<"\t$"<<StoredDailyOrders[x].ItemsOrderedVector[y].ItemCost;
			for (int m=0;m<StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size();m++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations[m].LocationFound=="BACKORDERED")
				{ 
					cout<<StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations[m].LocationFound<<endl;
				}
				else{
					double itemTotal=atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str())*atoi(StoredDailyOrders[x].ItemsOrderedVector[y].ItemCost.c_str());
				cout<<"\t$"<<itemTotal<<endl;
				subtotal=subtotal+atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str())*atoi(StoredDailyOrders[x].ItemsOrderedVector[y].ItemCost.c_str());
				}
			}

		}
		string decdiscount="."+StoredDailyOrders[x].CustomerDiscount;
		
		double Discount=subtotal*stof(decdiscount);
		
		double OrderTotal=subtotal-Discount;
		double Tax=OrderTotal*.06;
		double AmountDue=OrderTotal+Tax;
		cout<<endl;
		cout<<"Subtotal\t\t\t\t $ "<<subtotal<<endl;
		cout<<"\t\t\t\t\t ============"<<endl;
		cout<<"Discount Percentage-"<<StoredDailyOrders[x].CustomerDiscount<<"%"<<"\t\t\t\t- $ "<<Discount<<endl;
		cout<<"\t\t\t\t\t ============"<<endl;
		cout<<"Order total\t\t\t"<<OrderTotal<<endl;
		cout<<"Tax    6%\t\t\t"<<"+ $"<<Tax<<endl;
		cout<<"\t\t\t\t\t ============"<<endl;
		cout<<"AMOUNT DUE in "<<StoredDailyOrders[x].CustomerPaymentType<<"\t\t\t"<<"$ "<<AmountDue<<endl;
		
		
		cout<<endl<<"END";
	}
	return;
}

void CreatePackingSlip(vector<Orders> &StoredDailyOrders, vector<CatalogItem> Catalog)
{
	bool W1=false;
	bool W2=false;
	bool W3=false;
	//	for (int x=0;x<StoredDailyOrders.size();x++)
	//{
	//	/*for(int y=0;y<3;y++)
	//	{
	//		if
	//	}*/
	//	for(int y=0;y<StoredDailyOrders[x].ItemsOrderedVector.size();y++)
	//	{
	//		if(StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse=="1")W1=true;
	//		if(StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse=="2")W2=true;
	//		if(StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse=="3")W3=true;
	//	}
	//}
	for (int x=0;x<StoredDailyOrders.size();x++)
	{
		W1=false;W2=false;W3=false;
		for(int y=0;y<StoredDailyOrders[x].ItemsOrderedVector.size();y++)
		{
			if(StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse=="1")W1=true;
			if(StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse=="2")W2=true;
			if(StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse=="3")W3=true;
		}
		if(W1==true)
		{
			int itemCount=0;
			int pickedCount=0;
			cout<<endl<<endl<<endl;
			cout<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
			cout<<"Customer Name and Address:"<<endl;
			cout<<StoredDailyOrders[x].CustomerID<<endl;
			cout<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
			cout<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
			cout<<StoredDailyOrders[x].CustomerCity<<StoredDailyOrders[x].CustomerState_OR_Province<<StoredDailyOrders[x].CustomerPostalCode<<" "<<StoredDailyOrders[x].CustomerCountry<<endl;
			cout<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
			cout<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
			cout<<"Shipping Date:\t What is this?"<<endl;

			cout<<"Item ID\t Item Name\t\t Warehouse 1 Location\t Quantity\n";
			cout<<"_____________________________________________________________________\n";
			for(int k=0;k<StoredDailyOrders[x].ItemsOrderedVector.size();k++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[k].Warehouse=="1")
				{
					itemCount++;
				cout<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemID<<"\t\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemName<<"\t";
				if(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()==1)
				{
					cout<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[0].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].Count<<endl;
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());

				}
				else{
					int TOTAL=atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());
					int newTOT=TOTAL;
					
				for(int t=0;t<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;t++)
				{
					cout<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count<<endl<<"\t\t\t";
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
					newTOT=newTOT- atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
				}
				int lastplace=StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;
				pickedCount=pickedCount+newTOT;
				cout<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[lastplace].LocationFound<<"\t"<<newTOT<<"\n";
				cout<<"\t\t\tTOTAL\t"<<TOTAL<<endl;
				}
			}
			}
			cout<<itemCount<<"items\t"<<pickedCount<<"quantity picked\n";
		}
		if(W2==true)
		{
			int itemCount=0;
			int pickedCount=0;
			cout<<endl<<endl<<endl;
			cout<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
			cout<<"Customer Name and Address:"<<endl;
			cout<<StoredDailyOrders[x].CustomerID<<endl;
			cout<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
			cout<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
			cout<<StoredDailyOrders[x].CustomerCity<<StoredDailyOrders[x].CustomerState_OR_Province<<StoredDailyOrders[x].CustomerPostalCode<<" "<<StoredDailyOrders[x].CustomerCountry<<endl;
			cout<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
			cout<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
			cout<<"Shipping Date:\t What is this?"<<endl;

			cout<<"Item ID\t Item Name\t\t Warehouse 2 Location\t Quantity\n";
			cout<<"_____________________________________________________________________\n";
			for(int k=0;k<StoredDailyOrders[x].ItemsOrderedVector.size();k++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[k].Warehouse=="2")
				{
					itemCount++;
				cout<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemID<<"\t\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemName<<"\t";
				if(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()==1)
				{
					cout<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[0].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].Count<<endl;
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());

				}
				else{
					int TOTAL=atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());
					int newTOT=TOTAL;
					
				for(int t=0;t<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;t++)
				{
					cout<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count<<endl<<"\t\t\t";
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
					newTOT=newTOT- atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
				}
				int lastplace=StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;
				pickedCount=pickedCount+newTOT;
				cout<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[lastplace].LocationFound<<"\t"<<newTOT<<"\n";
				cout<<"\t\t\tTOTAL\t"<<TOTAL<<endl;
				}
			}
			}
			cout<<itemCount<<"items\t"<<pickedCount<<"quantity picked\n";
		}
		if(W3==true)
		{
			int itemCount=0;
			int pickedCount=0;
			cout<<endl<<endl<<endl;
			cout<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
			cout<<"Customer Name and Address:"<<endl;
			cout<<StoredDailyOrders[x].CustomerID<<endl;
			cout<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
			cout<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
			cout<<StoredDailyOrders[x].CustomerCity<<StoredDailyOrders[x].CustomerState_OR_Province<<StoredDailyOrders[x].CustomerPostalCode<<" "<<StoredDailyOrders[x].CustomerCountry<<endl;
			cout<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
			cout<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
			cout<<"Shipping Date:\t What is this?"<<endl;

			cout<<"Item ID\t Item Name\t\t Warehouse 3 Location\t Quantity\n";
			cout<<"_____________________________________________________________________\n";
			for(int k=0;k<StoredDailyOrders[x].ItemsOrderedVector.size();k++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[k].Warehouse=="3")
				{
					itemCount++;
				cout<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemID<<"\t\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemName<<"\t";
				if(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()==1)
				{
					cout<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[0].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].Count<<endl;
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());

				}
				else{
					int TOTAL=atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());
					int newTOT=TOTAL;
				
				for(int t=0;t<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;t++)
				{
					cout<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count<<endl<<"\t\t\t";
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
					newTOT=newTOT- atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
				}
				int lastplace=StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;
				pickedCount=pickedCount+newTOT;
				cout<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[lastplace].LocationFound<<"\t"<<newTOT<<"\n";
				cout<<"\t\t\tTOTAL\t"<<TOTAL<<endl;
				}
			}
			}
			cout<<itemCount<<"items\t"<<pickedCount<<"quantity picked\n";
		}
	}
}

void ProcessOrders(vector<CatalogItem>&Catalog, vector<Orders>& StoredDailyOrders,vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3)
{
	ItemsOrdered A;
	//vector<string> MultipleLocations;
	string ItemSize;
	for(int x=0;x<StoredDailyOrders.size();x++)
	{
		//int AmountSoFar=0;

		cout<<"hello";
		for(int y=0; y<StoredDailyOrders[x].ItemsOrderedVector.size();y++)
		{   
			int AmountSoFar=0;
			cout<<"hihi\n";
			//Check Catalog for legal item ordered
			string ID=StoredDailyOrders[x].ItemsOrderedVector[y].ItemID;
			if(SearchCatalog(Catalog,ID, ItemSize, StoredDailyOrders, x, y)==false)
			{
				cout<<"This item is not found in the Catalog and hence is not available at any of the Warehouses."<<endl;
				StoredDailyOrders[x].ItemsOrderedVector[y].LocationFound="Invalid Item";
			}
		//nolongerusing?forgotwhati was doing	int ItemLocationsSpace=-1;
			string WNum=StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse;
			int AmountLeft= atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());
			cout<<"minnie\n";

			int AmountOrdered= atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());
			int AmountAvailable = 0;
			if(WNum=="1")
			{
				if(ItemSize=="S")
				{
					for(int k=0;k<Warehouse1.at(0).size();k++)
					{
						if(Warehouse1[0][k].ItemID==ID)
						{ 
							A.Count=Warehouse1[0][k].quantity;
							A.LocationFound="S-0"+to_string(k);
							cout<<"in here";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse1[0][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse1[0][k].quantity=to_string(atoi(Warehouse1[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse1[0][i].ItemID)
									{
										Warehouse1[0][i].quantity="0";
									}
								}
								}
								k=Warehouse1.at(0).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
						
					}
				//delete empty spaces
					for(int l=0;l<Warehouse1.at(0).size();l++)
					{
						if(Warehouse1[0][l].quantity == "0") Warehouse1[0].erase(Warehouse1[0].begin() +l);
					}


				if(ItemSize=="M")
				{
					for(int k=0;k<Warehouse1.at(1).size();k++)
					{
						if(Warehouse1[1][k].ItemID==ID)
						{ 
							A.LocationFound="S-1"+to_string(k);
							
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse1[1][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse1[0][k].quantity=to_string(atoi(Warehouse1[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse1[1][i].ItemID)
									{
										Warehouse1[1][i].quantity="0";
									}
								}
								}
								k=Warehouse1.at(1).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
						//delete empty spaces
					for(int l=0;l<Warehouse1.at(1).size();l++)
					{
						if(Warehouse1[1][l].quantity == "0") Warehouse1[1].erase(Warehouse1[1].begin() +l);
					}	
				}
				if(ItemSize=="L")
				{	for(int k=0;k<Warehouse1.at(2).size();k++)
					{
						if(Warehouse1[2][k].ItemID==ID)
						{ 
							A.LocationFound="S-2"+to_string(k);
							cout<<"in here";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse1[2][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse1[0][k].quantity=to_string(atoi(Warehouse1[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse1[2][i].ItemID)
									{
										Warehouse1[2][i].quantity="0";
									}
								}
								}
								k=Warehouse1.at(2).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
					//delete empty spaces
					for(int l=0;l<Warehouse1.at(2).size();l++)
					{
						if(Warehouse1[2][l].quantity == "0") Warehouse1[2].erase(Warehouse1[2].begin() +l);
					}		
				}
			}
			else if(WNum=="2")
			{
				if(ItemSize=="S")
				{
					for(int k=0;k<Warehouse2.at(0).size();k++)
					{
						if(Warehouse2[0][k].ItemID==ID)
						{ 
							A.LocationFound="S-0"+to_string(k);
							cout<<"in here";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse2[0][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse2[0][k].quantity=to_string(atoi(Warehouse2[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse2[0][i].ItemID)
									{
										Warehouse2[0][i].quantity="0";
									}
								}
								}
								k=Warehouse2.at(0).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
						
					}
				//delete empty spaces
					for(int l=0;l<Warehouse2.at(0).size();l++)
					{
						if(Warehouse2[0][l].quantity == "0") Warehouse2[0].erase(Warehouse2[0].begin() +l);
					}


				if(ItemSize=="M")
				{
					for(int k=0;k<Warehouse2.at(1).size();k++)
					{
						if(Warehouse2[1][k].ItemID==ID)
						{ 
							A.LocationFound="S-1"+to_string(k);
							
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse2[1][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse2[0][k].quantity=to_string(atoi(Warehouse2[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse2[1][i].ItemID)
									{
										Warehouse2[1][i].quantity="0";
									}
								}
								}
								k=Warehouse2.at(1).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
						//delete empty spaces
					for(int l=0;l<Warehouse2.at(1).size();l++)
					{
						if(Warehouse2[1][l].quantity == "0") Warehouse2[1].erase(Warehouse2[1].begin() +l);
					}	
				}
				if(ItemSize=="L")
				{	for(int k=0;k<Warehouse2.at(2).size();k++)
					{
						if(Warehouse2[2][k].ItemID==ID)
						{ 
							A.LocationFound="S-2"+to_string(k);
							cout<<"in here";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse2[2][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse2[0][k].quantity=to_string(atoi(Warehouse2[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse2[2][i].ItemID)
									{
										Warehouse2[2][i].quantity="0";
									}
								}
								}
								k=Warehouse2.at(2).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
					//delete empty spaces
					for(int l=0;l<Warehouse2.at(2).size();l++)
					{
						if(Warehouse2[2][l].quantity == "0") Warehouse2[2].erase(Warehouse2[2].begin() +l);
					}		
				}
			} 
			else if(WNum=="3")
			{
				if(ItemSize=="S")
				{
					for(int k=0;k<Warehouse3.at(0).size();k++)
					{
						if(Warehouse3[0][k].ItemID==ID)
						{ 
							A.LocationFound="S-0"+to_string(k);
							cout<<"in here";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse3[0][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse3[0][k].quantity=to_string(atoi(Warehouse3[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse3[0][i].ItemID)
									{
										Warehouse3[0][i].quantity="0";
									}
								}
								}
								k=Warehouse3.at(0).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
						
					}
				//delete empty spaces
					for(int l=0;l<Warehouse3.at(0).size();l++)
					{
						if(Warehouse3[0][l].quantity == "0") Warehouse3[0].erase(Warehouse3[0].begin() +l);
					}


				if(ItemSize=="M")
				{
					for(int k=0;k<Warehouse3.at(1).size();k++)
					{
						if(Warehouse3[1][k].ItemID==ID)
						{ 
							A.LocationFound="S-1"+to_string(k);
							
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse3[1][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse3[0][k].quantity=to_string(atoi(Warehouse3[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse3[1][i].ItemID)
									{
										Warehouse3[1][i].quantity="0";
									}
								}
								}
								k=Warehouse3.at(1).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
						//delete empty spaces
					for(int l=0;l<Warehouse3.at(1).size();l++)
					{
						if(Warehouse3[1][l].quantity == "0") Warehouse3[1].erase(Warehouse3[1].begin() +l);
					}	
				}
				if(ItemSize=="L")
				{	for(int k=0;k<Warehouse3.at(2).size();k++)
					{
						if(Warehouse3[2][k].ItemID==ID)
						{ 
							A.LocationFound="S-2"+to_string(k);
							cout<<"in here";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse3[2][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								Warehouse3[0][k].quantity=to_string(atoi(Warehouse3[0][k].quantity.c_str())-AmountOrdered);
								if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size()>1)
								{
								for(int i=0;i<=k;i++)
								{
									if(ID==Warehouse3[2][i].ItemID)
									{
										Warehouse3[2][i].quantity="0";
									}
								}
								}
								k=Warehouse3.at(2).size();
							}

						}
					
						}
					if(AmountAvailable<AmountOrdered)
					{
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.clear();
							A.LocationFound="BACKORDERED";
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.";
					}
					//delete empty spaces
					for(int l=0;l<Warehouse3.at(2).size();l++)
					{
						if(Warehouse3[2][l].quantity == "0") Warehouse3[2].erase(Warehouse3[2].begin() +l);
					}		
				}
			}

		}

	//	CreatePackingSlip(StoredDailyOrders, Catalog);
	}

		CreateInvoice(StoredDailyOrders, Catalog);
		CreatePackingSlip(StoredDailyOrders, Catalog);
	return;

}

void ProcessShipments(vector<CatalogItem>&Catalog, vector<Shipments>& StoredDailyShipments,vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3)
{
	for(int x=0;x<StoredDailyShipments.size();x++)
	{
		for (int y=0;y<StoredDailyShipments[x].ItemsShippedVector.size();y++)
		{
			string ID=StoredDailyShipments[x].ItemsShippedVector[y].ItemID;
			string itemSize;
			string WarehouseID=StoredDailyShipments[x].ItemsShippedVector[y].Warehouse;
			int k=0;
			if(SearchCatalog(Catalog, ID, itemSize, x, y)==false)
			{
				cout<<"Invalid item "<<ID<<" shipped to the Warehouse. Return to Vendor: "<<StoredDailyShipments[x].VendorName<<endl;
				//StoredDailyOrders[x].ItemsOrderedVector[y].LocationFound="Invalid Item";
			
			}
			else
			{
				if(WarehouseID=="1")
				{
					if(itemSize=="S")
					{
					for(;k<Warehouse1.at(0).size();k++)
					{


						if(Warehouse1[0][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=250-atoi(Warehouse1[0][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse1[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<250)
							{
								int NewQuant=atoi(Warehouse1[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse1[0][k].quantity=to_string(NewQuant);
							}

							else if(Warehouse1.at(0).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/250;
								int SpacesLeft= 20 - (Warehouse1.at(0).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse1[0][k].quantity = to_string(atoi(Warehouse1[0][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>250)
								{
									Warehouse A;
									A.quantity="250";
									A.ItemID=ID;
									AmountLeft=AmountLeft-250;
									Warehouse1[0].push_back(A);
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse1[0].push_back(A);
									k=Warehouse1.at(0).size();
									y++;
									
								}
								else cout<<"Insufficient space for "<<Warehouse1[0][k].ItemID<<"in Warehouse 1.\n";

						}
							else cout<<"Insufficient space for "<<Warehouse1[0][k].ItemID<<"in Warehouse 1.\n";



						}

					}
					}

				}

			}
		}
	}



}





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
	ProcessShipments(Catalog, StoredDailyShipments, Warehouse1, Warehouse2, Warehouse3);
	
	
	
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

	//cody needs to add blank spaces
	Warehouse1[0].resize(20);
	Warehouse1[1].resize(60);
	Warehouse1[2].resize(20);

	Warehouse2[0].resize(20);
	Warehouse2[1].resize(60);
	Warehouse2[2].resize(20);

	Warehouse3[0].resize(20);
	Warehouse3[1].resize(60);
	Warehouse3[2].resize(20);



	cout<<"here"<<endl;

	//Initialize Catalog
	//Initialize Warehouse
	//Order Processing
	//Shipment Processing


	displayMainMenu(Catalog,Warehouse1,Warehouse2,Warehouse3);// call the main menu function

	return 0;
}


//Program functions go here:
void displayMainMenu(vector<CatalogItem>&Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3) {//main menu willdisplay to the user which options they have to choose from
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
		displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
	}

	//if the input is actally one of the inputs then do that functionality
		if (menuResponse == 0){
			logOut();
		}

		else if (menuResponse == 1){
			availableSpaceRemaining(Warehouse1,Warehouse2,Warehouse3);
		}

		else if (menuResponse == 2){
			inventoryValue();
		}

		else if (menuResponse == 3){
			searchHistoryLog();
		}
		else if (menuResponse == 4){
			itemInformationDisplay();
		}
		else if (menuResponse == 5){
			itemInventoryDisplay(Catalog, Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 6){
			showWarehouseContents(Catalog, Warehouse1,Warehouse2,Warehouse3);
		}
		else if (menuResponse == 7){
			editItemCatalog();
		}
		else if (menuResponse == 8){
			cout << "\nTo add a new user, contact Gold Stars."<<endl;
		}
		else//Any other number input will be invalid.
			cout<<"Error: Invalid input, please try again."<<endl<<endl;
			displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);

}

void logOut(){//(BASE FUNCTIONALITY)if the user decides to log out, it will save the current warehouse inventory and catalog to the file then close the program
	cout << "TEST: Save everything to the files functions go here, then close the program."<<endl<<endl;
	exit(0);//exit point of the program
}

void availableSpaceRemaining(vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3){//(EXTRA FUNCTIONALITY:CODY) Returns all open spaces available in the each warehouse.
	/*We can have multiple ways of displaying this:

	Example 1: Just how many empty are in each warehouse and size

	Warehouse 1:
	Small: #, Medium #, Large: #

	Warehouse 2:
	Small: #, Medium #, Large: #
	...
	--------------------------------------
	Example 2: Display each location that is empty followed by the total number.

	Warehouse 1:
	Small: 0,3,6,7,9,14,17,19
	Total empty warehouse locations: 8

	Medium: 1,3,5,7,9,20,56
	Total empty warehouse locations: 7

	Large: 0,1,2,3,4,5,6,7,8,9,10
	Total empty warehouse locations: 11
	...
	--------------------------------------
	*/
	cout<<"\nWarehouse 1:"<<endl;
	cout<<"\nSmall:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse1,0,0);

	cout<<"\nMedium:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse1,0,1);

	cout<<"\nLarge:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse1,0,2);

	cout<<endl;
	cout<<"\nWarehouse 2:"<<endl;
	cout<<"\nSmall:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse2,0,0);

	cout<<"\nMedium:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse2,0,1);

	cout<<"\nLarge:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse2,0,2);

	cout<<endl;
	cout<<"\nWarehouse 3:"<<endl;
	cout<<"\nSmall:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse3,0,0);

	cout<<"\nMedium:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse3,0,1);

	cout<<"\nLarge:";
	availableSpaceRemaining_WarehouseSpaces(Warehouse3,0,2);

	cout<<endl;
	system("pause");
	//cout << "TEST: Available Space Remaining functions go here."<<endl<<endl;
	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

void availableSpaceRemaining_WarehouseSpaces(vector<vector<Warehouse>> Warehouse, int counter, int Size) {
	
	for(int i = 0; i<Warehouse.at(Size).size();i++){	
		if (Warehouse[Size][i].ItemID == ""){
			counter++;
			
			cout<< i;
			if(i!=Warehouse.at(Size).size()-1){
				cout<< ",";
			}
		}
	}
	cout<<"\nTotal empty warehouse locations: ";
	cout<<counter<<endl;
}

void inventoryValue(){//(EXTRA FUNCTIONALITY:FERIQUE) displays the total value of all the items in the warehouses. 


	cout << "TEST: Inventory Value functions go here."<<endl<<endl;
	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

void searchHistoryLog(){//(EXTRA FUNCTIONALITY:ZACH) Search the History log for all transactions of the item ID


	cout << "TEST: Search History Log functions go here."<<endl<<endl;
	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

void itemInformationDisplay(){//(BASE FUNCTIONALITY) The inventory analyst is able to update the item name, id, price, stock, and size type.


	cout << "TEST: Item Information display and update functions go here."<<endl<<endl;
	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

void itemInventoryDisplay(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY) Retrieves current status of all 3 warehouses' inventory, and allows inventory analyst to override any location status and update inventory
	
	string Answer;// the users answer for if they want to edit a quantity.
	string warehouseResponse;//the users response for what warehouse number
	string sizeResponse;//the users response for what size type to look at
	int sizeConverter; //Takes the S,M,L that the user enters and converts it to the row of the matrix
	int locationResponse;//the users response for where in the vector to look.
	int quantityResponse;//the users response for what to change the quantity to?

	string addItemResponse;//the user response to adding a new item in that location spot.
	string newID;//the variable that the user will enter to add to the warehouse.
	int newQuantity; //the variable that the user will enter to add to the warehouse
	bool validID; // a check to see if the new item is in the catalog

	itemInformationDisplay_WarehouseContents(Warehouse1, Warehouse2, Warehouse3);//Display the warehouse to the user.

	do{
	cout<< "Would you like to edit a quantity (y/n)? ";
	cin>> Answer;

	if(Answer == "y"){//if the answer is y then continue on to the next question
		do{
		cout<< "What warehouse number is the item located in (1,2,3)?";
		cin>> warehouseResponse;
		}while(warehouseResponse != "1" && warehouseResponse != "2" &&warehouseResponse != "3");//keep asking unless the answer is 1,2 or 3

	
		do{
		cout<< "What size type is the item (S,M,L)?";
		cin>> sizeResponse;
		}while(sizeResponse!="S" && sizeResponse!="M" && sizeResponse!="L");//keep asking unless the answer is S,M or L
	
		if(sizeResponse == "S")//convert the response to vector row
			sizeConverter = 0;
		else if(sizeResponse == "M")
			sizeConverter = 1;
		else if(sizeResponse == "L")
			sizeConverter = 2;
		else
			cout<<"issue converting size to warehouse"<<endl;


		//Determine the location of the item
		do{
		cout<< "What location is the item in?";
		while(!(cin>>locationResponse)){//so this clears the current input value and ignores the character value.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Enter a valid warehouse location."<<endl;
			cout<< "What location is the item in?";
		}
		//cin>> locationResponse;
		//Test boundaries
		if(sizeResponse == "S" && locationResponse >=20 || sizeResponse == "S" && locationResponse <0 ||  sizeResponse == "L" && locationResponse >=20 || sizeResponse == "L" && locationResponse <0 || sizeResponse == "M" && locationResponse >=60|| sizeResponse == "M" && locationResponse <0 ){//if the item is out of the vector boundaries then notify.
			cout<<"Invalid boundary. Small: 0-19, Medium: 0-59, Large: 0-19."<<endl;
		}
		}while(sizeResponse == "S" && locationResponse >=20 || sizeResponse == "S" && locationResponse <0 ||  sizeResponse == "L" && locationResponse >=20 || sizeResponse == "L" && locationResponse <0 || sizeResponse == "M" && locationResponse >=60|| sizeResponse == "M" && locationResponse <0 );//keep asking untill it is within boundaries
		

		
		if(warehouseResponse =="1"){//take the responses and output the item that is in that position
			if(Warehouse1[sizeConverter][locationResponse].ItemID!="" && Warehouse1[sizeConverter][locationResponse].quantity != ""){//if there is an item in that location
				cout<< locationResponse; 
				cout<<" || Item ID: " + Warehouse1[sizeConverter][locationResponse].ItemID + " || Item Quantity: " + Warehouse1[sizeConverter][locationResponse].quantity<<endl;//display that item again
			}
			else if(Warehouse1[sizeConverter][locationResponse].ItemID=="" && Warehouse1[sizeConverter][locationResponse].quantity == ""){//if there is no item in that location then ask to add a new one.
				do{
				cout<<"There is no current item in this location, would you like to add one (y/n)? ";
				cin>>addItemResponse;

				if (addItemResponse == "n"){
					cout<<"Returning to the main menu"<<endl;
					displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
				}
				else if(addItemResponse == "y"){
					do{
					cout<<"Enter an Item ID (EXIT to return to main menu): ";
					cin>> newID;
					if(newID == "EXIT"){
						cout<<"Returning to the main menu"<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
					}
					validID =itemInformationDisplay_testCatalog(Catalog,newID, sizeResponse);
					if(validID ==false){
						cout<<"This Item ID and size combination is not in the catalog, please try again."<<endl;
					}
					else if(validID ==true){
						Warehouse1[sizeConverter][locationResponse].ItemID = newID;
					}

					}while(validID ==false);
				}

				}while(addItemResponse != "y" && addItemResponse != "n");
			}
		}
		else if(warehouseResponse =="2"){//take the responses and output the item that is in that position
			if(Warehouse2[sizeConverter][locationResponse].ItemID!="" && Warehouse2[sizeConverter][locationResponse].quantity != ""){//if there is an item in that location
				cout<< locationResponse; 
				cout<<" || Item ID: " + Warehouse2[sizeConverter][locationResponse].ItemID + " || Item Quantity: " + Warehouse2[sizeConverter][locationResponse].quantity<<endl;//display that item again
			}
			else if(Warehouse2[sizeConverter][locationResponse].ItemID=="" && Warehouse2[sizeConverter][locationResponse].quantity == ""){//if there is no item in that location then ask to add a new one.
				do{
				cout<<"There is no current item in this location, would you like to add one (y/n)? ";
				cin>>addItemResponse;

				if (addItemResponse == "n"){//if they dont want to add a new one go back to menu
					cout<<"Returning to the main menu"<<endl;
					displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
				}
				else if(addItemResponse == "y"){
					do{
					cout<<"Enter an Item ID (EXIT to return to main menu): ";
					cin>> newID;
					if(newID == "EXIT"){
						cout<<"Returning to the main menu"<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
					}
					validID =itemInformationDisplay_testCatalog(Catalog,newID, sizeResponse);
					if(validID ==false){
						cout<<"This Item ID and size combination is not in the catalog, please try again."<<endl;
					}
					else if(validID ==true){
						Warehouse2[sizeConverter][locationResponse].ItemID = newID;
					}

					}while(validID ==false);
				}

				}while(addItemResponse != "y" && addItemResponse != "n");
			}
		}
		else if(warehouseResponse =="3"){//take the responses and output the item that is in that position
			if(Warehouse3[sizeConverter][locationResponse].ItemID!="" && Warehouse2[sizeConverter][locationResponse].quantity != ""){//if there is an item in that location
				cout<< locationResponse; 
				cout<<" || Item ID: " + Warehouse3[sizeConverter][locationResponse].ItemID + " || Item Quantity: " + Warehouse3[sizeConverter][locationResponse].quantity<<endl;//display that item again
			}
			else if(Warehouse3[sizeConverter][locationResponse].ItemID=="" && Warehouse3[sizeConverter][locationResponse].quantity == ""){//if there is no item in that location then ask to add a new one.
				do{
				cout<<"There is no current item in this location, would you like to add one (y/n)? ";
				cin>>addItemResponse;

				if (addItemResponse == "n"){//if they dont want to add a new one go back to menu
					cout<<"Returning to the main menu"<<endl;
					displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
				}
				else if(addItemResponse == "y"){
					do{
					cout<<"Enter an Item ID (EXIT to return to main menu): ";
					cin>> newID;
					if(newID == "EXIT"){
						cout<<"Returning to the main menu"<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
					}
					validID =itemInformationDisplay_testCatalog(Catalog,newID, sizeResponse);
					if(validID ==false){
						cout<<"This Item ID and size combination is not in the catalog, please try again."<<endl;
					}
					else if(validID ==true){
						Warehouse3[sizeConverter][locationResponse].ItemID = newID;
					}

					}while(validID ==false);
				}

				}while(addItemResponse != "y" && addItemResponse != "n");
			}
		}

		do{//obtain the quantity to override the old quantity
		cout<< "What quantity would you like to change it to?"<<endl;
		while(!(cin>>quantityResponse)){//so this clears the current input value and ignores the character value.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Enter a valid quantity."<<endl;
			cout<< "What quantity would you like to change it to?";
		}

		
		//the mainflow path
		if(warehouseResponse =="1"){
			if(quantityResponse <= 0){//if the input is less than or equal to 0 delete the item from the warehouse.
				Warehouse1[sizeConverter][locationResponse].ItemID = "";//delete the id from the warehouse
				Warehouse1[sizeConverter][locationResponse].quantity = "";//delete the quantity from the warehouse
				cout<<"Item deleted."<<endl;
			}
			else if (sizeResponse == "S" && quantityResponse >250 || sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10){//if the quantity is more then boundaries then notify them
				cout<<"Quantity too large. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else//main flow path
				Warehouse1[sizeConverter][locationResponse].quantity = to_string(quantityResponse);
		}
		else if(warehouseResponse =="2"){
			if(quantityResponse <= 0){
				Warehouse2[sizeConverter][locationResponse].ItemID = "";
				Warehouse2[sizeConverter][locationResponse].quantity = "";
				cout<<"Item deleted."<<endl;
			}
			else if (sizeResponse == "S" && quantityResponse >250|| sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10){
				cout<<"Quantity too large. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else
				Warehouse2[sizeConverter][locationResponse].quantity = to_string(quantityResponse);
		}
		else if(warehouseResponse =="3"){
			if(quantityResponse <=0){
				Warehouse3[sizeConverter][locationResponse].ItemID = "";
				Warehouse3[sizeConverter][locationResponse].quantity = "";
				cout<<"Item deleted."<<endl;
			}
			else if (sizeResponse == "S" && quantityResponse >250 || sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10){
				cout<<"Quantity too large. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else
				Warehouse3[sizeConverter][locationResponse].quantity = to_string(quantityResponse);
		}

		}while(sizeResponse == "S" && quantityResponse >250 || sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10);

	}

	//if the ansewr is no then return to the main menu
	else if(Answer == "n"){
		cout<<"Returning to the main menu"<<endl;
	
	}
	}while(Answer != "y" && Answer != "n");
	
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

bool itemInformationDisplay_testCatalog(vector<CatalogItem>Catalog, string ItemId, string ItemSize){
	for(int x=0;x<Catalog.size();x++)
	{
		if(ItemId==Catalog[x].ID)
		{ //item valid
			cout<<"Item ID found"<<endl;
			if(ItemSize==Catalog[x].itemSize){
				cout<<"Item ID and size match."<<endl;
			return true;
			}
			else
				cout<<"Item ID and size do not match."<<endl;
		}
	}
	//item not valid
	return false;
}


void showWarehouseContents(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3){//(BASE FUNCTIONALITY) Given a Warehouse and a location show the contents

	string Answer;
	string warehouseResponse;//the users response for what warehouse number
	string sizeResponse;//the users response for what size type to look at
	int sizeConverter; //Takes the S,M,L that the user enters and converts it to the row of the matrix
	int locationResponse;//the users response for where in the vector to look.

	//Gather the input for the warehouse #
		do{
		cout<< "What warehouse number is the item located in (1,2,3)?";
		cin>> warehouseResponse;
		}while(warehouseResponse != "1" && warehouseResponse != "2" &&warehouseResponse != "3");//keep asking unless the answer is 1,2 or 3

	//Gather the input for the item Size
		do{
		cout<< "What size type is the item (S,M,L)?";
		cin>> sizeResponse;
		}while(sizeResponse!="S" && sizeResponse!="M" && sizeResponse!="L");//keep asking unless the answer is S,M or L
	
		if(sizeResponse == "S")//convert the response to vector row
			sizeConverter = 0;
		else if(sizeResponse == "M")
			sizeConverter = 1;
		else if(sizeResponse == "L")
			sizeConverter = 2;
		else
			cout<<"issue converting size to warehouse"<<endl;

	//Gather the input for the item location
		do{
		cout<< "What location is the item in?";
		while(!(cin>>locationResponse)){//so this clears the current input value and ignores the character value.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Enter a valid warehouse location."<<endl;
			cout<< "What location is the item in?";
		}
		//Test boundaries
		if(sizeResponse == "S" && locationResponse >=20 || sizeResponse == "S" && locationResponse <0 ||  sizeResponse == "L" && locationResponse >=20 || sizeResponse == "L" && locationResponse <0 || sizeResponse == "M" && locationResponse >=60|| sizeResponse == "M" && locationResponse <0 ){//if the item is out of the vector boundaries then notify.
			cout<<"Invalid boundary. Small: 0-19, Medium: 0-59, Large: 0-19."<<endl;
		}
		}while(sizeResponse == "S" && locationResponse >=20 || sizeResponse == "S" && locationResponse <0 ||  sizeResponse == "L" && locationResponse >=20 || sizeResponse == "L" && locationResponse <0 || sizeResponse == "M" && locationResponse >=60|| sizeResponse == "M" && locationResponse <0 );//keep asking untill it is within boundaries

	//Show the contents - search the catalog for all the information
		if(warehouseResponse =="1"){//take the responses and output the item that is in that position
			if(Warehouse1[sizeConverter][locationResponse].ItemID!="" && Warehouse1[sizeConverter][locationResponse].quantity != ""){//if there is an item in that location

				showWarehouseContents_ShowCatalogInfo(Catalog, Warehouse1, Warehouse1[sizeConverter][locationResponse].ItemID, Warehouse1[sizeConverter][locationResponse].quantity, locationResponse);
				
			}
			//check for spots without items
			else if(Warehouse1[sizeConverter][locationResponse].ItemID=="" && Warehouse1[sizeConverter][locationResponse].quantity == ""){
				cout<<"There is no item in this location."<<endl;
			}
		}
		else if(warehouseResponse =="2"){//take the responses and output the item that is in that position
			if(Warehouse2[sizeConverter][locationResponse].ItemID!="" && Warehouse2[sizeConverter][locationResponse].quantity != ""){//if there is an item in that location

				showWarehouseContents_ShowCatalogInfo(Catalog, Warehouse2, Warehouse2[sizeConverter][locationResponse].ItemID, Warehouse2[sizeConverter][locationResponse].quantity, locationResponse);
				
			}
			//check for spots without items
			else if(Warehouse2[sizeConverter][locationResponse].ItemID=="" && Warehouse2[sizeConverter][locationResponse].quantity == ""){
				cout<<"There is no item in this location."<<endl;
			}
		}
		else if(warehouseResponse =="3"){//take the responses and output the item that is in that position
			if(Warehouse3[sizeConverter][locationResponse].ItemID!="" && Warehouse3[sizeConverter][locationResponse].quantity != ""){//if there is an item in that location

				showWarehouseContents_ShowCatalogInfo(Catalog, Warehouse3, Warehouse3[sizeConverter][locationResponse].ItemID, Warehouse3[sizeConverter][locationResponse].quantity, locationResponse);
				
			}
			//check for spots without items
			else if(Warehouse3[sizeConverter][locationResponse].ItemID=="" && Warehouse3[sizeConverter][locationResponse].quantity == ""){
				cout<<"There is no item in this location."<<endl;
			}
		}
		

		//ask the user if he wants to look up another item.
		do{
		cout<< "Would you like to show the contents of another item (y/n)? ";
		cin>> Answer;
		if (Answer == "y"){
			showWarehouseContents(Catalog, Warehouse1,Warehouse2,Warehouse3);
		}
		else if (Answer == "n"){
			cout<<"Returning to the main menu"<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
		}

		}while(Answer != "y" && Answer != "n");
		
}

void showWarehouseContents_ShowCatalogInfo(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse, string ItemID, string quantity, int location){

	for(int x=0;x<Catalog.size();x++)
	{
		if(ItemID==Catalog[x].ID)
		{ //if the item is in the catalog then display its contents.
			cout<<"Item ID found"<<endl<<endl;
			cout<< "ID:          " + ItemID<<endl;
			cout<< "Name:        " + Catalog[x].itemName<<endl;
			cout<< "Price:       " + Catalog[x].itemPrice<<endl;
			cout<< "Size:        " + Catalog[x].itemSize<<endl;
			cout<< "Quantity:    " + quantity<<endl;
			cout<< "Description: " + Catalog[x].itemDesc<<endl;
		}
	}

}

void editItemCatalog(){//(EXTRA FUNCTIONALITY: GROUP) Able to Add or Delete an item from the catalog. From SPMP, "Edits the valid item catalog, ensuring that the number of accepted items never exceeds 400."


	cout << "TEST: Adding/Deleting Catalog items functions go here."<<endl<<endl;
	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

/*void addUser(vector<CatalogItem>&Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){// (EXTRA FUNCTIONALITY: ANNA) To add a new user they must contact the Gold Stars.


	cout << "\nTo add a new user, contact Gold Stars."<<endl;
	displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}*/