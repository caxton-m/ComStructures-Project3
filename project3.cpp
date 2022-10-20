// DSA 5005 - Computing Structures
// Fall 2022
// Project 3
// Original editor - Aditya Narasimhan
// Modified by Caxton Muchono

#include <iostream>
#include <string>  // for the string fields
#include <vector>  // to store data
#include <fstream> // to read the csv file
#include <cmath>  // for math function

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
	// TODO: write getters for each of the fields
	string getName() { return name; }
	char getSex() { return sex; }
	int getAge() { return age; }
	int getHeight() { return height; }
	int getWeight() { return weight; }
	string getCity() { return city; }

	// TODO: write setters for each of the fields
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
	
	// TODO: write destructor
	~DFrow() {}
};

// class to store the entire dataframe
class DataFrame
{
protected:
	vector<DFrow> data; // field storeing all the data
	vector<string> headers; // field to only the headers
	int nRows, nCols; // store the number of rows and cols

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

		while (ip.good()) {

			if (headerPresence == "true") {

				getline(ip, nametemp, ',');
				getline(ip, sextemp, ',');
				getline(ip, agetemp, ',');
				getline(ip, heighttemp, ',');
				getline(ip, weighttemp, ',');
				getline(ip, citytemp, '\n');

				headers.push_back(nametemp);
				headers.push_back(sextemp);
				headers.push_back(agetemp);
				headers.push_back(heighttemp);
				headers.push_back(weighttemp);
				headers.push_back(citytemp);

				headerPresence = "false";
				continue;
			}

			getline(ip, nametemp, ',');
			getline(ip, sextemp, ',');
			getline(ip, agetemp, ',');
			getline(ip, heighttemp, ',');
			getline(ip, weighttemp, ',');
			getline(ip, citytemp, '\n');
 
			data.push_back({ nametemp, sextemp[0], stoi(agetemp), stoi(heighttemp)
			, stoi(weighttemp), citytemp });

		}

		ip.close();
	
	}

	// Output Method
	void display() {
	
		for (int i = 0; i < nCols; i++) {
			cout << headers[i] << " ";
		}
		cout << endl;

		for (int i = 0; i < nRows; i++) {
			data[i].display();
		}
	}

	// Search Record
	DFrow searchRecord(string name) {

		for (int i = 0; i < nRows; i++) {

			if (data[i].getName() == name) {
				return data[i];
			}
			
		}

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

		// rLen = y - x 
		
		//           [size = 5]            5  , 6
		DataFrame* tempD = new DataFrame(rLen, nCols);
		/*string y = "  ";

		for (int i = 0; i < nCols; i++) {
			tempD->setColName(i, &y[0]);
		}*/

		for(int i = 0; i < rLen; i++){
			data[rows[i]].display();
		}
		

		//tempD->display();



		return tempD;
	}

	// returns a data frame given a set of row numbers and column numbers
	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen) {}

	// returns the header name given a index position
	string getHeader(int i) { return headers[i]; }

	// Find info of a given column
	// returns the average of the given column
	double findAverage(int colNumber) {
		double x = 0;

		for (int i = 0; i < nRows; i++) {

			if (colNumber == 2) {
				x = x + data[i].getAge();
			}
			else if (colNumber == 3) {
				x = x + data[i].getHeight();
			}
			else {
				x = x + data[i].getWeight();
			}
			
		}

		x = x / nRows;

		return x;
	}

	// returns the max of the given column
	double findMax(int colNumber) {
		double x = 0;

		for (int i = 0; i < nRows; i++) {

			if (colNumber == 2) {
				x = fmax(data[i].getAge(), x);
			}
			else if (colNumber == 3) {
				x = fmax(data[i].getHeight(), x);
			}
			else {
				x = fmax(data[i].getWeight(), x);
			}

		}

		return x;
	}

	// returns the min of the given column
	double findMin(int colNumber) {
		double x = 100000;

		for (int i = 0; i < nRows; i++) {

			if (colNumber == 2) {
				x = fmin(data[i].getAge(), x);
			}
			else if (colNumber == 3) {
				x = fmin(data[i].getAge(), x);
			}
			else {
				x = fmin(data[i].getAge(), x);
			}

		}

		return x;
	}

	// displays the frequency of the unique values
	double frequency(int colNumber) {
		int m = 0;
		int f = 0;

		for (int i = 0; i < nRows; i++) {
			if (data[i].getSex() == 'M') {
				m++;
			}
			else {
				f++;
			}
		}

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
	int numRows, numCols;
	int x, y;
	string fileName;
	string headerBool;
	string temp;
	char command;
	DFrow tempRow;

	std::cin >> numRows >> numCols >> headerBool >> fileName;

	DataFrame* d = new DataFrame(numRows, numCols);

	d->readCSV(fileName, headerBool); // use this method to read in the data from the csv file

	std::cin >> command;  // read the next command from input
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

			cin >> temp;

			if (temp == "Sex" || temp == "Name" || temp == "City") {
				cout << "Average for " << temp <<" cannot be found since it is nan";
			}
			else if (temp == "Age") {
				cout << "Average of " << temp << " is " << (int) d->findAverage(2);
			}
			else if (temp == "Height(in)") {
				cout << "Average of " << temp << " is " << (int) d->findAverage(3);
			}
			else {
				cout << "Average of " << temp << " is " << (int) d->findAverage(4);
			}

			cout << endl;
			break;
		}
		case 'Q': { // find the frequency of unique values in the Sex columns

			cin >> temp;

			if (temp == "Age" || temp == "Name" || temp == "City" || temp == "Height" || temp == "Weight") {
				cout << "Average for " << temp << " cannot be found since it is nan";
			}
			else if (temp == "Sex") {
				x = (int) d->frequency(1);
			}

			cout << endl;
			break;
		}
		case 'X': { // find the max value of different columns

			cin >> temp;

			if (temp == "Sex" || temp == "Name" || temp == "City") {
				cout << "Max for " << temp << " cannot be found since it is nan";
			}
			else if (temp == "Age") {
				cout << "Max of " << temp << " is " << (int)d->findMax(2);
			}
			else if (temp == "Height(in)") {
				cout << "Max of " << temp << " is " << (int)d->findMax(3);
			}
			else {
				cout << "Max of " << temp << " is " << (int)d->findMax(4);
			}

			cout << endl;
			break;
		}

		case 'I': { // find the min value of different columns

			cin >> temp;

			if (temp == "Sex" || temp == "Name" || temp == "City") {
				cout << "Min for " << temp << " cannot be found since it is nan";
			}
			else if (temp == "Age") {
				cout << "Min of " << temp << " is " << (int)d->findMin(2);
			}
			else if (temp == "Height(in)") {
				cout << "Min of " << temp << " is " << (int)d->findMin(3);
			}
			else {
				cout << "Min of " << temp << " is " << (int)d->findMin(4);
			}

			cout << endl;
			break;
		}

		case 'R': { // display rows

			cin >> x >> y;
			int disSize = y - x;

			int* disTemp = new int[disSize];
			

			for (int i = 0; i < disSize; i++) {
				disTemp[i] = x;
				x++;
			}

			/*cout << endl << "Array is: ";

			for (int i = 0; i < disSize; i++) {
				cout << disTemp[i] << " ";
			}

			cout << endl << endl ;*/

			DataFrame* tempD = new DataFrame(disSize + 1, numCols);
			string y = "  ";

			for (int i = 0; i < numCols; i++) {
				tempD->setColName(i, &y[0]);
			}

			//tempD->display();

			cout << endl;
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
