
#include "PartnerDevicePy.h"
#include "MixedValuePy.h"

PartnerDevicePy::PartnerDevicePy() : partnerDeviceRef(NULL)
{
	//partnerDeviceRef is null if the object is created in python using the python constructor.
	//In this case the object points to no partner, so it does nothing.
}


PartnerDevicePy::PartnerDevicePy(PartnerDevice& partnerDevice) : partnerDeviceRef(&partnerDevice)
{
	//partnerDeviceRef resources are managed by the STI device lib.
}

//bool PartnerDevicePy::read_py(unsigned short channel, const boost::python::object& valueIn, boost::python::object& dataOut)
bool PartnerDevicePy::read_py(unsigned short channel, const boost::python::object& valueIn, MixedValuePy& dataOut)
{
	if (partnerDeviceRef == 0)
		return false;

	MixedValuePy valuleInPy(valueIn);
	MixedData data;

	bool success = partnerDeviceRef->read(channel, valuleInPy, data);

	if (success) {
		dataOut.setValue(data);
		return true;
	}
	return false;
}

boost::python::object PartnerDevicePy::read_py2(unsigned short channel, const boost::python::object& valueIn)
{
	MixedValuePy dataOut;

	if (read_py(channel, valueIn, dataOut)) {
		return MixedValuePy::convertValue(dataOut);
	}

	//read failed for some reason
	boost::python::object empty;
	return empty;
}


//bool PartnerDevicePy::read(unsigned short channel, const MixedValuePy& valueIn, MixedValuePy& dataOut)
//{
//	if(partnerDeviceRef == 0)
//		return false;
//
//	std::cout << "PartnerDevicePy::read" << std::endl;
//
//	MixedData mixedDataOut;
//	if (partnerDeviceRef->read(channel, valueIn, mixedDataOut)) {
//		dataOut.setValue(mixedDataOut);
//	}
//	return false;
//}

bool PartnerDevicePy::write(unsigned short channel, const boost::python::object& value)
{
	if (partnerDeviceRef == 0)
		return false;

	MixedValuePy valuleInPy(value);
	bool success = partnerDeviceRef->write(channel, valuleInPy);
	return success;
}

std::string PartnerDevicePy::execute(const std::string& args)
{
	return partnerDeviceRef->execute(args);
}
