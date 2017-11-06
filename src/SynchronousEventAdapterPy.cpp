
#include <boost/python.hpp>
#include "SynchronousEventAdapterPy.h"


void SynchronousEventAdapterPub::setupEvent()
{
	std::cout << "(3) setupEvent" << std::endl;
	setupEvent_py();
//	return writeChannel_py(channel, obj);
	//	return writeChannel_py(channel, value.getDouble());
}

void SynchronousEventAdapterPub::setupEvent_py()
{
	std::cout << "(4) setupEvent_py" << std::endl;
	return;
}



void SynchronousEventAdapterPy::setupEvent_py()
{
	//STI library calls this if there is a python override
	if (boost::python::override setupEvent_py = this->get_override("setupEvent"))
	{
		std::cout << "(1) SynchronousEventAdapterPy HERE !!*!*!" << std::endl;
		setupEvent_py(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	SynchronousEventAdapterPub::setupEvent_py();
}

void SynchronousEventAdapterPy::default_setupEvent_py()
{
	this->SynchronousEventAdapterPub::setupEvent();
}
