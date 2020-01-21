/*
 * utilities.cpp
 *
 *  Created on: Jan 16, 2020
 *      Author: tyler
 */
#include "utilities.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
vector<process_stats> dataVec;

//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename){
	dataVec.clear();

	ifstream myfile;
	myfile.open(filename);

	//makes sure file is open and returns boolean depending on outcome
	if (!myfile.is_open() || myfile.fail()) {
		return COULD_NOT_OPEN_FILE;
	}
	//File is opened successfully at this point
	//Messy because parsing
	string contents;
	string curline = "";
	process_stats holderStat;
		while(!myfile.eof()){
			//pretty sure this follows requirements
			getline(myfile, curline);
			stringstream sCurline(curline);
			string holderString;
			int count =0;
				while (getline(sCurline, holderString, ',')) {
					if(count == 0){
						holderStat.process_number = stoi(holderString);
					}
					if(count == 1){
						holderStat.start_time = stoi(holderString);
					}
					if(count == 2){
						holderStat.cpu_time = stoi(holderString);
					}
					count ++;
				}
				dataVec.push_back(holderStat);
				count = 0;//Maybe redundant
			//contents += curline;
		}
		cout<<contents;
	myfile.close();
	return SUCCESS;
}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename){

	if(dataVec.size() == 0){
		cout<<"E mpty VECCtur";
	}

	ofstream myfile(filename);
	//makes sure file is open and returns boolean depending on outcome
	if (!myfile.is_open() || myfile.fail()) {
		return COULD_NOT_OPEN_FILE;
	}
	//File is open at this point and ready to write

	process_stats currentPStat;
	string writeLine;
	for (int x = 0; x < dataVec.size(); x++) {
		currentPStat = dataVec.at(x);
			writeLine = "";
			writeLine += to_string(dataVec.at(x).process_number) + ",";
			writeLine += to_string(dataVec.at(x).start_time) + ",";
			writeLine += to_string(dataVec.at(x).cpu_time);
			myfile << writeLine + "\n";
		}
	myfile.close();
return SUCCESS;
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder){
	vector<process_stats> holderVec;
	int lowIndex;
	int lowVal;

	if(mySortOrder == START_TIME){
		while(dataVec.size()>0){
			lowVal = dataVec.at(0).start_time;
			for(int x = 0; x <= dataVec.size(); x++){
				if(dataVec[x].start_time < lowVal){
					lowVal = dataVec[x].start_time;
					lowIndex = x;
				}
			}
			holderVec.push_back(dataVec[lowIndex]);
			dataVec.erase(dataVec.begin()+lowIndex)-1;
		}
	}

	if(mySortOrder == CPU_TIME){
		while(dataVec.size()>0){
			lowVal = dataVec.at(0).cpu_time;
			for(int x = 0; x <= dataVec.size(); x++){
				if(dataVec[x].cpu_time < lowVal){
					lowVal = dataVec[x].cpu_time;
					lowIndex = x;
				}
			}
			holderVec.push_back(dataVec[lowIndex]);
			dataVec.erase(dataVec.begin()+lowIndex)-1;
		}
	}

	if(mySortOrder == PROCESS_NUMBER){
		while(dataVec.size()>0){
			lowVal = dataVec.at(0).process_number;
			for(int x = 0; x <= dataVec.size(); x++){
				if(dataVec[x].process_number < lowVal){
					lowVal = dataVec[x].process_number;
					lowIndex = x;
				}
			}
			holderVec.push_back(dataVec[lowIndex]);
			dataVec.erase(dataVec.begin()+lowIndex)-1;
		}
	}
	dataVec = holderVec;
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext(){
	process_stats current = dataVec.at(0);
	//dataVec.pop_back();
	dataVec.erase (dataVec.begin());

	return current;
}




