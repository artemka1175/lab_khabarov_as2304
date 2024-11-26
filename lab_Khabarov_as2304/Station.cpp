#include "Station.h"
#include "Data.h"
int Station::maxId = 0;
int Station::GetId()
{
    return Id;
}
string Station::GetName() const
{
    return station_name;
}
int Station::GetWorkshops() const
{
    return station_workshops;
}
int Station::GetActWorkshops() const
{
    return station_working_workshops;
}
void Station::PrintWorkshops() const
{
    cout << station_working_workshops <<
        "�� " << station_workshops << " ����� ��������" << endl;
}
int Station::GetPercentOfNonActiveWorkshops() const
{
    return (station_workshops - station_working_workshops) * 100 / station_workshops;
}
istream& operator >> (istream& in, Station& new_station)
{
    cout << endl << "��������� ����� �������..." << endl;
    cout << "������� ��� �������: " << endl;
    in.ignore();
    getline(in, new_station.station_name);
    cout << "������� ����� ����� (�� 1 �� 10): " << endl;
    new_station.station_workshops = GetCorrectData(1, 10);
    cout << "������� ����� ���������� �����: " << endl;
    new_station.station_working_workshops = GetCorrectData(1, new_station.station_workshops);
    while (new_station.station_working_workshops > new_station.station_workshops)
    {
        cout << "����� ���������� ����� �� ����� ���� ������ ������ ����� �����!" << endl;
        cout << "�������������: " << endl;
        new_station.station_working_workshops = GetCorrectData(1, new_station.station_workshops);
    }
    cout << "������� ����� ������������� (�� 0 �� 1): " << endl;
    new_station.station_efficiency = GetCorrectData(0.0, 1.0);
    return in;
}
ostream& operator << (ostream& out, const Station& new_station)
{
    if (new_station.station_name == "Nothing")
    {
        out << "������ �����������..." << endl;
        cout << "---------------------------------------" << endl;
    }
    else
    {
        PRINT_PARAM(cout, new_station.Id);
        cout << "���������� �����: " << new_station.station_workshops << endl;
        cout << "���������� ���������� �����: " << new_station.station_working_workshops << endl;
        cout << "�������������: " << new_station.station_efficiency << endl;
        cout << "---------------------------------------" << endl;
    }
    return out;
}
ifstream& operator >> (ifstream& fin, Station& new_station)
{
    fin >> new_station.Id;
    new_station.maxId = new_station.Id;
    fin.ignore();
    getline(fin, new_station.station_name);
    fin >> new_station.station_workshops;
    fin >> new_station.station_working_workshops;
    fin >> new_station.station_efficiency;
    return fin;
}
ofstream& operator << (ofstream& fout, const Station& new_station)
{
    fout << new_station.Id << endl;
    fout << new_station.station_name << endl;
    fout << new_station.station_workshops << endl;
    fout << new_station.station_working_workshops << endl;
    fout << new_station.station_efficiency << endl;
    return fout;
}