#include "VariableInfo.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef VARIABLES_H
#define VARIABLES_H

class Variables { //class variables to create a vector of variables
private:
	vector <VariableInfo> variablesVector;
	int numVariables;
	int numIO;
public:
	Variables();
	void scanVariables(string FileName); //scans in the variables from input file
	void addVariable(VariableInfo newVariable);
	int getNumVariables();
	int getNumIO();
	VariableInfo getVarInfo(int i);
};



#endif
