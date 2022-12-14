// DSA 5005 - Computing Structures
// Fall 2022
// Project 3
// Original editor - Aditya Narasimhan
// Modified by Caxton Muchono

#include <iostream>
#include <string>  // for the string fields
#include <vector>  // to store data
#include <fstream> // to read the csv file
#include <cmath>   // for math function

using namespace std;

// class to store one row's information
class DFrow
{
protected:
	// all the fields to store information of a row
	string name;
	char sex;
	int age;
	int height;
	int weight;
	string city;

public:
	DFrow() {   // default constructor
		name = "";
		sex = ' ';
		age = -1;
		height = -1;
		weight = -1;
		city = "";
	} 
	DFrow(string n, char c, int one, int two, int three, string ci) {  // non-default constructor
		name = n;
		sex = c;
		age = one;
		height = two;
		weight = three;
		city = ci;
	} 
	// Getters for each of the fields
	string getName() { return name; }
	char getSex() { return sex; }
	int getAge() { return age; }
	int getHeight() { return height; }
	int getWeight() { return weight; }
	string getCity() { return city; }

	// Setters for each of the fields
	void setName(string x) {
		name = x;
	}
	void setSex(char c) {
		sex = c;
	}
	void setAge(int x) {
		age = x;
	}
	void setHeight(int x) {
		height = x;
	}
	void setWeight(int x) {
		weight = x;
	}
	void setCity(string x) {
		city = x;
	}

	// Display method to display all the fields in the same order
	void display() {
		cout << getName() << " " << getSex() << " " << getAge() << " " <<
			getHeight() << " " << getWeight() << " " << getCity() << endl;
	}
	
	// Destructor
	~DFrow() {}
};

// class to store the entire dataframe
class DataFrame
{
protected:
	vector<DFrow> data;     // field storeing all the data
	vector<string> headers; // field to only the headers
	int nRows, nCols;       // store the number of rows and cols

public:
	// Constructors
	DataFrame() {
		nRows = -1;
		nCols = -1;
	}
	DataFrame(int rows, int cols) {
		nRows = rows;
		nCols = cols;
	}

	// Overload the [] operator to access data in DF
	DFrow operator[](int i) {
		return data[i];
	}

	// File reading Method
	void readCSV(string filename, string headerPresence) {

		// Read the file 
		ifstream ip(filename);

		// Check to see if the file exists and if it does exist print error
		if (!ip.is_open()) cout << "Error: File Open" << endl;

		// all the fields to store information of a row
		string nametemp;
		string sextemp;
		string agetemp;
		string heighttemp;
		string weighttemp;
		string citytemp;

		// while the file has information or not end of file
		while (ip.good()) {

			// if header is present in csv file
			if (headerPresence == "true") {

				// loop through the row 
				for (int i = 0; i < (nCols - 1);i++) {
					getline(ip, nametemp, ',');  // store string before the next comma into nametemp
					headers.push_back(nametemp); // add headername to headers 
				}

				getline(ip, citytemp, '\n');     // store last string in row before newline
				headers.push_back(citytemp);     // add headername to headers

				headerPresence = "false";        // make headerPresence false for next row in csv
				continue;                        // continue to begining of loop
			}

			// store strings of column info before the next comma or newline
			getline(ip, nametemp, ',');
			getline(ip, sextemp, ',');
			getline(ip, agetemp, ',');
			getline(ip, heighttemp, ',');
			getline(ip, weighttemp, ',');
			getline(ip, citytemp, '\n');
 
			// add row with column info to DataFrame data with respective 
			//    variable types
			data.push_back({ nametemp, sextemp[0], stoi(agetemp), stoi(heighttemp)
			, stoi(weighttemp), citytemp });

		}

		// close the csv file 
		ip.close();
	
	}

	// Output Method
	void display() {
	
		// loop through headers and display them
		for (int i = 0; i < nCols; i++) {
			cout << headers[i] << " ";
		}
		cout << endl;

		// loop through row data and display them
		for (int i = 0; i < nRows; i++) {
			data[i].display();
		}
	}

	// Search Record
	DFrow searchRecord(string name) {

		// loop through all data rows
		for (int i = 0; i < nRows; i++) {

			// compare row data name with name and if they are the same
			//   return the whole row
			if (data[i].getName() == name) {
				return data[i];
			}
			
		}

		// if name not found in DataFrame return empty row
		return { "", ' ', -1, -1, -1, "" };
	}

	// Setters
	// change the name of a header/column
	void setColName(int col, char* name) {

		headers.push_back(name);
		//headers[col] = name;
	}

	// Getters
	// returns the number of rows
	int getNumberRows() { return nRows; }

	// returns the number of columns
	int getNumberCols() { return nCols; }

	// returns a dataframe with a set of cLen number of columns
	DataFrame* getColumns(int* columns, int cLen) {}

	// returns a data frame with a set of rLen number of rows
	DataFrame* getRows(int* rows, int rLen) {

		DataFrame* tempD = new DataFrame(rLen, nCols);
		/*string y = "  ";

		for (int i = 0; i < nCols; i++) {
			tempD->setColName(i, &y[0]);
		}*/

		// loop through DataFrame and display data at index with value of rows array
		for(int i = 0; i < rLen; i++){
			data[rows[i]].display();
		}
		
		return tempD;
	}

	// returns a data frame given a set of row numbers and column numbers
	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen) {}

	// returns the header name given a index position
	string getHeader(int i) { return headers[i]; }

	// return the data of a row given a index position
	DFrow getData(int i) {
		return data[i];
	}

	// Find info of a given column
	// returns the average of the given column
	double findAverage(int colNumber) {
		double x = 0;  // initialize x to zero average

		// loop through all data rows
		for (int i = 0; i < nRows; i++) {

			if (colNumber == 2) {             // if its Age column add up ages to x 
				x = x + data[i].getAge();
			}
			else if (colNumber == 3) {        // if its Height column add up heights to x 
				x = x + data[i].getHeight();
			}
			else {                            // if its Weight column add up weights to x
				x = x + data[i].getWeight();   
			}
		}

		x = x / nRows;  // divide sum of column by number of rows                      
		return x;       // return average
	}

	// returns the max of the given column
	double findMax(int colNumber) {
		double x = 0;  // initialize x to zero max

		// loop through all data rows
		for (int i = 0; i < nRows; i++) {

			if (colNumber == 2) {                 // if its Age column compare x to row i age 
				x = fmax(data[i].getAge(), x);    // set x to bigger value
			}
			else if (colNumber == 3) {            // if its Height column compare x to row i height
				x = fmax(data[i].getHeight(), x); // set x to bigger value
			}
			else {                                // if its Weight column compare x to row i weight
				x = fmax(data[i].getWeight(), x); // set x to bigger value
			}
		}

		return x;  // return max value 
	}

	// returns the min of the given column
	double findMin(int colNumber) {
		double x = 100000;  // initialize x to high max

		// loop through all data rows
		for (int i = 0; i < nRows; i++) {

			if (colNumber == 2) {               // if its Age column compare x to row i age
				x = fmin(data[i].getAge(), x);  // set x to smaller value
			}
			else if (colNumber == 3) {          // if its Height column compare x to row i height
				x = fmin(data[i].getAge(), x);  // set x to smaller value
			}
			else {                              // if its Weight column compare x to row i weight
				x = fmin(data[i].getAge(), x);  // set x to smaller value
			}
		}

		return x; // return min value
	}

	// displays the frequency of the unique values
	double frequency(int colNumber) {
		int m = 0;  // initialize m to zero value
		int f = 0;  // initialize f to zero value

		// loop through all data rows
		for (int i = 0; i < nRows; i++) {

			if (data[i].getSex() == 'M') {  // if row Sex is "M" increase m by 1
				m++;
			}
			else {                          // if row Sex is "F" increase f by 1
				f++;
			}
		}

		// display frequency of M and F
		cout << "M: " << m << endl;
		cout << "F: " << f;

		return 0.0;
	}

	// Destructor
	~DataFrame() {}
};

// main function
int main()
{
	int numRows, numCols;   // number of rows and columns in csv file
	int x, y;               // temp variables to store display range
	string fileName;        // variable to store filename 
	string headerBool;      // variable to store if header exists
	string temp;            // temp variable to store names
	char command;           // command to do something
	DFrow tempRow;          // temp row to find records 

	// read the csv file information
	std::cin >> numRows >> numCols >> headerBool >> fileName;

	// create DataFrame with non-default constructor
	DataFrame* d = new DataFrame(numRows, numCols); 

	d->readCSV(fileName, headerBool); // use this method to read in the data from the csv file

	std::cin >> command;              // read the next command from input
	cout << endl;

	// while input is not end of file get next command 
	while (!std::cin.eof()) {
		// use switch cases to see the different commands to do next
		switch (command) {

		case 'F': { // option to find the record with a specific name

			cin >> temp;                      // read in name to be found
			tempRow = d->searchRecord(temp);  // call search function

			try {
				// if name not part of graphDB throw error message
				if (tempRow.getAge() == -1) throw tempRow.getAge();

			}
			catch (int a) {
				// if name does not exist 
				cout << "Record not found: " << endl;
				cout << temp << endl << endl;
				break;
			}

			// If record name found name it
			cout << "Record found: " << endl;
			tempRow.display();

			cout << endl;
			break;
		}
		case 'D': { // option to display all the records along with the headers if exists 

			d->display(); // display all the records along with the headers
			cout << endl;
			break;
		}
		case 'A': { // find the average of the different columns

			// read in column name for average
			cin >> temp; 

			// if column name does not contain numbers 
			if (temp == "Sex" || temp == "Name" || temp == "City") {
				cout << "Average for " << temp <<" cannot be found since it is nan";
			}

			else if (temp == "Age") {          // if Age column return average
				cout << "Average of " << temp << " is " << (int) d->findAverage(2);
			}
			else if (temp == "Height(in)") {   // if Height column return average
				cout << "Average of " << temp << " is " << (int) d->findAverage(3);
			}
			else {                             // if Weight column return average
				cout << "Average of " << temp << " is " << (int) d->findAverage(4);
			}

			cout << endl;
			break;
		}
		case 'Q': { // find the frequency of unique values in the Sex columns

			// read in column name for frequency
			cin >> temp;

			// if column name does not contain categorical data 
			if (temp == "Age" || temp == "Name" || temp == "City" || temp == "Height" || temp == "Weight") {
				cout << "Frequency for " << temp << " cannot be found since it is non-categorical ";
			}
			else if (temp == "Sex") {   // if Sex column return frequency of unique values
				x = (int) d->frequency(1);
			}

			cout << endl;
			break;
		}
		case 'X': { // find the max value of different columns

			// read in column name for max
			cin >> temp;

			// if column name does not contain numbers
			if (temp == "Sex" || temp == "Name" || temp == "City") {
				cout << "Max for " << temp << " cannot be found since it is nan";
			}
			else if (temp == "Age") {           // if Age column return max
				cout << "Max of " << temp << " is " << (int)d->findMax(2);
			}
			else if (temp == "Height(in)") {   // if Height column return max
				cout << "Max of " << temp << " is " << (int)d->findMax(3);
			}
			else {                             // if Weight column return max
				cout << "Max of " << temp << " is " << (int)d->findMax(4);
			}

			cout << endl;
			break;
		}

		case 'I': { // find the min value of different columns

			// read in column name for min
			cin >> temp;

			// if column name does not contain numbers
			if (temp == "Sex" || temp == "Name" || temp == "City") {
				cout << "Min for " << temp << " cannot be found since it is nan";
			}
			else if (temp == "Age") {           // if Age column return min
				cout << "Min of " << temp << " is " << (int)d->findMin(2);
			}
			else if (temp == "Height(in)") {    // if Height column return min
				cout << "Min of " << temp << " is " << (int)d->findMin(3);
			}
			else {                              // if Weight column return min
				cout << "Min of " << temp << " is " << (int)d->findMin(4);
			}

			cout << endl;
			break;
		}

		case 'R': { // display rows

			// read in the range of display
			cin >> x >> y;

			int disSize = y - x;              // size of array
			int* disTemp = new int[disSize];  // array to store display range
			
			// store the display range rows in array
			for (int i = 0; i < disSize; i++) {
				disTemp[i] = x;
				x++;
			}

			cout << endl;

			// temp DataFrame to store range rows 
			DataFrame* tempD = new DataFrame(disSize + 1, numCols);
			tempD = d->getRows(disTemp, disSize);

			cout << endl;
			break;
		}

		default: cout << "No commands found";   // if no command found
		}

		std::cin >> command; // read the next command from input 
	}

 	return 0;
}
