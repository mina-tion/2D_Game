#include "stdafx.h"
#include "Mission.h"

Mission::Mission()
{
	this->activity = false;
	this->completeness = false;
	this->step = 0;
}

Mission::~Mission()
{
}

const bool Mission::isActive()
{
	if (this->activity)
		return true;

	return false;
}

const bool Mission::isComplited()
{
	if (this->completeness)
		return true;

	return false;
}

const int Mission::getStep()
{
	return this->step;
}

void Mission::comleteMission()
{
	this->completeness = true;
	this->step = 0;
}


void Mission::setStep(int step)
{
	this->step = step;
}

void Mission::activateMission()
{
	this->activity = true;
	this->step = 1;
}

void Mission::deactivateMission()
{
	this->activity = false;
	this->step = 0;
}
