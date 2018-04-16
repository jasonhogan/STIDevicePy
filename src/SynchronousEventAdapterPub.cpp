#include <boost/python.hpp>
#include "SynchronousEventAdapterPub.h"



void SynchronousEventAdapterPub::setupEvent()
{
	setupEvent_py();
}

void SynchronousEventAdapterPub::setupEvent_py()
{
	return;
}


void SynchronousEventAdapterPub::loadEvent()
{
	loadEvent_py();
}

void SynchronousEventAdapterPub::loadEvent_py()
{
	return;
}

void SynchronousEventAdapterPub::playEvent()
{
	std::unique_lock<std::mutex> lock(mtx);	//this did not fix the thread access bug; repeating play rapidly causes a crash.
	playEvent_py();
}

void SynchronousEventAdapterPub::playEvent_py()
{
	return;
}

void SynchronousEventAdapterPub::collectMeasurementData()
{
	collectMeasurementData_py();
}

void SynchronousEventAdapterPub::collectMeasurementData_py()
{
	return;
}
