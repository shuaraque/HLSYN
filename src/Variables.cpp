#include "Variables.h"
#include "Epressions.h"
#include <fstream>
#include <sstream>
#include <istream>

Variables::Variables() {
	numVariables = 0;
	numIO = 0;
}
void Variables::scanVariables(string FileName) { //scans in the variables from input file
	ifstream inFS;
	int tempint = 0;
	int getVar;
	int peek = 1;
	string tempstring;
	char tempchar;
	string numCheck = "000";
	char check = 'a';
	char tempsign;
	char tempcharvect[255];

	inFS.open(FileName); //open file
	while (!inFS.eof()) {  //while not end of file
		VariableInfo tempVI; //temporary variable info

		//inFS.getline(tempcharvect, 255);
		inFS >> tempstring; //get string to check variable type
		getVar = 1;
		peek = 0;
		if (tempstring == "input") { //check if input
			tempchar = 'i';
		}
		else if (tempstring == "output") { //check if output
			tempchar = 'o';
		}
		else if (tempstring == "variable") {
			tempchar = 'w';
		}
		else if (tempstring == "register") {
			tempchar = 'r';
		}
		else {
			getVar = 0; //not a variable line
		}

		if (getVar == 1) {

			inFS >> tempstring; //get string to get bit size
			numCheck = "000";
			if (tempstring[0] == 'I') { //check for signed Int
				tempsign = 's';
				numCheck[0] = tempstring[3]; //saves the integer from string
				if (tempstring.length() > 4) {
					numCheck[1] = tempstring[4];
				}
				else {
					numCheck[1] = '\0';
				}

				if (tempstring.length() > 5) {
					numCheck[2] = tempstring[5];
				}
				else {
					numCheck[2] = '\0';
				}

			}
			if (tempstring[0] == 'U') { //check for unsigned int
				tempsign = 'u';
				numCheck[0] = tempstring[4];
				if (tempstring.length() > 5) { //saves the integer from the string
					numCheck[1] = tempstring[5];
				}
				else {
					numCheck[1] = '\0';
				}
				if (tempstring.length() > 6) {
					numCheck[2] = tempstring[6];
				}
				else {
					numCheck[2] = '\0';
				}
			}
			tempint = stoi(numCheck); //converts string to integer

			while (((tempstring[0] != '/' && tempstring[1]) != '/') && (peek != 1)) { //while the string is not a comment or not at the end of the line
				inFS >> tempstring;
				if (tempstring[tempstring.length() - 1] == ',') { //if the tempstring has a comma 
					tempstring.pop_back();  //remove comma
				}
				tempVI.setNumBits(tempint); //set numbits to tempint
				tempVI.setType(tempchar); //sets type to tempchar
				tempVI.setVarName(tempstring); //sets varName to tempstring
				tempVI.setSign(tempsign);
				variablesVector.push_back(tempVI); //adds temp variable input to variables vector
				numVariables = numVariables + 1; //increases the number of variables
				if (tempchar == 'i' || tempchar == 'o') { //if input or output, numIO increases
					numIO = numIO + 1;
				}

				check = inFS.peek();
				
				while (check == 32) {
					if (check == '\n') { // if the next character is a new line character
						peek = 1;
					}
					inFS.get(check);
					check = inFS.peek();
				}
				if (check == '\n') { // if the next character is a new line character
					peek = 1;
				}

			}
		}

		while (peek != 1) { // if the string was a part of a comment or not a variable line, get to end of line
			inFS.get(check);
			if (check == '\n' || inFS.eof()) {
				peek = 1;
			}
		}



	}
	inFS.close();

}

void Variables::addVariable(VariableInfo newVariable) {
	variablesVector.push_back(newVariable);
	numVariables = numVariables + 1;
	if (newVariable.getType() == 'i' || newVariable.getType() == 'o') {
		numIO = numIO + 1;
	}
}


int Variables::getNumVariables() {
	return numVariables;
}

int Variables::getNumIO() {
	return numIO;
}

VariableInfo Variables::getVarInfo(int i) {
	return variablesVector.at(i);
}