#include "Epressions.h"
#include "Variables.h"
#include"ExpressionInfo.h"
#include "VariableInfo.h"
#include <fstream>

Expressions::Expressions() {
    numExpresssions = 0;
}
int Expressions::getNumExpressions() {
    return numExpresssions;
}
void Expressions::addExpression(ExpressionInfo newExpression) {
    expressionsVector.push_back(newExpression);
    numExpresssions = numExpresssions + 1;
}


int Expressions::scanExpressions(string inputFile, Variables variableVector, int latency) { // scans in expressions from file, returns an integer for error code
    int error = 0;
    int outputerror = 0;
    int numTabs = 0;
    int i = 0;
    ifstream inFS;
    inFS.open(inputFile);
    string tempstring;
    int skipline = 0;
    string outputstring;
    string input1string;
    string input2string;
    vector<string> conditions;
    char operationchar;
    char check = 0;
    int peek = 0;
    vector <string> newVarList;
    int tag = 0;
    string lastCon;
    bool consecIf = false;
    
    
    while (!inFS.eof()) {
        inFS >> tempstring;
        skipline = 0;
        check = 0;
        for (i = 0; i < numTabs; ++i) {
            
        }
        if (tempstring == "input" || tempstring == "output" || tempstring == "variable" || tempstring == "register") {
            skipline = 1;
        }
        
        while (skipline != 1 && peek == 0  && !inFS.eof()) { //when now reading in expressions
            ExpressionInfo tempExInfo; //t1
            if (tempstring == "if"){
                inFS >> tempstring;
                inFS >> tempstring;
                conditions.insert(conditions.begin(),tempstring);
                for(i=0; i<= tag; i++){
                tempExInfo.addConditionVar(conditions.at(i));
                    cout << tempExInfo.getConditionsVar().at(i);
                }
                inFS >> tempstring;
                inFS >> tempstring;
                inFS >> tempstring;
                
                if(tempstring == "if"){
                        tag = tag + 1;
                        consecIf = true;
                }
                
                else{
                    consecIf = false;
                }
                
                if(consecIf == false){
                outputstring = tempstring;
                newVarList.push_back(tempstring);
                tempExInfo.setCondition("if");
                
                if (outputerror == 0) {
                    outputerror = checkVariables(tempstring + '\0', 'o', variableVector); //check if variable was declared
                }
                
                inFS >> tempstring;
                inFS >> tempstring;
                input1string = tempstring;
                newVarList.push_back(tempstring);
                error = checkVariables(tempstring + '\0', 'i', variableVector);
                if (error != 0) {
                    return error + outputerror;
                }
                
                inFS.get(operationchar);
                if (operationchar != '\n') {
                    inFS.get(operationchar);
                }
                
                
                if (operationchar == '\n' || inFS.eof()) { //saves info as register
                    tempExInfo.setExType("REG");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                }
                else if (operationchar == '+') { //reads info and saves strings for add
                    tempExInfo.setExType("ADD");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '-') { //reads info and saves strings for sub
                    tempExInfo.setExType("SUB");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '*') { //reads info and saves strings for mult
                    tempExInfo.setExType("MUL");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '>') { //checks if SFR or comp (gt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '>') { //reads info and saves strings for SHR
                        tempExInfo.setExType("SHR");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (gt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("gt");
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    
                }
                else if (operationchar == '<') { //checks if SHL or comp (lt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '<') { //reads info and save strings for SHL
                        tempExInfo.setExType("SHL");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (lt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("lt");
                    }
                    
                }
                else if (operationchar == '=') { //reads info and saves string for the comp (eq)
                    tempExInfo.setExType("COMP");
                    inFS.get(operationchar);
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                    tempExInfo.setComp_Op("eq");
                }
                else if (operationchar == '?') { //reads info and saves strings for the Mux
                    tempExInfo.setExType("MUX2x1");
                    tempExInfo.setSel(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setOutput(outputstring);
                    inFS >> input1string;
                    newVarList.push_back(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    inFS >> tempstring;
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setInput2(input2string);
                    
                    
                }
                else {
                    return 4; //returns error for unknown operation
                }
                

                if(tempstring != "}"){
                    tag = tag + 1;
                }
                
                else{
                    tag = tag - 1;
                    lastCon = conditions.at(0);
                    conditions.erase(conditions.begin());
                }
                }}
            
            else if (conditions.size() != 0){
                for(i=0; i< tag; i++){
                tempExInfo.addConditionVar(conditions.at(i));
                }
                
                outputstring = tempstring;
                newVarList.push_back(tempstring);
                tempExInfo.setCondition("if");
                
                if (outputerror == 0) {
                    outputerror = checkVariables(tempstring + '\0', 'o', variableVector); //check if variable was declared
                }
                
                inFS >> tempstring;
                inFS >> tempstring;
                input1string = tempstring;
                newVarList.push_back(tempstring);
                error = checkVariables(tempstring + '\0', 'i', variableVector);
                if (error != 0) {
                    return error + outputerror;
                }
                
                inFS.get(operationchar);
                if (operationchar != '\n') {
                    inFS.get(operationchar);
                }
                
                
                if (operationchar == '\n' || inFS.eof()) { //saves info as register
                    tempExInfo.setExType("REG");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                }
                else if (operationchar == '+') { //reads info and saves strings for add
                    tempExInfo.setExType("ADD");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '-') { //reads info and saves strings for sub
                    tempExInfo.setExType("SUB");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '*') { //reads info and saves strings for mult
                    tempExInfo.setExType("MUL");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '>') { //checks if SFR or comp (gt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '>') { //reads info and saves strings for SHR
                        tempExInfo.setExType("SHR");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (gt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("gt");
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    
                }
                else if (operationchar == '<') { //checks if SHL or comp (lt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '<') { //reads info and save strings for SHL
                        tempExInfo.setExType("SHL");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (lt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("lt");
                    }
                    
                }
                else if (operationchar == '=') { //reads info and saves string for the comp (eq)
                    tempExInfo.setExType("COMP");
                    inFS.get(operationchar);
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                    tempExInfo.setComp_Op("eq");
                }
                else if (operationchar == '?') { //reads info and saves strings for the Mux
                    tempExInfo.setExType("MUX2x1");
                    tempExInfo.setSel(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setOutput(outputstring);
                    inFS >> input1string;
                    newVarList.push_back(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    inFS >> tempstring;
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setInput2(input2string);
                    
                    
                }
                else {
                    return 4; //returns error for unknown operation
                }
                

                if(tempstring != "}"){
                }
                
                else{
                    tag = tag - 1;
                    lastCon = conditions.at(0);
                    conditions.erase(conditions.begin());
                }
                }
            
            else if (tempstring == "else") {
                inFS >> tempstring;
                inFS >> tempstring;
                lastCon = "!" + lastCon;
                conditions.insert(conditions.begin(),lastCon);
                for(i=0; i<= tag; i++){
                tempExInfo.addConditionVar(conditions.at(i));
                }
                outputstring = tempstring;
                newVarList.push_back(tempstring);
                tempExInfo.setCondition("if");
                
                if (outputerror == 0) {
                    outputerror = checkVariables(tempstring + '\0', 'o', variableVector); //check if variable was declared
                }
                
                inFS >> tempstring;
                inFS >> tempstring;
                input1string = tempstring;
                newVarList.push_back(tempstring);
                error = checkVariables(tempstring + '\0', 'i', variableVector);
                if (error != 0) {
                    return error + outputerror;
                }
                
                inFS.get(operationchar);
                if (operationchar != '\n') {
                    inFS.get(operationchar);
                }
                
                
                if (operationchar == '\n' || inFS.eof()) { //saves info as register
                    tempExInfo.setExType("REG");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                }
                else if (operationchar == '+') { //reads info and saves strings for add
                    tempExInfo.setExType("ADD");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '-') { //reads info and saves strings for sub
                    tempExInfo.setExType("SUB");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '*') { //reads info and saves strings for mult
                    tempExInfo.setExType("MUL");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '>') { //checks if SFR or comp (gt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '>') { //reads info and saves strings for SHR
                        tempExInfo.setExType("SHR");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (gt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("gt");
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    
                }
                else if (operationchar == '<') { //checks if SHL or comp (lt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '<') { //reads info and save strings for SHL
                        tempExInfo.setExType("SHL");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (lt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("lt");
                    }
                    
                }
                else if (operationchar == '=') { //reads info and saves string for the comp (eq)
                    tempExInfo.setExType("COMP");
                    inFS.get(operationchar);
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                    tempExInfo.setComp_Op("eq");
                }
                else if (operationchar == '?') { //reads info and saves strings for the Mux
                    tempExInfo.setExType("MUX2x1");
                    tempExInfo.setSel(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setOutput(outputstring);
                    inFS >> input1string;
                    newVarList.push_back(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    inFS >> tempstring;
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setInput2(input2string);
                    
                    
                }
                else {
                    return 4; //returns error for unknown operation
                }
                
                if(tempstring != "}"){
                    tag = tag + 1;
                }
                
                else{
                    tag = tag - 1;
                    lastCon = conditions.at(0);
                    conditions.erase(conditions.begin());
                }
            }
            
            else{
                if(consecIf == false){
                tempExInfo.setCondition("none");
                outputstring = tempstring;
                newVarList.push_back(tempstring);
                
                if (outputerror == 0) {
                    outputerror = checkVariables(tempstring + '\0', 'o', variableVector); //check if variable was declared
                }
                
                inFS >> tempstring;
                inFS >> tempstring;
                input1string = tempstring;
                newVarList.push_back(tempstring);
                error = checkVariables(tempstring + '\0', 'i', variableVector);
                if (error != 0) {
                    return error + outputerror;
                }
                
                inFS.get(operationchar);
                if (operationchar != '\n') {
                    inFS.get(operationchar);
                }
                
                
                if (operationchar == '\n' || inFS.eof()) { //saves info as register
                    tempExInfo.setExType("REG");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                }
                else if (operationchar == '+') { //reads info and saves strings for add
                    tempExInfo.setExType("ADD");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string); //check this
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '-') { //reads info and saves strings for sub
                    tempExInfo.setExType("SUB");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '*') { //reads info and saves strings for mult
                    tempExInfo.setExType("MUL");
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                }
                else if (operationchar == '>') { //checks if SFR or comp (gt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '>') { //reads info and saves strings for SHR
                        tempExInfo.setExType("SHR");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (gt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("gt");
                        error = checkVariables(tempstring + '\0', 'i', variableVector);
                        if (error != 0) {
                            return error + outputerror;
                        }
                    }
                    
                }
                else if (operationchar == '<') { //checks if SHL or comp (lt)
                    inFS.get(operationchar);
                    inFS >> tempstring;
                    newVarList.push_back(tempstring);
                    error = checkVariables(tempstring + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    if (operationchar == '<') { //reads info and save strings for SHL
                        tempExInfo.setExType("SHL");
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setSftAmount(tempstring);
                    }
                    else {
                        tempExInfo.setExType("COMP"); //reads info and saves string for the comp (lt)
                        tempExInfo.setInput1(input1string);
                        tempExInfo.setOutput(outputstring);
                        tempExInfo.setInput2(tempstring);
                        tempExInfo.setComp_Op("lt");
                    }
                    
                }
                else if (operationchar == '=') { //reads info and saves string for the comp (eq)
                    tempExInfo.setExType("COMP");
                    inFS.get(operationchar);
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setOutput(outputstring);
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput2(input2string);
                    tempExInfo.setComp_Op("eq");
                }
                else if (operationchar == '?') { //reads info and saves strings for the Mux
                    tempExInfo.setExType("MUX2x1");
                    tempExInfo.setSel(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setOutput(outputstring);
                    inFS >> input1string;
                    newVarList.push_back(input1string);
                    error = checkVariables(input1string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    inFS >> tempstring;
                    inFS >> input2string;
                    newVarList.push_back(input2string);
                    error = checkVariables(input2string + '\0', 'i', variableVector);
                    if (error != 0) {
                        return error + outputerror;
                    }
                    tempExInfo.setInput1(input1string);
                    tempExInfo.setInput2(input2string);
                    
                    
                }
                else {
                    return 4; //returns error for unknown operation
                }
                }}
            
            cout << tempExInfo.getCondition() << " Size of Conditions:" << tempExInfo.getConditionsVar().size() << " " << tempExInfo.getOutput() << "=" << tempExInfo.getInput1() << " " << tempExInfo.getExType() << " " << tempExInfo.getInput2() << "\n";
            if(consecIf == false){
            expressionsVector.push_back(tempExInfo);
            numExpresssions = numExpresssions + 1;
            check = inFS.peek();
            while (check != '\n' && operationchar != '\n') { // if the next character is not a new line character, then this while loop will find the next
                inFS.get(check);							//'\n' character or end of file
                    if (inFS.eof()) {
                        check = '\n';
                    }
                }
            if (inFS.eof()) {
                break;
            }
            inFS >> tempstring;
                cout << tempstring;
            while(tempstring == "}"){
                tag = tag - 1;
                if(conditions.size() != 0){
                lastCon = conditions.at(0);
                conditions.erase(conditions.begin());
                inFS >> tempstring;
            }
                else{
                    break;
                }
            }}
        }

        check = inFS.peek();
        while (check != '\n' && operationchar != '\n') { // if the next character is not a new line character, then this while loop will find the next
                inFS.get(check);                            //'\n' character or end of file
                if (inFS.eof()) {
                    check = '\n';
                }
            }
        if (inFS.eof()) {
            break;
        }
    }
    error = ALAP(latency);
    return error + outputerror;
}
void Expressions::printExpressions(string outputFIle, Variables list, int latency) {  // writes the expressions in verilog format in output file
    ofstream printFile;
    int i;
    int j;
    int state = 0;
    int exLat = 0;
    int input1pos;
    int input2pos;
    int outputpos;
    int sign = 0;
    int input1sign = 0;
    int input2sign = 0;
    int maxbitsize = 0;
    
    
    
    printFile.open(outputFIle);
    if (printFile.is_open()) {
        printFile << "`timescale 1ns / 1ps\n";
        printFile << "module HLSM (";
        //printFile << list.getNumVariables
        
        printFile << "Clk, Rst, Start, Done, ";
        
        
        for (i = 0; i < list.getNumVariables(); i++) {
            if ((list.getVarInfo(i).getType() == 'i') | (list.getVarInfo(i).getType() == 'o')) {
                printFile << list.getVarInfo(i).getVarName();
                if ((i + 1) != list.getNumIO()) {
                    printFile << ", ";
                }
            }
        }
        printFile << ")\n";
        printFile << "\tinput Clk, Rst, Start;\n";
        for (i = 0; i < list.getNumVariables(); i++) {
            if (list.getVarInfo(i).getType() == 'i') {
                printFile << "\tinput ";
                if (list.getVarInfo(i).getSign() == 's') {
                    printFile << "signed ";
                }
                if (list.getVarInfo(i).getNumBits() != 1) {
                    printFile << "[";
                    printFile << (list.getVarInfo(i).getNumBits() - 1);
                    printFile << ":0] ";
                }
                printFile << list.getVarInfo(i).getVarName();
                if ((i + 1) != list.getNumVariables()) {
                    while ((list.getVarInfo(i).getNumBits() == list.getVarInfo(i + 1).getNumBits()) && (list.getVarInfo(i + 1).getType() == 'i') && (list.getVarInfo(i).getSign() == list.getVarInfo(i + 1).getSign())) {
                        if (i + 1 == list.getNumVariables()) {
                            break;
                        }
                        else {
                            i = i + 1;
                        }
                        printFile << ", " << list.getVarInfo(i).getVarName();
                        
                    }
                    
                }
                printFile << ";\n";
                if (i + 1 == list.getNumVariables()) {
                    break;
                }
            }
        }
        
        printFile << "\toutput reg Done;\n";
        for (i = 0; i < list.getNumVariables(); i++) {
            if (list.getVarInfo(i).getType() == 'o') {
                printFile << "\toutput reg ";
                if (list.getVarInfo(i).getSign() == 's') {
                    printFile << "signed ";
                }
                if (list.getVarInfo(i).getNumBits() != 1) {
                    printFile << "[";
                    printFile << (list.getVarInfo(i).getNumBits() - 1);
                    printFile << ":0] ";
                }
                printFile << list.getVarInfo(i).getVarName();
                if ((i + 1) != list.getNumVariables()) {
                    while ((list.getVarInfo(i).getNumBits() == list.getVarInfo(i + 1).getNumBits()) && (list.getVarInfo(i + 1).getType() == 'o') && (list.getVarInfo(i).getSign() == list.getVarInfo(i + 1).getSign())) {
                        if (i + 1 == list.getNumVariables()) {
                            break;
                        }
                        else {
                            i = i + 1;
                        }
                        printFile << ", " << list.getVarInfo(i).getVarName();
                        
                    }
                    
                }
                printFile << ";\n";
                if (i + 1 == list.getNumVariables()) {
                    break;
                }
            }
        }
        
        for (i = 0; i < list.getNumVariables(); i++) {
            if (list.getVarInfo(i).getType() == 'w') {
                printFile << "\treg ";
                if (list.getVarInfo(i).getSign() == 's') {
                    printFile << "signed ";
                }
                if (list.getVarInfo(i).getNumBits() != 1) {
                    printFile << "[";
                    printFile << (list.getVarInfo(i).getNumBits() - 1);
                    printFile << ":0] ";
                }
                printFile << list.getVarInfo(i).getVarName();
                
                if ((i + 1) != list.getNumVariables()) {
                    while ((list.getVarInfo(i).getNumBits() == list.getVarInfo(i + 1).getNumBits()) && (list.getVarInfo(i + 1).getType() == 'w') && (list.getVarInfo(i).getSign() == list.getVarInfo(i + 1).getSign())) {
                        if (i + 1 == list.getNumVariables()) {
                            break;
                        }
                        else {
                            i = i + 1;
                        }
                        printFile << ", " << list.getVarInfo(i).getVarName();
                        if (i + 1 == list.getNumVariables()) {
                            break;
                        }
                    }
                    
                }
                printFile << ";\n";
            }
        }
        
        
        printFile << "\n\tparameter Wait = 0, Final = 1, ";
        for (i = 0; i < latency; i++) {
            printFile << "S" << i << " = " << i + 2;
            if (i != (latency - 1)) {
                printFile << ", ";
            }
        }
        printFile << ";" << endl;
        
        printFile << "\n\treg [" << latency / 4 << ":0] State, StateNext;" << endl;  //************FIX ME******************
        printFile << "\n\talways @(*) begin\n";
        printFile << "\t\tcase(State)" << endl;
        printFile << "\t\t\tWait: begin" << endl;
        printFile << "\t\t\t\tif(Start == 1) begin" << endl;
        printFile << "\t\t\t\t\tStateNext <= S0;" << endl;
        printFile << "\t\t\t\tend\n\t\t\tend\n" << endl;
        printFile << "\t\t\tFinal: begin" << endl;
        printFile << "\t\t\t\tDone <= 1;" << endl;
        printFile << "\t\t\t\tStateNext <= Wait;" << endl;
        printFile << "\t\t\tend\n" << endl;
        
        for (i = 0; i < latency; i++) {
            for (j = 0; j < numExpresssions; j++) {
                if (expressionsVector.at(j).getTime() == i + 1) {
                printFile << "\t\t\tS" << state << ": begin" << endl;
                    state = state +1;
                if(expressionsVector.at(j).getCondition() == "if"){
                    cout << "caught " + expressionsVector.at(j).getCondition() << "\n";
                        printFile << "\t\t\tif(";
                        for(int k = 0; k < expressionsVector.at(j).getConditionsVar().size();k++){
                            if(k >= 1){
                                printFile << " && ";
                            }
                            printFile << expressionsVector.at(j).getConditionsVar().at(k);
                        }
                        printFile << "){\n";
                        
                        printFile << "\t\t\t\t" << expressionsVector.at(j).getOutput() << " <= ";
                        if (expressionsVector.at(j).getExType() == "MUX2x1") {
                            printFile << expressionsVector.at(j).getSel() << " ? " << expressionsVector.at(j).getInput1() << " : " << expressionsVector.at(j).getInput2() << ";";
                        }
                        else {
                            printFile << expressionsVector.at(j).getInput1();
                            if (expressionsVector.at(j).getExType() == "ADD") {
                                printFile << " + " << expressionsVector.at(j).getInput2() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "SUB") {
                                printFile << " - " << expressionsVector.at(j).getInput2() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "MUL") {
                                printFile << " * " << expressionsVector.at(j).getInput2() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "REG") {
                                printFile << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "COMP") {
                                if (expressionsVector.at(j).getComp_Op() == "gt") {
                                    printFile << " > " << expressionsVector.at(j).getInput2() << ";";
                                }
                                else if (expressionsVector.at(j).getComp_Op() == "lt") {
                                    printFile << " < " << expressionsVector.at(j).getInput2() << ";";
                                }
                                else if (expressionsVector.at(j).getComp_Op() == "eq") {
                                    printFile << " == " << expressionsVector.at(j).getInput2() << ";";
                                }
                            }
                            else if (expressionsVector.at(j).getExType() == "SHL") {
                                printFile << " << " << expressionsVector.at(j).getSftAmount() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "SHR") {
                                printFile << " >> " << expressionsVector.at(j).getSftAmount() << ";";
                            }
                        }
                        printFile << endl;
                    if (i == latency - 1) {
                        printFile << "\t\t\t\tStateNext <= Final;" << endl;
                    }
                    else {
                        printFile << "\t\t\t\tStateNext <= S" << state << ";\n\t\t\t}" << endl;
                    }
                    
                    printFile << "\t\t\telse{\n";
                    if (i == latency - 1) {
                        printFile << "\t\t\t\tStateNext <= Final;" << endl;
                    }
                    else {
                        printFile << "\t\t\t\tStateNext <= S" << state << ";" << endl;
                    }
                    printFile << "\t\t\t}\n\t\t\tend\n" << endl;
                }
                else if(expressionsVector.at(j).getCondition() == "none"){
                    if (expressionsVector.at(j).getTime() == i + 1) {
                        printFile << "\t\t\t\t" << expressionsVector.at(j).getOutput() << " <= ";
                        if (expressionsVector.at(j).getExType() == "MUX2x1") {
                            printFile << expressionsVector.at(j).getSel() << " ? " << expressionsVector.at(j).getInput1() << " : " << expressionsVector.at(j).getInput2() << ";";
                        }
                        else {
                            printFile << expressionsVector.at(j).getInput1();
                            if (expressionsVector.at(j).getExType() == "ADD") {
                                printFile << " + " << expressionsVector.at(j).getInput2() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "SUB") {
                                printFile << " - " << expressionsVector.at(j).getInput2() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "MUL") {
                                printFile << " * " << expressionsVector.at(j).getInput2() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "REG") {
                                printFile << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "COMP") {
                                if (expressionsVector.at(j).getComp_Op() == "gt") {
                                    printFile << " > " << expressionsVector.at(j).getInput2() << ";";
                                }
                                else if (expressionsVector.at(j).getComp_Op() == "lt") {
                                    printFile << " < " << expressionsVector.at(j).getInput2() << ";";
                                }
                                else if (expressionsVector.at(j).getComp_Op() == "eq") {
                                    printFile << " == " << expressionsVector.at(j).getInput2() << ";";
                                }
                            }
                            else if (expressionsVector.at(j).getExType() == "SHL") {
                                printFile << " << " << expressionsVector.at(j).getSftAmount() << ";";
                            }
                            else if (expressionsVector.at(j).getExType() == "SHR") {
                                printFile << " >> " << expressionsVector.at(j).getSftAmount() << ";";
                            }
                        }
                        printFile << endl;
                    }
                    if (i == latency - 1) {
                        printFile << "\t\t\t\tStateNext <= Final;" << endl;
                    }
                    else {
                        printFile << "\t\t\t\tStateNext <= S" << state << ";" << endl;
                    }
                    printFile << "\t\t\tend\n" << endl;
                }
            }
            }
        }
        
        if(state < latency){
            for (i=state; i <= latency; i++) {
                printFile << "\t\t\tS" << i << ": begin" << endl;
                if (i == latency) {
                    printFile << "\t\t\t\tStateNext <= Final;" << endl;
                }
                else {
                    printFile << "\t\t\t\tStateNext <= S" << i+1 << ";" << endl;
                }
                printFile << "\t\t\tend\n\n";
            }
        }
        
    }
            printFile << "\t\tendcase" << endl;
            printFile << "\tend\n" << endl;
            printFile << "\talways@(posedge Clk) begin" << endl;
            printFile << "\t\tif (Rst == 1) begin" << endl;
            printFile << "\t\t\tState <= Wait;" << endl;
            printFile << "\t\tend" << endl;
            printFile << "\t\telse begin" << endl;
            printFile << "\t\t\tState <= StateNext;" << endl;
            printFile << "\t\tend" << endl;
            printFile << "\tend" << endl;
            printFile << "endmodule\n";
}

int Expressions::checkVariables(string varName, char varType, Variables list) {  //checks if the name and type of variable is saved in list of variables, 
    string name;																	//returns an integer for error code
    int i = 0;
    for (i = 0; i < list.getNumVariables(); i++) {
        name = list.getVarInfo(i).getVarName();
        if (name[name.length() - 1] != '\0') {
            name = name + '\0';
        }
        if (name.compare(varName) == 0) {
            return 0;
        }
    }
    if (varType == 'i') {
        return 1;
    }
    else if (varType == 'o') {
        return 2;
    }
    return 20;
    
}

int Expressions::ALAP(int latency) {
    int i;
    int j;
    int time;
    for (i = 0; i < numExpresssions; i++) {
        expressionsVector.at(i).setTime(latency);
    }
    for (i = numExpresssions - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            if (expressionsVector.at(i).getInput1() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(i).getTime() <= expressionsVector.at(j).getTime()) {
                    if (expressionsVector.at(j).getExType() == "MUL") {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 2);
                    }
                    else {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 1);
                    }
                }
            }
            else if (expressionsVector.at(i).getInput2() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(i).getTime() <= expressionsVector.at(j).getTime()) {
                    if (expressionsVector.at(j).getExType() == "MUL") {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 2);
                    }
                    else {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 1);
                    }
                }
            }
            else if (expressionsVector.at(i).getSel() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(i).getTime() <= expressionsVector.at(j).getTime()) {
                    if (expressionsVector.at(i).getExType() == "MUL") {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 2);
                    }
                    else {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 1);
                    }
                }
            }
            else if (expressionsVector.at(i).getSftAmount() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(i).getTime() <= expressionsVector.at(j).getTime()) {
                    if (expressionsVector.at(j).getExType() == "MUL") {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 2);
                    }
                    else {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 1);
                    }
                }
            }
            else if (expressionsVector.at(i).getComp_Op() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(i).getTime() <= expressionsVector.at(j).getTime()) {
                    if (expressionsVector.at(j).getExType() == "MUL") {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 2);
                    }
                    else {
                        expressionsVector.at(j).setTime(expressionsVector.at(i).getTime() - 1);
                    }
                }
            }
            
        }
        
    }
    
    if (expressionsVector.at(0).getTime() <= 0) {
        return 10;
    }
    
    
    //starts List_R
    
    
    int numMUL = 1;
    int numALU = 1;
    int newMUL = 0;
    int newALU = 0;
    int prevMUL = 0;
    int tempMUL = 0;
    int numLOGIC = 1;
    int newLOGIC = 0;
    
    for (i = 0; i < numExpresssions; i++) {
        for (j = 0; j < numExpresssions; j++) {
            if (expressionsVector.at(i).getInput1() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(j).getExType() == "MUL") {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 2);
                }
                else {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 1);
                }
            }
            if (expressionsVector.at(i).getInput2() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(j).getExType() == "MUL") {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 2);
                }
                else {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 1);
                }
            }
            if (expressionsVector.at(i).getSel() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(j).getExType() == "MUL") {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 2);
                }
                else {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 1);
                }
            }
            if (expressionsVector.at(i).getSftAmount() == expressionsVector.at(j).getOutput()) {
                if (expressionsVector.at(j).getExType() == "MUL") {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 2);
                }
                else {
                    expressionsVector.at(i).setPos(expressionsVector.at(j).getPos() + 1);
                }
            }
        }
    }
    
    for (i = 1; i <= latency; ++i) {
        vector <int> MUL;
        vector <int> ALU;
        vector <int> LOGIC;
        for (j = 0; j < numExpresssions; j++) {
            if ((expressionsVector.at(j).getPos() <= i) && (expressionsVector.at(j).getDone() == 0)) {
                if (expressionsVector.at(j).getExType() == "MUL") {
                    MUL.push_back(j);
                }
                else if(expressionsVector.at(j).getExType() == "ADD"|expressionsVector.at(j).getExType() == "SUB"){
                    ALU.push_back(j);
                }
                else{
                    LOGIC.push_back(j);
                }
                expressionsVector.at(j).setSlack(expressionsVector.at(j).getTime() - i);
            }
        }
        
        for (j = 0; j < MUL.size(); j++) {
            if (expressionsVector.at(MUL.at(j)).getSlack() == 0) {
                newMUL = newMUL + 1;
            }
        }
        if (newMUL > numMUL) {
            numMUL = newMUL;
        }
        else {
            tempMUL = newMUL;
            newMUL = numMUL - prevMUL;
            prevMUL = tempMUL;
            
        }
        
        for (j = 0; j < ALU.size(); j++) {
            if (expressionsVector.at(ALU.at(j)).getSlack() == 0) {
                newALU = newALU + 1;
            }
        }
        if (newALU > numALU) {
            numALU = newALU;
        }
        else {
            newALU = numALU;
        }
        
        for (j = 0; j < LOGIC.size(); j++) {
            if (expressionsVector.at(LOGIC.at(j)).getSlack() == 0) {
                newLOGIC = newLOGIC + 1;
            }
        }
        if (newLOGIC > numLOGIC) {
            numLOGIC = newLOGIC;
        }
        else {
            newLOGIC = numLOGIC;
        }
        
        int loopnum = 0;
        while (newALU != 0 && loopnum < latency) {
            for (j = 0; j < ALU.size(); j++) {
                if ((expressionsVector.at(ALU.at(j)).getSlack() == loopnum) && (expressionsVector.at(ALU.at(j)).getDone() == 0) && (newALU != 0)) {
                    expressionsVector.at(ALU.at(j)).setTime(i);
                    newALU = newALU - 1;
                    expressionsVector.at(ALU.at(j)).setDone(1);
                }
            }
            loopnum = loopnum + 1;
        }
        
        loopnum = 0;
        while (newMUL != 0 && loopnum < latency) {
            for (j = 0; j < MUL.size(); j++) {
                if ((expressionsVector.at(MUL.at(j)).getSlack() == loopnum) && (expressionsVector.at(MUL.at(j)).getDone() == 0) && (newMUL != 0)) {
                    expressionsVector.at(MUL.at(j)).setTime(i);
                    newMUL = newMUL - 1;
                    expressionsVector.at(MUL.at(j)).setDone(1);
                }
            }
            loopnum = loopnum + 1;
        }
        
        loopnum = 0;
        while (newLOGIC != 0 && loopnum < latency) {
            for (j = 0; j < LOGIC.size(); j++) {
                if ((expressionsVector.at(LOGIC.at(j)).getSlack() == loopnum) && (expressionsVector.at(LOGIC.at(j)).getDone() == 0) && (newLOGIC != 0)) {
                    expressionsVector.at(LOGIC.at(j)).setTime(i);
                    newLOGIC = newLOGIC - 1;
                    expressionsVector.at(LOGIC.at(j)).setDone(1);
                }
            }
            loopnum = loopnum + 1;
        }
        
    }
    
    return 0;
    
    
}
