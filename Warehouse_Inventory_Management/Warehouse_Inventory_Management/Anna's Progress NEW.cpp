
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


//class Item{
//	string iD;
//	string iName;
//	int iQuantity;
//	double iCost;
//	char iSize;
//};


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


	cout<<"here"<<endl;

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

void inventoryValue(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1, vector<vector<Warehouse>> Warehouse2, vector<vector<Warehouse>> Warehouse3){//(EXTRA FUNCTIONALITY:FERIQUE) displays the total value of all the items in the warehouses. 
	float W1Qty[100], W1Price[100], W2Qty[100], W2Price[100], W3Qty[100], W3Price[100];
	float Value1 = 0, Value2 = 0, Value3 = 0, W1Total= 0, W2Total = 0, W3Total = 0, GrandTotal = 0;
	string tempID;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Warehouse1.size(); j++)
		{
			tempID = Warehouse1[i][j].ItemID;
			W1Qty[j] = atoi(Warehouse1[i][j].quantity.c_str());
			for (int x = 0; x < Catalog.size(); x++)
			{
				if (tempID == Catalog[x].ID)
				{
					W1Price[j] = atoi(Catalog[x].itemPrice.c_str());
					Value1 = W1Qty[j] * W1Price[j];
					W1Total = Value1 + W1Total;
				}
			}
		}	
	}	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Warehouse2.size(); j++)
		{
			tempID = Warehouse2[i][j].ItemID;
			cout << tempID << endl;
			W2Qty[j] = atoi(Warehouse2[i][j].quantity.c_str());
			for (int x = 0; x < Catalog.size(); x++)
			{
				if (tempID == Catalog[x].ID)
				{
					W2Price[j] = atoi(Catalog[x].itemPrice.c_str());
					Value2 = W2Qty[j] * W2Price[j];
					W2Total = Value2 + W2Total;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Warehouse3.size(); j++)
		{
			tempID = Warehouse3[i][j].ItemID;
			W3Qty[j] = atoi(Warehouse3[i][j].quantity.c_str());
			for (int x = 0; x < Catalog.size(); x++)
			{
				if (tempID == Catalog[x].ID)
				{
					W3Price[j] = atoi(Catalog[x].itemPrice.c_str());
					Value3 = W3Qty[j] * W3Price[j];
					W3Total = Value3 + W3Total;
				}
			}
		}
	}
	GrandTotal = W1Total + W2Total + W3Total;
	cout << " ========================================" << endl;
	cout << "             Warehouse Values            "<< endl;
	cout << " ========================================" << endl;
	cout << " Warehouse One:   $" << W1Total << "       " << endl; 
	cout << " Warehouse Two:   $" << W2Total << "       " << endl;
	cout << " Warehouse Three: $" << W3Total << "       " << endl;
	cout << " ----------------------------------------" << endl;
	cout << " Grand Total:     $" << GrandTotal << "      " << endl;
	cout << " ========================================" << endl;
	cout << endl;
	system("pause");
	


	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
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
