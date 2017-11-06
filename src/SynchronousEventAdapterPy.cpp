
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
	if (boost::python::override setupEvent_py2 = static_cast<SynchronousEventAdapterPy*>(this)->get_override("setupEvent"))
	{
		std::cout << "(1) SynchronousEventAdapterPy HERE !!*!*!" << std::endl;
		setupEvent_py2(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	std::cout << "(2) SynchronousEventAdapterPy setupEvent_py failed to find override" << std::endl;
	SynchronousEventAdapterPub::setupEvent_py();
}

void SynchronousEventAdapterPy::default_setupEvent_py()
{
	this->SynchronousEventAdapterPub::setupEvent();
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

