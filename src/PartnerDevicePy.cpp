
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
	std::cout << "PartnerDevicePy::read_py" << std::endl;
	//convert
	MixedValuePy valuleInPy(valueIn);
	//boost::python::object inObj(valuleInPy.getValue());
	
	MixedData data;

	partnerDeviceRef->read(channel, valuleInPy, data);

//	MixedValuePy dataVal;
//	dataVal.setValue(data);
//	dataOut = dataVal.getValue();

	std::cout << "PartnerDevicePy::read_py then read: " << data.print() << std::endl;

	dataOut.setValue(data);
	//dataOut.setValue(22);

	//dataOut = boost::python::object(3);

	return true;
}

boost::python::object PartnerDevicePy::read_py2(unsigned short channel, const boost::python::object& valueIn)
{
	MixedValuePy dataOut;

//	boost::python::object dataObj = MixedValuePy::convertValue(dataOut);
//	return dataObj;
	
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
	//if (partnerDeviceRef == 0)
	//	return false;

	//return partnerDeviceRef->write(channel, value);

	MixedValuePy valuleInPy(value);
	std::cout << "PartnerDevicePy::write: " << valuleInPy.print() << std::endl;
	bool success = partnerDeviceRef->write(channel, valuleInPy);
	std::cout << "... success? " << success << std::endl;
	return success;
}

std::string PartnerDevicePy::execute(const std::string& args)
{
	return partnerDeviceRef->execute(args);
}
