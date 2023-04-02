#pragma once
using namespace std;
template<class T>
class single {
public:
	static T* instance() {
		if (m_instance == NULL) {
			m_instance = new T();
		}
		return m_instance;
	}

private:
	single(){}
	~single(){}
	single<T> & operator =(const single<T>&){}
	single(const single<T>&) {}
private:
	static T* m_instance;
};
template<typename T> T* single<T>::m_instance = NULL;
