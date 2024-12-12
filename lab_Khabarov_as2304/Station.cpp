//��
#include "Station.h"
#include "Data.h"

using namespace std;

int Station::maxId = 0;

Station::Station() // https://github.com/papilinatm/cpp_lessons_2020/commit/9577d7431a4351dbdfe9de951d0b92b50e16a2f4
{
	Id = ++maxId;
	station_name = "";
	station_working_workshops = 0;
}; // ��� Id

ostream& operator << (ostream& out, const Station& Station) // ����� ������.
{
	out << "ID ��: " << Station.Id << endl;
	out << "���: " << Station.station_name << endl;
	out << "���������� �����: " << Station.station_workshops << endl;
	out << "���������� ������� �����: " << Station.station_working_workshops << endl;
		out << "�������������: " << Station.station_efficiency << endl;
		out << endl;

	return out;
}
istream& operator >> (istream& in, Station& Station) // ����� �����.
{
	cout << "ID ��: " << Station.Id << endl;
	cout << "������� ��� �������: " << endl;
	Station.station_name = inputString(in);
	cout << "������� ����� �����: " << endl;
	Station.station_workshops = getPositiveNumber<int>(in);
	cout << "���������� ������� �����: " << endl;
	Station.station_working_workshops = getCorrectNumber<int>(0, Station.station_workshops, true, in);
	cout << "������� ����� �������������: " << endl;
	Station.station_efficiency = getPositiveNumber<double>(in);

	return in;
}

ofstream& operator << (ofstream& fout, const Station& Station) // ����������
{
	fout << Station.Id << endl;
	fout << Station.station_name << endl;
	fout << Station.station_workshops << endl;
	fout << Station.station_working_workshops << endl;
	fout << Station.station_efficiency << endl;

	return fout;
}

ifstream& operator >> (ifstream& fin, Station& Station) // ��������
{
	fin >> Station.Id;
	getline(fin >> ws, Station.station_name);
	fin >> Station.station_workshops;
	fin >> Station.station_working_workshops;
	fin >> Station.station_efficiency;

	return fin;
}

Station Station::addStation() // ������ ����� �������
{
	Station Station;
	cin >> Station;
	return Station;
}
void Station::resetMaxId()
{
	maxId = 0; //�������� ��
}
bool Station::run_working_workshops() // ����� �������� ���������� ������� �����. ��������� � ����. �����.
{
	if (station_working_workshops < station_workshops)
	{
		station_working_workshops++;
		return 1;
	}
	else
		return 0;
}

bool Station::stop_working_workshops() // �����
{
	if (station_working_workshops > 0)
	{
		station_working_workshops--;
		return 1;
	}
	else
		return 0;
}


