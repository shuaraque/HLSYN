#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

#ifndef ExpressionInfo_H
#define ExpressionInfo_H

class ExpressionInfo {
private:
	int maxBitSize; //maximum bit size in the expression
	string exType; // the type of expression: "ADD", "SUB", "MUX", etc
	string input1;  //first input
	string input2; //second input
	string output; //output name
	string sftAmount; // the shift amount for L/R shift
	string sel; //select signal for Mux
	string comp_op; // the operation wanted from the comparitor, "lt", "eq", or "gt"
	string condition; //identifyer for if, else if and else 
	vector<string> conditionVar; //logic conditions 
	int time;
	int slack;
	int done;
	int pos;
public:
	ExpressionInfo();
	void setMaxBitsize(int bitSize);
	void setExType(string newType);
	void setInput1(string newInput1);
	void setInput2(string newInput2);
	void setOutput(string newOutput);
	void setSftAmount(string newSftAmount);
	void setSel(string newSel);
	void setComp_Op(string newComp_Op);
	void setCondition(string newCondition);
	void addConditionVar(string newConditionVar);
	void setTime(int newTime);
	void setSlack(int newSlack);
	void setDone(int newDone);
	void setPos(int newPos);

	int getMaxBitsize();
	string getExType();
	string getInput1();
	string getInput2();
	string getOutput();
	string getSftAmount();
	string getSel();
	string getComp_Op();
	string getCondition();
	vector<string> getConditionsVar();
	int getTime();
	int getSlack();
	int getDone();
	int getPos();

};


#endif
