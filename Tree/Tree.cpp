// Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Tree.h"

using namespace std;

template <class Data> Tree<Data>::Tree()
{
	proot = new Top<Data>(0,"root");
}

template <class Data> Tree<Data>::~Tree()
{
	if (proot->son)
	{
		DeleteTree(proot->son);
	}
	delete proot;
}

template <class Data> void Tree<Data>::DeleteTree(Top<Data> *&pcur)
{
	if ((pcur->son == NULL) & (pcur->next == NULL))
	{
		delete pcur;
		return;
	}
	if (pcur->son == NULL) DeleteTree(pcur->next);
	if (pcur->next = NULL) DeleteTree(pcur->son);
}

template <class Data> bool Tree<Data>::InsertTop(Top<Data> *&pcur, Top<Data> *pins)
{
	if (pcur == NULL)
	{
		pins->state = true;
		pcur = pins;
		return true;
	}
	else
	{
		if (pcur->value[0] < pins->value[0]) return InsertTop(pcur->next, pins);
		if (pcur->value[0] > pins->value[0])
		{
			pins->state = true;
			pins->next = pcur;
			pcur = pins;
			return true;
		}
		if (pcur->value[0] == pins->value[0])
		{
			if (pcur->value == pins->value)
			{
				if (pcur->state) return false;
				pins->state = true;
				pins->next = pcur->next;
				pins->son = pcur->son;
				pcur = pins;
				return true;
			}
			int i = 1;
			while ((pcur->value[i] == pins->value[i]) & (pcur->value.length() > i) & (pins->value.length() > i)) i++;
			if (i == pcur->value.length()) 
			{
				pins->value.erase(0, i);
				return InsertTop(pcur->son, pins);
			}
			else
			{
				string s = pcur->value;
				s.erase(0, i);
				Top<Data>* p = new Top<Data>(pcur->d, s);
				p->son = pcur->son;
				pcur->son = p;
				p->state = pcur->state;
				pcur->value.erase(i);
				pins->value.erase(0, i);
				if (pins->value.length() == 0)
				{
					pcur->state = true;
					pcur->d = pins->d;
					return true;
				}
				else
				{
					pcur->d = 0;
					pcur->state = false;
					return InsertTop(pcur->son, pins);
				}
			}
		}
	}
}

template <class Data> void Tree<Data>::Add(Data d, string key)
{
	Top<Data> *pv = new Top<Data>(d, key);
	if (!InsertTop(proot->son, pv))
	{
		cout << "This record (" << pv->value << ") is already exist!" << endl;
		delete pv;
	}
}

template <class Data> Top<Data>* Tree<Data>::FindTop(Top<Data> *&pcur, string key)
{
	if (pcur == NULL) return NULL;
	else
	{
		if (pcur->value[0] < key[0]) return FindTop(pcur->next, key);
		if (pcur->value[0] > key[0]) return NULL;
		if (pcur->value[0] == key[0])
		{
			if (pcur->value == key)
			{
				if (pcur->state) return pcur;
				return NULL;
			}
		}
		int i = 1;
		while ((pcur->value[i] == key[i]) & (pcur->value.length() > i) & (key.length() > i)) i++;
		if (i == pcur->value.length()) 
		{
			key.erase(0, i);
			return FindTop(pcur->son, key);
		}
		else return NULL;
	}
}

template <class Data> Top<Data>* Tree<Data>::Find(string key)
{
	Top<Data>* p = FindTop(proot->son, key);
	if (p) cout << "key: " << key << endl << p->d << endl;
	return p;
}

template <class Data> void Tree<Data>::DeleteTop(Top<Data> *&pcur, string key, bool &ret)
{
	if (pcur == NULL) ret = false;
	else
	{
		if (pcur->value[0] < key[0]) 
		{
			DeleteTop(pcur->next, key, ret);
			return;
		}
		if (pcur->value[0] > key[0]) 
		{
			ret = false;
			return;
		}
		if (pcur->value[0] == key[0])
		{
			if (pcur->value == key)
			{
				if (pcur->son == NULL)
				{
					if (pcur->next == NULL)
					{
						delete pcur;
						pcur = NULL;
						ret = true;
						return;
					}
					Top<Data>* p = pcur->next;
					delete pcur;
					pcur = p;
					ret = true;
				}
				if (pcur->state) 
				{
					if (pcur->son->next)
					{
						pcur->state = false;
						pcur->d = 0;
						ret = true;
					}
					else
					{
						Top<Data>* p = pcur->son;
						p->next = pcur->next;
						p->value = pcur->value + p->value;
						delete pcur;
						pcur = p;
						ret = true;
					}
				}
				else ret = false;
			}
			else
			{			
				int i = 1;
				while ((pcur->value[i] == key[i]) & (pcur->value.length() > i) & (key.length() > i)) i++;
				if (i == pcur->value.length()) 
				{
					key.erase(0, i);
					DeleteTop(pcur->son, key, ret);
					if (ret)
					{
						if (!pcur->state)
						{
							if (pcur->son->next == NULL)
							{
								Top<Data> *p = pcur->son;
								p->next = pcur->next;
								p->value = pcur->value + p->value;
								delete pcur;
								pcur = p;
								return;
							}
							pcur->state = false;
							pcur->d = 0;
							return;
						}
					}
				}
				else ret = false;
			}
		}
	}
}

template <class Data> bool Tree<Data>::Delete(string key)
{
	bool ret = false;
	DeleteTop(proot->son, key, ret);
	return ret;
}

template <class Data> void Tree<Data>::PrintTop(Top<Data> *&pcur, string s)
{
	s+=pcur->value;
	if (pcur->state) 
	{
		cout << pcur->d << endl;
	}
	if ((pcur->son == NULL) & (pcur->next == NULL))
	{
		return;
	}
	if (pcur->son) 
	{
		PrintTop(pcur->son, s);
	}
	if (pcur->next) 
	{
		s.erase(s.length() - pcur->value.length());
		PrintTop(pcur->next, s);
	}
}

template <class Data> void Tree<Data>::Print(string s)
{
	cout << s << ":" << endl;
	if (proot->son)
	{
		PrintTop(proot->son, "");
		return;
	}
	cout << "Empty tree" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Tree<int>* tr = new Tree<int>();
	tr->Add(123, "abcdef");
	tr->Add(456, "abde");
	tr->Add(789, "aaaa");
	tr->Add(145, "a");
	tr->Add(464, "ab");
	tr->Print("Tree");
	cout << endl;
	tr->Add(444, "a");
	cout << endl;
	tr->Find("abde");
	cout << endl;
	tr->Delete("abde");
	tr->Print("After deleting record (key - abde)");
	getchar();
	return 0;
}