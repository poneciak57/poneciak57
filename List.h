#pragma once
#include "Node.h"

template <typename T>
class lista
{
private:
	// size //
	int _size;
	int maxIndex;

	// Nodes //
	Node<T>* _first;
	Node<T>* _last;

public:
	// Constructor&Destructor //
	lista();
	~lista() = default;

	// Operations //
	void push_back(T rekord);
	void drop(int index);
	void sort(bool asc, bool (*con)(T, T, bool) = [](T a,T b,bool asc){ return (asc)? a>b : a<b;});// true - rosnaco | false - malejaca

	// Support methods //
	void swap(Node<T>* a, Node<T>* b);
	void index_fix(Node<T>* p);

	// Getters //
	int size();
	Node<T>* first();
	Node<T>* last();

	// Operators // 
	T operator[](const int& index);
};

// Constructor&Destructor //
template <typename T> lista<T>::
lista()
{
	_size = 0;
	maxIndex = 0;
	_first = NULL;
	_last = NULL;
}

// Operations //
template <typename T> void lista<T>::
push_back(T rekord)
{
	Node<T>* temp = new Node<T>;
	if (_first == NULL)
	{
		_first = temp;
		_last = temp;
	}
	else
	{
		_last->next = temp;
		temp->prev = _last;
		_last = temp;
	}
	maxIndex++;
	_size++;
	temp->index = maxIndex;
	temp->rekord = rekord;
}
template <typename T> void lista<T>::
drop(int index)
{
	Node<T>* temp = _first;
	while (temp && temp->index != index)
	{
		temp = temp->next;
	}
	if (temp == NULL)
		throw "Index out of range";
	else
	{
		_size--;
		maxIndex--;
		if (temp == _first)
		{
			if (temp->next)
				temp->next->prev = NULL;
			_first = temp->next;
		}
		else if (temp == _last)
		{
			if (temp->prev)
				temp->prev->next = NULL;
			_last = temp->prev;
		}
		else
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		index_fix(temp);
		delete temp;
	}
}
template <typename T> void lista<T>::
sort(bool asc, bool (*con)(T, T, bool))// true - rosnaco | false - malejaca
{
	if (_first == NULL)
		throw "List is empty!";

	Node<T>* temp1 = _first;
	Node<T>* temp2;
	while (temp1->next)
	{
		temp2 = temp1;
		while (temp2 && con(temp2->rekord, temp2->next->rekord, asc))
		{
			swap(temp2, temp2->next);
			temp2 = temp2->prev;
		}
		temp1 = temp1->next;
	}
	//nie ma
}

// Support methods //
template <typename T> void lista<T>::
index_fix(Node<T>* p)
{
	while (p)
	{
		p->index--;
		p = p->next;
	}
}
template <typename T> void lista<T>::
swap(Node<T>* a, Node<T>* b)
{
	Node<T>* temp = new Node<T>;
	temp->rekord = a->rekord;
	a->rekord = b->rekord;
	b->rekord = temp->rekord;
	delete temp;
}

// Operators //
template <typename T> T lista<T>::
operator[](const int& index)
{
	if (index > maxIndex)
		throw "Index out of range!";
	else {
		Node<T>* temp = _first;
		while (temp->index != index)
			temp = temp->next;
		return temp->rekord;
	}
}

// Getters //
template <typename T> int lista<T>::size() { return _size; }
template <typename T> Node<T>* lista<T>::first() { return _first; }
template <typename T> Node<T>* lista<T>::last() { return _last; }
