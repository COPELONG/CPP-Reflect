#include <iostream>
#include<string>
#include"classfactory.h"
#include"singleton.h"
#include"A.h"
#include"B.h"
using namespace std;

int main() {
	Factory* factory = single<Factory>::instance();
	Object* a = factory->create_class("A");
	a->show();
	int age;
	a->set("m_age",18);
	a->get("m_age", age);
	a->call("f1");
	cout<<a->call2("f2",2);
	cout << age << endl;

	////第一种
	//typedf function<void(test*)> test_method;
	//test_method method = &Test::f1;
	//Test t;
	//method(&t);
	////第二种
	//typedf function<void(test*)> test_method;
	//test_method method = &Test::f1;
	//uintptr_t func = (uintptr_t) & method;
	//Test t;
	//(*(test_method*)func)(&t);
	return 0;
}