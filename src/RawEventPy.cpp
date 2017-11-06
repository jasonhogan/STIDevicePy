#include "MixedValuePy.h"
#include "RawEventPy.h"


RawEventPy::RawEventPy() : rawEvent(NULL)
{

}


RawEventPy::RawEventPy(const RawEvent& evt) : rawEvent(&evt)
{

}

double RawEventPy::time() const
{
	if (rawEvent != 0) {
		return rawEvent->time();
	}
	return 0;
}

unsigned short RawEventPy::channel() const
{
	if (rawEvent != 0) {
		return rawEvent->channel();
	}
	return 0;
}

boost::python::object RawEventPy::value() const
{
	if (rawEvent != 0) {
		return MixedValuePy::convertValue(rawEvent->value());
	}
	
	boost::python::object obj(0);
	return obj;
}

