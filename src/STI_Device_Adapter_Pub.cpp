
#include "STI_Device_Adapter_Pub.h"
#include "STI_Device_Adapter.h"
#include "ORBManagerPy.h"
#include "RawEventPy.h"

#include "SynchronousEventAdapterPy.h"

#include <string>
#include <iostream>

#define PRINTF_DEBUG
#ifdef PRINTF_DEBUG
#define DEBUGHERE cerr << __FUNCTION__ << " (" << __FILE__ << ":" << __LINE__ << ")" << endl
#define IMPLEMENT cerr << "Implement (if needed): " <<  __FUNCTION__ << "() in " << __FILE__ << ":" << __LINE__ << endl
#define FIXME(feature) cerr << "FIXME: " << feature << __FILE__ << ":" << __LINE__ << " [" << __FUNCTION__ << "]" << endl
#define ADD_FEATURE(feature) cerr << "TODO: " << feature << __FILE__ << ":" << __LINE__ << " [" << __FUNCTION__ << "]" << endl
#define DEBUG(msg) cerr << __FUNCTION__ << "(): " << msg << endl
#else
#define DEBUGHERE // Do nothing if PRINTF_DEBUG isn't defined
#define IMPLEMENT
#define FIXME(feature)
#define ADD_FEATURE(feature)
#define DEBUG(msg)
#endif

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
	std::cout << "(3) readChannel_py" << std::endl;

	MixedValuePy valuleInPy(valueIn);
	boost::python::object inObj(valuleInPy.getValue());
//	boost::python::object inObj(valueIn.getDouble());

	boost::python::object outObj;

	MixedValuePy outVal;
	std::cout << "after MixedValuePy constructor" << std::endl;

	bool success = readChannel_py2(channel, inObj, outVal);
	
	
	MixedValue* v2 = &outVal;

	

	/*
	 * TODO: This should work, but MixedData doesn't know how to convert
	 * from MixedValue.
	 * Aside: WHY are there MixedValue and MixedData!! Merge...
	 * dataOut.setValue(*v2)
	 */
	
	setMixedData_tmp(v2, dataOut);	//temp hack
	
	//dataOut.setValue(outVal.getString());
	std::cout << "after setvalue" << std::endl;

	std::cout << "dataOut = " << dataOut.print() << std::endl;

//	dataOut.setValue(outVal.getString());
	return success;
}

// Whoa nelly, using screen realestate like it's goin' out of style.
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


void STI_Device_Adapter_Pub::parseDeviceEvents(const RawEventMap& eventsIn, SynchronousEventVector& eventsOut) throw(std::exception)
{
	//also see:  https://stackoverflow.com/questions/6157409/stdvector-to-boostpythonlist
	
	// Useful at one point, although not what is being used:
	// https://stackoverflow.com/questions/14642216/make-boost-python-not-delete-the-c-object-in-destructor

	// Also note this, for "GC Object already tracked" crash:
	// https://stackoverflow.com/questions/23178606/debugging-python-fatal-error-gc-object-already-tracked

	std::cout << "(3) parseDeviceEvents" << std::endl;
	
	//Python dict is unordered.  Not the right structure. Should probably convert to:
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
	
	std::cout << "length: " << len(eventsOutPy) << std::endl;

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
		
		//evt_ptr->setupEvent();
		
		std::cout << "In loop: " << i << " t=" << evt_ptr->getTime() << std::endl;
		//PyObject* evtA = eventsOutPy[i]().ptr();
		std::cout << "Got pointer" << std::endl;
		
		evt_ptr.get()->addRef(obj.ptr());		//ptr() returns PyObject* of the event created in python.

		//evt_ptr.get()->addRef(eventsOutPy[i]().ptr());		//ptr() returns PyObject* of the event created in python.
		std::cout << "A" << std::endl;
		eventsOut.push_back(evt_ptr.get());					//eventsOut is boost::ptr_vector (takes ownership).
		std::cout << "B" << std::endl;
		evt_ptr.release();									//Make the auto_ptr give up ownership so it doesn't call delete.
		std::cout << "C" << std::endl;
	}
}


void STI_Device_Adapter_Pub::parseDeviceEvents_py(const boost::python::list& eventsIn, boost::python::list& eventsOut)
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
