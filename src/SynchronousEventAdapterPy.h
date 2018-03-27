#ifndef SYNCHRONOUSEVENTADAPTERPY_H
#define SYNCHRONOUSEVENTADAPTERPY_H

#include "STI_Device_Adapter_Wrapper.h"
#include <STI_Device_Adapter.h>
#include <STI_Device.h>

#include "SynchronousEventAdapterPub.h"




//class SynchronousEventPyWrapper : public STI_Device::SynchronousEvent
//{
//public:
//	SynchronousEventPyWrapper(const boost::shared_ptr<SynchronousEventAdapterPy>& evt);
//};



class SynchronousEventAdapterPy : public SynchronousEventAdapterPub,
	public boost::python::wrapper<SynchronousEventAdapterPub>
{
public:
	SynchronousEventAdapterPy(double time, STI_Device_Adapter_Wrapper* device) :
		SynchronousEventAdapterPub(time, device), added(false) {}
	virtual ~SynchronousEventAdapterPy() 
	{

		if(added) {
			Py_DecRef(evt_);
			std::cout << "SynchronousEventAdapterPy::Py_DecRef" << std::endl;
		}
	}

	virtual void setupEvent_py();
	void default_setupEvent_py();

	virtual void loadEvent_py();
	void default_loadEvent_py();

	virtual void playEvent_py();
	void default_playEvent_py();

	virtual void collectMeasurementData_py();
	void default_collectMeasurementData_py();



	//virtual void stop();
	//virtual void reset();

	//virtual void waitBeforeLoad();
	//virtual void waitBeforePlay();
	//virtual void waitBeforeCollectData();

	//NOT VIRTUAL, no need to override? Expose to python.
	//void setEventNumber(unsigned eventNumber) { eventNumber_ = eventNumber; }
	//void addMeasurement(const RawEvent& measurementEvent);

	void addRef(PyObject* evt)
	{
		std::cout << "addRef" << std::endl;

		added = true;
		evt_ = evt;
		Py_IncRef(evt_);
	}

	static void no_op(SynchronousEventAdapterPy*);
	static boost::shared_ptr<SynchronousEventAdapterPy> create_event(double time, STI_Device_Adapter_Wrapper* device);

	bool added;
	PyObject* evt_;
//	boost::shared_ptr<SynchronousEventAdapterPy> evt_;

};

//void no_op(SynchronousEventAdapterPy*) {};
//
////factory function that makes shared_ptrs with custom deleter (no_op)
//boost::shared_ptr<SynchronousEventAdapterPy> create_event(double time, STI_Device_Adapter_Wrapper* device)
//{
//	return boost::shared_ptr<SynchronousEventAdapterPy>(
//		new SynchronousEventAdapterPy(time, device),
//		&no_op);
//}


#endif


