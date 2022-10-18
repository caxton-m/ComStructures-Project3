// DSA 5005 - Computing Structures
// Fall 2022
// Project 3
// Original editor - Aditya Narasimhan
// Modified by Caxton Muchono

#include <iostream>
#include <string>  // for the string fields
#include <vector>  // to store data
#include <fstream> // to read the csv file

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
	DFrow operator[](int i) {}

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

		display();
	
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
	DFrow searchRecord(string name) {}

	// Setters
	// change the name of a header/column
	void setColName(int col, char* name) {}

	// Getters
	// returns the number of rows
	int getNumberRows() {}

	// returns the number of columns
	int getNumberCols() {}

	// returns a dataframe with a set of cLen number of columns
	DataFrame* getColumns(int* columns, int cLen) {}

	// returns a data frame with a set of rLen number of rows
	DataFrame* getRows(int* rows, int rLen) {}

	// returns a data frame given a set of row numbers and column numbers
	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen) {}

	// returns the header name given a index position
	string getHeader(int i) {}

	// Find info of a given column
	// returns the average of the given column
	double findAverage(int colNumber) {}

	// returns the max of the given column
	double findMax(int colNumber) {}

	// returns the min of the given column
	double findMin(int colNumber) {}

	// displays the frequency of the unique values
	double frequency(int colNumber) {}

	// Destructor
	~DataFrame() {}
};

// main function
int main()
{
	int numRows, numCols;
	string fileName;
	string headerBool;
	char command;

	std::cin >> numRows >> numCols >> headerBool >> fileName;


	//// Read the file 
	//ifstream ip(fileName);

	//// Check to see if the file exists and if it does exist print error
	//if (!ip.is_open()) cout << "Error: File Open" << endl;

	//// all the fields to store information of a row
	//string nametemp;
	//string sextemp;
	//string agetemp;
	//string heighttemp;
	//string weighttemp;
	//string citytemp;
	//vector<string> headers;
	//vector<DFrow> data;


	//while (ip.good()) {

	//	if (headerBool == "true") {

	//		getline(ip, nametemp, ',');
	//		getline(ip, sextemp, ',');
	//		getline(ip, agetemp, ',');
	//		getline(ip, heighttemp, ',');
	//		getline(ip, weighttemp, ',');
	//		getline(ip, citytemp, '\n');

	//		headers.push_back(nametemp);
	//		headers.push_back(sextemp);
	//		headers.push_back(agetemp);
	//		headers.push_back(heighttemp);
	//		headers.push_back(weighttemp);
	//		headers.push_back(citytemp);

	//		headerBool = "false";
	//		continue;
	//	}

	//	getline(ip,nametemp,',');
	//	getline(ip, sextemp, ',');
	//	getline(ip, agetemp, ',');
	//	getline(ip, heighttemp, ',');
	//	getline(ip, weighttemp, ',');
	//	getline(ip, citytemp, '\n');

	//	data.push_back({ nametemp, sextemp[0], stoi(agetemp), stoi(heighttemp)
	//		, stoi(weighttemp), citytemp });

	//	//cout << headers[0] << ": " << nametemp << endl;
	//	//cout << headers[1] <<": " << s << endl;
	//	//cout << headers[2] <<": " << a << endl;
	//	//cout << headers[3] <<": " << h << endl;
	//	//cout << headers[4] <<": " << w << endl;
	//	//cout << headers[5] <<": " << citytemp << endl;
	//	//cout << " ------------------------- " << endl;
	//}

	//ip.close();

	//for (int i = 0; i < numCols; i++) {
	//	cout << headers[i] << " ";
	//}
	//cout << endl;

	//for (int i = 0; i < numRows; i++) {
	//	data[i].display();
	//}





	DataFrame* d = new DataFrame(numRows, numCols);

	d->readCSV(fileName, headerBool); // use this method to read in the data from the csv file

	// TODO: read the commands from the input file (redirected input)

	std::cin >> command;  // read the next command from input

	// while input is not end of file get next command 
	while (!std::cin.eof()) {
		// use switch cases to see the different commands to do next
		switch (command) {

		case 'F': { // option to find the record with a specific name

			cout << endl;
			break;
		}
		case 'D': { // option to display all the records along with the headers if exists 

			cout << endl;
			break;
		}
		case 'A': { // find the average of the different columns

			cout << endl;
			break;
		}
		case 'Q': { // find the frequency of unique values in the Sex columns

			cout << endl;
			break;
		}
		case 'X': { // find the max value of different columns

			cout << endl;
			break;
		}

		case 'I': { // find the min value of different columns

			cout << endl;
			break;
		}

		case 'R': { // display rows

			cout << endl;
			break;
		}

		default: cout << "No commands found";   // if no command found
		}

		std::cin >> command; // read the next command from input 
	}

 	return 0;
}
