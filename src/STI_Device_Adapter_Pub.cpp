
#include "STI_Device_Adapter_Pub.h"
#include "STI_Device_Adapter.h"
#include "ORBManagerPy.h"
#include "RawEventPy.h"

#include "SynchronousEventAdapterPy.h"

#include <string>
#include <memory>
#include <iostream>


STI_Device_Adapter_Pub::STI_Device_Adapter_Pub(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
	: STI_Device_Adapter(orb.orb_manager.get(), DeviceName, IPAddress, ModuleNumber), 
	orb_manager(orb.orb_manager)	//save a reference so shared_ptr will not delete orb manager durin device lifetime
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
	return STI_Device_Adapter::defineChannels();
}

bool STI_Device_Adapter_Pub::writeChannel(unsigned short channel, const MixedValue& value)
{
	MixedValuePy valuleInPy(value);
	boost::python::object obj(valuleInPy.getValue());

	bool success =  writeChannel_py(channel, obj);

	return success;
}

bool STI_Device_Adapter_Pub::writeChannel_py(unsigned short channel, const boost::python::object& value)
{
	return false;
}

bool STI_Device_Adapter_Pub::setMixedData_tmp(const MixedValue* valueIn, MixedData& dataOut)
{
	switch (valueIn->getType()) {
	case MixedValue::Double:
		dataOut.setValue(valueIn->getDouble());
		break;
	case MixedValue::Int:
		dataOut.setValue(valueIn->getInt());
		break;
	case MixedValue::String:
		dataOut.setValue(valueIn->getString());
		break;
	case MixedValue::Boolean:
		dataOut.setValue(valueIn->getBoolean());
		break;
	case MixedValue::Vector:
		//Not tested...
		for (const MixedValue& val : valueIn->getVector()) {
			std::cout << val.print() << std::endl;
			MixedData tmp;
			setMixedData_tmp(&val, tmp);
			dataOut.addValue(tmp);
		}
		break;
	case MixedValue::Empty:
		break;
	}
	return true;
}

bool STI_Device_Adapter_Pub::readChannel(unsigned short channel, const MixedValue& valueIn, MixedData& dataOut)
{
	MixedValuePy valuleInPy(valueIn);
	boost::python::object inObj(valuleInPy.getValue());

	MixedValuePy outVal;

	bool success = readChannel_py2(channel, inObj, outVal);
		
	//TODO: This should work, but MixedData doesn't know how to convert from MixedValue.
	//Aside: WHY are there MixedValue and MixedData!! Merge...
	//dataOut.setValue(*v2);
	
	//setMixedData_tmp(v2, dataOut);	//temp hack
	setMixedData_tmp(&outVal, dataOut);	//temp hack

	return success;
}

bool STI_Device_Adapter_Pub::readChannel_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut)
{
	return false;
}

bool STI_Device_Adapter_Pub::readChannel_py2(unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut)
{
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

//void convertList(const std::vector<RawEvent>& vec, boost::python::api::object_item& obj)
//{
//	boost::python::list rawEventsPy = boost::python::list();
//
//	for (auto evts : vec) {
//		rawEventsPy.append(RawEventPy(evts));
//	}
//	obj = rawEventsPy;
//}

void STI_Device_Adapter_Pub::convertRawEventMap(const RawEventMap& eventsIn, boost::python::dict& eventsInPy)
{
	boost::python::list rawEventsPy;
	
	for (auto it = eventsIn.begin(); it != eventsIn.end(); ++it) {

		rawEventsPy = boost::python::list();

		for (auto& evts : it->second) {
			rawEventsPy.append(RawEventPy(evts));
		}

		eventsInPy[it->first] = rawEventsPy;
	}
}

void STI_Device_Adapter_Pub::convertRawEventMap(const RawEventMap& eventsIn, boost::python::list& eventsInPy)
{
	boost::python::list rawEventsPy;

	for (auto it = eventsIn.begin(); it != eventsIn.end(); ++it) {

		rawEventsPy = boost::python::list();

		for (auto& evts : it->second) {
			rawEventsPy.append(RawEventPy(evts));
		}
		//tuple<double, boost::python::list> time_group(it->first, rawEventsPy);
		//boost::python::object obj = time_group;
		//eventsInPy.append(time_group);
		
		//eventsInPy.append(make_tuple(it->first, rawEventsPy));
		//eventsInPy.append(boost::python::make_tuple(it->first, it->first));	//works
		eventsInPy.append(boost::python::make_tuple(it->first, rawEventsPy));
	}
}

void STI_Device_Adapter_Pub::parseDeviceEvents(const RawEventMap& eventsIn, SynchronousEventVector& eventsOut) throw (std::exception)
{
	//also see:  https://stackoverflow.com/questions/6157409/stdvector-to-boostpythonlist
	
	// Useful at one point, although not what is being used:
	// https://stackoverflow.com/questions/14642216/make-boost-python-not-delete-the-c-object-in-destructor

	// Also note this, for "GC Object already tracked" crash:
	// https://stackoverflow.com/questions/23178606/debugging-python-fatal-error-gc-object-already-tracked

	// Python dict is unordered.  Not the right structure. Should probably convert to:
	// list [ tuple(time, list [events ...]), tuple(...), ... ]

	//Convert:  eventsIn --> eventsInPy
	//boost::python::dict eventsInPy;
	boost::python::list eventsInPy;

	convertRawEventMap(eventsIn, eventsInPy);

	//boost::python::list rawEventsPy;
	//for (auto it = eventsIn.begin(); it != eventsIn.end(); ++it) {

	//	rawEventsPy = boost::python::list();

	//	for (auto& evts : it->second) {
	//		rawEventsPy.append(RawEventPy(evts));
	//	}

	//	eventsInPy[it->first] = rawEventsPy;
	//}

	boost::python::list eventsOutPy;

	parseDeviceEvents_py(eventsInPy, eventsOutPy);	//call to python implementation
	
	//Convert:  eventsOutPy --> eventsOut
	for (int i = 0; i < len(eventsOutPy); ++i)
	{
		boost::python::object obj(eventsOutPy[i]);
		//boost::python::extract<std::auto_ptr<SynchronousEventAdapterPy>> extract_evt(eventsOutPy[i]);	//works
		//boost::python::extract<std::auto_ptr<SynchronousEventAdapterPy>> extract_evt(obj);	//works
		boost::python::extract<std::auto_ptr<SynchronousEventAdapterPy>> extract_evt(obj.ptr());	//works

		if (!extract_evt.check()) {
			std::cout << "It's a trap!" << std::endl;
		}
		std::auto_ptr<SynchronousEventAdapterPy>& evt_ptr = extract_evt();
				
		evt_ptr.get()->addRef(obj.ptr());		//ptr() returns PyObject* of the event created in python.
												//addRef avoids python GC releasing event object reference

		eventsOut.push_back(evt_ptr.get());		//eventsOut is boost::ptr_vector (takes ownership).
		evt_ptr.release();						//Make the auto_ptr give up ownership so it doesn't call delete.
	}
}

void STI_Device_Adapter_Pub::parseDeviceEvents_py(const boost::python::list& eventsIn, boost::python::list& eventsOut)
{
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

PartnerDevicePy STI_Device_Adapter_Pub::partnerDevice(std::string partnerName)
{
	return PartnerDevicePy(STI_Device_Adapter::partnerDevice(partnerName));
}
