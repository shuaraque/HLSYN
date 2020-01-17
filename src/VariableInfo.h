#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef VariableInfo_H
#define VariableInfo_H


class VariableInfo {//class variableInfo to store the all the inputs, wires, and outputs
private:
	int numbits;  //the number of bits for the variable
	string varName; //the name of the variable
	char type; // the type: "i" for input, "o" for output, "w" for wire, "u" for unassigned
	char sign; // "u" for unsigned, "s" for signed

public:
	VariableInfo();
	void setNumBits(int newNumBits);
	void setVarName(string newVarName);
	void setType(char newType);
	void setSign(char newSign);

	int getNumBits();
	string getVarName();
	char getType();
	char getSign();
};




#endif
