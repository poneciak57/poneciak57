#pragma once
#include <iostream>

template <typename T>
struct Node
{
	int index;

	T rekord;

	Node<T>* next;
	Node<T>* prev;

	Node() : next(NULL), prev(NULL) {};

};

