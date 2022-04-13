#include <iostream>
using namespace std;
#include"lib.h"

int main(){
	sys s;
	vector<Person> v;
	while (1) {
		srand((unsigned int)time(NULL));
		s.showmeun();
		s.choosemeun(v);
	}
	system("pause");
}