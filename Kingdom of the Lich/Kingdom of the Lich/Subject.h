#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Subject
{
private:
	std::vector<Observer*> observers;
public:
	//destructor. set subject to 0
	virtual ~Subject();

	//add a new observer to this subject. param is a pointer to an observer
	virtual void addObserver(Observer* observer);

	//update all observers for this subject
	virtual void Notify();
};

#endif
