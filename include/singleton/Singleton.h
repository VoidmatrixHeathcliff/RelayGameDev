///
/// The helper class for singleton pattern in paper library
///

#pragma once
#include <type_traits>


//tool class for singletons
template<class Type>
class Singleton {
private:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

public:
	//唯一的单例调用方式
	static Type& instance() {
		static Type _instance;
		return _instance;
	}
};


//returns the only instance
template<class Type>
Type& PGetSingleton() {
	static Type instance;
	return instance;
}

//returns the only instance
template<class Type> requires std::is_base_of_v<Singleton<Type>, Type>
Type& PGetSingleton() {
	return Singleton<Type>::instance();
}


//#define _SINGLETON_USAGE

#ifdef _SINGLETON_USAGE

class NormalClass {
public:
	int idx = 0;
};

class SingletonClass :public Singleton<SingletonClass> {
	friend class SingletonClass;
public:
	std::string str = "111";
};

static void someFunction() {
	auto& normal = PGetSingleton<NormalClass>();			//ok
	auto& singleton = PGetSingleton<SingletonClass>();		//ok
	auto& singleton1 = SingletonClass::instance();			//ok
	std::cout << std::boolalpha << ((&singleton1) == (&singleton)) << std::endl;	//same instance
}

#undef _SINGLETON_USAGE
#endif