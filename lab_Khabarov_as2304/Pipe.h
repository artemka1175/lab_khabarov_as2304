#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class Pipe
{
public:
	static int maxId;
	int Id;
	string pipe_name = "Nothing";
	double pipe_length = 0.0;
	int pipe_diameter = 0;
	bool pipe_repair = false;
int GetId();
string GetName() const;
bool GetStatus();
void PrintPipeRepair();
friend ostream& operator << (ostream& out, const Pipe& newPipe);
friend istream& operator >> (istream& in, Pipe& newPipe);
friend ofstream& operator << (ofstream& fout, const Pipe& newPipe);
friend ifstream& operator >> (ifstream& fin, Pipe& newPipe);
};


#pragma once
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <vector>
//using namespace std;
//class Pipe
//{
//private:
//	static int maxId;
//	int Id;
//	string pipe_name = "Nothing";
//	double pipe_length = 0.0;
//	int pipe_diameter = 0;
//	bool pipe_repair = false;
//int GetId();
//string GetName() const;
//bool GetStatus();
//void PrintPipeRepair();
//friend ostream& operator << (ostream& out, const Pipe& newPipe);
//friend istream& operator >> (istream& in, Pipe& newPipe);
//friend ofstream& operator << (ofstream& fout, const Pipe& newPipe);
//friend ifstream& operator >> (ifstream& fin, Pipe& newPipe);
//};
