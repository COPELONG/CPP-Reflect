#pragma once
#include<string>
using namespace std;



class classmethod {
public:
	  
	classmethod():m_name(""),m_method(0){}
	classmethod(const string& name,uintptr_t method):
		m_name(name),m_method(method){}
	~classmethod(){}

	const string& name() {
		return m_name;
	}
	uintptr_t method() {
		return m_method;
	}
private:
	string m_name;
	uintptr_t m_method;
};
