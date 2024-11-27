// header - ингредиенты для трубы
#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Pipe
{
private: //шаблон для труб менять нельзя.  не разрешаю. фу.
	static int maxId;
	int Id;
	std::string pipe_name = "Nothing";
	double pipe_length = 0.0;
	int pipe_diameter = 0;
	bool pipe_repair = false;
public:
	Pipe();

	static Pipe addPipe(); 
	static void resetMaxId();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);

	void editPipe();

	int getID()
	{
		return Id;
	}
	std::string getName() 
	{
		return pipe_name;
	}
	bool PrintPipeRepair()
	{
		return pipe_repair;
	}
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
