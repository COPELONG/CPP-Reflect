#pragma once
#include<string>
using namespace std;

class classfield {
public:
	classfield() :m_name(""),m_type(""),m_offset(0) {}
	~classfield(){}
	classfield(const string& name, const string& type, size_t offset):
		m_name(name), m_type(type), m_offset(offset){}
	const string& name() {
		return m_name;
	}
	const string& type() {
		return m_type;
	}
	size_t offset() {
		size_t a = m_offset;
		return m_offset;
	}
private:
	string m_name;
	string m_type;
	size_t m_offset;

};