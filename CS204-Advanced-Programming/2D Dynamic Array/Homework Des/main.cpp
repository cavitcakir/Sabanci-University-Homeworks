#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "matrixclass.h"

using namespace std;

int main()
{
	Matrix2D<string> stringMatrix1;
	Matrix2D<int> intMatrix1;

	Matrix2D<string> stringMatrix2;
	Matrix2D<int> intMatrix2;

	string fileName1, fileName2;

	cout << "Please enter a file name: ";
	cin >> fileName1;

	cout << "Please enter another file name: ";
	cin >> fileName2;

	ifstream file;
	file.open(fileName1.c_str());

	file >> intMatrix1;
	file.clear();
	file.seekg(0);
	file >> stringMatrix1;
	file.close();

	file.open(fileName2.c_str());

	file >> intMatrix2;
	file.clear();
	file.seekg(0);
	file >> stringMatrix2;
	file.close();

	cout << intMatrix1 + intMatrix2;
	cout << endl;
	cout << stringMatrix1 + stringMatrix2;

	cout << endl;
	intMatrix1 += intMatrix1;

	stringMatrix2 = stringMatrix1 + stringMatrix2;

	cout << intMatrix1 << endl <<  stringMatrix2 << endl;

	Matrix2D<int> newOne = intMatrix2 + intMatrix1;

	cout << newOne << endl;

	intMatrix1 = newOne;

	intMatrix1.SetIndex(0, 0, 10000);

	cout << intMatrix1 << endl;

	cout << newOne.GetIndex(0, 0) << endl;

	return 0;
}
