#define _CRT_SECURE_NO_WARNINGS
#include "Epressions.h"
#include "VariableInfo.h"
#include "ExpressionInfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	FILE* netListFile;

	Variables variableList;
	Expressions expressionList;
	int latency;

	int error = 0;  //stores error code


	if (argc != 4) { //if there are too few or too many commmand line arguments
		cout << "Incorrect number of inputs" << endl;
		cout << "usage: hlsyn cFile latency verilogFile" << endl;
		return 0;
	}

	//netListFile = fopen(argv[1], "r");

	//if (netListFile == NULL) { //checks if netlist files exists
	//cout << "Netlist file does not exist." << endl;
	//return 0;
	//}
	latency = atoi(argv[2]);
	variableList.scanVariables(argv[1]); //scans variables to variableList
	error = expressionList.scanExpressions(argv[1], variableList, latency); //scans expressions to expressionList outputting an integer for error

	if (error == 1) { //error warning for missing input
		cout << "Error! Missing input." << endl;
		return 1;
	}

	else if (error == 3) { // error warning for missing wire
		cout << "Error! Missing variable." << endl;
		return 3;
	}

	else if (error == 2) { //error warning for missing output
		cout << "Error! Missing output." << endl;
		return 2;
	}

	else if (error == 4) { //error for unknow operator
		cout << "Error! Unknown operator." << endl;
		return 4;
	}
	else if (error == 5) { //error for unknow operator
		cout << "Error! Different variable types." << endl;
		return 5;
	}
	else if (error == 10)   {
		cout << "Error! Latency too small." << endl;
		return 10;
	}
	else { // if there are no errors in netlist file
		expressionList.printExpressions(argv[3], variableList, latency);  //prints the list of expresions into the netlist file
	}




	return 0;
}





