#include "Data.h"
#include <iostream>
#include <string>
#define INPUT_LINE(in, str) getline(in>> ws, str); \
						 cerr << str <<  endl
#define PRINT_PARAM(out, x) out<< #x << "=" << x <<  endl
template <typename T>
T GetCorrectData(T min, T max)
{
	T x;
	while ((cin >> x).fail() || cin.peek() != '\n' || x < min || x > max)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "�� ��� �� ������. �������� ����� �� " << min << " �� " << max << ":" << endl;
	}
	cerr << x << endl;

	return x;
}
template <typename T>
T& SelectElement(unordered_map<int, T>& notes, int key)
{
	auto it = notes.find(key);
	if (it != notes.end())
	{
		return it->second;
	}
	else
	{
		cout << "��� ���� �� ��������. �������� ��������� :0 ( �� " << notes.size() << "): " << endl;
	}
}

template <typename T>
T GetCorrectDiameter(T min, T max)
{
	T diam;
	cin >> diam;
	while (((diam != 500) && (diam != 700) && (diam != 1000) && (diam != 1400)) || diam < min || diam > max || cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "����������, �������� ������ ������� ����� (500, 700, 1000, 1400): " << endl;
		cin >> diam;
	}
	cerr << diam << endl;
	return diam;
}


template <typename K>
unordered_map<int, K> removeKeyIfExists(unordered_map<int, K>& notes, int key) {
	while (true) {
		auto it = notes.find(key);
		if (it != notes.end()) {
			notes.erase(it);
			cout << "������. �������!" << endl;
			return notes;
		}
		else {
			cout << "�� �� ����� ��, ��� �� ������ �������. �������� �� ���� �����-�� ��� �������..." << endl;
			key = GetCorrectData(1, findMaxId(notes));
		}
	}
}
string inputString(istream& in = cin);
template<typename K, typename V>
K findMaxId(const  unordered_map<K, V>& map) {
	if (map.empty()) {
		throw  runtime_error("�����...");
	}

	K maxId = numeric_limits<K>::min();

	for (const auto& pair : map) {
		if (pair.first > maxId) {
			maxId = pair.first;
		}
	}
	return maxId;
}

template <typename T>
T inputNumber(istream& in = cin)
{
	T x;
	while ((in >> x).fail()
		|| in.peek() != '\n')
	{
		in.clear();
		in.ignore(10000, '\n');
		cout << "�� �����! " << endl;
	}
	cerr << x << endl;
	return x;
}
string inputString(istream& in)
{
	string str;
	 getline(in >>  ws, str);
	cerr << str << endl;
	return str;
}