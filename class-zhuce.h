#pragma once
#include"classfactory.h"
#include"singleton.h"
#include<functional>
using namespace std;


class fuzhu {
public:
	fuzhu(const string& classname, creat_object method)
	{
		Factory* factory = single<Factory>::instance();
		factory->zhuce_class(classname, method);
		cout << "注册类成功" << endl;
	}
	fuzhu(const string& classname, const string& name, const string& type, size_t offset) {
		Factory* factory = single<Factory>::instance();
		factory->zhuce_field(classname, name, type, offset);
		cout << "注册数据成员成功" << endl;
	}
	fuzhu(const string& classname, const string& methodname, uintptr_t method) {
		Factory* factory = single<Factory>::instance();
		factory->zhuce_method(classname, methodname,method);
		cout << "注册成员函数成功" << endl;
	}
};
#define ZHUCE_CLASS(classname)         \
Object * create_class##classname()     \
{                                      \
Object* obj = new classname();         \
obj->set_name(#classname);                 \
return obj;                            \
}                                      \
fuzhu zhuce##classname(#classname,create_class##classname)

#define ZHUCE_CLASSFIELD(classname,fieldname,fieldtype)     \
classname classname##fieldname;                             \
fuzhu fuzhu##classname##fieldname(#classname,#fieldname,#fieldtype,(size_t)(&(classname##fieldname.fieldname))-(size_t)(&classname##fieldname))


#define ZHUCE_METHOD1(classname,methodname)   \
function<void(classname *)>classname##methodname##method =&classname::methodname;\
fuzhu classzhuce##classname##methodname(#classname,#methodname,(uintptr_t)&(classname##methodname##method))


#define ZHUCE_METHOD2(classname,methodname)   \
function<int(classname *,int)>classname##methodname##method =&classname::methodname;\
fuzhu classzhuce##classname##methodname(#classname,#methodname,(uintptr_t)&(classname##methodname##method))









