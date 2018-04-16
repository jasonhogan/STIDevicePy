
#ifndef STI_DEVICE_ADAPTER_WRAPPER_H
#define STI_DEVICE_ADAPTER_WRAPPER_H

//#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#include "ORBManagerPy.h"
#include "STI_Device_Adapter_Pub.h"


#include <string>




class STI_Device_Adapter_Wrapper 
	: public STI_Device_Adapter_Pub, public boost::python::wrapper<STI_Device_Adapter_Pub>
{
public:
	STI_Device_Adapter_Wrapper(
		ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber);

	// Device Attributes
	virtual void defineAttributes();
	void default_defineAttributes();

	virtual void refreshAttributes();
	void default_refreshAttributes();

	virtual bool updateAttribute(std::string key, std::string value);
	bool default_updateAttribute(std::string key, std::string value);


	virtual void defineChannels();
	void default_defineChannels();

//	virtual bool writeChannel_py(unsigned short channel, double value);
//	bool default_writeChannel_py(unsigned short channel, double value);
	virtual bool writeChannel_py(unsigned short channel, const boost::python::object& value);
	bool default_writeChannel_py(unsigned short channel, const boost::python::object& value);

	virtual bool readChannel_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut);
	bool default_readChannel_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut);

	virtual bool readChannel_py2(unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut);
	bool default_readChannel_py2(unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut);


	virtual void definePartnerDevices();
	void default_definePartnerDevices();

	virtual std::string execute(int argc, char* argv[]);
	std::string default_execute(int argc, char* argv[]);

	virtual void parseDeviceEvents_py(const boost::python::list& eventsIn, boost::python::list& eventsOut);
	void default_parseDeviceEvents_py(const boost::python::list& eventsIn, boost::python::list& eventsOut);


	virtual void stopEventPlayback();
	void default_stopEventPlayback();

	virtual void pauseEventPlayback();
	void default_pauseEventPlayback();

	virtual void resumeEventPlayback();
	void default_resumeEventPlayback();

	virtual std::string getDeviceHelp();
	std::string default_getDeviceHelp();

};


#endif

