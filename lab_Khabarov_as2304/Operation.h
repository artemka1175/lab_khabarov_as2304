#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "Station.h"
#include "connections.h"

#pragma once
class GTS
{
public:
	unordered_map<int, Pipe> Pipes = {};
	unordered_map<int, CStations> Stations = {};
	unordered_map<int, connections> Connections = {};
	void InitializeCapacities(std::unordered_map<int, Pipe>& pipes);
	bool HasConnection(const unordered_map<int, Pipe>& Pipes, const int& CSid1, const int& CSid2);
	void ConnectInGTS(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations);
	void ConnectInGTS1(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections);
	int AddNewPipeConnect(unordered_map<int, Pipe>& Pipes, int diameter);
	void ShowGTS(unordered_map<int, vector<connections>>& Connections);
	void DeleteConnection(unordered_map<int, vector<connections>>& Connections, unordered_map<int, Pipe>& Pipes);
	void Djikstra(unordered_map<int, Pipe>& Pipes, unordered_map<int, vector<connections>>& Connections, unordered_map<int, CStations>& Stations);
	void FordFulkerson(unordered_map<int, vector<connections>>& Connections, unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations);
	vector<int> topologSort(unordered_map<int, Pipe>& Pipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Connections);
private:
	void dfs(int stationId, unordered_map<int, vector<connections>>& Connections, unordered_map<int, int>& state, vector<int>& result, bool& hasCycle);
};

class Operations
{
public:

	void EditPipes(unordered_map<int, Pipe>& pipes, const unordered_set<int>& selectedPipes, unordered_map<int, CStations>& Stations, unordered_map<int, vector<connections>>& Conns);

	void EditCStations(unordered_map <int, CStations>& CStations, unordered_set<int>& selected_stations, unordered_map<int, Pipe>& Pipes, unordered_map<int, vector<connections>>& Conns);

	template <typename T>
	static void Show(std::unordered_map<int, T> objs)
	{
		if (objs.size() == 0)
			cout << "��� ��������!" << endl;
		for (const auto& [id, obj] : objs)
			cout << obj;
	}

};