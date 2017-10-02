
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
//using namespace boost::python;

#include "ORBManagerPy.h"
#include "STI_Device_Adapter_Wrapper.h"
#include "STI_Device_Adapter_Pub.h"

#include <Attribute.h>


BOOST_PYTHON_MODULE(STIPy)
{
	using namespace boost::python;

	class_<ORBManagerPy>("ORBManagerPy")
		.def("run", &ORBManagerPy::run)
		.def("ORBshutdown", &ORBManagerPy::ORBshutdown)
		;

	//class_<Attribute>("Attribute")
	//	.def("value", &Attribute::value)
	//	.def("setValue", &Attribute::setValue)
	//	;

	////////////////////////////////////////////////////////////

	class_<STI_Device_Adapter_Wrapper, boost::noncopyable>("STI_Device",
		init<ORBManagerPy&, std::string, std::string, unsigned short>())
		
		.def("defineChannels", &STI_Device_Adapter_Pub::defineChannels, &STI_Device_Adapter_Wrapper::default_defineChannels)
		.def("execute", &STI_Device_Adapter_Pub::execute, &STI_Device_Adapter_Wrapper::default_execute)
		.def("addOutputChannel", &STI_Device_Adapter_Pub::addOutputChannel)
		;
	
	enum_<TValue>("TValue")
		.value("ValueNumber", ValueNumber)
		.value("ValueString", ValueString)
		.value("ValueVector", ValueVector)
		.value("ValueNone", ValueNone)
		;

}

