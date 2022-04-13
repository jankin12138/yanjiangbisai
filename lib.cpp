using namespace std;
#include "lib.h"

Person::Person(string name, int number){
	this->m_name = name;
	this->m_number = number;
	this->m_sorce = 0;
}


void Myprint::operator()(Person &p) {
	cout << "ѡ�ֱ��: " << p.m_number << "\tѡ������: " << p.m_name << "\tѡ�ֳɼ�: " << p.m_sorce << endl;
}

bool Mysort::operator()(Person& p1, Person& p2) {
	return p1.m_sorce > p2.m_sorce;
}
void sys::showmeun(){
	system("cls");
	cout << "********************************" << endl;
	cout << "******* ��ӭ�μ��ݽ����� *******" << endl;
	cout << "******** 1.��ʼ�ݽ����� ********" << endl;
	cout << "******** 2.�鿴�����¼ ********" << endl;
	cout << "******** 3.��ձ�����¼ ********" << endl;
	cout << "******** 0.�˳��������� ********" << endl;
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
		cout << "���������" << endl;
	}
}

void start(vector<Person>& v) {
	int sorce = 0;
	string n = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++) {
		string name="ѡ��";
		name = name + n[i];
		int number = 10001 + i;
		v.push_back(Person(name, number));
	}
	random_shuffle(v.begin(), v.end());
	vector<Person>::iterator it=v.begin();
	vector<Person> v1;//��һ��
	vector<Person> v2;//�ڶ���
	vector<Person> v3;//������
	vector<Person> v4;//ʤ����
	for (int i = 0; i < v.size(); i++) {
		if (i < v.size() / 2) {
			v1.push_back(*it);
		}
		else {
			v2.push_back(*it);
		}
		it++;
	}

	cout << "�ȴ�������ʼ" << endl;
	loading();
	//С����
	for (vector<Person>::iterator it1 = v1.begin(); it1 < v1.end();it1++) {
		it1->m_sorce = 60 + rand() % 40;
	}
	for (vector<Person>::iterator it2 = v2.begin(); it2 != v2.end(); it2++) {
		sorce = 60 + rand() % 40;
		it2->m_sorce = sorce;
	}
	sort(v1.begin(), v1.end(), Mysort());
	sort(v2.begin(), v2.end(), Mysort());
	//cout << "��һС���Ա:" << endl;
	//for_each(v1.begin(), v1.end(), Myprint());
	//cout << "�ڶ�С���Ա:" << endl;
	//for_each(v2.begin(), v2.end(), Myprint());
	it = v1.begin();
	for (int i = 0; i < v1.size() / 2; i++) { //�����������
		v3.push_back(*it);
		it++;
	}
	it = v2.begin();
	for (int i = 0; i < v1.size() / 2; i++) {
		v3.push_back(*it);
		it++;
	}
	cout << "��������" << endl;
	for_each(v3.begin(), v3.end(), Myprint());
	system("pause");
	cout << "�ȴ�������ʼ" << endl;
	loading();
	for (vector<Person>::iterator it1 = v3.begin(); it1 < v3.end(); it1++) {
		it1->m_sorce = 60 + rand() % 40;
	}
	//for_each(v3.begin(), v3.end(), Myprint());
	sort(v3.begin(), v3.end(), Mysort());
	it = v3.begin();
	for (int i = 0; i < v3.size() / 2; i++) { //�����������
		v4.push_back(*it);
		it++;
	}
	cout << "ʤ������" << endl;
	for_each(v4.begin(), v4.end(), Myprint());
	savefile(v4);
	system("pause");
}

void loading()
{
	system("cls");
	cout << "������." << endl;
	Sleep(1000);
	system("cls");
	cout << "������.." << endl;
	Sleep(1000);
	system("cls");
	cout << "������..." << endl;
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
	cout << "�������" << endl;
}

void filemanager::loadfile() {
	ifstream ifs("speach.csv",ios::in);
	if (!ifs.is_open())
	{
		this->file_Isempty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->file_Isempty = true;
		cout << "�ļ�Ϊ��" << endl;
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
		cout << "��" << i+1 << "�����" << "�ھ����:" << m_record[i][0] << "�ھ�����:" << m_record[i][1] << "�ھ�����:" << m_record[i][2]
			<< "�Ǿ����:" << m_record[i][3] << "�Ǿ�����:" << m_record[i][4] << "�Ǿ�����:" << m_record[i][5]
			<< "�������:" << m_record[i][6] << "��������:" << m_record[i][7] << "��������:" << m_record[i][8] << endl;
	}
	system("pause");
}

void filemanager::clear() {
	ofstream ofs;
	ofs.open("speach.csv", ios::trunc);
	ofs.close();
	cout << "ɾ���ļ��ɹ���" << endl;
}