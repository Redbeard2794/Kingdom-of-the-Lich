#include "stdafx.h"
#include "Observer.h"

//destructor
Observer::~Observer()
{
}

//set this observers subject. param is a subject pointer
void Observer::SetSubject(Subject* sub)
{
	subject = sub;
}
