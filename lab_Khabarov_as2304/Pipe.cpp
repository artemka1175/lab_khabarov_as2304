#include "Pipe.h"
#include "Data.h"
int Pipe::maxId = 0;
int Pipe::GetId()
{
	return Id;
}
string Pipe::GetName() const
{
	return pipe_name;
}
bool Pipe::GetStatus()
{
	return pipe_repair;
}
void Pipe::PrintPipeRepair()
{
	if (pipe_repair == 1)
	{
		cout << "����� � ������� (1)" << endl;
	}
	else
		cout << "����� ������ (0)" << endl;
}
istream& operator >> (istream& in, Pipe& new_pipe)
{

	cout << "��������� ����� �����..." << endl;
	cout << "�������� ��� �����: " << endl;
	in.ignore();
	getline(in, new_pipe.pipe_name);
	cout << "�������� ����� ����� (�� 100 �� 1000 ������): " << endl;
	new_pipe.pipe_length = GetCorrectData(100.0, 1000.0);
	cout << "�������� ������� ����� (�� 100 �� 1000 �����������): " << endl;
	new_pipe.pipe_diameter = GetCorrectData(100, 1000);
	cout << "�������� ������ ����� (0 - �����; 1 - � �������): " << endl;
	new_pipe.pipe_repair = GetCorrectData(0, 1);
	return in;
}
ostream& operator << (ostream& out, const Pipe& new_pipe)
{
	if (new_pipe.pipe_name == "Nothing")
	{
		out << "������ �����������..." << endl;
		cout << "---------------------------------------" << endl;
	}
	else
	{

		out << "ID: " << new_pipe.Id << endl;
		out << "�����: " << new_pipe.pipe_length << endl;
		out << "�������: " << new_pipe.pipe_diameter << endl;
		out << "������: " << new_pipe.pipe_repair << endl;
		cout << "---------------------------------------" << endl;
	}
	return out;
}


ifstream& operator >> (ifstream& fin, Pipe& new_pipe)
{
	fin >> new_pipe.Id;
	new_pipe.maxId = new_pipe.Id;
	fin.ignore();
	getline(fin, new_pipe.pipe_name);
	fin >> new_pipe.pipe_length;
	fin >> new_pipe.pipe_diameter;
	fin >> new_pipe.pipe_repair;
	return fin;
}
ofstream& operator << (ofstream& fout, const Pipe& new_pipe)
{
	fout << new_pipe.Id << endl;
	fout << new_pipe.pipe_name << endl;
	fout << new_pipe.pipe_length << endl;
	fout << new_pipe.pipe_diameter << endl;
	fout << new_pipe.pipe_repair << endl;
	return fout;
}
