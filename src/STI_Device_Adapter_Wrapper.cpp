//#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#include "STI_Device_Adapter_Wrapper.h"
#include "STI_Device_Adapter_Pub.h"



#include <string>
#include <iostream>


STI_Device_Adapter_Wrapper::STI_Device_Adapter_Wrapper(
	ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
	: STI_Device_Adapter_Pub(orb, DeviceName, IPAddress, ModuleNumber)
{
}

void STI_Device_Adapter_Wrapper::defineAttributes()
{
	//STI library calls this if there is a python override
	if (boost::python::override defineAttributes = this->get_override("defineAttributes"))
	{
		defineAttributes(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::defineAttributes();
}

void STI_Device_Adapter_Wrapper::default_defineAttributes()
{
	this->STI_Device_Adapter_Pub::defineAttributes();
}


void STI_Device_Adapter_Wrapper::refreshAttributes()
{
	//STI library calls this if there is a python override
	if (boost::python::override refreshAttributes = this->get_override("refreshAttributes"))
	{
		refreshAttributes(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::refreshAttributes();
}

void STI_Device_Adapter_Wrapper::default_refreshAttributes()
{
	this->STI_Device_Adapter_Pub::refreshAttributes();
}

bool STI_Device_Adapter_Wrapper::updateAttribute(std::string key, std::string value)
{
	//STI library calls this if there is a python override
	if (boost::python::override updateAttribute = this->get_override("updateAttribute"))
	{
		return updateAttribute(key, value); // calls python override (implemented by user-defined python derived class)
	}
	return STI_Device_Adapter_Pub::updateAttribute(key, value);
}

bool STI_Device_Adapter_Wrapper::default_updateAttribute(std::string key, std::string value)
{
	return this->STI_Device_Adapter_Pub::updateAttribute(key, value);
}

void STI_Device_Adapter_Wrapper::defineChannels()
{
	//STI library calls this if there is a python override
	if (boost::python::override defineChannels = this->get_override("defineChannels"))
	{
		defineChannels(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::defineChannels();
}

void STI_Device_Adapter_Wrapper::default_defineChannels()
{
	this->STI_Device_Adapter_Pub::defineChannels();
}

bool STI_Device_Adapter_Wrapper::writeChannel_py(unsigned short channel, const boost::python::object& value)
{
	//STI library calls this if there is a python override
	if (boost::python::override writeChannel_py = this->get_override("writeChannel"))
	{
		bool success = writeChannel_py(channel, value); // calls python override (implemented by user-defined python derived class)
		return success;
	}
	return STI_Device_Adapter_Pub::writeChannel_py(channel, value);
}

bool STI_Device_Adapter_Wrapper::default_writeChannel_py(unsigned short channel, const boost::python::object& value)
{
	return this->STI_Device_Adapter_Pub::writeChannel_py(channel, value);
}

bool STI_Device_Adapter_Wrapper::readChannel_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut)
{
	//STI library calls this if there is a python override
	if (boost::python::override readChannel_py = this->get_override("readChannel"))
	{
		bool success = readChannel_py(channel, valueIn, dataOut); // calls python override (implemented by user-defined python derived class)
		//boost::ref(dataOut)
		//boost::python::ptr<boost::python::object>(dataOut)
//		boost::python::call_method<bool>(boost::python::self, "readChannel", valueIn, boost::python::ptr(dataOut));
		return success;
	}
	return STI_Device_Adapter_Pub::readChannel_py(channel, valueIn, dataOut);
}

bool STI_Device_Adapter_Wrapper::default_readChannel_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut)
{
	return this->STI_Device_Adapter_Pub::readChannel_py(channel, valueIn, dataOut);
}


bool STI_Device_Adapter_Wrapper::readChannel_py2(
	unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut)
{
	//STI library calls this if there is a python override
	if (boost::python::override readChannel_py2 = this->get_override("readChannel"))
	{
		bool success = readChannel_py2(channel, valueIn,
			boost::ref(dataOut));	// calls python override (implemented by user-defined python derived class)
		//	dataOut);
		
		// calls python override (implemented by user-defined python derived class)
					  //boost::ref(dataOut)
					  //boost::python::ptr<boost::python::object>(dataOut)
//		boost::python::call_method<bool>(boost::python::self, "readChannel", valueIn, boost::python::ptr(dataOut));
		return success;
	}
	return STI_Device_Adapter_Pub::readChannel_py2(channel, valueIn, dataOut);
}

bool STI_Device_Adapter_Wrapper::default_readChannel_py2(
	unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut)
{
	return this->STI_Device_Adapter_Pub::readChannel_py2(channel, valueIn, dataOut);
}

void STI_Device_Adapter_Wrapper::definePartnerDevices()
{
	//STI library calls this if there is a python override
	if (boost::python::override definePartnerDevices = this->get_override("definePartnerDevices"))
	{
		definePartnerDevices(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::definePartnerDevices();
}

void STI_Device_Adapter_Wrapper::default_definePartnerDevices()
{
	this->STI_Device_Adapter_Pub::definePartnerDevices();
}

std::string STI_Device_Adapter_Wrapper::execute(int argc, char* argv[])
{
	//STI library calls this if there is a python override
	if (boost::python::override execute = this->get_override("execute"))
	{
		std::vector<std::string> args;
		STI::Utils::convertArgs(argc, argv, args);

		boost::python::list result;
		// put all the strings inside the python list
		vector<string>::iterator it;
		for (it = args.begin(); it != args.end(); ++it) {
			result.append(*it);
		}

		return execute(result); // *note* // call python function
	}
	return STI_Device_Adapter_Pub::execute(argc, argv);
}

std::string STI_Device_Adapter_Wrapper::default_execute(int argc, char* argv[])
{
	return this->STI_Device_Adapter_Pub::execute(argc, argv);
}

void STI_Device_Adapter_Wrapper::parseDeviceEvents_py(const boost::python::list& eventsIn, boost::python::list& eventsOut)
{
	//STI library calls this if there is a python override
	if (boost::python::override parseDeviceEvents_py = this->get_override("parseDeviceEvents"))
	{
		//parseDeviceEvents_py(eventsIn, boost::ref(eventsOut));
		parseDeviceEvents_py(eventsIn, eventsOut);
		//	dataOut);

		// calls python override (implemented by user-defined python derived class)
		//boost::ref(dataOut)
		//boost::python::ptr<boost::python::object>(dataOut)
		//		boost::python::call_method<bool>(boost::python::self, "readChannel", valueIn, boost::python::ptr(dataOut));
		return;
	}
	STI_Device_Adapter_Pub::parseDeviceEvents_py(eventsIn, eventsOut);
}

void STI_Device_Adapter_Wrapper::default_parseDeviceEvents_py(const boost::python::list& eventsIn, boost::python::list& eventsOut)
{
	this->STI_Device_Adapter_Pub::parseDeviceEvents_py(eventsIn, eventsOut);
}

void STI_Device_Adapter_Wrapper::stopEventPlayback()
{
	//STI library calls this if there is a python override
	if (boost::python::override stopEventPlayback = this->get_override("stopEventPlayback"))
	{
		stopEventPlayback(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::stopEventPlayback();
}

void STI_Device_Adapter_Wrapper::default_stopEventPlayback()
{
	this->STI_Device_Adapter_Pub::stopEventPlayback();
}

void STI_Device_Adapter_Wrapper::pauseEventPlayback()
{
	//STI library calls this if there is a python override
	if (boost::python::override pauseEventPlayback = this->get_override("pauseEventPlayback"))
	{
		pauseEventPlayback(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::pauseEventPlayback();
}

void STI_Device_Adapter_Wrapper::default_pauseEventPlayback()
{
	this->STI_Device_Adapter_Pub::pauseEventPlayback();
}

void STI_Device_Adapter_Wrapper::resumeEventPlayback()
{
	//STI library calls this if there is a python override
	if (boost::python::override resumeEventPlayback = this->get_override("resumeEventPlayback"))
	{
		resumeEventPlayback(); // calls python override (implemented by user-defined python derived class)
		return;
	}
	return STI_Device_Adapter_Pub::resumeEventPlayback();
}

void STI_Device_Adapter_Wrapper::default_resumeEventPlayback()
{
	this->STI_Device_Adapter_Pub::resumeEventPlayback();
}

std::string STI_Device_Adapter_Wrapper::getDeviceHelp()
{
	//STI library calls this if there is a python override
	if (boost::python::override getDeviceHelp = this->get_override("getDeviceHelp"))
	{
		return getDeviceHelp(); // calls python override (implemented by user-defined python derived class)
	}
	return STI_Device_Adapter_Pub::getDeviceHelp();
}

std::string STI_Device_Adapter_Wrapper::default_getDeviceHelp()
{
	return this->STI_Device_Adapter_Pub::getDeviceHelp();
}

