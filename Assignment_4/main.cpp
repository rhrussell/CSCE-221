/*Name: Ryan Russell
Username: rhrussell
Section: CSCE 221_511
Email: rhrussell@tamu.edu*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <utility>
#include <string>

#include "HashTable.hpp"
#include "CSVEditor.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    regex expr(".*,.*,(.*),(.*)");
	
    string inputPath = "./input.csv";
    string rosterPath = "./roster.csv";
    string outputPath = "./output.csv";
	
	//OBTAIN M HERE
    fstream file;
    file.open(rosterPath);
    int m;
    m = 0;
    string line;
    while(getline(file, line))
    {
        m++;
    }
    file.close();

    CSVEditor editor(inputPath, rosterPath, outputPath, expr, m);
    editor.readCSVToTable();
    editor.writeCSVToFile();
	
	std::tuple<int, int, double> stats = editor.getStats();
	
	cout << "minimum chain len = " << std::get<0>(stats) << endl;
	cout << "maximum chain len = " << std::get<1>(stats) << endl;
	cout << "average chain len = " << std::get<2>(stats) << endl;
	
    //return 0;    
}
