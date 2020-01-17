#include "VariableInfo.h"

VariableInfo::VariableInfo() {
	int numbits = 0;  //the number of bits for the variable, default 0
	string varName = "unassigned"; //the name of the variable, default "unassigned"
	char type = 'u'; // the type: "i" for input, "o" for output, "w" for wire, "u" for unassigned
	char sign = 'n'; //"u" for "unsigned", "s" for "signed", "n" for "not assigned"
}

//setters
void VariableInfo::setNumBits(int newNumBits) {
	numbits = newNumBits;
}

void VariableInfo::setVarName(string newVarName) {
	varName = newVarName;
}
void VariableInfo::setType(char newType) {
	type = newType;
}
void VariableInfo::setSign(char newSign) {
	sign = newSign;
}

//getters
int VariableInfo::getNumBits() {
	return numbits;
}
string VariableInfo::getVarName() {
	return varName;
}
char VariableInfo::getType() {
	return type;
}
char VariableInfo::getSign() {
	return sign;
}
