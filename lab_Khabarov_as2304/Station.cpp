#include "Station.h"
#include "Data.h"
int CStations::maxId = 0;

int CStations::GetId()
{
    return Id;
}
string CStations::Getname() const
{
    return Station_name;
}

int CStations::GetWorkshops() const
{
    return station_workshops;
}

int CStations::GetActWorkshops() const
{
    return Station_working_workshops;
}

int CStations::GetPercentOfNonActiveWorkshops() const
{
    return (station_workshops - Station_working_workshops) * 100 / station_workshops;
}

int CStations::Get_Id_in() const {
    return id_in;
}

int CStations::Get_Id_out() const {
    return id_out;

}
int CStations::GetShortestPath() const {
    return shortest_path;
}

void CStations::Set_Id_in(int in) {
    id_in = in;
}

void CStations::Set_Id_out(int out) {
    id_out = out;
}

void CStations::SetActWorkshops(int cnt)
{
    Station_working_workshops = cnt;
}
void CStations::SetShortestPath(int sh) {
    shortest_path = sh;
}

void CStations::PrintWorkshops() const
{
    cout << Station_working_workshops << " из " << station_workshops << " работают." << endl;
}
void CStations::EditCStation()
{
    cout << "Вы хотите изменить параметры цехов?" << endl;
    cout << "1. Да" << endl;
    cout << "2. Нет" << endl;
    switch (GetCorrectData(1, 2))
    {
    case 1:
    {
        cout << "Напишите количество РАБОЧИХ цехов: ";
        int active = GetCorrectData(1, station_workshops);
        SetActWorkshops(active);
        PrintWorkshops();

    }
    case 2:
        return;
    default:
    {
        cout << "а." << endl;
        break;
    }
    }
}
istream& operator >> (istream& in, CStations& newCStations)
{
    newCStations.Id = ++newCStations.maxId;
    cout << "ID: " << newCStations.Id << endl;
    cout << "Напишите имя КС: " << endl;
    INPUT_LINE(in, newCStations.Station_name);
    cout << "Напишите количество цехов : " << endl;
    newCStations.station_workshops = GetCorrectData(1, 100);
    cout << "Напишите количество РАБОЧИХ цехов: " << endl;
    newCStations.Station_working_workshops = GetCorrectData(1, newCStations.station_workshops);
    cout << "Напишите эффективность (от 0 до 1): " << endl;
    newCStations.Station_efficiency = GetCorrectData(0.0, 1.0);
    return in;
}

ostream& operator << (ostream& out, const CStations& newCStations)
{
    if (newCStations.Station_name == "Nothing")
    {
        out << "Вы ничего не записали!" << endl ;
    }
    else
    {
        out << "ID: " << newCStations.Id << ";" << endl;
        out << "Имя КС: " << newCStations.Station_name << ";" << endl; 
        out << "Количество цехов: " << newCStations.station_workshops << ";" << endl; 
        out << "Количество РАБОЧИХ цехов: " << newCStations.Station_working_workshops << ";" << endl;
        out << "Эффективность: " << newCStations.Station_efficiency << ";" << endl;
    }
    return out;
}

ifstream& operator >> (ifstream& flin, CStations& newCStations)
{
    flin >> newCStations.Id;
    newCStations.maxId = newCStations.Id;
    flin.ignore();
    getline(flin, newCStations.Station_name);
    flin >> newCStations.station_workshops;
    flin >> newCStations.Station_working_workshops;
    flin >> newCStations.Station_efficiency;
    return flin;
}

ofstream& operator << (ofstream& fout, const CStations& newCStations)
{
    fout << newCStations.Id << endl;
    fout << newCStations.Station_name << endl;
    fout << newCStations.station_workshops << endl;
    fout << newCStations.Station_working_workshops << endl;
    fout << newCStations.Station_efficiency << endl;
    return fout;
}