
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

	std::cout << "(3) parseDeviceEvents" << std::endl;
	
	boost::python::dict eventsInPy;
	boost::python::list rawEventsPy;

	for (auto it = eventsIn.begin(); it != eventsIn.end(); ++it) {

		rawEventsPy = boost::python::list();

		for (auto& evts : it->second) {
			rawEventsPy.append(RawEventPy(evts));
		}

		eventsInPy[it->first] = rawEventsPy;
	}

//This works:
//	for (auto it = eventsIn.begin(); it != eventsIn.end(); ++it) {
//		eventsInPy[it->first] = boost::python::list();
//		boost::python::list l = boost::python::extract<boost::python::list>(eventsInPy[it->first]);
////		std::cout << "t=" << it->first << " len=" << len(l);
//		
//		//convertList(it->second, eventsInPy[it->first]);
//		for (auto& evts : it->second) {
//		//	RawEventPy e = evts;
//			l.append(RawEventPy(evts));
//		}
//	}

	boost::python::list eventsOutPy;


	std::cout << "(3) parseDeviceEvents calling parseDeviceEvents_py" << std::endl;

	parseDeviceEvents_py(eventsInPy, eventsOutPy);
	
//	for (int x = 0; x < eventsOutPy.count(x); x++) {
//		std::cout << "event: " << std::endl;
////		eventsOutPy.index(x).setupEvent();
//	}

	std::cout << "Entering for loop: " << std::endl;

	for (int i = 0; i < len(eventsOutPy); ++i)
	{
		std::cout << "Loop: " << i << std::endl;
		
		//SynchronousEventAdapterPy& e = boost::python::extract<SynchronousEventAdapterPy>(eventsOutPy[i]);
		
		//boost::python::extract<SynchronousEventAdapterPy&> get_evt(eventsOutPy[i]);
		//boost::python::extract<SynchronousEventAdapterPy*> get_evt2(eventsOutPy[i]);
		//boost::python::extract<boost::shared_ptr<SynchronousEventAdapterPy>> get_evt3(eventsOutPy[i]);
		boost::python::extract<std::auto_ptr<SynchronousEventAdapterPy>> get_evt4(eventsOutPy[i]);

		//get_evt3()->setupEvent();

//		hold = get_evt2;

		//boost::python::handle<SynchronousEventAdapterPy> h(
		//	boost::python::borrowed(
		//		get_evt2()
		//		));


		//boost::python::borrowed(get_evt2());
		//eventsOut.push_back(get_evt2());

	
		//boost::shared_ptr<SynchronousEventAdapterPy> tmp = get_evt3();
		//tmp->addRef(tmp);
		//eventsOut.push_back(*tmp);

		//boost::python::object o(eventsOutPy[i]);
		//std::cout << "Refcount a: " << o.ptr()->ob_refcnt << std::endl;
		
		//Py_IncRef(o.ptr());		//almost certainly a memory leak.  Python never deletes, but c++ does?
		//std::cout << "Refcount b: " << o.ptr()->ob_refcnt << std::endl;
		//eventsOut.push_back(get_evt2());
		
		//eventsOut.push_back(get_evt3().get());
		//eventsOut.push_back(get_evt2());

		//get_evt4().
		boost::python::object o(eventsOutPy[i]);
		get_evt4().get()->addRef(o.ptr());
		eventsOut.push_back(get_evt4().get());
		get_evt4().release();

		// Here is the answer:
		// https://stackoverflow.com/questions/14642216/make-boost-python-not-delete-the-c-object-in-destructor



		//boost::python::handle<> h(eventsOutPy[i]);


		//try {
		//	std::cout << "Event time: " << get_evt().getTime() << std::endl;
		//	get_evt().setupEvent();
		//	std::cout << "In try" << std::endl;
		//}
		//catch (...) {
		//	std::cout << "setupEvent error" << std::endl;
		//}

		std::cout << "eventsOut.back().setup():" << std::endl;
		//eventsOut.back().setup();
		std::cout << "leaving parse...." << std::endl;
	}

//	eventsOut = eventsOutPy;
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
