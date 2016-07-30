#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <algorithm>
#include <type_traits>
#include <stdlib.h>
#include <string.h>

/**
 * ArrayList class
 *
 * This class implements an ArrayList in a fashion
 * that is similar to that of Java, but also adds
 * a lot of useful C++ features.
 */
template<class T>
class ArrayList
{
public:
	ArrayList();

	int indexOf(const T& other);
	int indexOf(const T& object, int occurrence);
	int lastIndexOf(const T& other);
	const int & size(){ return m_size; }
	const T & get(int index){ return pElements[index]; }
	const T remove(int index);
	void remove(const T & toRemove, bool * ok);
	inline T & operator [](int index){ return pElements[index]; }

	void print();

	void add(const T& toPush);
	void add(const T& toPush, int index);
	void push_back(const T& toPush);
	void push_front(const T& toPush);

	void clear();

	bool isEmpty(){ return m_size == 0; }
	bool contains(const T& object);

	void sort();
	ArrayList<T> & operator = (const ArrayList<T> & other)
	{
		for(int i = 0; i < this->m_size; i++)
		{
			other[i] = this->pElements[i];
		}
		return *this;
	}
	bool operator == (ArrayList<T> & other)
	{
		bool res = true;
		for(int i = 0; i < this->m_size; i++)
		{
			if( other[i] != this->pElements[i])
				res = false;
		}
		return res;
	}
	ArrayList<T> & operator << (const T & toAdd) {
		this->add(toAdd);
		return *this;
	}
	ArrayList<T> & operator << (ArrayList<T> & other) 
	{
		for(int i = 0; i < other.m_size; i++)
		{
			this->add(other.pElements[i]);
		}
		return *this;
	}
	ArrayList<T> & operator += (const T & toAdd)
	{
		this->add(toAdd);
		return *this;
	}
	ArrayList<T> & operator += (ArrayList<T> & other) {
		for(int i = 0; i < other.m_size; i++)
		{
			this->add(other.pElements[i]);
		}
		return *this;
	}

private:
	T * pElements;
	int m_size;
	int m_capacity;
	const static int SIZE_INCREMENT = 2;
};
#endif