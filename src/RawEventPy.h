#ifndef STI_RAWEVENTPY_H
#define STI_RAWEVENTPY_H

#include <RawEvent.h>
#include <boost/python.hpp>

class RawEventPy
{
public:

	RawEventPy();
	RawEventPy(const RawEvent& evt);

	double time() const;
	unsigned short channel() const;
	boost::python::object value() const;

private:

	const RawEvent* rawEvent;
};

#endif
