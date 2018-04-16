#ifndef STI_PARTNERDEVICEPY_H
#define STI_PARTNERDEVICEPY_H

#include "MixedValuePy.h"
#include <PartnerDevice.h>
#include <boost/python.hpp>


class PartnerDevicePy
{
public:

	PartnerDevicePy();
	PartnerDevicePy(PartnerDevice& partnerDevice);

//	bool read(unsigned short channel, const MixedValuePy& valueIn, MixedValuePy& dataOut);
	
	bool write(unsigned short channel, const boost::python::object& value);
	
	//bool read_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut);
	bool read_py(unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut);
	boost::python::object read_py2(unsigned short channel, const boost::python::object& valueIn);

	std::string execute(const std::string& args);


private:

	PartnerDevice* partnerDeviceRef;
};

#endif
