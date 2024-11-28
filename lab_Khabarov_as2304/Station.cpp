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

bool Station::stop_working_workshops() // change number of ws in in_repair for cs
{
	if (station_working_workshops > 0)
	{
		station_working_workshops--;
		return 1;
	}
	else
		return 0;
}
//ostream& operator << (ostream& out, const Station& new_station)
//{
//    if (new_station.station_name == "Nothing")
//    {
//        out << "������ �����������..." << endl;
//        cout << "---------------------------------------" << endl;
//    }
//    else
//    {
//        PRINT_PARAM(cout, new_station.Id);
//        cout << "���������� �����: " << new_station.station_workshops << endl;
//        cout << "���������� ���������� �����: " << new_station.station_working_workshops << endl;
//        cout << "�������������: " << new_station.station_efficiency << endl;
//        cout << "---------------------------------------" << endl;
//    }

//istream& operator >> (istream& in, Station& new_station)
//{
//    cout << endl << "��������� ����� �������..." << endl;
//    cout << "������� ��� �������: " << endl;
//    in.ignore();
//    getline(in, new_station.station_name);
//    cout << "������� ����� ����� (�� 1 �� 10): " << endl;
//    new_station.station_workshops = GetCorrectData(1, 10);
//    cout << "������� ����� ���������� �����: " << endl;
//    new_station.station_working_workshops = GetCorrectData(1, new_station.station_workshops);
//    while (new_station.station_working_workshops > new_station.station_workshops)
//    {
//        cout << "����� ���������� ����� �� ����� ���� ������ ������ ����� �����!" << endl;
//        cout << "�������������: " << endl;
//        new_station.station_working_workshops = GetCorrectData(1, new_station.station_workshops);
//    }
//    cout << "������� ����� ������������� (�� 0 �� 1): " << endl;
//    new_station.station_efficiency = GetCorrectData(0.0, 1.0);
//    return in;
//}
//ostream& operator << (ostream& out, const Station& new_station)
//{
//    if (new_station.station_name == "Nothing")
//    {
//        out << "������ �����������..." << endl;
//        cout << "---------------------------------------" << endl;
//    }
//    else
//    {
//        PRINT_PARAM(cout, new_station.Id);
//        cout << "���������� �����: " << new_station.station_workshops << endl;
//        cout << "���������� ���������� �����: " << new_station.station_working_workshops << endl;
//        cout << "�������������: " << new_station.station_efficiency << endl;
//        cout << "---------------------------------------" << endl;
//    }
//    return out;
//}
//ifstream& operator >> (ifstream& fin, Station& new_station)
//{
//    fin >> new_station.Id;
//    new_station.maxId = new_station.Id;
//    fin.ignore();
//    getline(fin, new_station.station_name);
//    fin >> new_station.station_workshops;
//    fin >> new_station.station_working_workshops;
//    fin >> new_station.station_efficiency;
//    return fin;
//}
//ofstream& operator << (ofstream& fout, const Station& new_station)
//{
//    fout << new_station.Id << endl;
//    fout << new_station.station_name << endl;
//    fout << new_station.station_workshops << endl;
//    fout << new_station.station_working_workshops << endl;
//    fout << new_station.station_efficiency << endl;
//    return fout;
//}

