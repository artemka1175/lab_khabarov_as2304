#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Pipe
{
private:
	static int maxId;
	int Id;
	string pipe_name = "Nothing";
	double Pipe_length = 0.0;
	int Pipe_diameter = 0;
	bool isUnderRepair = false;
	int CSid1 = 0;
	int CSid2 = 0;
	bool free = 1;
	int capac = 0;


public:
	int GetDiameter() const;
	int GetLen() const;
	int GetId();
	string Getname() const;
	bool GetRepairStatus();
	int GetCSid1() const;
	int GetCSid2() const;
	int GetCapac();
	bool Get_free();
	void Set_free(bool status);
	void SetRepairStatus(bool status);
	void SetDiameter(int diam);
	void SetCapac(int c);
	void PrintRepairStatus();
	void EditPipe();
	void DeleteConnection();
	bool ConnectionNotBusy() const;


	friend ostream& operator << (ostream& out, const Pipe& newPipe);
	friend istream& operator >> (istream& in, Pipe& newPipe);
	friend ofstream& operator << (ofstream& fout, const Pipe& newPipe);
	friend ifstream& operator >> (ifstream& flin, Pipe& newPipe);
};