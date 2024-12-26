#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include "Pipe.h"
#include "Station.h"
#include "Operation.h"
#include "Data.h"
#include "Connections.h"


using namespace std;
using namespace chrono;
template<typename T, typename U>
using Filter = bool(*)(T& val, U param);
template<typename T>
bool checkByName(T& val, string name)
{
	size_t pos = val.Getname().find(name);
	if (pos !=  string::npos) return true;
	else return false;
}
bool checkByRepairStatus(Pipe& p, bool status)
{
	return p.GetRepairStatus() == status;
}
bool checkByWSInWork(CStations& cs, double percent)
{
	return cs.GetPercentOfNonActiveWorkshops() >= percent;
}

template<typename T, typename U>
unordered_set<int> findByFilter(unordered_map<int, T>& map, Filter<T, U> f, U param)
{
	unordered_set<int> res;
	int i = 0;
	for (auto& [id, val] : map)
	{
		if (f(val, param))
			res.emplace(id);
	}
	return res;
}

unordered_set<int> selectByChosenFilter(unordered_map<int, Pipe>& map)
{
	unordered_set<int> res;
	cout << "Как вы хотите выбрать трубы?" << endl;
	cout << "1. По имени" << endl;
	cout << "2. По статусу" << endl;
	switch (GetCorrectData(1, 2))
	{
	case 1:
	{
		cout << "Напишите имя КС: "; string name = inputString();
		res = findByFilter(map, checkByName, name);
		break;
	}
	case 2:
	{
		cout << "Напиши статус трубы (Если трубы в ремонте - пишите 1. Если труба готова/не в ремонте - пишите 0): "; bool status = GetCorrectData<int>(0, 1);
		res = findByFilter(map, checkByRepairStatus, status);
		break;
	}
	default:
		break;
	}
	return res;
}

unordered_set<int> selectByChosenFilter(unordered_map<int, CStations>& map)
{
	unordered_set<int> res;
	cout << "Как вы хотите выбрать КС?" << endl;
	cout << "1. По имени" << endl;
	cout << "2. По проценты нерабочих цехов" << endl;
	switch (GetCorrectData(1, 2))
	{
	case 1:
	{
		cout << "Напишите имя: "; string name = inputString();
		res = findByFilter(map, checkByName, name);
		break;
	}
	case 2:
	{
		cout << "Напишите процент НЕ рабочих цехов: "; double percent = GetCorrectData<double>(0.0, 100.0);
		res = findByFilter(map, checkByWSInWork, percent);
		break;
	}
	default:
		break;
	}
	return res;
}


void PipeEdit(unordered_map<int, Pipe>& Pipes) {
	if (Pipes.size() == 0) {
		cout << "Нечего редактировать." << endl;
	}
	else {
		cout << "Напишите ID трубы: ";
		int id;
		while (true) {
			id = GetCorrectData(1, numeric_limits<int>::max());
			if (Pipes.find(id) != Pipes.end())
				break;
			else
				cout << "Нет такого. Заново" << endl;
		}
		Pipe& pipe0 = SelectElement(Pipes, id);
		pipe0.EditPipe();
	}
}

void StationEdit(unordered_map<int, CStations>& Stations) {
	if (Stations.size() == 0) {
		cout << "Нечего редактировать." << endl;
	}
	else {
		cout << "Напишите ID КС: ";
		int id;
		while (true) {
			id = GetCorrectData(1, numeric_limits<int>::max());
			if (Stations.find(id) != Stations.end())
				break;
			else
				cout << "Мы не нашли это ID. Попробуйте снова и правильно!" << endl;
		}
		CStations& station0 = SelectElement(Stations, id);
		station0.EditCStation();
	}
}

void PipeDelete(unordered_map<int, Pipe>& Pipes, unordered_map<int, vector<connections>>& Conns, unordered_map<int, CStations>& Stations) {
	if (Pipes.size() == 0) {
		cout << "Нечего удалять!" << endl;
		return;
	}

	cout << "Введите ID трубы: ";
	int key0;
	key0 = GetCorrectData(1, findMaxId(Pipes));


	bool pipeInNetwork = false;
	for (const auto& connection_list : Conns) {
		for (const auto& conn : connection_list.second) {
			if (conn.id_pipe == key0) {
				pipeInNetwork = true;
				break;
			}
		}
		if (pipeInNetwork) break;
	}

	if (pipeInNetwork) {
		cout << "Обнаружена сеть, содержащая эту трубу. Вы уверены, что хотите удалить эту трубу? (0 - нет, 1 - да): ";
		int confirmation = GetCorrectData(0, 1);
		if (confirmation == 0) {
			cout << "Процесс удаления отменен :(." << endl;
			return;
		}
	}

	for (auto it = Conns.begin(); it != Conns.end(); ) {
		auto& connectionsVector = it->second;
		for (auto connIt = connectionsVector.begin(); connIt != connectionsVector.end(); ) {
			if (connIt->id_pipe == key0) {
				cout << "Происходит удаление сети, содержащей эту трубу (поломаете ведь)" << endl;
				int id_entry = connIt->id_entry;
				int id_out = connIt->id_out;

				Stations[id_entry].Set_Id_in(Stations[id_entry].Get_Id_in() - 1);
				Stations[id_out].Set_Id_out(Stations[id_out].Get_Id_out() - 1);
				connIt = connectionsVector.erase(connIt);
			}
			else {
				++connIt;
			}
		}
		if (connectionsVector.empty()) {
			it = Conns.erase(it); 
		}
		else {
			++it;
		}
	}
	removeKeyIfExists(Pipes, key0);
	cout << "Удаление прошло успешно!" << endl;
}
void StationDelete(unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Conns, unordered_map<int, Pipe>& Pipes) {
	if (Stations.size() == 0) {
		cout << "0 станций доступно!" << endl;
		return;
	}

	cout << "Введите ID: ";
	int key0;
	key0 = GetCorrectData(1, findMaxId(Stations));

	bool stationInNetwork = false;
	for (const auto& connection_list : Conns) {
		for (const auto& conn : connection_list.second) {
			if (conn.id_entry == key0 || conn.id_out == key0) {
				stationInNetwork = true;
				break;
			}
		}
		if (stationInNetwork) break;
	}

	if (stationInNetwork) {
		cout << "Обнаружена сеть, содержащая эту КС. Вы уверены, что хотите удалить эту КС? (0 - нет, 1 - да): ";
		int confirmation = GetCorrectData(0, 1);
		if (confirmation == 0) {
			cout << "Процесс удаления отменен -_-." << endl;
			return;
		}
	}

	for (auto it = Conns.begin(); it != Conns.end(); ) {
		auto& connectionsVector = it->second;
		for (auto connIt = connectionsVector.begin(); connIt != connectionsVector.end(); ) {
			if (connIt->id_entry == key0 || connIt->id_out == key0) {
				int pipeId = connIt->id_pipe;
				cout << "Происходит удаление сети, содержащей эту КСКСКСКСКСС! " << endl;
				if (Pipes.find(pipeId) != Pipes.end()) {
					Pipes[pipeId].Set_free(true);
				}
				if (connIt->id_entry == key0) {
					int id_out = connIt->id_out;
					Stations[id_out].Set_Id_in(Stations[id_out].Get_Id_in() - 1);
				}
				if (connIt->id_out == key0) {
					int id_entry = connIt->id_entry;
					Stations[id_entry].Set_Id_out(Stations[id_entry].Get_Id_out() - 1);
				}
				connIt = connectionsVector.erase(connIt);
			}
			else {
				++connIt;
			}
		}
		if (connectionsVector.empty()) {
			it = Conns.erase(it); 
		}
		else {
			++it;
		}
	}
	removeKeyIfExists(Stations, key0);
	cout << "Удаление прошло успешно!" << endl;
}
void saving(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections) {
	ofstream fout;
	string fileName;
	cout << "Напишите имя файла: ";
	INPUT_LINE(cin, fileName);
	fout.open(fileName);
	if (!fout.is_open())
	{
		cout << "Произошла ошибка...как-то!" << endl;
	}
	else {
		fout << Pipes.size() << endl;
		for (const auto& elem : Pipes)
			fout << elem.second;
		cout << "Данные о трубах сохранены!" << endl;

		fout << Stations.size() << endl;
		for (const auto& elem : Stations)
			fout << elem.second;
		cout << "Данные о КС сохранены!" << endl;

		fout << Connections.size() << endl;
		for (const auto& elem : Connections) {
			for (const auto& conn : elem.second) {
				fout << conn;
			}
		}
		cout << "Данные о связях сохранены!" << endl;
	}
	fout.close();
}

void loading(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections) {
	ifstream fin;
	string fileName;
	cout << "Напишите имя файла: ";
	INPUT_LINE(cin, fileName);
	fin.open(fileName);
	if (!fin.is_open())
	{
		cout << "Не нашли..." << endl;
	}
	else {
		int pipesSize;
		fin >> pipesSize;
		if (pipesSize == 0)
			cout << "Данных о трубах нет!" << endl;
		else {
			cout << "Данные о трубах загружены!" << endl;
		}
		while (pipesSize-- > 0)
		{
			Pipe pipe0;
			fin >> pipe0;
			Pipes.insert({ pipe0.GetId(), pipe0 });
		}

		int csSize;
		fin >> csSize;
		if (csSize == 0)
			cout << "Данных о КС нет!" << endl;
		else {
			cout << "Данные о КС загружены!" << endl;
		}
		while (csSize-- > 0)
		{
			CStations station0;
			fin >> station0;
			Stations.insert({ station0.GetId(), station0 });
		}

		int connection_size;
		fin >> connection_size;
		if (connection_size == 0)
			cout << "Данных о связях нет!" << endl;
		else {
			cout << "Данные о связях загружены!" << endl;
		}

		while (connection_size-- > 0) {
			connections connection0;
			fin >> connection0;
			Connections[connection0.id_entry].push_back(connection0);
		}
		fin.close();
	}
}

void filtering(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, Operations& operations, unordered_map<int, vector<connections>>& Connections) {
	bool flag = true;
	while (flag) {
		cout << "Что вы хотите отфильтровать?" << endl;
		cout << "1. Трубу" << endl;
		cout << "2. КС" << endl;
		cout << "3. !НАЗАД!" << endl;
		int cm = GetCorrectData(1, 3);
		unordered_set<int> nameResults;
		switch (cm) {
		case 1: {
			nameResults = selectByChosenFilter(Pipes);
			if (nameResults.empty()) {
				cout << "Простите. Мы не нашли трубы у вас там..." << endl;
			}
			else {
				cout << "Мы нашли!" << endl;
				for (int id : nameResults) {
					auto it = Pipes.find(id);
					if (it != Pipes.end()) {
						cout << "ID " << id << ": ";
						cout << it->second;
					}
				}
				cout << endl;
				operations.EditPipes(Pipes, nameResults, Stations, Connections);
			}
			break;
		}
		case 2: {
			nameResults = selectByChosenFilter(Stations);
			if (nameResults.empty()) {
				cout << "Простите. Их нет!" << endl;
			}
			else {
				cout << "Мы нашли!" << endl;
				for (int id : nameResults) {
					auto it = Stations.find(id);
					if (it != Stations.end()) {
						cout << "ID " << id << ": ";
						cout << it->second;
					}
				}
				cout << endl;
				operations.EditCStations(Stations, nameResults, Pipes, Connections);
			}
			break;
		}
		case 3:
			flag = false;
			break;
		default:
			cout << "Ё" << endl;
			break;
		}
	}
}
int MainMenu()
{
	cout << endl << "Выберите, что вы хотите сделать:" << endl;
	cout << "1. Создать новую трубу " << endl;
	cout << "2. Создать новую КС" << endl;
	cout << "3. Просмотреть объекты" << endl;
	cout << "4. Отредактировать трубу" << endl;
	cout << "5. Отредактировать КС" << endl;
	cout << "6. Удалить трубу" << endl;
	cout << "7. Удалить КС" << endl;
	cout << "8. Сохраниться" << endl;
	cout << "9. Загрузиться" << endl;
	cout << "10. Фильтрация" << endl;
	cout << "11. Соединенить трубы и КС в газотранспортную сеть" << endl;
	cout << "12. Показать сеть" << endl;
	cout << "13. Удалить связь" << endl;
	cout << "14. Топологическая сортировка" << endl;
	cout << "15. Кратчайший путь из А в Б" << endl;
	cout << "16. Максимальный поток из А в Б" << endl;
	cout << "0. Выход." << endl;
	return GetCorrectData(0, 16);
}



int main()
{
	setlocale(LC_ALL, "Russian"); // русификатор
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
	ofstream logfile("log_" + time);
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	unordered_map<int, Pipe> Pipes = {};
	unordered_map<int, CStations> Stations = {};
	Operations operations;
	SPIDER SPIDER;
	unordered_map<int, vector<connections>> Connections; 
	cout << endl;
    cout << "Здравствуйте. Добро пожаловать в меню по созданию и редактированию  трубы и КС или НПС!" << endl;
    cout << "***" << endl;
    cout << "В НОВОЙ версии 1.3 Мы добавили связи, топ. сортировку и поправили фильтр." << endl;
    cout << "***" << endl;

	while (true) {
		switch (MainMenu())
		{
		case 1:
		{
			cout << "----------------------------------------------------" << endl;
			Pipe pipe0;
			cin >> pipe0;
			Pipes.insert({ pipe0.GetId(), pipe0 });
			break;
		}
		case 2:
		{
			cout << "----------------------------------------------------" << endl;
			CStations station0;
			cin >> station0;
			Stations.insert({ station0.GetId(), station0 });
			break;
		}
		case 3:
		{
			cout << "----------------------------------------------------" << endl;
			Operations::Show(Pipes);
			cout << endl;
			Operations::Show(Stations);
			break;
		}
		case 4:
		{
			cout << "----------------------------------------------------" << endl;
			PipeEdit(Pipes);
			break;
		}
		case 5:
		{
			cout << "----------------------------------------------------" << endl;
			StationEdit(Stations);
			break;
		}
		case 6:
		{
			cout << "----------------------------------------------------" << endl;
			PipeDelete(Pipes, Connections, Stations);
			break;
		}
		case 7:
		{
			cout << "----------------------------------------------------" << endl;
			StationDelete(Stations, Connections, Pipes);
			break;
		}
		case 8:
		{
			cout << "----------------------------------------------------" << endl;
			saving(Pipes, Stations, Connections);
			break;
		}
		case 9:
		{
			cout << "----------------------------------------------------" << endl;
			loading(Pipes, Stations, Connections);
			break;
		}
		case 10:
		{
			cout << "----------------------------------------------------" << endl;
			filtering(Pipes, Stations, operations, Connections);
			break;
		}
		case 11:
		{
			cout << "----------------------------------------------------" << endl;
			SPIDER.ConnectInSPIDER1(Pipes, Stations, Connections);
			break;
		}
		case 12:
		{
			cout << "----------------------------------------------------" << endl;
			SPIDER.ShowSPIDER(Connections);
			break;
		}
		case 13:
		{
			cout << "----------------------------------------------------" << endl;
			SPIDER.DeleteConnection(Connections, Pipes);
			break;
		}
		case 14:
		{
			cout << "----------------------------------------------------" << endl;
			vector<int> sortStations = SPIDER.topologSort(Pipes, Stations, Connections);
			if (sortStations.empty()) {
				cout << "Нечего сортировать или есть ЦИКЛ!" << endl;
				break;
			}
			for (int id : sortStations)
			{
				cout << id << " ";
			}
			cout << endl;
			break;
		}
		case 15:
		{
			cout << "----------------------------------------------------" << endl;
			SPIDER.Way(Pipes, Connections, Stations);
			break;
		}
		case 16:
		{
			cout << "----------------------------------------------------" << endl;
			SPIDER.flow(Connections, Pipes, Stations);
			break;
		}

		case 0:
		{
			return false;
			break;
		}
		default:
		{
			cout << endl << "!ЗАНОВО!" << endl;
			break;
		}
		}
	}
	return 0;
}