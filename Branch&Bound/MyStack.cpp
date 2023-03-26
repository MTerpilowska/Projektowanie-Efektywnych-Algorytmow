#include "MyStack.h"

string MyStack::toString()
{
	string mystack = "";
	int *tempB = base;

	if(!size)
	{
		mystack = "Stos jest pusty";
	}
	else
	{
		for(int i=0;i<size;i++)
		{
			mystack += to_string(*tempB) + " ";
			tempB++;
		}
	}

	return mystack;
}

void MyStack::push(int element)
{
	if(!size)
	{
		size++;
		base = new int[1];
		*base = element;
	}
	else
	{
		size++;
		int *temp = new int[size];
		int *tempB = base;
		int *temporary = temp;

		for (int i = 0; i < size - 1; i++)
		{
			*temporary = *tempB;
			temporary++;
			tempB++;
		}

		*temporary = element;
		delete[] base;
		base = temp;
	}
}

int MyStack::pop()
{
	int peak;

	if(size > 1)
	{
		size--;
		peak = *(base + size);

		int *temp= new int[size];
		int *tempB=base;
		int *temporary = temp;

		for (int i = 0; i < size; i++)
		{
			*temporary = *tempB;
			tempB++;
			temporary++;
		}

		delete[] base;
		base = temp;

		return peak;
	}
	else if(size == 1)
	{
		peak = *base;
		size = 0;

		delete[] base;
		base = nullptr;

		return peak;
	}
	else
	{
		return -1;
	}
}

void MyStack::cclear()
{
	delete[] base;
	base = nullptr;
	size = 0;
}

void MyStack::ccopy(MyStack *dest)
{
	int *tempB = base;
	dest->cclear();

	if(size)
	{
		for(int i=0;i<size;i++)
		{
			dest->push(*tempB);
			tempB++;
		}
	}
}

int MyStack::getSize()
{
	return size;
}

MyStack::MyStack()
{

}

MyStack::~MyStack()
{
	if(base != nullptr)
	{
		delete[] base;
	}
}
