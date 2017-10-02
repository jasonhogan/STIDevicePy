#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
using namespace boost::python;

#include <string>

//__declspec(dllexport) 
char const* greet()
{
	return "hello, world";
}


//BOOST_PYTHON_MODULE(testDLL)
//{
//	using namespace boost::python;
//	def("greet", greet);
//}


struct World
{
	World(std::string msg) : msg(msg) {} // added constructor
	void set(std::string msg) { this->msg = msg; }
	std::string greet() { return msg; }
	std::string msg;
};

//BOOST_PYTHON_MODULE(testDLL2)
//{
//	class_<World>("World", init<std::string>())
//		.def("greet", &World::greet)
//		.def("set", &World::set)
//		;
//}

BOOST_PYTHON_MODULE(testDLL)
{
	using namespace boost::python;
	def("greet", greet);

	class_<World>("World", init<std::string>())
		.def("greet", &World::greet)
		.def("set", &World::set)
		;
}