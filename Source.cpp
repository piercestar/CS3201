#include <iostream>
#include <iterator>
#include "ResultTable.h"
using namespace std;

// First off, i need a main tester that will help me test my functions
void main() {

	/*****************************************************************/
	// Insert your modules to test in here:
	
	ResultTable newTable = ResultTable(1);
	vector<string> variableOne;
	vector<string> variableTwo;

	variableOne.push_back(to_string(10));
	for (int i = 0; i < 10; i++) {
		variableOne.push_back(to_string(stoi(variableOne.back()) - 1));
	}
	variableTwo.push_back(to_string(12));
	for (int i = 0; i < 6; i++) {
		variableTwo.push_back(to_string(stoi(variableTwo.back()) - 2));
	}

	//vector<string>::iterator it = variableOne.begin();
	//vector<string>::iterator it2 = variableTwo.begin();
	//while (it != variableOne.end()) {
	//	cout << (*it) << ",";
	//	it++;
	//}
	//cout << endl;
	//while (it2 != variableTwo.end()) {
	//	cout << (*it2) << ",";
	//	it2++;
	//}
	//cout << endl;

	newTable.addClauseSet(0, variableOne);
	newTable.addClauseSet(0, variableTwo);
	newTable.addClauseSet(0, variableOne);

	newTable.displayResultTable();

	newTable.mergeTable();

	newTable.displayResultTable();

	/*****************************************************************/

	// Pause program
	cin.get();
}