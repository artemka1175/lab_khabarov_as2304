#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "Station.h"
#include "Data.h"
#pragma once

struct connections {
	int id_entry;
	int id_pipe;
	int id_out;
};

class connect
{
public:
	unordered_map<int, Pipe> Pipes = {};
	unordered_map<int, Station> Stations = {};
	unordered_map<int, connections> Connections = {};
	bool HasConnection(const unordered_map<int, Pipe>& Pipes, const int& CSid1, const int& CSid2);
	void ConnectIn(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations);
	void ConnectIn1(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations, unordered_map<int, connections>& Connections);
	int AddNewPipeConnect(unordered_map<int, Pipe>& Pipes, int diameter);
	void Show(unordered_map<int, connections>& Connections);
	void DeleteConnection(unordered_map<int, connections>& Connections, unordered_map<int, Pipe>& Pipes);
	vector<int> topologicalSort(unordered_map<int, Pipe>& Pipes, unordered_map<int, Station>& Stations, unordered_map<int, connections>& Connections);
};
