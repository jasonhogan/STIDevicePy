
//#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
//using namespace boost::python;

#include "ORBManagerPy.h"
#include "STI_Device_Adapter_Wrapper.h"
#include "STI_Device_Adapter_Pub.h"
#include "SynchronousEventAdapterPy.h"

#include "MixedValuePy.h"
#include "RawEventPy.h"

#include <Attribute.h>

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(addOutputChannel_member_overloads, addOutputChannel, 2, 3)
//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(addInputChannel_1_member_overloads, addInputChannel_1, 2, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(addInputChannel_3_member_overloads, addInputChannel_3, 3, 4)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(addAttribute_member_overloads, addAttribute, 2, 3)


BOOST_PYTHON_MODULE(STIPy)
{
	using namespace boost::python;

	class_<ORBManagerPy>("ORBManager")
		.def("run", &ORBManagerPy::run)
		.def("ORBshutdown", &ORBManagerPy::ORBshutdown)
		;

	//class_<Attribute>("Attribute")
	//	.def("value", &Attribute::value)
	//	.def("setValue", &Attribute::setValue)
	//	;

	class_<MixedValuePy>("MixedValue", "Mixed value class.", init<>("__init__ docstring") )
		.def(init<const boost::python::object&>())
		.def("getValue", &MixedValuePy::getValue)
		.def("setValue", &MixedValuePy::setValue)
		.def("addValue", &MixedValuePy::addValue)
		.def("clear", &MixedValuePy::clear)
		.def("print", &MixedValuePy::print)
		;
	
	class_<RawEventPy>("RawEvent")
		.def("time", &RawEventPy::time)
		.def("channel", &RawEventPy::channel)
		.def("value", &RawEventPy::value)
		;


//	class_<SynchronousEventAdapterPy, std::unique_ptr<SynchronousEventAdapterPy>>("SynchronousEvent", "STI event class.",
//	class_<SynchronousEventAdapterPy, boost::noncopyable>("SynchronousEvent", "STI event class.",


	
	//class_<SynchronousEventAdapterPy, boost::shared_ptr<SynchronousEventAdapterPy>, boost::noncopyable>("SynchronousEvent", "STI event class.",
	
	class_<SynchronousEventAdapterPy, std::auto_ptr<SynchronousEventAdapterPy>, boost::noncopyable>("SynchronousEvent", "STI event class.",
//		boost::python::no_init)
			init<double, STI_Device_Adapter_Wrapper*>(args("Time", "Device"), "__init__ docstring"))
//		.def("setupEvent", &SynchronousEventAdapterPy::setupEvent)
//		.def("__init__", boost::python::make_constructor(&SynchronousEventAdapterPy::create_event))
		.def("setupEvent", &SynchronousEventAdapterPub::setupEvent_py, &SynchronousEventAdapterPy::default_setupEvent_py)
		.def("loadEvent", &SynchronousEventAdapterPub::loadEvent_py, &SynchronousEventAdapterPy::default_loadEvent_py)
		.def("playEvent", &SynchronousEventAdapterPub::playEvent_py, &SynchronousEventAdapterPy::default_playEvent_py)
		.def("collectMeasurementData", &SynchronousEventAdapterPub::collectMeasurementData_py, &SynchronousEventAdapterPy::default_collectMeasurementData_py)
		;
	//boost::python::implicitly_convertible<boost::shared_ptr<SynchronousEventAdapterPy>, boost::shared_ptr<SynchronousEventAdapterPub> >();


	////////////////////////////////////////////////////////////

	class_<STI_Device_Adapter_Wrapper, boost::noncopyable>("STI_Device", "STI device base class.",
		init<ORBManagerPy&, std::string, std::string, unsigned short>(args("Orb", "Device Name", "IP Address", "Module"), "__init__ docstring"))
		
		.def("defineAttributes", &STI_Device_Adapter_Pub::defineAttributes, &STI_Device_Adapter_Wrapper::default_defineAttributes)
		.def("refreshAttributes", &STI_Device_Adapter_Pub::refreshAttributes, &STI_Device_Adapter_Wrapper::default_refreshAttributes)
		.def("updateAttribute", &STI_Device_Adapter_Pub::updateAttribute, &STI_Device_Adapter_Wrapper::default_updateAttribute)
		
		.def("defineChannels", &STI_Device_Adapter_Pub::defineChannels, &STI_Device_Adapter_Wrapper::default_defineChannels)
		.def("writeChannel", &STI_Device_Adapter_Pub::writeChannel_py, &STI_Device_Adapter_Wrapper::default_writeChannel_py)
		.def("readChannel", &STI_Device_Adapter_Pub::readChannel_py2, &STI_Device_Adapter_Wrapper::default_readChannel_py2)

		.def("definePartnerDevices", &STI_Device_Adapter_Pub::definePartnerDevices, &STI_Device_Adapter_Wrapper::default_definePartnerDevices)
		.def("execute", &STI_Device_Adapter_Pub::execute, &STI_Device_Adapter_Wrapper::default_execute)

		.def("parseDeviceEvents", &STI_Device_Adapter_Pub::parseDeviceEvents_py, &STI_Device_Adapter_Wrapper::default_parseDeviceEvents_py)


		.def("stopEventPlayback", &STI_Device_Adapter_Pub::stopEventPlayback, &STI_Device_Adapter_Wrapper::default_stopEventPlayback)
		.def("pauseEventPlayback", &STI_Device_Adapter_Pub::pauseEventPlayback, &STI_Device_Adapter_Wrapper::default_pauseEventPlayback)
		.def("resumeEventPlayback", &STI_Device_Adapter_Pub::resumeEventPlayback, &STI_Device_Adapter_Wrapper::default_resumeEventPlayback)

		.def("getDeviceHelp", &STI_Device_Adapter_Pub::getDeviceHelp, &STI_Device_Adapter_Wrapper::default_getDeviceHelp)

		.def("addOutputChannel", &STI_Device_Adapter_Pub::addOutputChannel, 
			addOutputChannel_member_overloads(
			args("self", "channel", "type", "name"), 
				"addOutputChannel's docstring"
				)
			)
		.def("addInputChannel", &STI_Device_Adapter_Pub::addInputChannel_1,
			args("self", "channel", "inputType"),
			"addInputChannel docstring"
			)
		.def("addInputChannel", &STI_Device_Adapter_Pub::addInputChannel_2,
			args("self", "channel", "inputType", "name"),
			"addInputChannel docstring"
			)
		.def("addInputChannel", &STI_Device_Adapter_Pub::addInputChannel_3,
			addInputChannel_3_member_overloads(
				args("self", "channel", "inputType", "outputType", "name"),
				"addInputChannel's docstring"
				)
			)
		.def("addAttribute", &STI_Device_Adapter_Pub::addAttribute,
			addAttribute_member_overloads(
				boost::python::args("self", "key", "initialValue", "allowedValues"),
				"addAttribute's docstring"
				)
			)
		.def("setAttribute", &STI_Device_Adapter_Pub::setAttribute, 
			boost::python::args("self", "key", "value"), 
			"setAttribute docstring"
			)
		.def("addPartnerDevice", &STI_Device_Adapter_Pub::addPartnerDevice,
			boost::python::args("self", "partnerAlias", "deviceIP", "devicemodule", "deviceName"),
			"addPartnerDevice docstring"
			)
		;
	

	enum_<TValue>("TValue")
		.value("ValueNumber", ValueNumber)
		.value("ValueString", ValueString)
		.value("ValueVector", ValueVector)
		.value("ValueNone", ValueNone)
		;

	enum_<TData>("TData")
		.value("DataBoolean", DataBoolean)
		.value("DataOctet", DataOctet)
		.value("DataLong", DataLong)
		.value("DataDouble", DataDouble)
		.value("DataString", DataString)
		.value("DataPicture", DataPicture)
		.value("DataVector", DataVector)
		.value("DataFile", DataFile)
		.value("DataNone", DataNone);

}

