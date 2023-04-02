#pragma once
using namespace std;
#include<string>
#include<map>
#include<vector>
#include"singleton.h"
#include "classfield.h"
#include "class-method.h"
//using creat_object = Object* (*)(void);
//typedef Object* (*creat_object)(void);

class Object {
public:
	Object() {};
	virtual ~Object() {};
	virtual void show() = 0;
	const string & get_name() const {
		return m_classname;
	}
	void set_name(const string& name) {
		m_classname = name;
	}
	void call(const string& methodname);
	int call2(const string& methodname,int num);
	int get_field_count();
	classfield* get_field(int pos);
	classfield* get_field(const string& fieldname);
	template<typename T>
	void get(const string& fieldname,T& value);
	template<typename T>
	void set(const string& fieldname, const T& value);

private:
	string m_classname;
};
using creat_object = Object * (*)(void);
class Factory {
public:
	friend class single<Factory>;
	//解析数据类
	void zhuce_class(const string& classname, creat_object method);//注册类
	Object* create_class(const string& classname);//创建类
	//解析数据成员
	void zhuce_field(const string& classname,const string&fieldname,const string&fieldtype,size_t fieldoffset);
	auto get_field_count(const string& classname);
	classfield* get_field(const string& classname, int pos);
	classfield* get_field(const string& classname, const string& fieldname);
	//解析成员函数
	void zhuce_method(const string&classname,const string&methodname,uintptr_t method);
	auto get_method_count(const string& classname);
	classmethod* get_method(const string& classname,int pos);
	classmethod* get_method(const string& classname,const string methodname);


private:
	Factory(){}
	~Factory(){}
private:
	map<string, creat_object> m_classmap;
	map<string, vector<classfield*>> m_classfields;
	map<string, vector<classmethod*>> m_classmethods;
};

template<typename T>
inline void Object::get(const string& fieldname, T& value)
{
	Factory* factory = single<Factory>::instance();
	classfield * field =factory->get_field(m_classname, fieldname);
	size_t offset = field->offset();
	unsigned char* ptr = reinterpret_cast<unsigned char*>(this);
	value = *(reinterpret_cast<T *>(ptr + offset));
}

template<typename T>
inline void Object::set(const string& fieldname, const T& value)
{
	Factory* factory = single<Factory>::instance();
	classfield* field = factory->get_field(m_classname, fieldname);
	size_t offset = field->offset();
	unsigned char* ptr = reinterpret_cast<unsigned char*>(this);
	*(reinterpret_cast<T*>(ptr + offset)) = value;
}
