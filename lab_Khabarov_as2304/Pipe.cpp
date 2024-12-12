// �����
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
	out << "ID ����� = " << Pipe.Id << endl;
	out << "���: " << Pipe.pipe_name << endl;
	out << "�������: " << Pipe.pipe_diameter << endl;
	out << "�����: " << Pipe.pipe_length << endl;
		out << "������: " << Pipe.pipe_repair << endl;
		out << endl;

	return out;
}

istream& operator>>(istream& in, Pipe& Pipe)
{
	cout << "ID ����� (�� �� ����) = " << Pipe.Id << endl;
	cout << "�������� ��� �����: ";
	Pipe.pipe_name = inputString(in);
	cout << "�������� ����� �����: ";
	Pipe.pipe_diameter = getPositiveNumber<int>(in);
	cout << "�������� ������� �����: ";
	Pipe.pipe_length = getPositiveNumber<double>(in);
	cout << "������ �����: 0 (� �������)" << endl;


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


void Pipe::editPipe() // ������ ������. ������ ._.
{
	pipe_repair = !pipe_repair;
}

void Pipe::resetMaxId()
{
	maxId = 0; //�������� ��
}

//void GTS::EditPipe(Pipe& pipe)
//{
//	cout << "������ ����� ���������. ��������?" << endl;
//	cout << "1. ��;" << endl;
//	cout << "2. ���." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "�������� ������ ����� (0 - �����; 1 - � �������): ";
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
//		cout << "�� ��� �� ������. �������� �����:" << endl;
//		break;
//	}
//	}
//}
//void GTS::EditPipes(vector<Pipe*>& pipes)
//{
//	cout << "������ ���� ���������. ��������?" << endl;
//	cout << "1. ��;" << endl;
//	cout << "2. ���." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "�������� ������ ���� (0 - �����; 1 - � �������): ";
//		bool repSt = GetCorrectData(false, true);
//		for (auto& pipe : pipes)
//		{
//			pipe->pipe_repair = repSt;
//		}
//		cout << "������!" << endl;
//		break;
//	}
//	case 2:
//		return;
//	default:
//		cout << "�� ��� �� ������. �� ��� �� ������." << endl;
//		break;
//	}
//}
//void GTS::searchPipe(unordered_map<int, Pipe>& Pipes)
//{
//	while (true)
//	{
//		cout << "��������, ��� �� ����� ����� ����� ��� �����: " << endl;
//		cout << "1. �� �����;" << endl;
//		cout << "2. �� ������� �����;" << endl;
//		cout << "3. �����. � �� ���� ������ � ������ � ���� �������� �����." << endl;
//		switch (GetCorrectData(1, 3))
//		{
//		case 1:
//		{
//			string pipeName;
//			cout << "�������� ��� ����� (�� ���� ������ ��������, ���� �� �� ��� ��������): " << endl;
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
//				cout << "��� �� �� ��� ��������, ��� �� �������� ������. Anyway, ���� � ����� ������ ���." << endl;
//			else
//				EditPipes(editPipes);
//		}
//		break;
//		case 2:
//		{
//			cout << "�������� ������ ����� (0 - �����; 1 - � �������):" << endl;
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
//				cout << "��� ����� � ����� ��������. ��� ��� ������, ��� � �������." << endl;
//			else
//				EditPipes(editPipes);
//		}
//		break;
//		case 3:
//			return;
//		default:
//		{
//			cout << "�� ��� �� ������..." << endl;
//			break;
//		}
//		}
//	}
//}
//void GTS::EditStation(Station& station)
//{
//	cout << "�� ����� ������ �������� ���������� ������� �����?" << endl;
//	cout << "1. ��;" << endl;
//	cout << "2. ���." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "�������� ���������� ������� �����:";
//		station.station_working_workshops = GetCorrectData(1, station.GetWorkshops());
//		cout << "ID: " << station.Id << ": ";
//		station.PrintWorkshops();
//	}
//	case 2:
//		return;
//	default:
//	{
//		cout << "�������� ����� � ���������:" << endl;
//		break;
//	}
//	}
//}
//void GTS::EditStations(vector<Station*> stations)
//{
//	cout << "�� ����� ������ �������� ���������� ������� �����?" << endl;
//	cout << "1. ��;" << endl;
//	cout << "2. ���." << endl;
//	switch (GetCorrectData(1, 2))
//	{
//	case 1:
//	{
//		cout << "����������, �������� ������� �� ������� ����� (��� ����� �������): ";
//		float percent = GetCorrectData(0.0, 100.0);
//		for (auto& station : stations)
//		{
//			station->station_working_workshops = round(station->station_workshops * (100 - percent) / 100);
//		}
//		cout << "�� �������� �������." << endl;
//		break;
//	}
//	case 2:
//		return;
//	default:
//		cout << "�� ������...";
//		break;
//	}
//}
//void GTS::searchStation(unordered_map<int, Station>& Stations)
//{
//	while (true)
//	{
//		cout << "��� �� ����� ����� ��: " << endl;
//		cout << "1. �� �����:" << endl;
//		cout << "2. �� �������� ��������� �����;" << endl;
//		cout << "3. �����! �����! � �������� �����!" << endl;
//		switch (GetCorrectData(1, 3))
//		{
//		case 1:
//		{
//			string stationName;
//			cout << "�������� ��� (����, ����� �� �������� ���������):" << endl;
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
//				cout << "������� �� ���� ��������. �� �� �����." << endl;
//			else
//				EditStations(editStations);
//		}
//		break;
//		case 2:
//		{
//			cout << "�������� �������: " << endl;
//			int percent = GetCorrectData(0, 100);
//			cout << "����� �� �� ������ �����:" << endl;
//			cout << "1. ����� ������� (������� ��������� ����� ������ ���������);" << endl;
//			cout << "2. � ����� �� ���������;" << endl;
//			cout << "3. ����� ������� (������� ��������� ����� ������ ���������)." << endl;
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
//				cout << "������ �������. �� �� �����." << endl;
//			else
//				EditStations(editStations);
//		}
//		break;
//		case 3:
//			return;
//		default:
//		{
//			cout << "�� ��� �� ��������." << endl;
//			break;
//		}
//		}
//	}
//}