#include "Pipe.h"
#include "Station.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "connections.h"
#include "Operation.h"

using namespace std;


void SPIDER::ConnectInSPIDER1(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections)
{
	if (Stations.size() == 0)
	{
		cout << "КС нет.";
		return;
	}
	if (Pipes.size() == 0)
	{
		cout << "Труб нет.";
		return;
	}
	int k = 0;
	vector<int> free_cs;
	for (auto& elem : Stations)
	{
		if (elem.second.Get_Id_in() + elem.second.Get_Id_out() < 2)
		{
			k += 1;
			free_cs.push_back(elem.first);
		}
	}
	if (k < 2)
	{
		cout << "ЗАНЯТО!";
		return;
	}

	int n = 0;
	vector<int> free_pipes;
	for (auto& elem : Pipes)
	{
		if (elem.second.Get_free())
		{
			n += 1;
			free_pipes.push_back(elem.first);
		}
	}
	if (n < 1)
	{
		cout << "Трубы заняты...";
		return;
	}

	connections pipe_connect;
	cout << "Напишите ID КС (вход): ";
	pipe_connect.id_entry = inputNumber<int>(cin);
	if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_entry) == free_cs.end())
	{
		while (true)
		{
			cout << "ещё раз. ВХОД. ";
			pipe_connect.id_entry = inputNumber<int>(cin);
			if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_entry) != free_cs.end())
			{
				Stations[pipe_connect.id_entry].Set_Id_in(Stations[pipe_connect.id_entry].Get_Id_in() + 1);
				break;
			}
		}
	}
	else
	{
		Stations[pipe_connect.id_entry].Set_Id_in(Stations[pipe_connect.id_entry].Get_Id_in() + 1);
	}

	cout << "Напишите ID КС (выход): ";
	pipe_connect.id_out = inputNumber<int>(cin);
	if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_out) == free_cs.end() || (pipe_connect.id_out == pipe_connect.id_entry))
	{
		while (true)
		{
			cout << "Напишите ID КС (выход): ";
			pipe_connect.id_out = inputNumber<int>(cin);
			if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_out) != free_cs.end() && (pipe_connect.id_out != pipe_connect.id_entry))
			{
				Stations[pipe_connect.id_out].Set_Id_out(Stations[pipe_connect.id_out].Get_Id_out() + 1);
				break;
			}
		}
	}
	else
	{
		Stations[pipe_connect.id_out].Set_Id_out(Stations[pipe_connect.id_out].Get_Id_out() + 1);
	}

	int i = 0;
	int pipe_diameter;
	while (true)
	{
		cout << "Напишите диаметр трубы (500, 700, 1000, 1400): ";
		pipe_diameter = GetCorrectDiameter(500, 1400);
		for (auto& idp : free_pipes)
		{
			if (Pipes[idp].GetDiameter() == pipe_diameter)
			{
				pipe_connect.id_pipe = idp;
				i += 1;
				Pipes[idp].Set_free(0);
				break;
			}
		}
		if (i == 1)
		{
			Connections[pipe_connect.id_entry].push_back(pipe_connect);
			break;
		}
		else
		{
			cout << "Мы не нашли подходящую трубу. Придётся создать новую";
			int new_id_pipe = AddNewPipeConnect(Pipes, pipe_diameter);
			pipe_connect.id_pipe = new_id_pipe;
			Pipes[new_id_pipe].Set_free(0);
			Connections[pipe_connect.id_entry].push_back(pipe_connect);
			break;
		}
	}
}
int SPIDER::AddNewPipeConnect(unordered_map<int, Pipe>& Pipes, int diameter)
{
	cout << "Новая труба:" << endl;
	Pipe pipe;
	cin >> pipe;
	pipe.SetDiameter(diameter);
	int new_pipe_id = pipe.GetId();
	Pipes.insert({ new_pipe_id, pipe });
	return new_pipe_id;
}

void SPIDER::ShowSPIDER(unordered_map<int, vector<connections>>& Connections)
{
	cout << "КС ВХОД ----- ТРУБА ----КС ВЫХОД" << endl;
	if (Connections.size() == 0)
	{
		cout << "Пусто!" << endl;
	}
	else
	{
		for (const auto& elem : Connections)
		{
			for (const auto& conn : elem.second)
			{
				cout << "\t" << conn.id_entry << " \t" << conn.id_pipe << " \t" << conn.id_out << endl;
			}
		}
	}
}


void SPIDER::DeleteConnection(unordered_map<int, vector<connections>>& Connections, unordered_map<int, Pipe>& Pipes)
{
	cout << "Напишите ID трубы, которую хотите удалить ";
	int idp = GetCorrectData(1, int(Pipes.size()));
	for (auto& elem : Connections)
	{
		auto& connection_list = elem.second;
		connection_list.erase(remove_if(connection_list.begin(), connection_list.end(),
			[idp](const connections& conn) { return conn.id_pipe == idp; }),
			connection_list.end());
	}
}

void SPIDER::dfs(int stationId, unordered_map<int, vector<connections>>& Connections, unordered_map<int, int>& state, vector<int>& result, bool& hasCycle) {
	if (state[stationId] == 1) {
		hasCycle = true;
		return;
	}
	if (state[stationId] == 0) {
		state[stationId] = 1;
		for (auto& conn : Connections[stationId]) {
			dfs(conn.id_out, Connections, state, result, hasCycle);
		}
		state[stationId] = 2;
		result.push_back(stationId);
	}
}




vector<int> SPIDER::topologSort(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections)
{
	vector<int> result;
	unordered_map<int, int> enterEdges;
	unordered_map<int, int> outEdges;
	unordered_map<int, int> state;
	bool hasCycle = false;

	for (auto& elem : Connections)
	{
		for (auto& conn : elem.second)
		{
			if (conn.id_out != 0)
				enterEdges[conn.id_out]++;
		}
	}
	for (auto& elem : Connections)
	{
		for (auto& conn : elem.second)
		{
			if (conn.id_entry != 0)
				outEdges[conn.id_entry]++;
		}
	}

	for (auto& elem : Stations) {
		state[elem.first] = 0;
	}

	for (auto& elem : Stations) {
		if (enterEdges.find(elem.first) == enterEdges.end() && outEdges.find(elem.first) != outEdges.end()) {
			dfs(elem.first, Connections, state, result, hasCycle);
		}
	}

	for (auto& elem : Stations) {
		if (state[elem.first] == 0) {
			dfs(elem.first, Connections, state, result, hasCycle);
		}
	}

	if (hasCycle) {
		return {};
	}

	reverse(result.begin(), result.end());
	return result;
}


void Operations::EditPipes(unordered_map<int, Pipe>& pipes, const unordered_set<int>& selectedPipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections) {
	cout << "Что вы хотите сделать?" << endl;
	cout << "1. Отредачить (статус)" << endl;
	cout << "2. Удалить" << endl;
	cout << "3. Ничего. Назад" << endl;

	switch (GetCorrectData(1, 3)) {
	case 1: {
		cout << "Напиши статус трубы (Если трубы в ремонте - пишите 1. Если труба готова/не в ремонте - пишите 0): ";
		bool repSt = GetCorrectData(false, true);

		for (int id : selectedPipes) {
			auto it = pipes.find(id);
			if (it != pipes.end()) {
				it->second.SetRepairStatus(repSt);
			}
		}
		cout << "Вот." << endl;
		break;
	}
	case 2: {
		for (int id : selectedPipes) {
			auto it = pipes.find(id);
			if (it != pipes.end()) {
				for (auto& connVec : Connections) {
					auto& connList = connVec.second;  
					for (auto connIt = connList.begin(); connIt != connList.end(); ) {
						if (connIt->id_pipe == id) {
							cout << "Нашли!" << endl;
							int id_entry = connIt->id_entry;
							int id_out = connIt->id_out;

							Stations[id_entry].Set_Id_in(Stations[id_entry].Get_Id_in() - 1);
							Stations[id_out].Set_Id_out(Stations[id_out].Get_Id_out() - 1);
							connIt = connList.erase(connIt);  
						}
						else {
							++connIt;
						}
					}
				}
				pipes.erase(it);
				cout << "ID " << id << endl;
			}
			else {
				cout << "Не нашли..." << endl;
			}
		}
		cout << "Всё .-." << endl;
		break;
	}
	case 3:
		return;

	default:
		cout << "welll welll welll" << endl;
		break;
	}
}

void SPIDER::InitializeCapacities(unordered_map<int, Pipe>& pipes) {
	for (auto& pipePair : pipes) {
		Pipe& pipe = pipePair.second;
		int diameter = pipe.GetDiameter();


		if (diameter == 700) {
			pipe.SetCapac(12);
		}
		else if (diameter == 1000) {
			pipe.SetCapac(28);
		}
		else if (diameter == 1400) {
			pipe.SetCapac(95);
		}
		else if (diameter == 500) {
			pipe.SetCapac(5);
		}
	}
}

void SPIDER::Way(unordered_map<int, Pipe>& Pipes, unordered_map<int, vector<connections>>& Connections, unordered_map<int, CStations>& Stations)
{
	if (Connections.size() == 0)
	{
		cout << "Нету связей... :( " << endl;
		return;
	}

	set<int> vertices;
	int maxLenght = 0;
	int minLenght = numeric_limits<int>::max();

	for (auto& connection_list : Connections)
	{
		for (auto& conn : connection_list.second)
		{
			vertices.insert(conn.id_entry);
			vertices.insert(conn.id_out);
			if (conn.id_entry > maxLenght)
			{
				maxLenght = conn.id_entry;
			}
			if (conn.id_entry < minLenght)
			{
				minLenght = conn.id_entry;
			}
			if (conn.id_out > maxLenght)
			{
				maxLenght = conn.id_out;
			}
			if (conn.id_out < minLenght)
			{
				minLenght = conn.id_out;
			}
		}
	}

	int start_vertices;
	int end_vertices;

	cout << "Напишите ID КС начало: ";
	start_vertices = GetCorrectData(minLenght, maxLenght);
	while (vertices.find(start_vertices) == vertices.end())
	{
		cout << "Ещё раз. Напишите. ID. КС. НАЧАЛО.: ";
		start_vertices = GetCorrectData(minLenght, maxLenght);
	}

	cout << "Напишите ID КС конец: ";
	end_vertices = GetCorrectData(minLenght, maxLenght);
	while (vertices.find(end_vertices) == vertices.end())
	{
		cout << "конец...: ";
		end_vertices = GetCorrectData(minLenght, maxLenght);
	}

	for (const auto& vertex : vertices) {
		Stations[vertex].SetShortestPath(numeric_limits<int>::max());
	}
	Stations[start_vertices].SetShortestPath(0);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> queueueue;
	queueueue.push({ 0, start_vertices });

	unordered_map<int, int> predecessors;

	while (!queueueue.empty()) {
		int current_vertices = queueueue.top().second;
		int current_distance = queueueue.top().first;
		queueueue.pop();

		if (current_vertices == end_vertices) {
			break;
		}

		for (const auto& conn : Connections[current_vertices]) {
			int neighbor_vertices = conn.id_out;
			Pipe& pipe = Pipes[conn.id_pipe];

			if (pipe.GetRepairStatus() == 1) continue;

			int new_distance = current_distance + pipe.GetLen();

			if (new_distance < Stations[neighbor_vertices].GetShortestPath()) {
				Stations[neighbor_vertices].SetShortestPath(new_distance);
				queueueue.push({ new_distance, neighbor_vertices });
				predecessors[neighbor_vertices] = current_vertices;
			}
		}
	}

	if (Stations[end_vertices].GetShortestPath() == numeric_limits<int>::max())
	{
		cout << "трубы или труба не работает... " << endl;
	}
	else
	{
		cout << "Ответ: " << Stations[end_vertices].GetShortestPath() << endl;
		vector<int> path;
		for (int Path = end_vertices; Path != start_vertices; Path = predecessors[Path]) {
			path.push_back(Path);
		}
		path.push_back(start_vertices);
		reverse(path.begin(), path.end());

		cout << "Посещаемые КС: ";
		for (size_t i = 0; i < path.size(); ++i) {
			cout << path[i];
			if (i < path.size() - 1) {
				cout << " -> ";
			}
		}
		cout << endl;
	}
}


bool BFS(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent)
{
	int V = rGraph.size();
	vector<bool> visited(V, false);

	queue<int> que;
	que.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!que.empty())
	{
		int u = que.front();
		que.pop();

		for (int v = 0; v < V; v++)
		{
			if (!visited[v] && rGraph[u][v] > 0)
			{
				que.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[t];
}

void SPIDER::flow(unordered_map<int, vector<connections>>& Connections, unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations) {
	InitializeCapacities(Pipes);

	if (Connections.size() == 0) {
		cout << "Нет связей!" << endl;
		return;
	}

	set<int> vertices;
	int maxLenght = 0;
	int minLenght = numeric_limits<int>::max();

	for (auto& connection_list : Connections) {
		for (auto& conn : connection_list.second) {
			vertices.insert(conn.id_entry);
			vertices.insert(conn.id_out);
			if (conn.id_entry > maxLenght) {
				maxLenght = conn.id_entry;
			}
			if (conn.id_entry < minLenght) {
				minLenght = conn.id_entry;
			}
			if (conn.id_out > maxLenght) {
				maxLenght = conn.id_out;
			}
			if (conn.id_out < minLenght) {
				minLenght = conn.id_out;
			}
		}
	}

	int s;
	cout << "Напишите начало (КС): ";
	s = GetCorrectData(minLenght, maxLenght);
	cout << "Напишите конец (КС): ";
	int t;
	t = GetCorrectData(minLenght, maxLenght);

	while (s == t) {
		cout << "Другое значение." << endl;
		t = GetCorrectData(minLenght, maxLenght);
	}

	int V = maxLenght + 1;
	vector<vector<int>> RGraph(V, vector<int>(V, 0));

	for (const auto& connection_list : Connections) {
		for (const auto& conn : connection_list.second) {
			int capacity = Pipes[conn.id_pipe].GetCapac();
			RGraph[conn.id_entry][conn.id_out] = capacity;
		}
	}

	vector<int> parent(V, -1);
	int maxFlow = 0;

	while (BFS(RGraph, s, t, parent)) {
		int pathFlow = numeric_limits<int>::max();
		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			pathFlow = min(pathFlow, RGraph[u][v]);
		}

		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			RGraph[u][v] -= pathFlow;
			RGraph[v][u] += pathFlow;
		}

		maxFlow += pathFlow;
	}

	cout << "Ответ: " << maxFlow << endl;
}

void Operations::EditCStations(unordered_map<int, CStations>& stations, unordered_set<int>& selected_stations, unordered_map<int, Pipe>& Pipes, unordered_map<int, vector<connections>>& Connections) {
	cout << "Что вы хотите сделать?" << endl;
	cout << "1. Отредачить (процент)" << endl;
	cout << "2. Удалить" << endl;
	cout << "3. Ничего. Назад" << endl;

	switch (GetCorrectData(1, 3)) {
	case 1: {
		cout << "Напишите процент нерабочих цехов: " << endl;
		float percent = GetCorrectData(0.0f, 100.0f);
		for (int id : selected_stations) {
			auto it = stations.find(id);
			if (it != stations.end()) {
				int station_workshops = it->second.GetWorkshops();
				int activeWorkshops = round(station_workshops * (100 - percent) / 100.0f);
				it->second.SetActWorkshops(activeWorkshops);
			}
		}
		cout << "Всё!" << endl;
		break;
	}
	case 2: {
		for (int id : selected_stations) {
			auto it = stations.find(id);
			if (it != stations.end()) {
				for (auto& connVec : Connections) {
					auto& connList = connVec.second;  
					for (auto connIt = connList.begin(); connIt != connList.end(); ) {
						if (connIt->id_entry == id || connIt->id_out == id) {
							int pipe_id = connIt->id_pipe;
							Pipes.erase(pipe_id);  
							connIt = connList.erase(connIt);  
						}
						else {
							++connIt;
						}
					}
				}
				stations.erase(it);
				cout << "ID " << id << " Удалено" << endl;
			}
			else {
				continue;
			}
		}
		cout << "Готово" << endl;
		break;
	}
	case 3:
		return;

	default:
		cout << "!" << endl;
		break;
	}
}