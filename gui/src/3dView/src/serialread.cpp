#include <iostream>
#include <string>
#include "serialread.h"

Serial* SP = new Serial("\\\\.\\COM3");
void serialRead(serialData_T *data)
{
	std::string element;
	int readResult = 0;
	char incomingData[256] = "";
	int dataLength = 255;
	std::string conVert;
	char delimiter = ',';
	int count = 0;

	if(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData, dataLength);
		incomingData[readResult] = 0;
		
		conVert = incomingData;

		std::stringstream ss(conVert);

		while(getline(ss, element, delimiter))
		{
			count++;
			if(count == 2) 
				data->roll = std::stof(element); 

			if(count == 3)
				data->pitch = std::stof(element);
		}
	}
}

void serialDisconnect()
{
	delete SP;
}


