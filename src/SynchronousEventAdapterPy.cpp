
#include <boost/python.hpp>
#include "SynchronousEventAdapterPy.h"


void SynchronousEventAdapterPy::setupEvent_py()
{
	//STI library calls this if there is a python override
	if (boost::python::override setupEvent_py2 = static_cast<SynchronousEventAdapterPy*>(this)->get_override("setupEvent"))
	{
		setupEvent_py2(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	SynchronousEventAdapterPub::setupEvent_py();
}

void SynchronousEventAdapterPy::default_setupEvent_py()
{
	this->SynchronousEventAdapterPub::setupEvent();
}

void SynchronousEventAdapterPy::loadEvent_py()
{
	//STI library calls this if there is a python override
	if (boost::python::override loadEvent_py2 = static_cast<SynchronousEventAdapterPy*>(this)->get_override("loadEvent"))
	{
		loadEvent_py2(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	SynchronousEventAdapterPub::loadEvent_py();
}

void SynchronousEventAdapterPy::default_loadEvent_py()
{
	this->SynchronousEventAdapterPub::loadEvent();
}

void SynchronousEventAdapterPy::playEvent_py()
{
	//STI library calls this if there is a python override
	if (boost::python::override playEvent_py2 = static_cast<SynchronousEventAdapterPy*>(this)->get_override("playEvent"))
	{
		playEvent_py2(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	SynchronousEventAdapterPub::playEvent_py();
}

void SynchronousEventAdapterPy::default_playEvent_py()
{
	this->SynchronousEventAdapterPub::playEvent();
}

void SynchronousEventAdapterPy::collectMeasurementData_py()
{
	//STI library calls this if there is a python override
	if (boost::python::override collectMeasurementData_py2 = static_cast<SynchronousEventAdapterPy*>(this)->get_override("collectMeasurementData"))
	{
		collectMeasurementData_py2(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	SynchronousEventAdapterPub::collectMeasurementData_py();
}

void SynchronousEventAdapterPy::default_collectMeasurementData_py()
{
	this->SynchronousEventAdapterPub::collectMeasurementData();
}

void SynchronousEventAdapterPy::no_op(SynchronousEventAdapterPy*)
{
	std::cout << "no_op delete" << std::endl;
}

//factory function that makes shared_ptrs with custom deleter (no_op)
boost::shared_ptr<SynchronousEventAdapterPy> SynchronousEventAdapterPy::create_event(double time, STI_Device_Adapter_Wrapper* device)
{
	return boost::shared_ptr<SynchronousEventAdapterPy>(
		new SynchronousEventAdapterPy(time, device),
		&no_op);
}

