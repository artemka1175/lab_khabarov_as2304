#pragma once
#include <string>
#include "Data.h"
#include <fstream>
using namespace std;
class Station
{
public:
	static int maxId;
	int Id;
	string station_name = "Nothing";
	int station_workshops = 0;
	int station_working_workshops = 0;
	double station_efficiency = 0.0;
int GetId();
string GetName() const;
int GetWorkshops() const;
int GetActWorkshops() const;
int GetPercentOfNonActiveWorkshops() const;
void PrintWorkshops() const;;
friend ostream& operator << (ostream& out, const Station& newStation);
friend istream& operator >> (istream& in, Station& newStation);
friend ofstream& operator << (ofstream& fout, const Station& newStation);
friend ifstream& operator >> (ifstream& fin, Station& newStation);
};