#pragma once

#include <list>

template<typename T>
class AbstractFactory
{
public:
	virtual T* create(T* obj) = 0;
	virtual bool remove(T* obj) = 0;
	virtual T* update(T* obj) = 0;
	virtual T* find(int index) = 0;
	virtual std::list<T*> findAll() = 0;
};

