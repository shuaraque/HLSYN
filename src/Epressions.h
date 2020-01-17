#ifndef EXPRSSIONS_H
#define EXPRESSIONS_H
#include "ExpressionInfo.h"
#include "Variables.h"
#include <vector>
#include <string>

using namespace std;

class Expressions {
private:
	vector<ExpressionInfo> expressionsVector;
	int numExpresssions;

public:
	Expressions();
	int getNumExpressions();
	void addExpression(ExpressionInfo newExpression);
	int scanExpressions(string inputFile, Variables variableVector, int latency); // scans in expressions from file, returns an integer for error code
	void printExpressions(string outputFIle, Variables list, int latency);  // writes the expressions in verilog format in output file
	int checkVariables(string varName, char varType, Variables list);  //checks if the name and type of variable is saved in list of variables, 
	int ALAP(int latency);													//returns an integer for error code


};


#endif
