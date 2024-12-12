// Труба
#include "Pipe.h"
#include "Data.h"

using namespace std;

int Pipe::maxId = 0;


Pipe::Pipe()  // https://github.com/papilinatm/cpp_lessons_2020/commit/9577d7431a4351dbdfe9de951d0b92b50e16a2f4
{
	Id = ++maxId;
	pipe_name = "";
	pipe_repair = 0;
}; //Id

ostream& operator<<(std::ostream& out, const Pipe& Pipe)
{
	out << "ID трубы = " << Pipe.Id << endl;
	out << "Имя: " << Pipe.pipe_name << endl;
	out << "Диаметр: " << Pipe.pipe_diameter << endl;
	out << "Длина: " << Pipe.pipe_length << endl;
		out << "Статус: " << Pipe.pipe_repair << endl;
		out << endl;

	return out;
}

istream& operator>>(istream& in, Pipe& Pipe)
{
	cout << "ID трубы (он же ключ) = " << Pipe.Id << endl;
	cout << "Напишите имя трубы: ";
	Pipe.pipe_name = inputString(in);
	cout << "Напишите длину трубы: ";
	Pipe.pipe_diameter = getPositiveNumber<int>(in);
	cout << "Напишите диаметр трубы: ";
	Pipe.pipe_length = getPositiveNumber<double>(in);
	cout << "Статус трубы: 0 (в ремонте)" << endl;


	return in;
}

ofstream& operator << (ofstream& fout, const Pipe& Pipe) 
{
	fout << Pipe.Id << endl;
	fout << Pipe.pipe_name << endl;
	fout << Pipe.pipe_diameter << endl;
	fout << Pipe.pipe_length << endl;
	fout << Pipe.pipe_repair << endl;

	return fout;
}

ifstream& operator >> (ifstream& fin, Pipe& Pipe)
{
	fin >> Pipe.Id;
	getline(fin >> ws, Pipe.pipe_name); 
	fin >> Pipe.pipe_diameter;
	fin >> Pipe.pipe_length;
	fin >> Pipe.pipe_repair;

	return fin;
}

Pipe Pipe::addPipe() 
{
	Pipe Pipe;
	cin >> Pipe;
	return Pipe;
}


void Pipe::editPipe() // меняет статус. просто ._.
{
	pipe_repair = !pipe_repair;
}

void Pipe::resetMaxId()
{
	maxId = 0; //Удаление КС
}

//void GTS::EditPipe(Pipe& pipe)
//{
//	cout << "Статус трубы изменится. Поменять?" << endl;
//	cout << "1. Да;" << endl;
//	cout << "2. Нет." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "Напишите статус трубы (0 - готов; 1 - в ремонте): ";
//		pipe.pipe_repair = 1;
//		cout << "ID: " << pipe.Id << ": ";
//		pipe.PrintPipeRepair();
//		break;
//	}
//	case 2:
//	{
//		return;
//	}
//	default:
//	{
//		cout << "Мы вас не поняли. Напишите снова:" << endl;
//		break;
//	}
//	}
//}
//void GTS::EditPipes(vector<Pipe*>& pipes)
//{
//	cout << "Статус труб изменится. Поменять?" << endl;
//	cout << "1. Да;" << endl;
//	cout << "2. Нет." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "Напишите статус труб (0 - готов; 1 - в ремонте): ";
//		bool repSt = GetCorrectData(false, true);
//		for (auto& pipe : pipes)
//		{
//			pipe->pipe_repair = repSt;
//		}
//		cout << "Готово!" << endl;
//		break;
//	}
//	case 2:
//		return;
//	default:
//		cout << "Мы вас не поняли. Вы нас не поняли." << endl;
//		break;
//	}
//}
//void GTS::searchPipe(unordered_map<int, Pipe>& Pipes)
//{
//	while (true)
//	{
//		cout << "Выберите, как мы хотим найти трубу или трубы: " << endl;
//		cout << "1. По имени;" << endl;
//		cout << "2. По статусу трубы;" << endl;
//		cout << "3. Назад. Я не хочу искать и вообще я сюда случайно попал." << endl;
//		switch (GetCorrectData(1, 3))
//		{
//		case 1:
//		{
//			string pipeName;
//			cout << "Напишите имя трубы (вы сами будете виноваты, если вы не так напишите): " << endl;
//			cin.ignore();
//			getline(cin, pipeName);
//			vector<Pipe*> editPipes;
//			for (auto& elem : Pipes)
//			{
//				if (elem.second.GetName().find(pipeName) != string::npos)
//				{
//					cout << elem.second;
//					editPipes.push_back(&(elem.second));
//				}
//			}
//			if (editPipes.empty())
//				cout << "Или вы не так написали, или вы позабыли слегка. Anyway, труб с таким именем нет." << endl;
//			else
//				EditPipes(editPipes);
//		}
//		break;
//		case 2:
//		{
//			cout << "Напишите статус трубы (0 - готов; 1 - в ремонте):" << endl;
//			bool repairStatus = GetCorrectData(false, true);
//			vector<Pipe*> editPipes;
//			for (auto& elem : Pipes)
//			{
//				if (elem.second.GetStatus() == repairStatus)
//				{
//					cout << elem.second;
//					editPipes.push_back(&(elem.second));
//				}
//			}
//			if (editPipes.empty())
//				cout << "Нет трубы с таким статусом. Или все готовы, или в ремонте." << endl;
//			else
//				EditPipes(editPipes);
//		}
//		break;
//		case 3:
//			return;
//		default:
//		{
//			cout << "Мы вас не поняли..." << endl;
//			break;
//		}
//		}
//	}
//}
//void GTS::EditStation(Station& station)
//{
//	cout << "Вы ТОЧНО хотите поменять количество рабочих цехов?" << endl;
//	cout << "1. Да;" << endl;
//	cout << "2. Нет." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "Напишите количество рабочих цехов:";
//		station.station_working_workshops = GetCorrectData(1, station.GetWorkshops());
//		cout << "ID: " << station.Id << ": ";
//		station.PrintWorkshops();
//	}
//	case 2:
//		return;
//	default:
//	{
//		cout << "Напишите снова и правильно:" << endl;
//		break;
//	}
//	}
//}
//void GTS::EditStations(vector<Station*> stations)
//{
//	cout << "Вы ТОЧНО хотите поменять количество рабочих цехов?" << endl;
//	cout << "1. Да;" << endl;
//	cout << "2. Нет." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "Пожалуйста, напишите процент НЕ рабочих цехов (так будет удобней): ";
//		float percent = GetCorrectData(0.0, 100.0);
//		for (auto& station : stations)
//		{
//			station->station_working_workshops = round(station->station_workshops * (100 - percent) / 100);
//		}
//		cout << "Мы поменяли успешно." << endl;
//		break;
//	}
//	case 2:
//		return;
//	default:
//		cout << "Не поняли...";
//		break;
//	}
//}
//void GTS::searchStation(unordered_map<int, Station>& Stations)
//{
//	while (true)
//	{
//		cout << "Как мы хотим найти КС: " << endl;
//		cout << "1. По имени:" << endl;
//		cout << "2. По проценту НЕрабочих цехов;" << endl;
//		cout << "3. НАЗАД! НАЗАД! Я СЛУЧАЙНО НАЖАЛ!" << endl;
//		switch (GetCorrectData(1, 3))
//		{
//		case 1:
//		{
//			string stationName;
//			cout << "Напишите имя (молю, чтобы вы написали правильно):" << endl;
//			cin.ignore();
//			getline(cin, stationName);
//			vector<Station*> editStations;
//			for (auto& elem : Stations)
//			{
//				if (elem.second.GetName().find(stationName) != string::npos)
//				{
//					cout << elem.second;
//					editStations.push_back(&(elem.second));
//				}
//			}
//			if (editStations.empty())
//				cout << "Молитвы не были услышаны. Мы не нашли." << endl;
//			else
//				EditStations(editStations);
//		}
//		break;
//		case 2:
//		{
//			cout << "Напишите процент: " << endl;
//			int percent = GetCorrectData(0, 100);
//			cout << "Какие КС мы должны найти:" << endl;
//			cout << "1. Более рабочие (процент нерабочих цехов меньше заданного);" << endl;
//			cout << "2. С таким же процентом;" << endl;
//			cout << "3. Более ленивые (процент нерабочих цехов больше заданного)." << endl;
//			vector<Station*> editStations;
//			switch (GetCorrectData(1, 3))
//			{
//			case 1:
//			{
//				for (auto& elem : Stations)
//				{
//					if (elem.second.GetPercentOfNonActiveWorkshops() < percent)
//					{
//						cout << elem.second;
//						editStations.push_back(&(elem.second));
//					}
//				}
//			}
//			break;
//			case 2:
//			{
//				for (auto& elem : Stations)
//				{
//					if (elem.second.GetPercentOfNonActiveWorkshops() == percent)
//					{
//						cout << elem.second;
//						editStations.push_back(&(elem.second));
//					}
//				}
//			}
//			break;
//			case 3:
//			{
//				for (auto& elem : Stations)
//				{
//					if (elem.second.GetPercentOfNonActiveWorkshops() > percent)
//					{
//						cout << elem.second;
//						editStations.push_back(&(elem.second));
//					}
//				}
//			}
//			break;
//			}
//			if (editStations.empty())
//				cout << "Плохие новости. Мы не нашли." << endl;
//			else
//				EditStations(editStations);
//		}
//		break;
//		case 3:
//			return;
//		default:
//		{
//			cout << "Мы вас не понимать." << endl;
//			break;
//		}
//		}
//	}
//}