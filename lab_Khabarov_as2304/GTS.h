#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Station.h"
class GTS
{
public:
	void EditPipe(Pipe& pipe);
	void EditPipes(vector <Pipe*>& pipes);
	void searchPipe(unordered_map<int, Pipe>& Pipes);
	void EditStation(Station& station);
	void EditStations(vector <Station*> stations);
	void searchStation(unordered_map<int, Station>& Stations);
};