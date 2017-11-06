#include <boost/python.hpp>

#include "MixedValuePy.h"

MixedValuePy::MixedValuePy()
	: MixedValue()
{

}

MixedValuePy::MixedValuePy(const MixedValue& value) : MixedValue(value)
{
}


MixedValuePy::MixedValuePy(const boost::python::object& value)
{
	setValue(value);
}

void MixedValuePy::setValue(const boost::python::object& value)
{
//	std::string str = boost::python::extract<std::string>(boost::python::str(value))();

	if (setValueExtract<double>(value)) return;
	if (setValueExtract<int>(value)) return;
	if (setValueExtract<std::string>(value)) return;
	if (setValueExtract<bool>(value)) return;
}

void MixedValuePy::addValue(const boost::python::object& value)
{
	if (addValueExtract<bool>(value)) return;
	if (addValueExtract<int>(value)) return;
	if (addValueExtract<double>(value)) return;
	if (addValueExtract<std::string>(value)) return;
}

void MixedValuePy::clear()
{
	MixedValue::clear();
}

boost::python::object MixedValuePy::getValue() const
{
	using boost::python::object;
	
	object obj = convertValue(*this);
	
	return obj;
}

boost::python::object MixedValuePy::convertValue(const MixedValue& value)
{
	using boost::python::object;

	object obj;

	switch (value.getType())
	{
	case Boolean:
		obj = object(value.getBoolean());
		break;
	case Int:
		obj = object(value.getInt());
		break;
	case Double:
		obj = object(value.getDouble());
		break;
	case String:
		obj = object(value.getString());
		break;
	case Vector:
	{
		boost::python::list pyList;
		const MixedValueVector& vec = value.getVector();

		for (const MixedValue& v : vec) {
			pyList.append( convertValue(v) );
		}

		obj = object(pyList);
		break;
	}
	case Empty:
		break;
	default:
		break;
	}

	return obj;
}

std::string MixedValuePy::print() const
{
	return MixedValue::print();
}
