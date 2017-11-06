
#include "STI_Device_Adapter_Pub.h"
#include "STI_Device_Adapter.h"
#include "ORBManagerPy.h"
#include "RawEventPy.h"

#include "SynchronousEventAdapterPy.h"

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

bool STI_Device_Adapter_Pub::writeChannel_py(unsigned short channel, const boost::python::object& value)
//bool STI_Device_Adapter_Pub::writeChannel_py(unsigned short channel, double value)
{
	std::cout << "(4) writeChannel_py" << std::endl;
	return false;
	//MixedValue mVal;
	//mVal.setValue( boost::python::extract<std::string>(boost::python::str(value))() );
	//return STI_Device_Adapter::writeChannel(channel, mVal);
}

bool STI_Device_Adapter_Pub::readChannel(unsigned short channel, const MixedValue& valueIn, MixedData& dataOut)
{
	std::cout << "(3) readChannel_py" << std::endl;

	MixedValuePy valuleInPy(valueIn);
	boost::python::object inObj(valuleInPy.getValue());
//	boost::python::object inObj(valueIn.getDouble());

	boost::python::object outObj;

	MixedValuePy outVal;
	std::cout << "after MixedValuePy constructor" << std::endl;

	bool success = readChannel_py2(channel, inObj, outVal);
	
	std::cout << "after readChannel_py2(" << std::endl;

	std::cout << "readChannel_py: " << outVal.getNumber() << std::endl;

//	std::cout << "readChannel_py: " << boost::python::extract<std::string>(boost::python::str(outObj))() << std::endl;
	
//	std::cout << "static_cast: " << static_cast<MixedValue>(outVal).getString() << std::endl;

//	MixedValue v = static_cast<MixedValue>(outVal);
	std::cout << "after static_cast" << std::endl;
	MixedValue* v2 = &outVal;

	dataOut.setValue(*v2);
	//dataOut.setValue(outVal.getString());
	std::cout << "after setvalue" << std::endl;

	std::cout << "dataOut = " << dataOut.print() << std::endl;

//	dataOut.setValue(outVal.getString());
	return success;
}

bool STI_Device_Adapter_Pub::readChannel_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut)
{
	std::cout << "(4) readChannel_py" << std::endl;
	return false;
	//MixedValue mVal;
	//mVal.setValue( boost::python::extract<std::string>(boost::python::str(value))() );
	//return STI_Device_Adapter::writeChannel(channel, mVal);
}

bool STI_Device_Adapter_Pub::readChannel_py2(unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut)
{
	std::cout << "(5) readChannel_py" << std::endl;
	return false;

}




void STI_Device_Adapter_Pub::definePartnerDevices()
{
	return STI_Device_Adapter::definePartnerDevices();
}


std::string STI_Device_Adapter_Pub::execute(int argc, char* argv[]) 
{ 
	return STI_Device_Adapter::execute(argc, argv);
}
void convertList(const std::vector<RawEvent>& vec, boost::python::api::object_item& obj)
{
	boost::python::list rawEventsPy = boost::python::list();

	for (auto evts : vec) {
		rawEventsPy.append(RawEventPy(evts));
	}
	obj = rawEventsPy;
}

void STI_Device_Adapter_Pub::parseDeviceEvents(const RawEventMap& eventsIn, SynchronousEventVector& eventsOut)
{
	//also see:  https://stackoverflow.com/questions/6157409/stdvector-to-boostpythonlist
	
	// Useful at one point, although not what is being used:
	// https://stackoverflow.com/questions/14642216/make-boost-python-not-delete-the-c-object-in-destructor

	std::cout << "(3) parseDeviceEvents" << std::endl;
	
	//Python dict is unordered.  Not the right structure. Should probably convert to:
	// list [ tuple(time, list [events ...]), tuple(...), ... ]

	//Convert:  eventsIn --> eventsInPy
	boost::python::dict eventsInPy;
	boost::python::list rawEventsPy;

	for (auto it = eventsIn.begin(); it != eventsIn.end(); ++it) {

		rawEventsPy = boost::python::list();

		for (auto& evts : it->second) {
			rawEventsPy.append(RawEventPy(evts));
		}

		eventsInPy[it->first] = rawEventsPy;
	}

	boost::python::list eventsOutPy;

	parseDeviceEvents_py(eventsInPy, eventsOutPy);	//call to python implementation
	
	//Convert:  eventsOutPy --> eventsOut
	for (int i = 0; i < len(eventsOutPy); ++i)
	{
		boost::python::extract<std::auto_ptr<SynchronousEventAdapterPy>> extract_evt(eventsOutPy[i]);

		std::auto_ptr<SynchronousEventAdapterPy>& evt_ptr = extract_evt();

		evt_ptr.get()->addRef(eventsOutPy[i]().ptr());		//ptr() returns PyObject* of the event created in python.
		eventsOut.push_back(evt_ptr.get());					//eventsOut is boost::ptr_vector (takes ownership).
		evt_ptr.release();									//Make the auto_ptr give up ownership so it doesn't call delete.
	}
}


void STI_Device_Adapter_Pub::parseDeviceEvents_py(const boost::python::dict& eventsIn, boost::python::list& eventsOut)
{
	std::cout << "(5) parseDeviceEvents_py" << std::endl;
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

std::string STI_Device_Adapter_Pub::getDeviceHelp()
{
	return STI_Device_Adapter::getDeviceHelp();
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
