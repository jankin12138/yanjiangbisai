using namespace std;
#include "lib.h"

Person::Person(string name, int number){
	this->m_name = name;
	this->m_number = number;
	this->m_sorce = 0;
}


void Myprint::operator()(Person &p) {
	cout << "选手编号: " << p.m_number << "\t选手姓名: " << p.m_name << "\t选手成绩: " << p.m_sorce << endl;
}

bool Mysort::operator()(Person& p1, Person& p2) {
	return p1.m_sorce > p2.m_sorce;
}
void sys::showmeun(){
	system("cls");
	cout << "********************************" << endl;
	cout << "******* 欢迎参加演讲比赛 *******" << endl;
	cout << "******** 1.开始演讲比赛 ********" << endl;
	cout << "******** 2.查看往届记录 ********" << endl;
	cout << "******** 3.清空比赛记录 ********" << endl;
	cout << "******** 0.退出比赛程序 ********" << endl;
	cout << "********************************" << endl;

}

void sys::choosemeun(vector<Person> &v) {
	filemanager f;
	int a;
	cin >> a;
	switch (a){
	case 0:
		exit(0);
		break;
	case 1:
		start(v);
		break;
	case 2:
		f.loadfile();
		f.showfile();
		break;
	case 3:
		f.clear();
		break;
	default:
		cout << "求你别乱输" << endl;
	}
}

void start(vector<Person>& v) {
	int sorce = 0;
	string n = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++) {
		string name="选手";
		name = name + n[i];
		int number = 10001 + i;
		v.push_back(Person(name, number));
	}
	random_shuffle(v.begin(), v.end());
	vector<Person>::iterator it=v.begin();
	vector<Person> v1;//第一组
	vector<Person> v2;//第二组
	vector<Person> v3;//决赛组
	vector<Person> v4;//胜出组
	for (int i = 0; i < v.size(); i++) {
		if (i < v.size() / 2) {
			v1.push_back(*it);
		}
		else {
			v2.push_back(*it);
		}
		it++;
	}

	cout << "等待比赛开始" << endl;
	loading();
	//小组赛
	for (vector<Person>::iterator it1 = v1.begin(); it1 < v1.end();it1++) {
		it1->m_sorce = 60 + rand() % 40;
	}
	for (vector<Person>::iterator it2 = v2.begin(); it2 != v2.end(); it2++) {
		sorce = 60 + rand() % 40;
		it2->m_sorce = sorce;
	}
	sort(v1.begin(), v1.end(), Mysort());
	sort(v2.begin(), v2.end(), Mysort());
	//cout << "第一小组成员:" << endl;
	//for_each(v1.begin(), v1.end(), Myprint());
	//cout << "第二小组成员:" << endl;
	//for_each(v2.begin(), v2.end(), Myprint());
	it = v1.begin();
	for (int i = 0; i < v1.size() / 2; i++) { //存入决赛容器
		v3.push_back(*it);
		it++;
	}
	it = v2.begin();
	for (int i = 0; i < v1.size() / 2; i++) {
		v3.push_back(*it);
		it++;
	}
	cout << "晋级名单" << endl;
	for_each(v3.begin(), v3.end(), Myprint());
	system("pause");
	cout << "等待决赛开始" << endl;
	loading();
	for (vector<Person>::iterator it1 = v3.begin(); it1 < v3.end(); it1++) {
		it1->m_sorce = 60 + rand() % 40;
	}
	//for_each(v3.begin(), v3.end(), Myprint());
	sort(v3.begin(), v3.end(), Mysort());
	it = v3.begin();
	for (int i = 0; i < v3.size() / 2; i++) { //存入决赛容器
		v4.push_back(*it);
		it++;
	}
	cout << "胜出名单" << endl;
	for_each(v4.begin(), v4.end(), Myprint());
	savefile(v4);
	system("pause");
}

void loading()
{
	system("cls");
	cout << "进行中." << endl;
	Sleep(1000);
	system("cls");
	cout << "进行中.." << endl;
	Sleep(1000);
	system("cls");
	cout << "进行中..." << endl;
	Sleep(1000);
	system("cls");
}

void savefile(vector<Person>& v) {
	ofstream ofs;
	ofs.open("speach.csv", ios::out | ios::app);
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		ofs << it->m_number << "," << it->m_name << "," << it->m_sorce << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "保存完毕" << endl;
}

void filemanager::loadfile() {
	ifstream ifs("speach.csv",ios::in);
	if (!ifs.is_open())
	{
		this->file_Isempty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->file_Isempty = true;
		cout << "文件为空" << endl;
		ifs.close();
		return;
	}

	this->file_Isempty = false;
	ifs.putback(ch);
	int index = 0;
	
	string data;
	while(ifs>>data){
		vector<string> v;
		int pos = -1;
		int start = 0;
	
		while (1) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		//cout << index << endl;
		//this->m_record.insert(pair<int,vector<string>>(0,v));
		this->m_record.insert(pair<int, vector<string>>(index, v));
		index++;
	}
}

void filemanager::showfile() {
	for (int i = 0; i < m_record.size(); i++) {
		cout << "第" << i+1 << "届比赛" << "冠军编号:" << m_record[i][0] << "冠军名字:" << m_record[i][1] << "冠军分数:" << m_record[i][2]
			<< "亚军编号:" << m_record[i][3] << "亚军名字:" << m_record[i][4] << "亚军分数:" << m_record[i][5]
			<< "季军编号:" << m_record[i][6] << "季军名字:" << m_record[i][7] << "季军分数:" << m_record[i][8] << endl;
	}
	system("pause");
}

void filemanager::clear() {
	ofstream ofs;
	ofs.open("speach.csv", ios::trunc);
	ofs.close();
	cout << "删除文件成功！" << endl;
}