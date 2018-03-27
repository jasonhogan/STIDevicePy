#include <boost/python.hpp>
#include "SynchronousEventAdapterPub.h"



void SynchronousEventAdapterPub::setupEvent()
{
//	std::cout << "(3) setupEvent" << std::endl;
	setupEvent_py();
	//	return writeChannel_py(channel, obj);
	//	return writeChannel_py(channel, value.getDouble());
}

void SynchronousEventAdapterPub::setupEvent_py()
{
//	std::cout << "(4) setupEvent_py" << std::endl;

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
	std::unique_lock<std::mutex> lock(mtx);
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
