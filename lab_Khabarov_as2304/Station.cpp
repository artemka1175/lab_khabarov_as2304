//КС
#include "Station.h"
#include "Data.h"

using namespace std;

int Station::maxId = 0;

Station::Station() // https://github.com/papilinatm/cpp_lessons_2020/commit/9577d7431a4351dbdfe9de951d0b92b50e16a2f4
{
	Id = ++maxId;
	station_name = "";
	station_working_workshops = 0;
}; // Для Id

ostream& operator << (ostream& out, const Station& Station) // поток вывода.
{
	out << "ID КС: " << Station.Id << endl;
	out << "Имя: " << Station.station_name << endl;
	out << "Количество цехов: " << Station.station_workshops << endl;
	out << "Количество РАБОЧИХ цехов: " << Station.station_working_workshops << endl;
		out << "Эффективность: " << Station.station_efficiency << endl;
		out << endl;

	return out;
}
istream& operator >> (istream& in, Station& Station) // поток ввода.
{
	cout << "ID КС: " << Station.Id << endl;
	cout << "Введите имя станции: " << endl;
	Station.station_name = inputString(in);
	cout << "Введите число цехов: " << endl;
	Station.station_workshops = getPositiveNumber<int>(in);
	cout << "Количество РАБОЧИХ цехов: " << endl;
	Station.station_working_workshops = getCorrectNumber<int>(0, Station.station_workshops, true, in);
	cout << "Введите число эффективности: " << endl;
	Station.station_efficiency = getPositiveNumber<double>(in);

	return in;
}

ofstream& operator << (ofstream& fout, const Station& Station) // сохранение
{
	fout << Station.Id << endl;
	fout << Station.station_name << endl;
	fout << Station.station_workshops << endl;
	fout << Station.station_working_workshops << endl;
	fout << Station.station_efficiency << endl;

	return fout;
}

ifstream& operator >> (ifstream& fin, Station& Station) // загрузка
{
	fin >> Station.Id;
	getline(fin >> ws, Station.station_name);
	fin >> Station.station_workshops;
	fin >> Station.station_working_workshops;
	fin >> Station.station_efficiency;

	return fin;
}

Station Station::addStation() // создаёт новую станцию
{
	Station Station;
	cin >> Station;
	return Station;
}
void Station::resetMaxId()
{
	maxId = 0; //Удаление КС
}
bool Station::run_working_workshops() // чтобы поменять количество рабочих цехов. Посмотрел у Аллы. Каюсь.
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
//        out << "Данные отсутствуют..." << endl;
//        cout << "---------------------------------------" << endl;
//    }
//    else
//    {
//        PRINT_PARAM(cout, new_station.Id);
//        cout << "Количество цехов: " << new_station.station_workshops << endl;
//        cout << "Количество работающих цехов: " << new_station.station_working_workshops << endl;
//        cout << "Эффективность: " << new_station.station_efficiency << endl;
//        cout << "---------------------------------------" << endl;
//    }

//istream& operator >> (istream& in, Station& new_station)
//{
//    cout << endl << "Добавляем новую станцию..." << endl;
//    cout << "Введите имя станции: " << endl;
//    in.ignore();
//    getline(in, new_station.station_name);
//    cout << "Введите число цехов (от 1 до 10): " << endl;
//    new_station.station_workshops = GetCorrectData(1, 10);
//    cout << "Введите число работающих цехов: " << endl;
//    new_station.station_working_workshops = GetCorrectData(1, new_station.station_workshops);
//    while (new_station.station_working_workshops > new_station.station_workshops)
//    {
//        cout << "Число работающих цехов не может быть больше общего числа цехов!" << endl;
//        cout << "Переделывайте: " << endl;
//        new_station.station_working_workshops = GetCorrectData(1, new_station.station_workshops);
//    }
//    cout << "Введите число эффективности (от 0 до 1): " << endl;
//    new_station.station_efficiency = GetCorrectData(0.0, 1.0);
//    return in;
//}
//ostream& operator << (ostream& out, const Station& new_station)
//{
//    if (new_station.station_name == "Nothing")
//    {
//        out << "Данные отсутствуют..." << endl;
//        cout << "---------------------------------------" << endl;
//    }
//    else
//    {
//        PRINT_PARAM(cout, new_station.Id);
//        cout << "Количество цехов: " << new_station.station_workshops << endl;
//        cout << "Количество работающих цехов: " << new_station.station_working_workshops << endl;
//        cout << "Эффективность: " << new_station.station_efficiency << endl;
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

