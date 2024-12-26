#include "Data.h"
#include <iostream>
#include <string>

string inputString(istream& in)
{
	string str;
	 getline(in >>  ws, str);
	cerr << str << endl;
	return str;
}