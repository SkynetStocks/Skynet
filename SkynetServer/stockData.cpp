#include "stockData.h"

bool stockData::save(const char* fileName)
{
	fstream stockFile(fileName, ios::out|ios::binary);
	if (!stockFile)
		return false; //error opening file

	stockFile.write((const char*)&timeInterval, sizeof(int));
	stockFile.write((const char*)&timeLength, sizeof(int));
	
	double dataPoint;
	for (int i = 0; i < timeLength / timeInterval; ++i)
	{
		dataPoint = pData->dequeue();
		stockFile.write(reinterpret_cast<char*>(&dataPoint), sizeof(double)); //there is a better way to write this, should change later down the line
	}

	stockFile.close();
	return true;
}

bool stockData::load(const char* fileName)
{
	ifstream stockFile(fileName, ios::in | ios::binary);
	if (!stockFile)
		return false;
	if (pData == nullptr)
		pData = new Queue<double>;

	stockFile.read((char*)&timeInterval, sizeof(int));
	stockFile.read((char*)&timeLength, sizeof(int));
	

	double dataPoint;
	for (int i = 0; i < timeLength / timeInterval; ++i)
	{
		stockFile.read(reinterpret_cast<char*>(&dataPoint), sizeof(double)); //there is a better way to write this, should change later down the line
		pData->enqueue(dataPoint);
	}

	stockFile.close();
	return true;


}