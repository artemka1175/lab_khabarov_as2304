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

bool Station::stop_working_workshops() // Также
{
	if (station_working_workshops > 0)
	{
		station_working_workshops--;
		return 1;
	}
	else
		return 0;
}


