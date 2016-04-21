#ifndef OBSERVER_H
#define OBSERVER_H

//forward reference
class Subject;

class Observer
{
private:
	Subject* subject;
public:
	//destructor
	virtual ~Observer();

	//pure virtual update method
	virtual void Update() = 0;

	//set this observers subject. param is a subject pointer
	void SetSubject(Subject* sub);
};

#include "Subject.h"

#endif
