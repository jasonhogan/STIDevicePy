#ifndef STI_MIXEDVALUEPY_H
#define STI_MIXEDVALUEPY_H

#include <boost/python.hpp>
#include <MixedValue.h>

class MixedValuePy : public MixedValue
{
public:
		
	MixedValuePy();
	MixedValuePy(const MixedValue& value);
	MixedValuePy(const boost::python::object& value);

	boost::python::object getValue() const;
	void setValue(const boost::python::object& value);
	void addValue(const boost::python::object& value);

	void clear();

	std::string print() const;
	
	static boost::python::object convertValue(const MixedValue& value);

private:


	template<typename T>
	bool setValueExtract(const boost::python::object& value)
	{
		boost::python::extract<T> t_val(value);

		if (t_val.check()) {
			MixedValue::setValue(t_val());
			return true;
		}
		return false;
	}

	template<typename T>
	bool addValueExtract(const boost::python::object& value)
	{
		boost::python::extract<T> t_val(value);

		if (t_val.check()) {
			MixedValue::addValue(t_val());
			return true;
		}
		return false;
	}
};

#endif

