#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<Windows.h>
#include<fstream>
#include<Windows.h>
#include<map>
class Person{
public:
	string m_name;
	int m_sorce;
	int m_number;
	Person(string name, int number);
};

class sys{
public:
	void showmeun();
	void choosemeun(vector<Person> &v);
};

class Myprint {
public:
	void operator()(Person &p);
};

class Mysort {
public:
	bool operator()(Person& p1, Person& p2);
};

class filemanager {
public:
	bool file_Isempty;
	void loadfile();
	void showfile();
	void clear();
	map <int, vector<string>> m_record;
};
void start(vector<Person>& v);

void loading();

void savefile(vector<Person>& v);

