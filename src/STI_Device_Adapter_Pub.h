#ifndef STI_DEVICE_ADAPTER_PUB_H
#define STI_DEVICE_ADAPTER_PUB_H

#include <STI_Device_Adapter.h>
#include "ORBManagerPy.h"

#include <string>

class STI_Device_Adapter_Pub : public STI_Device_Adapter
{
public:
	STI_Device_Adapter_Pub(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber);
	virtual ~STI_Device_Adapter_Pub();

public:
	//STI calls this function if there is no python override:
	virtual void defineChannels();
	virtual std::string execute(int argc, char* argv[]);

	//	using STI_Device_Adapter::addOutputChannel;
	void addOutputChannel(unsigned short Channel, TValue OutputType, std::string defaultName);
};


#endif

