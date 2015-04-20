#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<istream>
#include<fstream>
#include<sstream>
#include<ctime>

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


struct Orders{
	vector<ItemsOrdered> ItemsOrderedVector;
	string ShippingDate;
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
	string ReceivingDate;
	string ItemCount;//must be less than 9
	vector <ItemsShipped> ItemsShippedVector;
};

class logItems
{
  private:
	string line;
	string month;
	string day;
	string year;


  public:
	logItems(string in, string mm, string dd, string yyyy)
	{
		line = in;
		month = mm;
		day = dd;
		year = yyyy;
	}
	void setLogFileLine(string in)
	{
		line = in;
	}
	void setDate(string mm, string dd, string yyyy)
	{
		month = mm;
		day = dd;
		year = yyyy;
	}
	string getLogFileLine()
	{
		return line;
	}
	string getYear()
	{
		return year;
	}
	string getMonth()
	{
		return month;
	}
	string getDay()
	{
		return day;
	}
};

void logDateDecomp(string line, string &month, string &day, string &year)
{
	string temp;

	for(unsigned int i = line.size(); i>0; i--)
	{
		temp = temp + line.at(i-1);
	}

	for(unsigned int i = 0; i < 10; i++)//this is making things backward
	{
		if(i<4)
			year = year + temp.at(i);
		else if(i > 4 && i < 7)
			day = day + temp.at(i);
		else if(i > 7)
			month = month + temp.at(i);
	}
// turn everything around
	temp = year;
	year = "";
	for(unsigned int i = temp.size(); i>0; i--)
	{
		year = year + temp.at(i-1);
	}

	temp = month;
	month = "";
	for(unsigned int i = temp.size(); i>0; i--)
	{
		month = month + temp.at(i-1);
	}

	temp = day;
	day = "";
	for(unsigned int i = temp.size(); i>0; i--)
	{
		day = day + temp.at(i-1);
	}
};

void AddToLogFile(string itemNumber, string warehouse, string quantity, string INorOUT, string date);
void searchHistoryLog(bool first);

void logSearch(string itemNumber)
{
	// check for valid item number

	cout << "Searching the log for item: " << itemNumber << "\n";

	int count = 0;
	vector<logItems> foundItems;
	string month, day, year;

	string line = "";
	string firstTenFromFile = "";

	ifstream infile;
	infile.open("WIPLogFile.txt");

	if(!infile.is_open())
		cout << "ERROR: History Log file does not exist\n";

	while( getline(infile, line) )
	{
		firstTenFromFile = "";
		if(line.size() >= 10)		
			for(unsigned int i = 0; i < 10; i++)
			{
				firstTenFromFile = firstTenFromFile + line.at(i);
			}

		if( itemNumber == firstTenFromFile)
		{
			unsigned int i = 0;
			count = count + 1;

			month = "";
			day = "";
			year = "";

			logDateDecomp(line, month, day, year);
			logItems newItem(line, month, day, year);
			
			if(foundItems.size() == 0)	// when vector is empty
			{
				foundItems.push_back(newItem);
			}
			else
			{
				bool one = false;
				bool equal = false;

				while( i < foundItems.size() && one == false )
				{
					if(year >= foundItems.at(i).getYear())
					{
						one = true;
						if(year == foundItems.at(i).getYear() )
							equal = true;
					}
					else
						i++;
				}

				if( equal == false ) // year > foundItems.at(i-1).getYear())	// item year newer than line year, insert
				{
					if(i == foundItems.size())
					{	
						foundItems.push_back(newItem);
					}
					else
					{
						foundItems.insert(foundItems.begin()+i, newItem);
					}
				}
				else if( equal == true ) // year == foundItems.at(i-1).getYear() )	// year is same as list item year, check month
				{
					equal = false;
					one = false;

					while( i < foundItems.size() && one == false )
					{
						if( month >= foundItems.at(i).getMonth() )
						{
							one = true;
							if( month == foundItems.at(i).getMonth() )
								equal = true;
						}
						else
							i++;
					}

					if( equal == false )	// item month newer than line month, insert
					{
						if(i == foundItems.size())
						{	
							foundItems.push_back(newItem);
						}
						else
						{
							foundItems.insert(foundItems.begin()+i, newItem);
						}
					}
					else if( equal == true ) 	// month is the same as list item month, check day
					{
						equal = false;
						one = false;

						while( i < foundItems.size() && one == false )
						{
							if( day >= foundItems.at(i).getDay() )
							{
								one = true;
							}
							else
								i++;
						}
						// item day is the same or newer than line day, insert
						if(i == foundItems.size() )
							foundItems.push_back(newItem);
						else
							foundItems.insert(foundItems.begin()+i, newItem);
					}
				}
			}
		}
	}

	if(count == 0)
	{
		cout << "Item not found in history log\n";
		searchHistoryLog(true);
		// search for a new item
	}
	else
	{
		cout << "\nLog History for item: " << itemNumber << endl;
		for(unsigned int i = 0; i < foundItems.size(); i++)
			cout << foundItems.at(i).getLogFileLine() << endl;
	}

	infile.close();
};


vector<Shipments> loadShipments(string&VendorFileSequenceID)
{
	Shipments A;
	ItemsShipped B;
	vector<Shipments> StoredDailyShipments;
	ifstream cat;
	string sLine;
	string SequenceID;
	cat.open("Vendor.txt");
	vector<char> data(sLine.begin(), sLine.end());
	string Exit;
	int numberofDash=0;

	if(cat.fail())         
       { 
		  cout<<"System Error: Unable to load Vendor Shipments File.\n";
		  cout<<"Enter 'Exit' to exit from the program.\n";
		  cin>>Exit;
		    while(Exit!="Exit"){
				   cin>>Exit;
			}
			if(Exit=="Exit")exit(0);
		}

	//getting the header
	getline(cat,sLine);

	for(int x=0;sLine.substr(x,1)!="-";x++)
	{
	A.ReceivingDate = sLine.substr(x+2);
	SequenceID=sLine.substr(1,x);
	}
	//check sequence number incorrect
	if(SequenceID!=VendorFileSequenceID)
	{
		cout<<"Vendor File sequence number incorrect."<<endl;
	}
	
	getline(cat,sLine);
	data.clear();
	for(int i=0;i<sLine.length();i++)
	{
		data.push_back(sLine[i]);
	}
	numberofDash=0;
	for(int y=0;y<data.size();y++)
	{
		if(data[y]=='-')
			numberofDash++;
	}
	

	while (numberofDash!=1)
	{
		//get vendor name, shipping date and item count
		A.VendorName= sLine.substr(0, 50);
		A.VendorShippingDate = sLine.substr(50,10);
		A.ItemCount= sLine.substr(60,1);

		//read in items ordered
		for(int x=0;x!= atoi(A.ItemCount.c_str()); x++){

		getline(cat,sLine);
		data.clear();	
		for(int i=0;i<sLine.length();i++)
		{
			data.push_back(sLine[i]);
		}
		numberofDash=0;
		for(int y=0;y<data.size();y++)
		{
			if(data[y]=='-')
			numberofDash++;
		}

		B.ItemID = sLine.substr(0,10);
		B.Warehouse = sLine.substr(11,1);
		B.Count = sLine.substr(13);
		A.ItemsShippedVector.push_back(B);

		}


		StoredDailyShipments.push_back(A);
		A.ItemsShippedVector.clear();
		getline(cat,sLine);
		
		data.clear();	
		for(int i=0;i<sLine.length();i++)
		{
			data.push_back(sLine[i]);
		}
		numberofDash=0;
		for(int y=0;y<data.size();y++)
		{
			if(data[y]=='-')
			numberofDash++;
		}

	}

	//check total number of items in trailer matches what was received
	vector<string> TEST;
	stringstream stream(sLine);
    while( getline(stream, sLine, '-') )
	{
		TEST.push_back(sLine);
	}
	if(TEST[0].substr(1)== to_string(StoredDailyShipments.size()))
	{
		cout<<"All "<<StoredDailyShipments.size()<<" vendors were processed.\n";
	}else cout<<"There was an error with the Vendor File. The Trailer number does not match the number of Vendors in the file.\n";
	if(TEST[1]== to_string(StoredDailyShipments.size()))
	{
		cout<<"All "<<StoredDailyShipments.size()<<" items shipped were processed.\n";
	}else cout<<"There was an error with the Vendor File. The Trailer number does not match the number of items shipped in the file.\n";

	return StoredDailyShipments;
}

vector<Orders> loadOrders(string&CustomerSequenceID){

	Orders A;
	ItemsOrdered B;
	vector<Orders> StoredDailyOrders;
	ifstream cat;
	string sLine;
	string SequenceID;
	string Exit;
	vector<char> data(sLine.begin(), sLine.end());
	
	int numberofDash=0;
	cat.open("Customer.txt");
	if(cat.fail())         
       { 
		  cout<<"System Error: Unable to load Customer Orders File.\n";
		  cout<<"Enter 'Exit' to exit from the program.\n";
		  cin>>Exit;
		    while(Exit!="Exit"){
				   cin>>Exit;
			}
			if(Exit=="Exit")exit(0);
	}


	//getting the header

	getline(cat,sLine);

	for(int x=0;sLine.substr(x,1)!="-";x++)
	{
	A.ShippingDate = sLine.substr(x+2);
	SequenceID=sLine.substr(1,x);
	}
	//check sequence number incorrect
	if(SequenceID!=CustomerSequenceID)
	{
		cout<<"Customer File sequence ID number incorrect."<<endl;
	}

	getline(cat,sLine);

		
	data.clear();
	for(int i=0;i<sLine.length();i++)
	{
		data.push_back(sLine[i]);
	}
	numberofDash=0;
	for(int y=0;y<data.size();y++)
	{
		if(data[y]=='-')
			numberofDash++;
	}


	//this needs to change
	while (numberofDash!=1)
	{
		//get customer type:b/p & name
		A.CustomerType= sLine.substr(0, 1);
		A.Cusomer_OR_EntityName = sLine.substr(1,60);
		
		//get address
		A.CustomerStreetAddress = sLine.substr(61,30);
		A.CustomerCity = sLine.substr(92,20);
		//include comma in the space
		A.CustomerState_OR_Province = sLine.substr(112,20);//.substr(45);
		A.CustomerPostalCode = sLine.substr(132,10);
		A.CustomerCountry = sLine.substr(142,40);

		A.OrderDate = sLine.substr(182,10);
		A.OrderItemCount = sLine.substr(192,1);
		
		//get Customer id payment discount
		getline(cat,sLine);

			
		data.clear();
			
			for(int i=0;i<sLine.length();i++)
			{
				data.push_back(sLine[i]);
			}
		numberofDash=0;
		for(int y=0;y<data.size();y++)
		{
			if(data[y]=='-')
			numberofDash++;
		}

		A.CustomerID = sLine.substr(0,10);
		A.CustomerOrderID = sLine.substr(10,10);
		A.CustomerPaymentType = sLine.substr(20,10);
		A.CustomerDiscount = sLine.substr(30,3);
		//read in items ordered
		//importans fix
		//IMPORTANT TO DISCUSS HOW TO LOOP THROUGH ITEMS
		for(int x=0;x!= atoi(A.OrderItemCount.c_str()); x++){

		getline(cat,sLine);

			
		data.clear();
			//(sLine.begin(), sLine.end());
			for(int i=0;i<sLine.length();i++)
			{
				data.push_back(sLine[i]);
			}
		numberofDash=0;
		for(int y=0;y<data.size();y++)
		{
			if(data[y]=='-')
			numberofDash++;
		}

		B.ItemID = sLine.substr(0,10);
		B.Warehouse = sLine.substr(11,1);
		B.Count = sLine.substr(13);
		A.ItemsOrderedVector.push_back(B);

		}

		StoredDailyOrders.push_back(A);
		getline(cat,sLine);
		
		data.clear();

			for(int i=0;i<sLine.length();i++)
			{
				data.push_back(sLine[i]);
			}
		numberofDash=0;
		for(int y=0;y<data.size();y++)
		{
			if(data[y]=='-')
			numberofDash++;
		}
		A.ItemsOrderedVector.clear();
	}

	//check total number of items in trailer matches what was received
	vector<string> TEST;
	stringstream stream(sLine);
    while( getline(stream, sLine, '-') )
	{
		TEST.push_back(sLine);
	}
	if(TEST[0].substr(1)== to_string(StoredDailyOrders.size()))
	{
		cout<<"All "<<StoredDailyOrders.size()<<" Customers were processed.\n";
	}else cout<<"There was an error with the Customer File. The Trailer number does not match the number of Customers in the file.\n";
	if(TEST[1]== to_string(StoredDailyOrders.size()))
	{
		cout<<"All "<<StoredDailyOrders.size()<<" items shipped were processed.\n";
	}else cout<<"There was an error with the Customer File. The Trailer number does not match the number of items ordered in the file.\n";

	return StoredDailyOrders;
}


vector<CatalogItem> loadCatalog(){
	vector<CatalogItem> Catalog;
	CatalogItem A;
	ifstream cat;
	string sLine;
	string Exit;

	cat.open("Catalog.txt");
	if(cat.fail())         
       { 
		  cout<<"System Error: Unable to load Catalog.\n";
		  cout<<"Enter 'Exit' to exit from the program.\n";
		  cin>>Exit;
		    while(Exit!="Exit"){
				   cin>>Exit;
			}
			if(Exit=="Exit")exit(0);
	}
	getline(cat,sLine);

	getline(cat,sLine);

	while (sLine.length()>11)
	{
		A.ID = sLine.substr(0, 10);

		A.itemName = sLine.substr(10,30);

		A.itemSize = sLine.substr(40,1);

		A.itemPrice = sLine.substr(41,8);

		A.itemDesc = sLine.substr(49,300);

	
		Catalog.push_back(A);
		getline(cat,sLine);
	}

	//check total number of items in trailer matches what was received
	if(sLine.substr(1)== to_string(Catalog.size()))
	{
		cout<<"All "<<Catalog.size()<<" items were processed and saved within the Catalog.\n";
	}else cout<<"There was an error with the Catalog File. The Trailer number does not match the number of items in the file.\n";

	return Catalog;
}

struct Warehouse{
	string ItemID;
	string quantity;
};


//Prototypes of functions go here:

void displayMainMenu(vector<CatalogItem>&Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3,string& OrdersFileSequenceNumber,string& ShipmentsFileSequenceNumber);

void logOut(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3,string&  OrdersFileSequenceNumber, string& ShipmentsFileSequenceNumber, vector<CatalogItem>Catalog);
void availableSpaceRemaining(vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3);
void availableSpaceRemaining_WarehouseSpaces(vector<vector<Warehouse>> Warehouse, int counter, int Size);

void inventoryValue(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1, vector<vector<Warehouse>> Warehouse2, vector<vector<Warehouse>> Warehouse3,string OrdersFileSequenceNumber,string ShipmentsFileSequenceNumber);
void itemInformationDisplay(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse1, vector<vector<Warehouse>>& Warehouse2, vector<vector<Warehouse>>& Warehouse3,string& OrdersFileSequenceNumber,string& ShipmentsFileSequenceNumber);

void itemInventoryDisplay(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3,string& OrdersFileSequenceNumber,string& ShipmentsFileSequenceNumber);
void itemInventoryDisplay_WarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3);
bool itemInventoryDisplay_testCatalog(vector<CatalogItem>Catalog, string ItemId, string ItemSize);

void showWarehouseContents(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3, string OrdersFileSequenceNumber,string ShipmentsFileSequenceNumber);
void showWarehouseContents_ShowCatalogInfo(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse, string ItemID, string quantity, int location);

void editItemCatalog(vector<CatalogItem>& Catalog, vector<vector<Warehouse>> Warehouse1, vector<vector<Warehouse>> Warehouse2, vector<vector<Warehouse>> Warehouse3, bool first);
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
	string Exit;

	cat.open("WarehouseStatus.txt");
	if(cat.fail())         
       { 
		  cout<<"System Error: Unable to load Warehouse Status.\n";
		  cout<<"Enter 'Exit' to exit from the program.\n";
		  cin>>Exit;
		    while(Exit!="Exit"){
				   cin>>Exit;
			}
			if(Exit=="Exit")exit(0);
	}

	getline(cat,sLine);
	OrdersFileSequenceNumber= sLine.substr(27);

	getline(cat,sLine);
	ShipmentsFileSequenceNumber= sLine.substr(29);

	getline(cat,sLine);

	while(sLine!="Warehouse 2:")
	{
		
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
	
	ColumnLarge.clear();
	ColumnMedium.clear();
	ColumnSmall.clear();

	while(sLine!="Warehouse 3:")
	{
		
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
	Warehouse2.push_back(ColumnSmall);
	Warehouse2.push_back(ColumnMedium);
	Warehouse2.push_back(ColumnLarge);
	

	ColumnLarge.clear();
	ColumnMedium.clear();
	ColumnSmall.clear();

	getline(cat,sLine);
	
	while(!cat.eof())
	{
		
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
			
			return true;
		}
	}
	//item not valid
	return false;
}

void CreateInvoice(vector<Orders> &StoredDailyOrders, vector<CatalogItem> Catalog)
{
	ofstream outputFile;
	outputFile.open("Invoice.txt");

		for(int x=0; x<StoredDailyOrders.size();x++)
	{
		float subtotal=0;
		outputFile<<StoredDailyOrders[x].CustomerID<<endl;
		outputFile<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
		outputFile<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
		outputFile<<StoredDailyOrders[x].CustomerCity<<" "<<StoredDailyOrders[x].CustomerState_OR_Province<<" "<<StoredDailyOrders[x].CustomerPostalCode<<endl;
		outputFile<<endl;
		outputFile<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
		outputFile<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
		outputFile<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
		outputFile<<"Shipping Date:\t"<<StoredDailyOrders[x].ShippingDate<<endl;
		outputFile<<"Payment Type:\t"<<StoredDailyOrders[x].CustomerPaymentType<<endl;
		outputFile<<endl;
		outputFile<<"Item ID\t\tItem Name\t\t\tQuantity\tPrice\tItem Total"<<endl;
		outputFile<<"____________________________________________________________"<<endl;
		for(int y=0;y<StoredDailyOrders[x].ItemsOrderedVector.size();y++){
			outputFile<<StoredDailyOrders[x].ItemsOrderedVector[y].ItemID<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[y].ItemName<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<"\t$"<<StoredDailyOrders[x].ItemsOrderedVector[y].ItemCost;
			for (int m=0;m<StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.size();m++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations[m].LocationFound=="BACKORDERED" | StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations[m].LocationFound=="Invalid Item")
				{ 
					outputFile<<" "<<StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations[m].LocationFound<<endl;
				}
				else{
					double itemTotal=atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str())*atoi(StoredDailyOrders[x].ItemsOrderedVector[y].ItemCost.c_str());
				outputFile<<" $"<<itemTotal<<endl;
				subtotal=subtotal+atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str())*atoi(StoredDailyOrders[x].ItemsOrderedVector[y].ItemCost.c_str());
				break;
				}
			}

		}
		string decdiscount="."+StoredDailyOrders[x].CustomerDiscount;
		
		double Discount=subtotal*stof(decdiscount);
		
		double OrderTotal=subtotal-Discount;
		double Tax=OrderTotal*.06;
		double AmountDue=OrderTotal+Tax;
		outputFile<<endl;
		outputFile<<"Subtotal\t\t\t\t\t\t\t\t $ "<<subtotal<<endl;
		outputFile<<"\t\t\t\t\t\t\t\t\t ============"<<endl;
		outputFile<<"Discount Percentage-"<<StoredDailyOrders[x].CustomerDiscount<<"%"<<"\t\t\t\t\t- $ "<<Discount<<endl;
		outputFile<<"\t\t\t\t\t\t\t\t\t ============"<<endl;
		outputFile<<"Order total\t\t\t\t\t\t\t"<<"  $"<<OrderTotal<<endl;
		outputFile<<"Tax    6%\t\t\t\t\t\t\t\t"<<"+ $"<<Tax<<endl;
		outputFile<<"\t\t\t\t\t\t\t\t\t ============"<<endl;
		outputFile<<"AMOUNT DUE in "<<StoredDailyOrders[x].CustomerPaymentType<<"\t\t\t\t\t"<<"$ "<<AmountDue<<endl;
		
		
		outputFile<<endl;
	}


	return;
}

void CreatePackingSlip(vector<Orders> &StoredDailyOrders, vector<CatalogItem> Catalog)
{
	ofstream outputFile;
	outputFile.open("PackingSlip.txt");
	bool W1=false;
	bool W2=false;
	bool W3=false;
	
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

			outputFile<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
			outputFile<<"Customer Name and Address:"<<endl;
			outputFile<<StoredDailyOrders[x].CustomerID<<endl;
			outputFile<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
			outputFile<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
			outputFile<<StoredDailyOrders[x].CustomerCity<<StoredDailyOrders[x].CustomerState_OR_Province<<StoredDailyOrders[x].CustomerPostalCode<<" "<<StoredDailyOrders[x].CustomerCountry<<endl;
			outputFile<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
			outputFile<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
			outputFile<<"Shipping Date:\t"<<StoredDailyOrders[x].ShippingDate<<endl;

			outputFile<<"Item ID\t Item Name\t\t Warehouse 1 Location\t Quantity\n";
			outputFile<<"_____________________________________________________________\n";
			for(int k=0;k<StoredDailyOrders[x].ItemsOrderedVector.size();k++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[k].Warehouse=="1")
				{
					itemCount++;
				outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemID<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemName<<"\t";
				if(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()==1)
				{
					outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[0].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].Count<<endl;
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());

				}
				else{
					int TOTAL=atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());
					int newTOT=TOTAL;
					
				for(int t=0;t<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;t++)
				{
					outputFile<<""<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count<<endl<<"";
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
					newTOT=newTOT- atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
				}
				int lastplace=StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;
				pickedCount=pickedCount+newTOT;
				outputFile<<"\t\t\t\t\t\t\t\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[lastplace].LocationFound<<"\t"<<newTOT<<"\n";
				outputFile<<"\t\t\t\t\t\t\t\tTOTAL\t"<<TOTAL<<endl;
				}
			}
			}
			outputFile<<itemCount<<" Item(s)\t"<<pickedCount<<" Quantity Picked\n";
			outputFile<<endl<<endl;
		}
		if(W2==true)
		{
			int itemCount=0;
			int pickedCount=0;
			outputFile<<endl<<endl<<endl;
			outputFile<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
			outputFile<<"Customer Name and Address:"<<endl;
			outputFile<<StoredDailyOrders[x].CustomerID<<endl;
			outputFile<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
			outputFile<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
			outputFile<<StoredDailyOrders[x].CustomerCity<<StoredDailyOrders[x].CustomerState_OR_Province<<StoredDailyOrders[x].CustomerPostalCode<<" "<<StoredDailyOrders[x].CustomerCountry<<endl;
			outputFile<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
			outputFile<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
			outputFile<<"Shipping Date:\t"<<StoredDailyOrders[x].ShippingDate<<endl;

			outputFile<<"Item ID\t Item Name\t\t Warehouse 2 Location\t Quantity\n";
			outputFile<<"______________________________________________________________\n";
			for(int k=0;k<StoredDailyOrders[x].ItemsOrderedVector.size();k++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[k].Warehouse=="2")
				{
					itemCount++;
				outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemID<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemName<<"\t";
				if(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()==1)
				{
					outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[0].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].Count<<endl;
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());

				}
				else{
					int TOTAL=atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());
					int newTOT=TOTAL;
					
				for(int t=0;t<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;t++)
				{
					outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count<<endl<<"\t\t\t";
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
					newTOT=newTOT- atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
				}
				int lastplace=StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;
				pickedCount=pickedCount+newTOT;
				outputFile<<"\t\t\t\t\t\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[lastplace].LocationFound<<"\t"<<newTOT<<"\n";
				outputFile<<"\t\t\t\t\t\t\t\t\tTOTAL\t"<<TOTAL<<endl;
				}
			}
			}
			outputFile<<itemCount<<" Item(s)\t"<<pickedCount<<" Quantity Picked\n";
			outputFile<<endl<<endl;
		}
		if(W3==true)
		{
			int itemCount=0;
			int pickedCount=0;
		
			outputFile<<"Customer ID:\t"<<StoredDailyOrders[x].CustomerID<<endl;
			outputFile<<"Customer Name and Address:"<<endl;
			outputFile<<StoredDailyOrders[x].CustomerID<<endl;
			outputFile<<StoredDailyOrders[x].Cusomer_OR_EntityName<<endl;
			outputFile<<StoredDailyOrders[x].CustomerStreetAddress<<endl;
			outputFile<<StoredDailyOrders[x].CustomerCity<<StoredDailyOrders[x].CustomerState_OR_Province<<StoredDailyOrders[x].CustomerPostalCode<<" "<<StoredDailyOrders[x].CustomerCountry<<endl;
			outputFile<<"Order ID:\t"<<StoredDailyOrders[x].CustomerOrderID<<endl;
			outputFile<<"Order Date:\t"<<StoredDailyOrders[x].OrderDate<<endl;
			outputFile<<"Shipping Date:\t"<<StoredDailyOrders[x].ShippingDate<<endl;

			outputFile<<"Item ID\t Item Name\t\t Warehouse 3 Location\t Quantity\n";
			outputFile<<"_______________________________________________________________\n";
			for(int k=0;k<StoredDailyOrders[x].ItemsOrderedVector.size();k++)
			{
				if(StoredDailyOrders[x].ItemsOrderedVector[k].Warehouse=="3")
				{
					itemCount++;
				outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemID<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].ItemName<<"\t";
				if(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()==1)
				{
					outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[0].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].Count<<endl;
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());

				}
				else{
					int TOTAL=atoi(StoredDailyOrders[x].ItemsOrderedVector[k].Count.c_str());
					int newTOT=TOTAL;
				
				for(int t=0;t<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;t++)
				{
					outputFile<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].LocationFound<<"\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count<<endl<<"\t\t\t";
					pickedCount=pickedCount+atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
					newTOT=newTOT- atoi(StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[t].Count.c_str());
				}
				int lastplace=StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations.size()-1;
				pickedCount=pickedCount+newTOT;
				outputFile<<"\t\t\t\t\t\t"<<StoredDailyOrders[x].ItemsOrderedVector[k].MultipleLocations[lastplace].LocationFound<<"\t"<<newTOT<<"\n";
				outputFile<<"\t\t\t\t\t\t\t\t\tTOTAL\t"<<TOTAL<<endl;
				}
			}
			}
			outputFile<<itemCount<<" Item(s)\t"<<pickedCount<<" Quantity Picked\n";
			outputFile<<endl<<endl;
		}
	}
}

void ProcessOrders(vector<CatalogItem>&Catalog, vector<Orders>& StoredDailyOrders,vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3)
{
	ofstream outputFile;
	outputFile.open("Backorders.txt");
	ItemsOrdered A;
	string ItemSize;
	for(int x=0;x<StoredDailyOrders.size();x++)
	{
		for(int y=0; y<StoredDailyOrders[x].ItemsOrderedVector.size();y++)
		{   
			int AmountSoFar=0;
			
			//Check Catalog for legal item ordered
			string ID=StoredDailyOrders[x].ItemsOrderedVector[y].ItemID;
			if(SearchCatalog(Catalog,ID, ItemSize, StoredDailyOrders, x, y)==false)
			{
				cout<<"This item is not found in the Catalog and hence is not available at any of the Warehouses."<<endl;
				StoredDailyOrders[x].ItemsOrderedVector[y].LocationFound="Invalid Item";
			}
		
			string WNum=StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse;
			int AmountLeft= atoi(StoredDailyOrders[x].ItemsOrderedVector[y].Count.c_str());
			
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
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse1[0][k].quantity.c_str());

							if(AmountOrdered<AmountAvailable)
							{
								Warehouse1[0][k].quantity=to_string(atoi(Warehouse1[0][k].quantity.c_str())-AmountOrdered);
								
								AddToLogFile(Warehouse1[0][k].ItemID, "Warehouse 1",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
								
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
								AddToLogFile(Warehouse1[1][k].ItemID, "Warehouse 1",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
							
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse1[2][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								AddToLogFile(Warehouse1[2][k].ItemID, "Warehouse 1",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse2[0][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								AddToLogFile(Warehouse2[0][k].ItemID, "Warehouse 2",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
								AddToLogFile(Warehouse2[1][k].ItemID, "Warehouse 2",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse2[2][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								AddToLogFile(Warehouse2[2][k].ItemID, "Warehouse 2",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse3[0][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								AddToLogFile(Warehouse3[0][k].ItemID, "Warehouse 3",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
								AddToLogFile(Warehouse3[1][k].ItemID, "Warehouse 3",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
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
							StoredDailyOrders[x].ItemsOrderedVector[y].MultipleLocations.push_back(A);
							AmountAvailable=AmountAvailable+ atoi( Warehouse3[2][k].quantity.c_str());
							if(AmountOrdered<AmountAvailable)
							{
								AddToLogFile(Warehouse3[2][k].ItemID, "Warehouse 3",to_string(AmountOrdered), "OUT", StoredDailyOrders[x].OrderDate);
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
							cout<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Insufficient amount of item number "<< ID<<" on hand for the order.\n";
							outputFile<<"Customer ID: "<<StoredDailyOrders[x].CustomerID<<endl;
							outputFile<<ID<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Warehouse<<"-"<<StoredDailyOrders[x].ItemsOrderedVector[y].Count<<endl;
					}
					//delete empty spaces
					for(int l=0;l<Warehouse3.at(2).size();l++)
					{
						if(Warehouse3[2][l].quantity == "0") Warehouse3[2].erase(Warehouse3[2].begin() +l);
					}		
				}
			}

		}

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
			bool Store=false;
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
						
							//check if it can all fill in the same small spot;
							if((atoi(Warehouse1[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<250)
							{
								int NewQuant=atoi(Warehouse1[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse1[0][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse1[0][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
							}

							else if(Warehouse1.at(0).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=(AmountLeft/250)+1;
								int SpacesLeft= 20 - (Warehouse1.at(0).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse1[0][k].quantity = to_string(atoi(Warehouse1[0][k].quantity.c_str())+HowManyToFillLocation1);
									AddToLogFile(Warehouse1[0][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								while(AmountLeft>250)
								{
									Warehouse A;
									A.quantity="250";
									A.ItemID=ID;
									AmountLeft=AmountLeft-250;
									Warehouse1[0].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse1[0].push_back(A);
									k=Warehouse1.at(0).size();
									Store=true;
								}
								else cout<<"Insufficient space for "<<Warehouse1[0][k].ItemID<<"in Warehouse 1.\n";//fix this

						}
							else cout<<"Insufficient space for "<<Warehouse1[0][k].ItemID<<"in Warehouse 1.\n";//fix this
						} 
					}
					if (Store!=true)
							{
							if(k==Warehouse1.at(0).size() && Warehouse1.at(0).size()<20)
							{
								//AddToLogFile(Warehouse1[0][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/250;
								int SpacesLeft= 20 - (Warehouse1.at(0).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
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
									AddToLogFile(ID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
									Store=true;
								}
							}


							}
					}else if(itemSize=="M")
					{
					for(;k<Warehouse1.at(1).size();k++)
					{
						if(Warehouse1[1][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=100-atoi(Warehouse1[1][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse1[1][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<100)
							{
								int NewQuant=atoi(Warehouse1[1][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse1[1][k].quantity=to_string(NewQuant);
								Store= true;
								AddToLogFile(Warehouse1[1][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
							}

							else if(Warehouse1.at(1).size()<60)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/100;
								int SpacesLeft= 60 - (Warehouse1.at(1).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse1[1][k].quantity = to_string(atoi(Warehouse1[1][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>100)
								{
									Warehouse A;
									A.quantity="100";
									A.ItemID=ID;
									AmountLeft=AmountLeft-100;
									Warehouse1[1].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse1[1].push_back(A);
									k=Warehouse1.at(1).size();
									Store=true;
									AddToLogFile(Warehouse1[1][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
									
								}
								else cout<<"Insufficient space for "<<Warehouse1[1][k].ItemID<<"in Warehouse 1.\n";

						}
							else cout<<"Insufficient space for "<<Warehouse1[1][k].ItemID<<"in Warehouse 1.\n";
						}
					}
						if (Store!=true)
							{
							if(k==Warehouse1.at(1).size() && Warehouse1.at(1).size()<60)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/100;
								int SpacesLeft= 60 - (Warehouse1.at(1).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>100)
									{
									Warehouse A;
									A.quantity="100";
									A.ItemID=ID;
									AmountLeft=AmountLeft-100;
									Warehouse1[1].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse1[1].push_back(A);
									k=Warehouse1.at(1).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								}
							}
							}
					}
					else if(itemSize=="L")
					{
					for(;k<Warehouse1.at(2).size();k++)
					{
						if(Warehouse1[2][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=100-atoi(Warehouse1[2][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse1[2][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<10)
							{
								int NewQuant=atoi(Warehouse1[2][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse1[2][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse1[2][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse1.at(2).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/10;
								int SpacesLeft= 20 - (Warehouse1.at(2).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse1[2][k].quantity = to_string(atoi(Warehouse1[2][k].quantity.c_str())+HowManyToFillLocation1);
									Store=true;
									
								while(AmountLeft>10)
								{
									Warehouse A;
									A.quantity="10";
									A.ItemID=ID;
									AmountLeft=AmountLeft-10;
									Warehouse1[2].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse1[2].push_back(A);
									k=Warehouse1.at(2).size();
									Store=true;
									AddToLogFile(Warehouse1[2][k].ItemID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
									
								}
								else cout<<"Insufficient space for "<<Warehouse1[2][k].ItemID<<"in Warehouse 1.\n";
						}
							else cout<<"Insufficient space for "<<Warehouse1[2][k].ItemID<<"in Warehouse 1.\n";
						}
					}
						if (Store!=true)
							{
							if(k==Warehouse1.at(2).size() && Warehouse1.at(2).size()<20)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/10;
								int SpacesLeft= 20 - (Warehouse1.at(2).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>10)
									{
									Warehouse A;
									A.quantity="10";
									A.ItemID=ID;
									AmountLeft=AmountLeft-10;
									Warehouse1[2].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse1[2].push_back(A);
									k=Warehouse1.at(2).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 1",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
							}
							}
					}
				}else if(WarehouseID=="2")
				{
					if(itemSize=="S")
					{
					for(;k<Warehouse2.at(0).size();k++)
					{
						if(Warehouse2[0][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=250-atoi(Warehouse2[0][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse2[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<250)
							{
								int NewQuant=atoi(Warehouse2[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse2[0][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse2[0][k].ItemID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse2.at(0).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/250;
								int SpacesLeft= 20 - (Warehouse2.at(0).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse2[0][k].quantity = to_string(atoi(Warehouse2[0][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>250)
								{
									Warehouse A;
									A.quantity="250";
									A.ItemID=ID;
									AmountLeft=AmountLeft-250;
									Warehouse2[0].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse2[0].push_back(A);
									k=Warehouse2.at(0).size();
									Store=true;
									AddToLogFile(Warehouse2[0][k].ItemID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
									
								}
								else cout<<"Insufficient space for "<<Warehouse2[0][k].ItemID<<"in Warehouse 2.\n";

						}
							else cout<<"Insufficient space for "<<Warehouse2[0][k].ItemID<<"in Warehouse 2.\n";

						}

					}
						if (Store!=true)
							{
							if(k==Warehouse2.at(0).size() && Warehouse2.at(0).size()<20)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/250;
								int SpacesLeft= 20 - (Warehouse2.at(0).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>250)
									{
									Warehouse A;
									A.quantity="250";
									A.ItemID=ID;
									AmountLeft=AmountLeft-250;
									Warehouse2[0].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse2[0].push_back(A);
									k=Warehouse2.at(0).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								

								}
							}

							}
					}else if(itemSize=="M")
					{
					for(;k<Warehouse2.at(1).size();k++)
					{


						if(Warehouse2[1][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=100-atoi(Warehouse2[1][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse2[1][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<100)
							{
								int NewQuant=atoi(Warehouse2[1][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse2[1][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(ID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse2.at(1).size()<60)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/100;
								int SpacesLeft= 60 - (Warehouse2.at(1).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse2[1][k].quantity = to_string(atoi(Warehouse2[1][k].quantity.c_str())+HowManyToFillLocation1);
									Store=true;
								while(AmountLeft>100)
								{
									Warehouse A;
									A.quantity="100";
									A.ItemID=ID;
									AmountLeft=AmountLeft-100;
									Warehouse2[1].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse2[1].push_back(A);
									k=Warehouse2.at(1).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
									
								}
								else cout<<"Insufficient space for "<<Warehouse2[1][k].ItemID<<"in Warehouse 2.\n";

						}
							else cout<<"Insufficient space for "<<Warehouse2[1][k].ItemID<<"in Warehouse 2.\n";
						}
					}

							if (Store!=true)
							{
							if(k==Warehouse2.at(1).size() && Warehouse2.at(1).size()<60)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/100;
								int SpacesLeft= 60 - (Warehouse2.at(1).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>100)
									{
									Warehouse A;
									A.quantity="100";
									A.ItemID=ID;
									AmountLeft=AmountLeft-100;
									Warehouse2[1].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse2[1].push_back(A);
									k=Warehouse2.at(1).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
							}

							}

					}
					else if(itemSize=="L")
					{
					for(;k<Warehouse2.at(2).size();k++)
					{

						if(Warehouse2[2][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=100-atoi(Warehouse2[2][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse2[2][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<10)
							{
								int NewQuant=atoi(Warehouse2[2][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse2[2][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse2[2][k].ItemID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse2.at(2).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/10;
								int SpacesLeft= 20 - (Warehouse2.at(2).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse2[2][k].quantity = to_string(atoi(Warehouse2[2][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>10)
								{
									Warehouse A;
									A.quantity="10";
									A.ItemID=ID;
									AmountLeft=AmountLeft-10;
									Warehouse2[2].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse2[2].push_back(A);
									k=Warehouse2.at(2).size();
									Store=true;
									AddToLogFile(Warehouse2[2][k].ItemID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
									
								}
								else cout<<"Insufficient space for "<<Warehouse2[2][k].ItemID<<"in Warehouse 2.\n";
						}
							else cout<<"Insufficient space for "<<Warehouse2[2][k].ItemID<<"in Warehouse 2.\n";

						}

					}
					
						if (Store!=true)
							{
							if(k==Warehouse2.at(2).size() && Warehouse2.at(2).size()<20)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/10;
								int SpacesLeft= 20 - (Warehouse2.at(2).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>10)
									{
									Warehouse A;
									A.quantity="10";
									A.ItemID=ID;
									AmountLeft=AmountLeft-10;
									Warehouse2[2].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse2[2].push_back(A);
									k=Warehouse2.at(2).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 2",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
							}
						}
					}
				}if(WarehouseID=="3")
				{
					if(itemSize=="S")
					{
					for(;k<Warehouse3.at(0).size();k++)
					{
						if(Warehouse3[0][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=250-atoi(Warehouse3[0][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse3[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<250)
							{
								int NewQuant=atoi(Warehouse3[0][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse3[0][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse3[0][k].ItemID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse3.at(0).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/250;
								int SpacesLeft= 20 - (Warehouse3.at(0).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse3[0][k].quantity = to_string(atoi(Warehouse3[0][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>250)
								{
									Warehouse A;
									A.quantity="250";
									A.ItemID=ID;
									AmountLeft=AmountLeft-250;
									Warehouse3[0].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse3[0].push_back(A);
									k=Warehouse3.at(0).size();
									Store=true;
									//y++;
									//AddToLogFile(Warehouse3[0][k].ItemID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
								else cout<<"Insufficient space for "<<Warehouse3[0][k].ItemID<<"in Warehouse 3.\n";

						}
							else cout<<"Insufficient space for "<<Warehouse3[0][k].ItemID<<"in Warehouse 3.\n";

						}
					}
							if (Store!=true)
							{
							if(k==Warehouse3.at(0).size() && Warehouse3.at(0).size()<20)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/250;
								int SpacesLeft= 20 - (Warehouse3.at(0).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>250)
									{
									Warehouse A;
									A.quantity="250";
									A.ItemID=ID;
									AmountLeft=AmountLeft-250;
									Warehouse3[0].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse3[0].push_back(A);
									k=Warehouse3.at(0).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
							}
							}
					}
					else if(itemSize=="M")
					{
					for(;k<Warehouse3.at(1).size();k++)
					{


						if(Warehouse3[1][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=100-atoi(Warehouse3[1][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse3[1][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<100)
							{
								int NewQuant=atoi(Warehouse3[1][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse3[1][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse3[1][k].ItemID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse3.at(1).size()<60)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/100;
								int SpacesLeft= 60 - (Warehouse3.at(3).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse3[1][k].quantity = to_string(atoi(Warehouse3[1][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>100)
								{
									Warehouse A;
									A.quantity="100";
									A.ItemID=ID;
									AmountLeft=AmountLeft-100;
									Warehouse3[1].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse3[1].push_back(A);
									k=Warehouse3.at(1).size();
									Store=true;
									AddToLogFile(Warehouse3[1][k].ItemID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
									
								}
								else cout<<"Insufficient space for "<<Warehouse3[1][k].ItemID<<"in Warehouse 3.\n";

						}
							else cout<<"Insufficient space for "<<Warehouse3[1][k].ItemID<<"in Warehouse 3.\n";

						}

					}
					if(Store!=true)
					{
					if(k==Warehouse3.at(1).size() && Warehouse3.at(1).size()<60)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/100;
								int SpacesLeft= 60 - (Warehouse3.at(1).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>100)
									{
									Warehouse A;
									A.quantity="100";
									A.ItemID=ID;
									AmountLeft=AmountLeft-100;
									Warehouse3[1].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse3[1].push_back(A);
									k=Warehouse3.at(1).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
							}

					}
					}
					else if(itemSize=="L")
					{
					for(;k<Warehouse3.at(2).size();k++)
					{


						if(Warehouse3[2][k].ItemID==ID)
						{
							//for multiple location fills
							int HowManyToFillLocation1=100-atoi(Warehouse3[2][k].quantity.c_str());	
							int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
						
							if((atoi(Warehouse3[2][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str()))<10)
							{
								int NewQuant=atoi(Warehouse3[2][k].quantity.c_str())+atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());
								Warehouse3[2][k].quantity=to_string(NewQuant);
								Store=true;
								AddToLogFile(Warehouse3[2][k].ItemID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
							}

							else if(Warehouse3.at(2).size()<20)
							{
								AmountLeft=AmountLeft-HowManyToFillLocation1;
								int HowManySpacesDoINeed=AmountLeft/10;
								int SpacesLeft= 20 - (Warehouse3.at(2).size());
								
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									Warehouse3[2][k].quantity = to_string(atoi(Warehouse3[2][k].quantity.c_str())+HowManyToFillLocation1);
									
								while(AmountLeft>10)
								{
									Warehouse A;
									A.quantity="10";
									A.ItemID=ID;
									AmountLeft=AmountLeft-10;
									Warehouse3[2].push_back(A);
									Store=true;
								}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse3[2].push_back(A);
									k=Warehouse3.at(2).size();
									Store=true;
									AddToLogFile(Warehouse3[2][k].ItemID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
								else cout<<"Insufficient space for "<<Warehouse3[2][k].ItemID<<"in Warehouse 3.\n";
						}
							else cout<<"Insufficient space for "<<Warehouse3[2][k].ItemID<<"in Warehouse 3.\n";

						}

					}
					
						if (Store!=true)
							{
							if(k==Warehouse3.at(2).size() && Warehouse3.at(2).size()<20)
							{
								int AmountLeft=atoi(StoredDailyShipments[x].ItemsShippedVector[y].Count.c_str());//amount remaining to put away
								int HowManySpacesDoINeed=AmountLeft/10;
								int SpacesLeft= 20 - (Warehouse3.at(2).size());
								if(HowManySpacesDoINeed<SpacesLeft)
								{
									while(AmountLeft>10)
									{
									Warehouse A;
									A.quantity="10";
									A.ItemID=ID;
									AmountLeft=AmountLeft-10;
									Warehouse3[2].push_back(A);
									Store=true;
									}
									Warehouse A;
									A.quantity=to_string(AmountLeft);
									AmountLeft=0;
									A.ItemID=ID;
									Warehouse3[2].push_back(A);
									k=Warehouse3.at(2).size();
									Store=true;
									AddToLogFile(ID, "Warehouse 3",StoredDailyShipments[x].ItemsShippedVector[y].Count, "IN", StoredDailyShipments[x].VendorShippingDate);
								
								}
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

	SetUpWarehouses(Warehouse1, Warehouse2, Warehouse3, OrdersFileSequenceNumber, ShipmentsFileSequenceNumber);
	vector<Orders> StoredDailyOrders = loadOrders(OrdersFileSequenceNumber);
	
	vector<Shipments> StoredDailyShipments = loadShipments(ShipmentsFileSequenceNumber);


	ProcessOrders(Catalog, StoredDailyOrders, Warehouse1, Warehouse2, Warehouse3);

	ProcessShipments(Catalog, StoredDailyShipments, Warehouse1, Warehouse2, Warehouse3);
	

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


	//Initialize Catalog
	//Initialize Warehouse
	//Order Processing
	//Shipment Processing


	displayMainMenu(Catalog,Warehouse1,Warehouse2,Warehouse3, OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);// call the main menu function

	return 0;
}


//Program functions go here:
void displayMainMenu(vector<CatalogItem>&Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3, string&OrdersFileSequenceNumber,string& ShipmentsFileSequenceNumber) {//main menu willdisplay to the user which options they have to choose from
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
		displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
	}

	//if the input is actally one of the inputs then do that functionality
		if (menuResponse == 0){
			logOut(Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber, ShipmentsFileSequenceNumber, Catalog);
		}

		else if (menuResponse == 1){
			availableSpaceRemaining(Warehouse1,Warehouse2,Warehouse3);
		}

		else if (menuResponse == 2){
			inventoryValue(Catalog,Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}

		else if (menuResponse == 3){
			searchHistoryLog(true);
		}
		else if (menuResponse == 4){
			itemInformationDisplay(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
		else if (menuResponse == 5){
			itemInventoryDisplay(Catalog, Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
		else if (menuResponse == 6){
			showWarehouseContents(Catalog, Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
		else if (menuResponse == 7){
			editItemCatalog(Catalog, Warehouse1, Warehouse2, Warehouse3, true);
		}
		else if (menuResponse == 8){
			cout << "\nTo add a new user, contact Gold Stars."<<endl;
			displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
		else//Any other number input will be invalid.
			cout<<"Error: Invalid input, please try again."<<endl<<endl;
			displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);

}

void logOut(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3,string& OrdersFileSequenceNumber, string& ShipmentsFileSequenceNumber, vector<CatalogItem>Catalog)
{
	ofstream outputFile;
	outputFile.open("WarehouseStatus.txt");
	int OrdersFileSequenceNumberINT= atoi(OrdersFileSequenceNumber.c_str());//++;
	int ShipmentsFileSequenceNumberINT=atoi(ShipmentsFileSequenceNumber.c_str());//++;
	
	OrdersFileSequenceNumberINT++;
	ShipmentsFileSequenceNumberINT++;

	outputFile<<"OrdersFileSequenceNumber = "<<OrdersFileSequenceNumberINT<<endl;
	outputFile<<"ShipmentFileSequenceNumber = "<<ShipmentsFileSequenceNumberINT<<endl;
	outputFile<<"Warehouse 1:"<<endl;
	for(int x=0;x<20;x++)
	{
		if(Warehouse1[0][x].ItemID.length()>0)outputFile<<"S"<<Warehouse1[0][x].ItemID<<Warehouse1[0][x].quantity<<endl;
	}
	for(int x=0;x<60;x++)
	{
		if(Warehouse1[1][x].ItemID.length()>0)outputFile<<"M"<<Warehouse1[1][x].ItemID<<Warehouse1[1][x].quantity<<endl;
	}
	for(int x=0;x<20;x++)
	{
		if(Warehouse1[2][x].ItemID.length()>0)outputFile<<"L"<<Warehouse1[2][x].ItemID<<Warehouse1[2][x].quantity<<endl;
	}
	outputFile<<"Warehouse 2:"<<endl;
	for(int x=0;x<20;x++)
	{
		if(Warehouse2[0][x].ItemID.length()>0)outputFile<<"S"<<Warehouse2[0][x].ItemID<<Warehouse2[0][x].quantity<<endl;
	}
	for(int x=0;x<60;x++)
	{
		if(Warehouse2[1][x].ItemID.length()>0)outputFile<<"M"<<Warehouse2[1][x].ItemID<<Warehouse2[1][x].quantity<<endl;
	}
	for(int x=0;x<20;x++)
	{
		if(Warehouse2[2][x].ItemID.length()>0)outputFile<<"L"<<Warehouse2[2][x].ItemID<<Warehouse2[2][x].quantity<<endl;
	}
	outputFile<<"Warehouse 3:"<<endl;
	for(int x=0;x<20;x++)
	{
		if(Warehouse3[0][x].ItemID.length()>0)outputFile<<"S"<<Warehouse3[0][x].ItemID<<Warehouse3[0][x].quantity<<endl;
	}
	for(int x=0;x<60;x++)
	{
		if(Warehouse3[1][x].ItemID.length()>0)outputFile<<"M"<<Warehouse3[1][x].ItemID<<Warehouse3[1][x].quantity<<endl;
	}
	for(int x=0;x<20;x++)
	{
		if(Warehouse3[2][x].ItemID.length()>0)outputFile<<"L"<<Warehouse3[2][x].ItemID<<Warehouse3[2][x].quantity<<endl;
	}
	outputFile.close();
	
	outputFile.open("Catalog.txt");
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	outputFile<<"H"<< (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'<<  now->tm_mday<< endl;
	for (int x=0;x<Catalog.size();x++)
	{
		outputFile<<Catalog[x].ID<<Catalog[x].itemName<<Catalog[x].itemSize<<Catalog[x].itemPrice<<Catalog[x].itemDesc<<endl;
	}
	outputFile<<"T"<<Catalog.size()<<endl;
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

void inventoryValue(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1, vector<vector<Warehouse>> Warehouse2, vector<vector<Warehouse>> Warehouse3,string OrdersFileSequenceNumber,string ShipmentsFileSequenceNumber){//(EXTRA FUNCTIONALITY:FERIQUE) displays the total value of all the items in the warehouses.
	float W1Qty[100], W1Price[100], W2Qty[100], W2Price[100], W3Qty[100], W3Price[100];
	float MTemp = 0, LTemp = 0, STemp = 0, W1Small = 0, W1Med = 0, W1Large = 0, W2Small = 0, W2Med = 0, W2Large = 0, W3Small = 0, W3Med = 0, W3Large = 0, Value1 = 0, Value2 = 0, Value3 = 0, W1Total = 0, W2Total = 0, W3Total = 0, GrandTotal = 0;
	string tempID, temp;
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
					if (Catalog[x].itemSize == "S")
					{
						STemp = W1Qty[j] * W1Price[j];
						W1Small = STemp + W1Small;
					}
					if (Catalog[x].itemSize == "M")
					{
						MTemp = W1Qty[j] * W1Price[j];
						W1Med = W1Med + MTemp;
					}
					if (Catalog[x].itemSize == "L")
					{
						LTemp = W1Qty[j] * W1Price[j];
						W1Large = W1Large + LTemp;
					}
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Warehouse2.size(); j++)
		{
			tempID = Warehouse2[i][j].ItemID;
			W2Qty[j] = atoi(Warehouse2[i][j].quantity.c_str());
			for (int x = 0; x < Catalog.size(); x++)
			{
				if (tempID == Catalog[x].ID)
				{
					W2Price[j] = atoi(Catalog[x].itemPrice.c_str());
					Value2 = W2Qty[j] * W2Price[j];
					W2Total = Value2 + W2Total;
					if (Catalog[x].itemSize == "S")
					{
						STemp = W2Qty[j] * W2Price[j];
						W2Small = STemp + W2Small;
					}
					if (Catalog[x].itemSize == "M")
					{
						MTemp = W2Qty[j] * W2Price[j];
						W2Med = W2Med + MTemp;
					}
					if (Catalog[x].itemSize == "L")
					{
						LTemp = W2Qty[j] * W2Price[j];
						W2Large = W2Large + LTemp;
					}

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
					if (Catalog[x].itemSize == "S")
					{
						STemp = W3Qty[j] * W3Price[j];
						W3Small = STemp + W3Small;
					}
					if (Catalog[x].itemSize == "M")
					{
						MTemp = W3Qty[j] * W3Price[j];
						W3Med = W3Med + MTemp;
					}
					if (Catalog[x].itemSize == "L")
					{
						LTemp = W3Qty[j] * W3Price[j];
						W3Large = W3Large + LTemp;
					}
				}
			}
		}
	}
	GrandTotal = W1Total + W2Total + W3Total;  // Totals all the ware houses.
	cout << " ========================================" << endl;
	cout << "             Warehouse Values            " << endl;
	cout << " ========================================" << endl;
	cout << " Warehouse One:                          " << endl;
	cout << " ----------------------------------------" << endl;
	cout << "           Small : $" << W1Small << "    " << endl;
	cout << "           Medium: $" << W1Med << "      " << endl;
	cout << "           Large : $" << W1Large << "    " << endl;
	cout << "           ------------------------------" << endl;
	cout << "           Total : $" << W1Total << "    " << endl;
	cout << endl;
	cout << " Warehouse Two:                          " << endl;
	cout << " ----------------------------------------" << endl;
	cout << "           Small : $" << W2Small << "    " << endl;
	cout << "           Medium: $" << W2Med << "      " << endl;
	cout << "           Large : $" << W2Large << "    " << endl;
	cout << "           ------------------------------" << endl;
	cout << "           Total : $" << W2Total << "    " << endl;
	cout << endl;
	cout << " Warehouse Three:                        " << endl;
	cout << " ----------------------------------------" << endl;
	cout << "           Small : $" << W3Small << "    " << endl;
	cout << "           Medium: $" << W3Med << "    " << endl;
	cout << "           Large : $" << W3Large << "    " << endl;
	cout << "           ------------------------------" << endl;
	cout << "           Total : $" << W3Total << "    " << endl;
	cout << " ========================================" << endl;
	cout << " Grand Total     : $" << GrandTotal << " " << endl;
	cout << " ========================================" << endl;
	cout << endl << "Returning to main menu..." << endl << endl;

	displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);



	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

void searchHistoryLog(bool first){//(EXTRA FUNCTIONALITY:ZACH) Search the History log for all transactions of the item ID

	string number = "";

	if (first == true)
		getline(cin, number);
		
	cout << "\n\"EXIT\" to exit search";
	cout << "\nEnter an item number to view it's history log: ";
	getline(cin, number);

	while (number.size() != 10 && number != "EXIT")
	{
		cout << "\nERROR: invalid item number" << endl;
		cout << "\nEnter an item number to view it's history log: ";
		cin >> number;
	}
	if (number != "EXIT")
		logSearch(number);

	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}

void itemInformationDisplay(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse1, vector<vector<Warehouse>>& Warehouse2, vector<vector<Warehouse>>& Warehouse3, string& OrderFileSequenceNumber, string& ShipmentsFileSequenceNumber){//(BASE FUNCTIONALITY) The inventory analyst is able to update the item name, id, price, stock, and size type.
	string Answer, itemID, Metric, selection, tempID, tempName, tempDesc, tempPrice, tempSize, newID, newName, newDesc, newPrice, newSize;
	int tempLoc;
	int sizeConverter;
	int counterSmall = 0;
	int counterMed = 0;
	int counterLarge = 0;

	for (int i = 0; i<20; i++) // Totals the amount of empty space in all small sections of each warehouse.
	{
		if (Warehouse1[0][i].ItemID == ""){
			counterSmall++;
		}
		if (Warehouse2[0][i].ItemID == ""){
			counterSmall++;
		}
		if (Warehouse3[0][i].ItemID == ""){
			counterSmall++;
		}
	}
	for (int i = 0; i<60; i++) // Totals the amount of empty space in all medium sections of each warehouse.
	{
		if (Warehouse1[1][i].ItemID == ""){
			counterMed++;
		}
		if (Warehouse2[1][i].ItemID == ""){
			counterMed++;
		}
		if (Warehouse3[1][i].ItemID == ""){
			counterMed++;
		}
	}
	for (int i = 0; i<20; i++) // Totals the amount of empty space in all large sections of each warehouse.
	{
		if (Warehouse1[2][i].ItemID == ""){
			counterLarge++;
		}
		if (Warehouse2[2][i].ItemID == ""){
			counterLarge++;
		}
		if (Warehouse3[2][i].ItemID == ""){
			counterLarge++;
		}
	}

	cout << "Type the item ID to edit or 'quit' to return to main menu." << endl;
	cin >> itemID;

	for (int x = 0; x < Catalog.size(); x++)  //Searches the catalog for an item name matching input
	{
		if (itemID == Catalog[x].ID)	// If item ID input matches one in the catalog, the information is stored.
		{
			cout << ">Item ID found." << endl << endl;;
			tempID = itemID;
			tempName = Catalog[x].itemName;
			tempPrice = Catalog[x].itemPrice;
			tempDesc = Catalog[x].itemDesc;
			tempSize = Catalog[x].itemSize;

			int buffer = 0; // Used to convert a string input to an int

			{
				{
					do
					{
						cout << "What would you like to edit? " << endl;
						cout << "1. Edit Item ID" << endl;
						cout << "2. Edit Item Name" << endl;
						cout << "3. Edit Item Price" << endl;
						cout << "4. Edit Size" << endl;
						cout << "5. Edit Description" << endl;
						cout << "6. Exit" << endl;
						cin >> selection;
						buffer = atoi(selection.c_str()); //converts string to int
						switch (buffer)
						{
						case 1:
							cout << "Current ID: " << Catalog[x].ID << endl;
							cout << "Enter new ID: " << endl;
							cin >> newID;
							Catalog[x].ID = newID;
							cout << "Item Changed." << endl;
							cout << "New item ID: " << Catalog[x].ID << endl << endl;
							break;
						case 2:
							cout << "Current Name: " << Catalog[x].itemName << endl;
							cout << "Enter new item name: " << endl;
							cin >> newName;
							Catalog[x].itemName = newName;
							cout << "Item Changed." << endl;
							cout << "New Item Name: " << Catalog[x].itemName << endl << endl;
							break;
						case 3:
							cout << "Current Price: " << Catalog[x].itemPrice << endl;
							cout << "Enter new price: " << endl;
							cin >> newPrice;
							Catalog[x].itemPrice = newPrice;
							cout << "Item Changed." << endl;
							cout << "New Item Price: " << Catalog[x].itemPrice << endl << endl;
							break;
						case 4:
							//cout << "Small Space: " << counterSmall << " Med Space: " << counterMed << " Large Space: " << endl;
							do {
								cout << "Current Size: " << Catalog[x].itemSize << endl;
								cout << "Enter new Size (S, M, or L): " << endl;
								cin >> newSize;
							} while (newSize != "S" && newSize != "M" && newSize != "L");

							if (newSize == "S")               //convert the response to vector row
								sizeConverter = 0;
							else if (newSize == "M")
								sizeConverter = 1;
							else if (newSize == "L")
								sizeConverter = 2;

							if (newSize == Catalog[x].itemSize)
							{
								cout << "The size is already " << newSize << ". No changes were made." << endl;
							}

							if (tempSize == "S" && counterSmall > 0)
							{
								for (int i = 0; i < 20; i++)
								{
									if (Warehouse1[0][i].ItemID == Catalog[x].ID)
									{
										for (int j = 0; j < 20; j++)
										{
											if (Warehouse1[sizeConverter][j].ItemID == "")
											{
												Warehouse1[sizeConverter][j].ItemID = Warehouse1[0][i].ItemID;
												Warehouse1[sizeConverter][j].quantity = Warehouse1[0][i].quantity;
												Warehouse1[0][i].ItemID = "";
												Warehouse1[0][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
									else if (Warehouse2[0][i].ItemID == itemID)
									{
										for (int j = 0; j < 20; j++)
										{
											if (Warehouse2[sizeConverter][j].ItemID == "")
											{
												Warehouse2[sizeConverter][j].ItemID = Warehouse2[0][i].ItemID;
												Warehouse2[sizeConverter][j].quantity = Warehouse2[0][i].quantity;
												Warehouse2[0][i].ItemID = "";
												Warehouse2[0][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
									else if (Warehouse3[0][i].ItemID == itemID)
									{
										for (int j = 0; j < 20; j++)
										{
											if (Warehouse3[sizeConverter][j].ItemID == "")
											{
												Warehouse3[sizeConverter][j].ItemID = Warehouse3[0][i].ItemID;
												Warehouse3[sizeConverter][j].quantity = Warehouse3[0][i].quantity;
												Warehouse3[0][i].ItemID = "";
												Warehouse3[0][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
								}
								Catalog[x].itemSize = newSize;
								cout << "Item successfully moved and changed." << endl;
								cout << "New Item Size: " << Catalog[x].itemSize << endl << endl;
							}
							else if (tempSize == "M" && counterMed > 0)
							{
								for (int i = 0; i < 60; i++)
								{
									if (Warehouse1[1][i].ItemID == itemID)
									{
										for (int j = 0; j < 60; j++)
										{
											if (Warehouse1[sizeConverter][j].ItemID == "")
											{
												Warehouse1[sizeConverter][j].ItemID = Warehouse1[1][i].ItemID;
												Warehouse1[sizeConverter][j].quantity = Warehouse1[1][i].quantity;
												Warehouse1[1][i].ItemID = "";
												Warehouse1[1][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
									else if (Warehouse2[1][i].ItemID == itemID)
									{
										for (int j = 0; j < 60; j++)
										{
											if (Warehouse2[sizeConverter][j].ItemID == "")
											{
												Warehouse2[sizeConverter][j].ItemID = Warehouse2[1][i].ItemID;
												Warehouse2[sizeConverter][j].quantity = Warehouse2[1][i].quantity;
												Warehouse2[1][i].ItemID = "";
												Warehouse2[1][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
									else if (Warehouse3[1][i].ItemID == itemID)
									{
										for (int j = 0; j < 60; j++)
										{
											if (Warehouse3[sizeConverter][j].ItemID == "")
											{
												Warehouse3[sizeConverter][j].ItemID = Warehouse3[1][i].ItemID;
												Warehouse3[sizeConverter][j].quantity = Warehouse3[1][i].quantity;
												Warehouse3[1][i].ItemID = "";
												Warehouse3[1][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
								}
								Catalog[x].itemSize = newSize;
								cout << "Item successfully moved and changed." << endl;
								cout << "New Item Size: " << Catalog[x].itemSize << endl << endl;
							}
							else if (tempSize == "L" && counterLarge > 0)
							{
								for (int i = 0; i < 20; i++)
								{
									if (Warehouse1[2][i].ItemID == itemID)
									{
										for (int j = 0; j < 20; j++)
										{
											if (Warehouse1[sizeConverter][j].ItemID == "")
											{
												Warehouse1[sizeConverter][j].ItemID = Warehouse1[2][i].ItemID;
												Warehouse1[sizeConverter][j].quantity = Warehouse1[0][i].quantity;
												Warehouse1[2][i].ItemID = "";
												Warehouse1[2][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
									else if (Warehouse2[2][i].ItemID == itemID)
									{
										for (int j = 0; j < 20; j++)
										{
											if (Warehouse2[sizeConverter][j].ItemID == "")
											{
												Warehouse2[sizeConverter][j].ItemID = Warehouse2[2][i].ItemID;
												Warehouse2[sizeConverter][j].quantity = Warehouse2[2][i].quantity;
												Warehouse2[2][i].ItemID = "";
												Warehouse2[2][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
									else if (Warehouse3[2][i].ItemID == itemID)
									{
										for (int j = 0; j < 20; j++)
										{
											if (Warehouse3[sizeConverter][j].ItemID == "")
											{
												Warehouse3[sizeConverter][j].ItemID = Warehouse3[2][i].ItemID;
												Warehouse3[sizeConverter][j].quantity = Warehouse3[2][i].quantity;
												Warehouse3[2][i].ItemID = "";
												Warehouse3[2][i].quantity = "";
												cout << "Item Changed." << endl;
												break;
											}
										}
									}
								}
								Catalog[x].itemSize = newSize;
								cout << "Item successfully moved and changed." << endl;
								cout << "New Item Size: " << Catalog[x].itemSize << endl << endl;
							}
							break;

						case 5:
							cout << "Current Description: " << Catalog[x].itemDesc << endl;
							cout << "Enter new description: " << endl;
							cin.ignore();
							getline(cin, newDesc);
							Catalog[x].itemDesc = newDesc;
							cout << "Item Changed." << endl;
							cout << "New Item Description: " << Catalog[x].itemDesc << endl << endl;
							break;
						case 6:
							displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3, OrderFileSequenceNumber, ShipmentsFileSequenceNumber);
							break;

						default: cout << endl;
							cout << "Error: " << selection << " is invalid input, please try again." << endl << endl;
							break;
						}
					} while (buffer != 6);
				}
			}
		}
		else if (x == Catalog.size() - 1) //If the program searches entire catalog and does not have a matching ID to input, display msg.
		{
			cout << "Item not found, please try again." << endl << endl;
			itemInformationDisplay(Catalog, Warehouse1, Warehouse2, Warehouse3, OrderFileSequenceNumber, ShipmentsFileSequenceNumber);
		}
		else if (itemID == "QUIT" || itemID == "quit") // case for exiting program in case mistake in main menu was made. 
		{
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3, OrderFileSequenceNumber, ShipmentsFileSequenceNumber);
		}
	}
}
void itemInventoryDisplay(vector<CatalogItem>Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3,string&OrdersFileSequenceNumber,string&ShipmentsFileSequenceNumber){//(BASE FUNCTIONALITY) Retrieves current status of all 3 warehouses' inventory, and allows inventory analyst to override any location status and update inventory
	
	string Answer;// the users answer for if they want to edit a quantity.
	string warehouseResponse;//the users response for what warehouse number
	string sizeResponse;//the users response for what size type to look at
	int sizeConverter; //Takes the S,M,L that the user enters and converts it to the row of the matrix
	string testLocation;
	string tryAgainResponse;
	int locationResponse;//the users response for where in the vector to look.
	int quantityResponse;//the users response for what to change the quantity to?

	string addItemResponse;//the user response to adding a new item in that location spot.
	string newID;//the variable that the user will enter to add to the warehouse.
	int newQuantity; //the variable that the user will enter to add to the warehouse
	bool validID; // a check to see if the new item is in the catalog

	itemInventoryDisplay_WarehouseContents(Warehouse1, Warehouse2, Warehouse3);//Display the warehouse to the user.

	do{
	cout<< "Would you like to edit a quantity (y/n)? ";
	cin>> Answer;

	if(Answer == "y"){//if the answer is y then continue on to the next question
		do{
		cout<< "What warehouse number is the item located in (1,2,3,EXIT)? ";
		cin>> warehouseResponse;

		if(warehouseResponse == "EXIT"){//if the response is EXIT return to the main menu
			cout<< "Returning to the main menu."<<endl;
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}

		}while(warehouseResponse != "1" && warehouseResponse != "2" &&warehouseResponse != "3");//keep asking unless the answer is 1,2 or 3

	
		do{
		cout<< "What size type is the item (S,M,L,EXIT)? ";
		cin>> sizeResponse;

		if(sizeResponse == "EXIT"){//if the response is EXIT return to the main menu
			cout<< "Returning to the main menu."<<endl;
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}

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
		cout<< "What location is the item in (-1 to return to main menu) ? ";
		while(!(cin>>locationResponse)){//so this clears the current input value and ignores the character value.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Invalid warehouse location."<<endl;
			cout<< "What location is the item in (-1 to return to main menu) ? ";
		}

		//Test boundaries
		if(sizeResponse == "S" && locationResponse >=20 || sizeResponse == "S" && locationResponse <0 ||  sizeResponse == "L" && locationResponse >=20 || sizeResponse == "L" && locationResponse <0 || sizeResponse == "M" && locationResponse >=60|| sizeResponse == "M" && locationResponse <0 ){//if the item is out of the vector boundaries then notify.
			if(locationResponse == -1){
				cout<< "Returning to the main menu."<<endl;
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
			}
			else
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
					cout<<"Returning to the main menu."<<endl;
					displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
				}
				else if(addItemResponse == "y"){
					do{
					cout<<"Enter an Item ID (EXIT to return to main menu): ";
					cin>> newID;
					if(newID == "EXIT"){
						cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
					}
					validID =itemInventoryDisplay_testCatalog(Catalog,newID, sizeResponse);
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
					cout<<"Returning to the main menu."<<endl;
					displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
				}
				else if(addItemResponse == "y"){
					do{
					cout<<"Enter an Item ID (EXIT to return to main menu): ";
					cin>> newID;
					if(newID == "EXIT"){
						cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
					}
					validID =itemInventoryDisplay_testCatalog(Catalog,newID, sizeResponse);
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
					cout<<"Returning to the main menu."<<endl;
					displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
				}
				else if(addItemResponse == "y"){
					do{
					cout<<"Enter an Item ID (EXIT to return to main menu): ";
					cin>> newID;
					if(newID == "EXIT"){
						cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
					}
					validID =itemInventoryDisplay_testCatalog(Catalog,newID, sizeResponse);
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
		cout<< "What quantity would you like to change it to (-1 to return to main menu)? ";
		while(!(cin>>quantityResponse)){//so this clears the current input value and ignores the character value.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Enter a valid quantity."<<endl;
			cout<< "What quantity would you like to change it to (-1 to return to main menu)? ";
		}

		
		//the mainflow path
		if(warehouseResponse =="1"){
			if(quantityResponse == 0){//if the input is 0 delete the item from the warehouse.
				Warehouse1[sizeConverter][locationResponse].ItemID = "";//delete the id from the warehouse
				Warehouse1[sizeConverter][locationResponse].quantity = "";//delete the quantity from the warehouse
				cout<<"Item deleted."<<endl;
			}
			else if(quantityResponse <= -2){//if the input is less than or equal to 0 delete the item from the warehouse.
				cout<<"Quantity too small. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else if (sizeResponse == "S" && quantityResponse >250 || sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10){//if the quantity is more then boundaries then notify them
				cout<<"Quantity too large. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else if(quantityResponse == -1){//if the user exits
				if(Warehouse1[sizeConverter][locationResponse].ItemID != "" && Warehouse1[sizeConverter][locationResponse].quantity == ""){//if they are trying to add a new Id but decide to quit, make sure to delete the new ID from the warehouse.
					Warehouse1[sizeConverter][locationResponse].ItemID = "";
				}
				cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
			}
			else//main flow path
				Warehouse1[sizeConverter][locationResponse].quantity = to_string(quantityResponse);
		}
		else if(warehouseResponse =="2"){
			if(quantityResponse == 0){
				Warehouse2[sizeConverter][locationResponse].ItemID = "";
				Warehouse2[sizeConverter][locationResponse].quantity = "";
				cout<<"Item deleted."<<endl;
			}
			else if(quantityResponse <= -2){//if the input is less than or equal to 0 delete the item from the warehouse.
				cout<<"Quantity too small. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else if (sizeResponse == "S" && quantityResponse >250|| sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10){
				cout<<"Quantity too large. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else if(quantityResponse == -1){//if the user exits
				if(Warehouse2[sizeConverter][locationResponse].ItemID != "" && Warehouse2[sizeConverter][locationResponse].quantity == ""){//if they are trying to add a new Id but decide to quit, make sure to delete the new ID from the warehouse.
					Warehouse2[sizeConverter][locationResponse].ItemID = "";
				}
				cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
			}
			else
				Warehouse2[sizeConverter][locationResponse].quantity = to_string(quantityResponse);
		}
		else if(warehouseResponse =="3"){
			if(quantityResponse ==0){
				Warehouse3[sizeConverter][locationResponse].ItemID = "";
				Warehouse3[sizeConverter][locationResponse].quantity = "";
				cout<<"Item deleted."<<endl;
			}
			else if(quantityResponse <= -2){//if the input is less than or equal to 0 delete the item from the warehouse.
				cout<<"Quantity too small. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else if (sizeResponse == "S" && quantityResponse >250 || sizeResponse == "M" && quantityResponse >100 || sizeResponse == "L" && quantityResponse >10){
				cout<<"Quantity too large. Small: 0-250, Medium: 0-100, Large: 0-10."<<endl;
			}
			else if(quantityResponse == -1){//if the user exits
				if(Warehouse3[sizeConverter][locationResponse].ItemID != "" && Warehouse3[sizeConverter][locationResponse].quantity == ""){//if they are trying to add a new Id but decide to quit, make sure to delete the new ID from the warehouse.
					Warehouse3[sizeConverter][locationResponse].ItemID = "";
				}
				cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
			}
			else
				Warehouse3[sizeConverter][locationResponse].quantity = to_string(quantityResponse);
		}

		}while(sizeResponse == "S" && quantityResponse >250 || sizeResponse == "S" && quantityResponse <= -1 || sizeResponse == "M" && quantityResponse >100 || sizeResponse == "M" && quantityResponse <= -1 || sizeResponse == "L" && quantityResponse >10 || sizeResponse == "L" && quantityResponse <= -1);

	}

	//if the answer is no then return to the main menu
	else if(Answer == "n"){
		cout<<"Returning to the main menu."<<endl;
	
	}
	}while(Answer != "y" && Answer != "n");
	
}

void itemInventoryDisplay_WarehouseContents(vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){//(BASE FUNCTIONALITY) Retrieves current status of all 3 warehouses' inventory, and allows inventory analyst to override any location status and update inventory
	
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

bool itemInventoryDisplay_testCatalog(vector<CatalogItem>Catalog, string ItemId, string ItemSize){//Search the catalog for the correct ID and size values
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


void showWarehouseContents(vector<CatalogItem>Catalog, vector<vector<Warehouse>> Warehouse1,vector<vector<Warehouse>> Warehouse2,vector<vector<Warehouse>> Warehouse3,string OrdersFileSequenceNumber,string ShipmentsFileSequenceNumber){//(BASE FUNCTIONALITY) Given a Warehouse and a location show the contents

	string Answer;
	string warehouseResponse;//the users response for what warehouse number
	string sizeResponse;//the users response for what size type to look at
	int sizeConverter; //Takes the S,M,L that the user enters and converts it to the row of the matrix
	int locationResponse;//the users response for where in the vector to look.

	//Gather the input for the warehouse #
		do{
		cout<< "What warehouse number is the item located in (1,2,3,EXIT)? ";
		cin>> warehouseResponse;
		if(warehouseResponse == "EXIT"){//if the response is EXIT return to the main menu
			cout<< "Returning to the main menu."<<endl;
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
		}while(warehouseResponse != "1" && warehouseResponse != "2" &&warehouseResponse != "3");//keep asking unless the answer is 1,2 or 3

	//Gather the input for the item Size
		do{
		cout<< "What size type is the item (S,M,L,EXIT)? ";
		cin>> sizeResponse;
		if(sizeResponse == "EXIT"){//if the response is EXIT return to the main menu
			cout<< "Returning to the main menu."<<endl;
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
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
		cout<< "What location is the item in (-1 to return to the main menu)? ";
		while(!(cin>>locationResponse)){//so this clears the current input value and ignores the character value.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Enter a valid warehouse location."<<endl;
			cout<< "What location is the item in (-1 to return to the main menu)? ";
		}
		//Test boundaries
		if(sizeResponse == "S" && locationResponse >=20 || sizeResponse == "S" && locationResponse <0 ||  sizeResponse == "L" && locationResponse >=20 || sizeResponse == "L" && locationResponse <0 || sizeResponse == "M" && locationResponse >=60|| sizeResponse == "M" && locationResponse <0 ){//if the item is out of the vector boundaries then notify.
			if(locationResponse == -1){
				cout<< "Returning to the main menu."<<endl;
			displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
			}
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
			showWarehouseContents(Catalog, Warehouse1,Warehouse2,Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
		}
		else if (Answer == "n"){
			cout<<"Returning to the main menu."<<endl;
						displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3,OrdersFileSequenceNumber,ShipmentsFileSequenceNumber);
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



void AddToLogFile(string itemNumber, string warehouse, string quantity, string INorOUT, string date)
{
	ofstream logFile;
	logFile.open ("WIPLogFile.txt", std::ofstream::app);
	logFile << itemNumber << "	" << warehouse << "	" << quantity << "	" << INorOUT << " " << date << endl;
	logFile.close();
};



void editItemCatalog(vector<CatalogItem>& Catalog, vector<vector<Warehouse>> Warehouse1, vector<vector<Warehouse>> Warehouse2, vector<vector<Warehouse>> Warehouse3, bool first){	//(EXTRA FUNCTIONALITY: GROUP) Able to Add or Delete an item from the catalog. From SPMP, "Edits the valid item catalog, ensuring that the number of accepted items never exceeds 400."

	CatalogItem Item;
	string input;
	string newItemID = "";
	int itemLocation;
	int decimalCounter = 0;
	bool newItem;
	bool warehouseItem = false;
	bool choice = false;

	if (first == true)
		getline(cin, input);

	cout << "\nPlease choose:" << endl;
	cout << "1. Add an item to the catalog" << endl;
	cout << "2. Delete an item from the catalog" << endl;
	cout << "3. Exit" << "\n\n";
	getline(cin, input);

	if (input == "1" || input == "2" || input == "3")
	{
		choice = true;
	}

	while (choice == false)
	{
		input = "";
		cout << "\nERROR: Incorrect input" << endl;
		cout << "\nPlease choose:" << endl;
		cout << "1. Add an item to the catalog" << endl;
		cout << "2. Delete an item from the catalog" << endl;
		cout << "3. Exit" << "\n\n";
		getline(cin, input);

		if (input == "1" || input == "2" || input == "3")
		{
			choice = true;
		}
	}

	if (input == "1") // add
	{
		cout << "Enter the ID of the item that you would like to add: ";
		getline(cin, newItemID);

		while (newItemID.size() != 10)
		{
			newItemID = "";
			cout << "\nERROR: Invalid Item ID" << endl;
			cout << "\nEnter the ID of the item that you would like to add: ";
			getline(cin, newItemID);
		}

		newItem = false;
		for (int x = 0; x<Catalog.size(); x++)
		{
			if (newItemID == Catalog[x].ID)
			{ //item valid
				newItem = true;
			}
		}

		if (newItem == false && Catalog.size() < 400)
		{
			Item.ID = newItemID; // if the ID is valid (10 characters)

			input = "";

			cout << "Enter the name of the item that you would like to add: ";
			getline(cin, input);
			if (input.size() > 30)
			{
				Item.itemName = input.substr(0, 30);
			}
			else
			{
				while(input.length()<30)
				{
					input=input+" ";
				}
				Item.itemName = input;
			}
			input = "";
			choice = false;

			cout << "Enter the cost of the item that you would like to add: ";
			getline(cin, input);

			if (input.size() == 8)
				choice = true;

			for (int i = 0; i < input.size(); i++)
			{
				if (choice == true)
				{
					if (input.at(i) == '0' || input.at(i) == '1' || input.at(i) == '2' || input.at(i) == '3' || input.at(i) == '4' || input.at(i) == '5' || input.at(i) == '6' || input.at(i) == '7' || input.at(i) == '8' || input.at(i) == '9' || input.at(i) == '.')
					{
						if (input.at(i) == '.')
							decimalCounter++;
					}
					else
						choice = false;
				}
			}

			if (decimalCounter != 1)
				choice = false;

			if (choice == true && input.at(5) != '.')
				choice = false;

			while (choice == false)
			{
				input = "";
				cout << "\nERROR: Invalid Item Price" << endl;
				cout << "\nEnter the cost of the item that you would like to add: ";
				getline(cin, input);

				if (input.size() == 8)
					choice = true;

				for (int i = 0; i < input.size(); i++)
				{
					if (choice == true)
					{
						if (input.at(i) == '0' || input.at(i) == '1' || input.at(i) == '2' || input.at(i) == '3' || input.at(i) == '4' || input.at(i) == '5' || input.at(i) == '6' || input.at(i) == '7' || input.at(i) == '8' || input.at(i) == '9' || input.at(i) == '.')
						{
							if (input.at(i) == '.')
								decimalCounter++;
						}
						else
							choice = false;
					}
				}

				if (choice == true && decimalCounter != 1)
					choice = false;

				if (choice == true && input.at(5) != '.')
					choice = false;
			}

			Item.itemPrice = input; // if price is valid

			input = "";

			cout << "Enter the size of the item that you would like to add (S, M, L): ";
			getline(cin, input);

			choice = false;

			if (input == "S" || input == "M" || input == "L")
			{
				choice = true;
			}

			while (choice == false)
			{
				input = "";
				cout << "ERROR: Incorrect Item Size" << endl;
				cout << "Enter the size of the item that you would like to add (S, M, L): ";
				getline(cin, input);

				if (input == "S" || input == "M" || input == "L")
				{
					choice = true;
				}
			}

			Item.itemSize = input;

			input = "";

			cout << "Enter the description of the item that you would like to add:\n-> ";
			getline(cin, input);
			if (input.size() > 500)
			{
				Item.itemDesc = input.substr(0, 500);
			}
			else
				Item.itemDesc = input; // only first 500 characters from description

			input = "";

			cout << "Please confirm the addition of this item (Y/N): ";
			getline(cin, input);

			choice = false;

			if (input == "Y" || input == "N")
			{
				choice = true;
			}

			while (choice == false)
			{
				input = "";
				cout << "Please confirm the addition of this item (Y/N): ";
				getline(cin, input);

				if (input == "Y" || input == "N")
				{
					choice = true;
				}
			}

			if (input == "Y")
			{
				// add the new item to the end of the catalog
				Catalog.push_back(Item);
				cout << "Successfully Added!" << endl;
				cout << "Returning to the main menu" << endl;

				//return to the main menu
				//void displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
			}
			else
			{
				cout << "Item not added!" << endl;
				// go back to the beginning
				editItemCatalog(Catalog, Warehouse1, Warehouse2, Warehouse3, false);
			}


			//cout << "Returning to the main menu" << endl;
			//void displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
		}

		else if (Catalog.size() == 400)
		{
			cout << "\nERROR: Cannot Add Item" << endl;
			cout << "The Catalog Is Full" << endl;
			cout << "Returning to the main menu" << endl;

			// display main menu
			//void displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
		}

		else // item exists in catalog
		{
			cout << "\nERROR: Cannot Add Item" << endl;
			cout << "Item Already Exists In The Catalog" << endl;
			// go back to the beginning
			editItemCatalog(Catalog, Warehouse1, Warehouse2, Warehouse3, false);
		}
	}

	else if (input == "2") // delete
	{

		cout << "Insert the Item ID you would like to delete: ";
		getline(cin, newItemID);

		bool newItem = false;
		for (int x = 0; x<Catalog.size(); x++)
		{
			if (newItemID == Catalog[x].ID)
			{ //item valid
				itemLocation = x;
				newItem = true;
			}
		}

		if (newItem == true)
		{

			for (int i = 0; i<3; i++) // check warehouse 1
			{
				for (int j = 0; j < Warehouse1.at(i).size(); j++)
				{
					if (Warehouse1[i][j].ItemID == newItemID)
					{
						warehouseItem = true;
					}
				}
			}

			if (warehouseItem == false) // check warehouse 2 if not already found
			{
				for (int i = 0; i<3; i++)
				{
					for (int j = 0; j < Warehouse2.at(i).size(); j++)
					{
						if (Warehouse2[i][j].ItemID == newItemID)
						{
							warehouseItem = true;
						}
					}
				}
			}

			if (warehouseItem == false) // check warehouse 3 if not already found
			{
				for (int i = 0; i<3; i++)
				{
					for (int j = 0; j < Warehouse3.at(i).size(); j++)
					{
						if (Warehouse3[i][j].ItemID == newItemID)
						{
							warehouseItem = true;
						}
					}
				}
			}

			if (warehouseItem == true) // one of the 3 warehouses contains the item
			{
				cout << "\nERROR: Cannot Delete Item" << endl;
				cout << "Item Exists In One or More Warehouses" << endl;

				// go back to the beginning
				editItemCatalog(Catalog, Warehouse1, Warehouse2, Warehouse3, false);

			}

			else // no warehouse contains item
			{
				cout << "Are you sure you would like to delete item " << newItemID << "? (Y/N): ";
				getline(cin, input);

				choice = false;

				if (input == "Y" || input == "N")
					choice = true;

				while (choice == false)
				{
					input = "";
					cout << "Are you sure you would like to delete item " << newItemID << "? (Y/N): ";
					getline(cin, input);

					if (input == "Y" || input == "N")
					{
						choice = true;
					}

				}

				if(input == "Y") // delete
				{
					Catalog.erase(Catalog.begin() + itemLocation);
					cout << "Successfully Deleted!" << endl;
					cout << "Returning to the main menu" << endl;
					//void displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
				}

				else // do not delete
				{
					cout << "Item Not Deleted." << endl;
					//go back to the beginning
					editItemCatalog(Catalog, Warehouse1, Warehouse2, Warehouse3, false);
				}
			}
		}

		else
		{
			cout << "Item does not exist in the catalog\n";

			// go back to the beginning
			editItemCatalog(Catalog, Warehouse1, Warehouse2, Warehouse3, false);
		}
	}

	else // input == '3') exit
	{
		cout << "\nReturning to the main menu" << endl;
		// display main menu
		//void displayMainMenu(Catalog, Warehouse1, Warehouse2, Warehouse3);
	}

	//displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}


/*void addUser(vector<CatalogItem>&Catalog, vector<vector<Warehouse>>& Warehouse1,vector<vector<Warehouse>>& Warehouse2,vector<vector<Warehouse>>& Warehouse3){// (EXTRA FUNCTIONALITY: ANNA) To add a new user they must contact the Gold Stars.


	cout << "\nTo add a new user, contact Gold Stars."<<endl;
	displayMainMenu(Catalog, Warehouse1,Warehouse2,Warehouse3);
}*/
