#include "stdafx.h"
#include "Subject.h"

//destructor. set subject to 0
Subject::~Subject()
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers.at(i)->SetSubject(0);
	}
}

//add a new observer to this subject. param is a pointer to an observer
void Subject::addObserver(Observer * observer)
{
	observers.push_back(observer);
}

//update all observers for this subject
void Subject::Notify()
{
	for (int i = 0; i < observers.size(); i++)
	{
		observers.at(i)->Update();
	}
}
