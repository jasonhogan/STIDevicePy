
#include "STI_Device_Adapter_Pub.h"
#include "STI_Device_Adapter.h"
#include "ORBManagerPy.h"

#include <string>
#include <iostream>


STI_Device_Adapter_Pub::STI_Device_Adapter_Pub(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
	: STI_Device_Adapter(orb.orb_manager, DeviceName, IPAddress, ModuleNumber)
{
}

STI_Device_Adapter_Pub::~STI_Device_Adapter_Pub()
{
}

void STI_Device_Adapter_Pub::defineAttributes()
{
	return STI_Device_Adapter::defineAttributes();
}

void STI_Device_Adapter_Pub::refreshAttributes()
{
	return STI_Device_Adapter::refreshAttributes();
}

bool STI_Device_Adapter_Pub::updateAttribute(std::string key, std::string value)
{
	return STI_Device_Adapter::updateAttribute(key, value);
}


//STI calls this function if there is no python override:
void STI_Device_Adapter_Pub::defineChannels()
{ 
	std::cout << ".......1......." << std::endl;
	return STI_Device_Adapter::defineChannels();
} //{ return STI_Device_Adapter::defineChannels(); }

bool STI_Device_Adapter_Pub::writeChannel(unsigned short channel, const MixedValue& value)
{
	std::cout << "(3) writeChannel_py" << std::endl;
	boost::python::object obj(value.getDouble());
	return writeChannel_py(channel, obj);
//	return writeChannel_py(channel, value.getDouble());
}

bool STI_Device_Adapter_Pub::writeChannel_py(unsigned short channel, boost::python::object value)
//bool STI_Device_Adapter_Pub::writeChannel_py(unsigned short channel, double value)
{
	std::cout << "(4) writeChannel_py" << std::endl;
	return false;
	//MixedValue mVal;
	//mVal.setValue( boost::python::extract<std::string>(boost::python::str(value))() );
	//return STI_Device_Adapter::writeChannel(channel, mVal);
}


void STI_Device_Adapter_Pub::definePartnerDevices()
{
	return STI_Device_Adapter::definePartnerDevices();
}


std::string STI_Device_Adapter_Pub::execute(int argc, char* argv[]) 
{ 
	return STI_Device_Adapter::execute(argc, argv);
}

void STI_Device_Adapter_Pub::stopEventPlayback()
{
	return STI_Device_Adapter::stopEventPlayback();
}

void STI_Device_Adapter_Pub::pauseEventPlayback()
{
	return STI_Device_Adapter::pauseEventPlayback();
}

void STI_Device_Adapter_Pub::resumeEventPlayback()
{
	return STI_Device_Adapter::resumeEventPlayback();
}

void STI_Device_Adapter_Pub::addAttribute(std::string key, boost::python::object initialValue, std::string allowedValues)
{
	STI_Device_Adapter::addAttribute(key,
		boost::python::extract<std::string>(boost::python::str(initialValue))(),
		allowedValues);
}

bool STI_Device_Adapter_Pub::setAttribute(std::string key, boost::python::object value)
{
	return STI_Device_Adapter::setAttribute(key,
		boost::python::extract<std::string>(boost::python::str(value))());
}

void STI_Device_Adapter_Pub::addOutputChannel(unsigned short Channel, TValue OutputType, std::string defaultName)
{
	STI_Device_Adapter::addOutputChannel(Channel, OutputType, defaultName);
}

void STI_Device_Adapter_Pub::addInputChannel_1(unsigned short Channel, TData InputType)
{
	STI_Device_Adapter::addInputChannel(Channel, InputType);
}

void STI_Device_Adapter_Pub::addInputChannel_2(unsigned short Channel, TData InputType, std::string defaultName)
{
	STI_Device_Adapter::addInputChannel(Channel, InputType, defaultName);
}

void STI_Device_Adapter_Pub::addInputChannel_3(unsigned short Channel, TData InputType, TValue OutputType, std::string defaultName)
{
	STI_Device_Adapter::addInputChannel(Channel, InputType, OutputType, defaultName);
}

bool STI_Device_Adapter_Pub::addPartnerDevice(std::string partnerName, std::string IP, short module, std::string deviceName)
{
	return STI_Device_Adapter::addPartnerDevice(partnerName, IP, module, deviceName);
}
