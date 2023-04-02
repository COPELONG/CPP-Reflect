# C++-Reflect

## 功能：

1.解析数据类：

根据传入的字符串名称，自动创建类对象。并且可以调用类中的任何成员函数。

```c++
	Object* a = factory->create_class("A");
	a->show();
```

2.解析类数据成员：

根据传入的字符串名称，可以获取和设置类中指定数据成员的值。

```c++
	int age;
	a->set("m_age",18);
	a->get("m_age", age);
```

3.解析类成员函数：

根据传入的函数字符串名称，可以调用其类中指定的成员函数。

```c++
	a->call("f1");
	cout<<a->call2("f2",2);
```

## 模块设计：

### 1.设计单例：

在程序运行的过程中，确保只有一个指定对象。只能通过单例创建对象，指定的类中的构造函数被设置为private。

```c++
核心代码：static T* instance() {
		if (m_instance == NULL) {
			m_instance = new T();
		}
		return m_instance;
	}
static T* m_instance;
template<typename T> T* single<T>::m_instance = NULL;//类外初始化静态成员
friend class single<Factory>;//设置类友元，可以使用Factoty中的私有构造函数创建对象。
```

### 2.设计工厂类：

类中包含了功能实现所需的各种函数，通过直接或间接拿取工厂类中的函数来实现功能。

```c++
using creat_object = Object * (*)(void);//设计一个函数指针，类型为一个类指针且参数为空。
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
	map<string, creat_object> m_classmap;//存储类的名字和函数指针
	map<string, vector<classfield*>> m_classfields;//存储类的名字和一个数组，存放的是类字段指针
	map<string, vector<classmethod*>> m_classmethods;//存储类的名字和一个数组，存放的是类方法指针
};
```

### 2.宏定义：

在测试类中写入宏，为了注册：通过调用宏定义，向上述的map集合中存入数据。

```c++
ZHUCE_CLASS(A);//注册类，将类的名称和方法存入m_classmap中
ZHUCE_CLASSFIELD(A, m_name, string);//注册数据成员，将类的名称、字段的名字、字段的类型存入m_classfields中
ZHUCE_CLASSFIELD(A, m_age, int);
ZHUCE_METHOD1(A, f1);
ZHUCE_METHOD2(A, f2);//注册成员函数，将类的名称和成员函数(有参和无参)存入m_classmethods中
//--------------注意-----------------
```

实现宏定义：

```c++
#define ZHUCE_CLASS(classname)         \       //类注册宏
Object * create_class##classname()     \
{                                      \
Object* obj = new classname();         \
obj->set_name(#classname);             \
return obj;                            \
}                                      \
fuzhu zhuce##classname(#classname,create_class##classname)
//注意格式问题
//##代表链接字符串，#代表解析：例如A->"A",int->"int"。
```

```c++
#define ZHUCE_CLASSFIELD(classname,fieldname,fieldtype)     \
classname classname##fieldname;                             \
fuzhu fuzhu##classname##fieldname(#classname,#fieldname,#fieldtype,

(size_t)(&(classname##fieldname.fieldname))-(size_t)(&classname##fieldname))
//类成员数据成员注册
//                      -----------重点-----------------
//(size_t)(&(classname##fieldname.fieldname))-(size_t)(&classname##fieldname))
//目的：获取类中数据成员的偏移量offset，根据偏移量，可以计算数据成员的真实值。
//size_t &（A.m_name）-size_t & (A)
```

例：

```c++
a->set("m_age",18);

template<typename T>
inline void Object::set(const string& fieldname, const T& value)
{
	Factory* factory = single<Factory>::instance();
	classfield* field = factory->get_field(m_classname, fieldname);
	size_t offset = field->offset();
	unsigned char* ptr = reinterpret_cast<unsigned char*>(this);
	*(reinterpret_cast<T*>(ptr + offset)) = value;//类的指针+偏移值：指针指向了数据成员，解引用即可操作。
}
// reinterpret_cast<unsigned char*>底层转换使用unsigned char*，操作指针更安全，字节级别。
```

### 3.设计类-注册类

3.1设计字段类，每个字段看作一个类，并且存储每个类的偏移值。

3.2设计注册类：类中包含类的名称和构造函数方法。

3.3设计成员函数类：类中包含函数的名字和指针。
