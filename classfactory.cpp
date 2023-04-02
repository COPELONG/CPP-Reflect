#include"classfactory.h"
#include<functional>
using namespace std;

void Factory::zhuce_class(const string& classname, creat_object method)
{
	m_classmap[classname] = method;
}

Object* Factory::create_class(const string& classname)
{
	auto it = m_classmap.find(classname);
	if (it == m_classmap.end()) {
		return nullptr;
	}
	return it->second();
}

void Factory::zhuce_field(const string& classname, const string& fieldname, const string& fieldtype, size_t fieldoffset)
{
	m_classfields[classname].push_back(new classfield(fieldname, fieldtype, fieldoffset));
}

auto Factory::get_field_count(const string& classname)
{
	return m_classfields[classname].size();
}

classfield* Factory::get_field(const string& classname, int pos)
{
	int size = m_classfields[classname].size();
	if (size < pos) {
             return nullptr;
	}
	return m_classfields[classname][pos];
}

classfield* Factory::get_field(const string& classname, const string& fieldname)
{
	auto it1 = m_classfields[classname].begin();
	auto it2 = m_classfields[classname].end();
	for (it1; it1 != it2; it1++) {
		const string& NAME = (*it1)->name();
		if (NAME == fieldname) {
			return *it1;
		}
	}
	return nullptr;
}

void Factory::zhuce_method(const string& classname, const string& methodname, uintptr_t method)
{
	m_classmethods[classname].push_back(new classmethod(methodname, method));
}

auto Factory::get_method_count(const string& classname)
{
	return m_classmethods[classname].size();
}

classmethod* Factory::get_method(const string& classname, int pos)
{
	auto size = m_classmethods[classname].size();
	if (pos > size) {
		return nullptr;
	}
	return m_classmethods[classname][pos];
}

classmethod* Factory::get_method(const string& classname, const string methodname)
{
	auto method = m_classmethods[classname];
	for (auto it = method.begin(); it != method.end(); it++) {
		if ((*it)->name() == methodname) {
			return *it;
		}
	}
	return nullptr;
}

void Object::call(const string& methodname)
{
	Factory* factory = single<Factory>::instance();
	classmethod* method=factory->get_method(m_classname,methodname);
	auto func = method->method();
	typedef std::function<void(decltype(this))>  class_method;
	(*((class_method*)func))(this);
}

int Object::call2(const string& methodname,int num)
{
	Factory* factory = single<Factory>::instance();
	classmethod* method = factory->get_method(m_classname, methodname);
	auto func = method->method();
	typedef std::function<int(decltype(this),int)>  class_method;
	return (*((class_method*)func))(this,num);
	
}

int Object::get_field_count()
{
	Factory* factory = single<Factory>::instance();
	return factory->get_field_count(m_classname);
}

classfield* Object::get_field(int pos)
{
	Factory* factory = single<Factory>::instance();
	return factory->get_field(m_classname, pos);;
}

classfield* Object::get_field(const string& fieldname)
{
	Factory* factory = single<Factory>::instance();
	factory->get_field(m_classname, fieldname);
	return nullptr;
}
