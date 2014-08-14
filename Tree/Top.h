#include <string>

#pragma once

using namespace std;

template <class Data>
class Top
{
public:
	string value;
	bool state;
	Top<Data>* next;
	Top<Data>* son;
	Data d;
	Top<Data>(Data dat = 0, string val = 0)
	{
		d = dat;
		value = val;
		next = NULL;
		son = NULL;
	}
};