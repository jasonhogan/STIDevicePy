
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

	//STI calls this function if there is no python override:
void STI_Device_Adapter_Pub::defineChannels()
{ 
	std::cout << ".......1......." << std::endl;
} //{ return STI_Device_Adapter::defineChannels(); }

std::string STI_Device_Adapter_Pub::execute(int argc, char* argv[]) 
{ 
	return "";
};

void STI_Device_Adapter_Pub::addOutputChannel(unsigned short Channel, TValue OutputType, std::string defaultName)
{
	STI_Device_Adapter::addOutputChannel(Channel, OutputType, defaultName);
}
