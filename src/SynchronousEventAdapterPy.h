#ifndef SYNCHRONOUSEVENTADAPTERPY_H
#define SYNCHRONOUSEVENTADAPTERPY_H

#include "STI_Device_Adapter_Wrapper.h"
#include <STI_Device_Adapter.h>
#include <STI_Device.h>


//class SynchronousEventPyWrapper : public STI_Device::SynchronousEvent
//{
//public:
//	SynchronousEventPyWrapper(const boost::shared_ptr<SynchronousEventAdapterPy>& evt);
//};

class SynchronousEventAdapterPub : public STI_Device::SynchronousEventAdapter
{
public:
	SynchronousEventAdapterPub(double time, STI_Device* device) : 
		STI_Device::SynchronousEventAdapter(time, device) {}
	virtual  ~SynchronousEventAdapterPub() {}

	void setupEvent();
	virtual void setupEvent_py();
};


class SynchronousEventAdapterPy : public SynchronousEventAdapterPub,
	public boost::python::wrapper<SynchronousEventAdapterPub>
{
public:
	SynchronousEventAdapterPy(double time, STI_Device_Adapter_Wrapper* device) :
		SynchronousEventAdapterPub(time, device) {}
	virtual  ~SynchronousEventAdapterPy() {}

	virtual void setupEvent_py();
	void default_setupEvent_py();

	//virtual void loadEvent() {}
	//virtual void playEvent() {}
	//virtual void collectMeasurementData() {}

	//void addRef(const boost::shared_ptr<SynchronousEventAdapterPy>& evt)
	//{
	//	evt_ = evt;
	//}

//	boost::shared_ptr<SynchronousEventAdapterPy> evt_;
};


#endif

