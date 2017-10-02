
#ifndef STI_DEVICE_ADAPTER_WRAPPER_H
#define STI_DEVICE_ADAPTER_WRAPPER_H

#include "ORBManagerPy.h"
#include "STI_Device_Adapter_Pub.h"

#include <string>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>


class STI_Device_Adapter_Wrapper 
	: public STI_Device_Adapter_Pub, public boost::python::wrapper<STI_Device_Adapter_Pub>
{
public:
	STI_Device_Adapter_Wrapper(
		ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber);

	virtual void defineChannels();
	void default_defineChannels();

	virtual std::string execute(int argc, char* argv[]);
	std::string default_execute(int argc, char* argv[]);

};


#endif

