#ifndef RECORD__H 
#define RECORD__H 
#include <vector>
#include <fstream>

struct replayData
{
	std::vector<float> roll;
	std::vector<float> pitch;
};

void fillData(std::ifstream inputFile, struct replayData *rData_s);
//void fillData(std::ifstream inputFile);

#endif
