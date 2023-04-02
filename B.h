#pragma once
using namespace std;
#include "class-zhuce.h"
#include <iostream>
#include <string>
class B:public Object {

public:
	B() {}
	~B() {}
	void show() {
		cout << "m_name :B" << endl;
	}
private:
	string m_name;
};
ZHUCE_CLASS(B);

