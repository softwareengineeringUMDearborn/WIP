void AddToLogFile(string itemNumber, string warehouse, int quantity, string INorOUT, string date)
{
	ofstream logFile;
	logFile.open ("WIPLogFile.txt", std::ofstream::app);
	logFile << itemNumber << "	" << warehouse << "	" << quantity << "	" << INorOUT << " " <<	logFile << date << endl;
	logFile.close();
};
