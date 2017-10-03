#ifndef STI_DEVICE_ADAPTER_PUB_H
#define STI_DEVICE_ADAPTER_PUB_H

#include <boost/python.hpp>

#include <STI_Device_Adapter.h>
#include "ORBManagerPy.h"


#include <string>

// This class exposes protected STI_Device_Adapter methods so they can be accessed by boost::python
// _Pub stands for "public" access.
// Methods redirect to STI_Device_Adapter.
// Note: STI will call these function if there is no python override provided.

class STI_Device_Adapter_Pub : public STI_Device_Adapter
{
public:
	STI_Device_Adapter_Pub(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber);
	virtual ~STI_Device_Adapter_Pub();

public:

	// Device Attributes
	virtual void defineAttributes();
	virtual void refreshAttributes();
	virtual bool updateAttribute(std::string key, std::string value);


	virtual void defineChannels();
	bool writeChannel(unsigned short channel, const MixedValue& value);
	virtual bool writeChannel_py(unsigned short channel, boost::python::object value);
//	virtual bool writeChannel_py(unsigned short channel, double value);

	virtual void definePartnerDevices();
	virtual std::string execute(int argc, char* argv[]);

	// Event Playback control
	virtual void stopEventPlayback();
	virtual void pauseEventPlayback();
	virtual void resumeEventPlayback();


	void addOutputChannel(unsigned short Channel, TValue OutputType, std::string defaultName="");
	void addInputChannel_1(unsigned short Channel, TData InputType);
	void addInputChannel_2(unsigned short Channel, TData InputType, std::string defaultName);
	void addInputChannel_3(unsigned short Channel, TData InputType, TValue OutputType, std::string defaultName = "");

	void addAttribute(std::string key, boost::python::object initialValue, std::string allowedValues = "");

	bool setAttribute(std::string key, boost::python::object value);

	bool addPartnerDevice(std::string partnerName, std::string IP, short module, std::string deviceName);


	//template<class T>
	//void addAttribute(std::string key, T initialValue, std::string allowedValues = "")
	//{
	//	STI_Device_Adapter::addAttribute(key, initialValue, allowedValues)
	//}
};


#endif

