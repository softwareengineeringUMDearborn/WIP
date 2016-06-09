/*
LOG SEARCH FUNCTION WITH SAMPLE MAIN()
AUTHOR: ZACHARY MUZZIN
DATE: 4/1/2015
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

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

					if( equal == false ) //month > foundItems.at(i-1).getMonth() )	// item month newer than line month, insert
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
					else if( equal == true ) // month == foundItems.at(i-1).getMonth() )	// month is the same as list item month, check day
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

	}
	else
	{
		cout << "\nLog History for item: " << itemNumber << endl;
		for(unsigned int i = 0; i < foundItems.size(); i++)
			cout << foundItems.at(i).getLogFileLine() << endl;
	}

	infile.close();
};


int main()
{
	string number = "0000012345";
	while( number.size() != 10 )
	{
		cout << "ERROR: invalid item number\nItem number: ";
		cin >> number;
	}

	logSearch(number);

	return 0;
}
