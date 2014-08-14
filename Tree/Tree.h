#include <string>
#include "Top.h"

#pragma once

using namespace std;

template <class Data>
class Tree
{
	Top<Data>* proot;
	Top<Data>* FindTop (Top<Data>*& pcur, string key);
	void DeleteTree(Top<Data>*& pcur);
	void PrintTop(Top<Data>*& pcur, string s);
	void DeleteTop(Top<Data>*& pcur, string key, bool& ret);
	bool InsertTop(Top<Data>*& pcur, Top<Data>* pins);
public:
	Tree();
	~Tree();
	void Add (Data d, string key);
	Top<Data>* Find (string key);
	bool Delete(string key);
	void Print(string s);
};
