// header - ����������� ��� ��
#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Station
{
private: // � ����� ������������ ������ �������������� ��������??? ������. ������� ��������� ����� ��������� � ������ ��� ���� (�� ����������).
	static int maxId;
	int Id;
	std::string station_name = "Nothing";
	int station_workshops = 0;
	int station_working_workshops = 0;
	double station_efficiency = 0.0; // ����������� ������������� - ��� �� 0 �� 1 ._.
public: // ��� ������������
	Station();

	static Station addStation();
	static void resetMaxId();

	friend std::ostream& operator << (std::ostream& out, const Station& cs);
	friend std::istream& operator >> (std::istream& in, Station& cs);
	friend std::ofstream& operator << (std::ofstream& fout, const Station& cs);
	friend std::ifstream& operator >> (std::ifstream& fin, Station& cs); // 4 �����, ������ ������ � �����.

	int getID()
	{
		return Id;
	}

	std::string getName()
	{
		return station_name;
	}
	double GetPercentOfNonActiveWorkshops()
	{
		return(double)(station_workshops - station_working_workshops) * 100 / station_workshops; // ������� ��������� �����
	}
	bool run_working_workshops();
	bool stop_working_workshops();

};
