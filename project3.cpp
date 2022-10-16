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
	DFrow(); // default constructor
	DFrow(string n, char c, int one, int two, int three, string ci); // non-default constructor
	// TODO: write getters for each of the fields

	// TODO: write setters for each of the fields

	// TODO: write display method to display all the fields in the same order
	// 			refer to output sample for exact format

	// TODO: write destructor
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
	DataFrame();
	DataFrame(int rows, int cols);

	// Overload the [] operator to access data in DF
	DFrow operator[](int i);

	// File reading Method
	void readCSV(string filename, string headerPresence);

	// Output Method
	void display();

	// Search Record
	DFrow searchRecord(string name);

	// Setters
	void setColName(int col, char* name); // change the name of a header/column

	// Getters
	int getNumberRows();                                              // returns the number of rows
	int getNumberCols();                                              // returns the number of columns
	DataFrame* getColumns(int* columns, int cLen);                    // returns a dataframe with a set of cLen number of columns
	DataFrame* getRows(int* rows, int rLen);                          // returns a data frame with a set of rLen number of rows
	DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen); // returns a data frame given a set of row numbers and column numbers
	string getHeader(int i);                                          // returns the header name given a index position

	// Find info of a given column
	double findAverage(int colNumber); // returns the average of the given column
	double findMax(int colNumber);     // returns the max of the given column
	double findMin(int colNumber);     // returns the min of the given column
	double frequency(int colNumber);   // displays the frequency of the unique values

	// Destructor
	~DataFrame();
};

// main function
int main()
{
	int numRows, numCols;
	string fileName;
	string headerBool;
	char command;

	cin >> numRows >> numCols >> headerBool >> fileName;

	DataFrame* d = new DataFrame(numRows, numCols);

	d->readCSV(fileName, headerBool); // use this method to read in the data from the csv file

	// TODO: read the commands from the input file (redirected input)

	return 0;
}
