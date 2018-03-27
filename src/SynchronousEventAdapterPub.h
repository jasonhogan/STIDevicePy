#ifndef SYNCHRONOUSEVENTADAPTERPUB_H
#define SYNCHRONOUSEVENTADAPTERPUB_H


#include "STI_Device_Adapter_Wrapper.h"
#include <STI_Device_Adapter.h>
#include <STI_Device.h>

#include <mutex>

class SynchronousEventAdapterPub : public STI_Device::SynchronousEventAdapter
{
public:
	SynchronousEventAdapterPub(double time, STI_Device* device) :
		STI_Device::SynchronousEventAdapter(time, device) {}
	virtual  ~SynchronousEventAdapterPub() {}

	void setupEvent();
	virtual void setupEvent_py();

	void loadEvent();
	virtual void loadEvent_py();

	void playEvent();
	virtual void playEvent_py();

	void collectMeasurementData();
	virtual void collectMeasurementData_py();

	//	static void no_op(SynchronousEventAdapterPub*);
	//	static boost::shared_ptr<SynchronousEventAdapterPub> create_event(double time, STI_Device_Adapter_Wrapper* device);

	std::mutex mtx;

};


#endif
