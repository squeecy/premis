#include <iostream>
#include "record.h"


//void fillData(std::ifstream inputFile)
void fillData(std::ifstream inputFile, struct replayData *rData_s)
{

	std::vector<std::string> pitch; //hold input

	if(inputFile.is_open())	
	{
		std::string line; //hold data

		while(!inputFile.eof())
		{
			getline(inputFile, line, ' '); //get line and delim spaces
			pitch.push_back(line); //fill vector
		}
		inputFile.close(); //close file
	}

	for(int i = 0; i < pitch.size(); i++)
	{
		//rData_s->roll = roll[i];
		rData_s->pitch.push_back(std::stof(pitch[i]));
		std::cout << pitch[i] << std::endl; //print to console
	}
}
