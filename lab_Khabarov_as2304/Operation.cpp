#include "Pipe.h"
#include "Station.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "connections.h"
#include "Operation.h"

using namespace std;


void GTS::ConnectInGTS1(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections)
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
		cout << "Труба занята...";
		return;
	}

	connections pipe_connect;
	cout << "Напишите ID КС (вход): ";
	pipe_connect.id_entry = inputNumber<int>(cin);
	if (find(free_cs.begin(), free_cs.end(), pipe_connect.id_entry) == free_cs.end())
	{
		while (true)
		{
			cout << "Напишите ID КС (вход): ";
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

	cout << "Напишите ID трубы: ";
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
			cout << "Диаметр трубы не совпадает. Давайте заново!";
			int new_id_pipe = AddNewPipeConnect(Pipes, pipe_diameter);
			pipe_connect.id_pipe = new_id_pipe;
			Pipes[new_id_pipe].Set_free(0);
			Connections[pipe_connect.id_entry].push_back(pipe_connect);
			break;
		}
	}
}
int GTS::AddNewPipeConnect(unordered_map<int, Pipe>& Pipes, int diameter)
{
	cout << "Новая труба:" << endl;
	Pipe pipe;
	cin >> pipe;
	pipe.SetDiameter(diameter);
	int new_pipe_id = pipe.GetId();
	Pipes.insert({ new_pipe_id, pipe });
	return new_pipe_id;
}

void GTS::ShowGTS(unordered_map<int, vector<connections>>& Connections)
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
				cout << "\t[" << conn.id_entry << "] \t[" << conn.id_pipe << "] \t[" << conn.id_out << "]" << endl;
			}
		}
	}
}


void GTS::DeleteConnection(unordered_map<int, vector<connections>>& Connections, unordered_map<int, Pipe>& Pipes)
{
	cout << "Напишите ID трубы, которую хотите удалить ";
	int idp = GetCorrectData(1, int(Pipes.size()));
	for (auto& elem : Connections)
	{
		auto& conn_list = elem.second;
		conn_list.erase(remove_if(conn_list.begin(), conn_list.end(),
			[idp](const connections& conn) { return conn.id_pipe == idp; }),
			conn_list.end());
	}
}

void GTS::dfs(int stationId, unordered_map<int, vector<connections>>& Connections, unordered_map<int, int>& state, vector<int>& result, bool& hasCycle) {
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




vector<int> GTS::topologSort(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections)
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

void GTS::InitializeCapacities(unordered_map<int, Pipe>& pipes) {
	for (auto& pipePair : pipes) {
		Pipe& pipe = pipePair.second;
		int diameter = pipe.GetDiameter();

		if (diameter == 500) {
			pipe.SetCapac(5);
		}
		else if (diameter == 700) {
			pipe.SetCapac(12);
		}
		else if (diameter == 1000) {
			pipe.SetCapac(28);
		}
		else if (diameter == 1400) {
			pipe.SetCapac(95);
		}
	}
}


using namespace std;

void GTS::Djikstra(unordered_map<int, Pipe>& Pipes, unordered_map<int, vector<connections>>& Connections, unordered_map<int, CStations>& Stations)
{
	if (Connections.size() == 0)
	{
		cout << "Нет связей." << endl;
		return;
	}

	set<int> vertexes;
	int maxel = 0;
	int minel = numeric_limits<int>::max();

	for (auto& conn_list : Connections)
	{
		for (auto& conn : conn_list.second)
		{
			vertexes.insert(conn.id_entry);
			vertexes.insert(conn.id_out);
			if (conn.id_entry > maxel)
			{
				maxel = conn.id_entry;
			}
			if (conn.id_entry < minel)
			{
				minel = conn.id_entry;
			}
			if (conn.id_out > maxel)
			{
				maxel = conn.id_out;
			}
			if (conn.id_out < minel)
			{
				minel = conn.id_out;
			}
		}
	}

	int start_vertex;
	int end_vertex;

	cout << "Напишите стартовую вершину: ";
	start_vertex = GetCorrectData(minel, maxel);
	while (vertexes.find(start_vertex) == vertexes.end())
	{
		cout << "Напишите стартовую вершину: ";
		start_vertex = GetCorrectData(minel, maxel);
	}

	cout << "Напишите конечную вершину: ";
	end_vertex = GetCorrectData(minel, maxel);
	while (vertexes.find(end_vertex) == vertexes.end())
	{
		cout << "Напишите конечную вершину: ";
		end_vertex = GetCorrectData(minel, maxel);
	}

	for (const auto& vertex : vertexes) {
		Stations[vertex].SetShortestPath(numeric_limits<int>::max());
	}
	Stations[start_vertex].SetShortestPath(0);

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0, start_vertex });

	unordered_map<int, int> predecessors;

	while (!pq.empty()) {
		int current_vertex = pq.top().second;
		int current_distance = pq.top().first;
		pq.pop();

		if (current_vertex == end_vertex) {
			break;
		}

		for (const auto& conn : Connections[current_vertex]) {
			int neighbor_vertex = conn.id_out;
			const Pipe& truba = Pipes[conn.id_pipe];
			int new_distance = current_distance + truba.GetLen();

			if (new_distance < Stations[neighbor_vertex].GetShortestPath()) {
				Stations[neighbor_vertex].SetShortestPath(new_distance);
				pq.push({ new_distance, neighbor_vertex });
				predecessors[neighbor_vertex] = current_vertex;
			}
		}
	}

	if (Stations[end_vertex].GetShortestPath() == numeric_limits<int>::max())
	{
		cout << "вввв " << start_vertex << " ввв " << end_vertex << "." << endl;
	}
	else
	{
		cout << "ююю " << start_vertex << " кс " << end_vertex << ": " << Stations[end_vertex].GetShortestPath() << endl;
		vector<int> path;
		for (int at = end_vertex; at != start_vertex; at = predecessors[at]) {
			path.push_back(at);
		}
		path.push_back(start_vertex);
		reverse(path.begin(), path.end());

		cout << "Значение КС: ";
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

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++)
		{
			if (!visited[v] && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[t];
}

void GTS::FordFulkerson(unordered_map<int, vector<connections>>& Connections, unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations) {
	InitializeCapacities(Pipes);

	if (Connections.size() == 0) {
		cout << "Связей 0!" << endl;
		return;
	}

	set<int> vertexes;
	int maxel = 0;
	int minel = numeric_limits<int>::max();

	for (auto& conn_list : Connections) {
		for (auto& conn : conn_list.second) {
			vertexes.insert(conn.id_entry);
			vertexes.insert(conn.id_out);
			if (conn.id_entry > maxel) {
				maxel = conn.id_entry;
			}
			if (conn.id_entry < minel) {
				minel = conn.id_entry;
			}
			if (conn.id_out > maxel) {
				maxel = conn.id_out;
			}
			if (conn.id_out < minel) {
				minel = conn.id_out;
			}
		}
	}

	int s;
	cout << "ВЫВЫ: ";
	s = GetCorrectData(minel, maxel);
	cout << "КККУ: ";
	int t;
	t = GetCorrectData(minel, maxel);

	while (s == t) {
		cout << "ЧВВВ!" << endl;
		t = GetCorrectData(minel, maxel);
	}

	int V = maxel + 1;
	vector<vector<int>> RGraph(V, vector<int>(V, 0));

	for (const auto& conn_list : Connections) {
		for (const auto& conn : conn_list.second) {
			RGraph[conn.id_entry][conn.id_out] = Pipes[conn.id_pipe].GetCapac();
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
							connIt = connList.erase(connIt);  // Erase the connection from the vector
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