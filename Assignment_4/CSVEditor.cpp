/*Name: Ryan Russell
Username: rhrussell
Section: CSCE 221_511
Email: rhrussell@tamu.edu*/

#include "CSVEditor.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <utility>

CSVEditor::CSVEditor(string& inputPath, string& rosterPath, string& outputPath, regex expr, int m) {
	input.open(inputPath);
	roster.open(rosterPath);
	output.open(outputPath);
	regexPattern = expr;
	hashTable = new HashTable<string>(m);
}

CSVEditor::~CSVEditor(){
	delete hashTable;
	input.close();
	roster.close();
	output.close();
}

void CSVEditor::readCSVToTable() {
	string line;
	while(getline(input, line))
	{
		smatch matched_result;
        regex_search(line, matched_result, regexPattern);
        string uin_str = matched_result[1];
        int UIN = stoi(uin_str);
        string grade = matched_result[2];
		hashTable->insert(UIN, grade);
	}
}


void CSVEditor::writeCSVToFile() {
	string line;
	while(getline(roster, line))
	{
		smatch matched_result;
        regex_search(line, matched_result, regexPattern);
        string uin_str = matched_result[1];
        int UIN = stoi(uin_str);
		string *result;
		result = hashTable->search(UIN);
		string *value;
		if(result != nullptr)
		{
			value = hashTable->search(UIN);
			line.pop_back();
			output << line << *value << ",\n";
		}
		else
		{
			output << line;
		}
	}  
}

std::tuple<int, int, double> CSVEditor::getStats(){
	int min;
	int max;
	double average;
	min = hashTable->minChainLen();
	max = hashTable->maxChainLen();
	average = hashTable->averageChainLen();
	return std::make_tuple(min, max, average);
}