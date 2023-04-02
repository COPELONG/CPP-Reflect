#pragma once
using namespace std;
#include "class-zhuce.h"
#include <iostream>
#include <string>


class A:public Object {

public:
	A(){}
	~A(){}
	void show() {
		cout << "m_name :A" << endl;
	}
	void f1() {
		cout << "f1" << endl;
	}
	int f2(int num) {
		
		return num;
	}
public:
	string m_name;
	int m_age;
};

ZHUCE_CLASS(A);
ZHUCE_CLASSFIELD(A, m_name, string);
ZHUCE_CLASSFIELD(A, m_age, int);
ZHUCE_METHOD1(A, f1);
ZHUCE_METHOD2(A, f2);