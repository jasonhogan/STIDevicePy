
#include "STI_Device_Adapter_Wrapper.h"
#include "STI_Device_Adapter_Pub.h"

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#include <string>
#include <iostream>


STI_Device_Adapter_Wrapper::STI_Device_Adapter_Wrapper(
	ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
	: STI_Device_Adapter_Pub(orb, DeviceName, IPAddress, ModuleNumber)
{
}

void STI_Device_Adapter_Wrapper::defineChannels()
{
	//STI library calls this if there is a python override
	if (boost::python::override defineChannels = this->get_override("defineChannels"))
	{
		std::cout << "......2........" << std::endl;
		defineChannels(); // *note* // call python function
		return;
	}
	return STI_Device_Adapter_Pub::defineChannels();
}

void STI_Device_Adapter_Wrapper::default_defineChannels()
{
	std::cout << ".......3......." << std::endl; 
	this->STI_Device_Adapter_Pub::defineChannels();
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

		std::cout << "......2........" << std::endl;
		return execute(result); // *note* // call python function
	}
	return STI_Device_Adapter_Pub::execute(argc, argv);
}

std::string STI_Device_Adapter_Wrapper::default_execute(int argc, char* argv[])
{
	std::cout << ".......3......." << std::endl;
	return this->STI_Device_Adapter_Pub::execute(argc, argv);
}

