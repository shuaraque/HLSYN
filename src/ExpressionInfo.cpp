#include "ExpressionInfo.h"

ExpressionInfo::ExpressionInfo() {
	maxBitSize = 0; //maximum bit size in the expression, default 0
	exType = "unassigned"; // the type of expression: "ADD", "SUB", "MUX", etc, default "unassigned"
	input1 = "none";  //first input, default "none"
	input2 = "none"; //second input, default "none"
	output = "none"; //output name, default "none"
	sftAmount = "none"; // the shift amount for L/R shift, default "none"
	sel = "none"; //select signal for Mux, default "none"
	comp_op = "none"; // the operation wanted from the comparitor, "lt", "eq", or "gt", default "none"
	time = 0;
	slack = 0;
	done = 0;
	pos = 1;
}

//Setters
void ExpressionInfo::setMaxBitsize(int bitSize) {
	maxBitSize = bitSize;
}
void ExpressionInfo::setTime(int newtime) {
	time = newtime;
}
void ExpressionInfo::setExType(string newType) {
	exType = newType;
}
void ExpressionInfo::setInput1(string newInput1) {
	input1 = newInput1;
}
void ExpressionInfo::setInput2(string newInput2) {
	input2 = newInput2;
}
void ExpressionInfo::setOutput(string newOutput) {
	output = newOutput;
}
void ExpressionInfo::setSftAmount(string newSftAmount) {
	sftAmount = newSftAmount;
}
void ExpressionInfo::setSel(string newSel) {
	sel = newSel;
}
void ExpressionInfo::setComp_Op(string newComp_Op) {
	comp_op = newComp_Op;
}
void ExpressionInfo::setCondition(string newCondition) {
	condition = newCondition;
}
void ExpressionInfo::addConditionVar(string newConditionVar) {
	conditionVar.push_back(newConditionVar);
}
void ExpressionInfo::setSlack(int newSlack) {
	slack = newSlack;
}
void ExpressionInfo::setDone(int newDone) {
	done = newDone;
}
void ExpressionInfo::setPos(int newPos) {
	pos = newPos;
}


//getters
int ExpressionInfo::getMaxBitsize() {
	return maxBitSize;
}
string ExpressionInfo::getExType() {
	return exType;
}
string ExpressionInfo::getInput1() {
	return input1;
}
string ExpressionInfo::getInput2() {
	return input2;
}
string ExpressionInfo::getOutput() {
	return output;
}
string ExpressionInfo::getSftAmount() {
	return sftAmount;
}
string ExpressionInfo::getSel() {
	return sel;
}
string ExpressionInfo::getComp_Op() {
	return comp_op;
}
string ExpressionInfo::getCondition() {
	return condition;
}
vector<string> ExpressionInfo::getConditionsVar() {
	return conditionVar;
}
int ExpressionInfo::getTime() {
	return time;
}
int ExpressionInfo::getSlack() {
	return slack;
}
int ExpressionInfo::getDone() {
	return done;
}
int ExpressionInfo::getPos() {
	return pos;
}
