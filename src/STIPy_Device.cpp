
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
//using namespace boost::python;

#include <STI_Device_Adapter.h>
#include <ORBManager.h>
#include <Attribute.h>

#include <iostream>


//class ORBManagerPy : public ORBManager
//{
//public:
//	ORBManagerPy() : ORBManager(argc, argv) {}
//	void run() { ORBManager::run(); }
//	void ORBshutdown() { ORBManager::ORBshutdown(); }
//};

class ORBManagerPy
{
public:
	ORBManagerPy() 
	{
		int argc = 1;
		char* argv[] = { "" };
		orb_manager = new ORBManager(argc, argv);
	}
	void run() {
		orb_manager->run();
	}
	void ORBshutdown() {
		orb_manager->ORBshutdown();
	}

	ORBManager* orb_manager;

private:
};

class MyClass
{
public:
	MyClass(int y) : x(y) {}
	int x;
};

//class STIPy_Device : public STI_Device_Adapter
class STIPy_Device_Test
{
public:
	//STIPy_Device(ORBManagerPy* orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
	//	: STI_Device_Adapter(orb->orb_manager, DeviceName, IPAddress, ModuleNumber) {}
	STIPy_Device_Test(MyClass& my, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
	: module(ModuleNumber), my(my) {}
	unsigned short getMod() { return module; }
	unsigned short module;
	MyClass my;

};



class STIPy_Device : private STI_Device_Adapter //, public boost::python::wrapper<STI_Device_Adapter>
{
public:
	STIPy_Device(std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
		: STI_Device_Adapter(orb_manager, DeviceName, IPAddress, ModuleNumber) {}

	unsigned short getMod() { return module; }
	unsigned short module;
	ORBManager* orb_manager;
};

class Base
{
public:
	Base() {};

	virtual ~Base() {};
};

class Derived : public Base
{
public:
	Derived() : Base(), module(128) {}
	~Derived() {}
	unsigned short getMod() { return module; }
	unsigned short module;
};


class STIPy_Device_Test2 : public Base //, public boost::python::wrapper<STI_Device_Adapter>
{
public:
	STIPy_Device_Test2(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
		: Base(), module(ModuleNumber) {}
	~STIPy_Device_Test2() {}
	unsigned short getMod() { return module; }
	unsigned short module;

};

class A 
{
private:
	virtual int f() = 0;
};

class B : public A 
{
public:
	B(int x) : A(), x(x) {}
	virtual ~B() {}
public:
	virtual int f() { return x; }
	int x;
};

class B2 : public A
{
public:
	B2(int x) : A(), x(x) {}
	virtual ~B2() {}
protected:
	virtual int f() { return x; }
	int x;
};

class B2Pub : public B2
{
public:
	B2Pub(int x) : B2(x) {}
	virtual ~B2Pub() {}
public:
	virtual int f() { return B2::f(); }
//	using B2::f;
};

class C : public B 
{
public:
	C(int x) : B(x) {}
	int f() { return B::f(); }
};

class BWrap : public B, public boost::python::wrapper<B>
{
public:
	BWrap(int x) : B(x) {}

	int f()
	{
		if (boost::python::override f = this->get_override("f"))
			return f(); // *note*
		return B::f();
	}
	int default_f() { return this->B::f(); }
};

class B2Wrap : public B2Pub, public boost::python::wrapper<B2Pub>
{
public:
	B2Wrap(int x) : B2Pub(x) {}

	int f()
	{
		if (boost::python::override f = this->get_override("f"))
			return f(); // *note*
		return B2Pub::f();
	}
	int default_f() { return this->B2Pub::f(); }
};



class D
{
public:
	D(C& c) : b(&c) {}
	int check() { return b->f(); }
	B* b;
};

class G
{
public:
	G(B& bin) : b(&bin) {}
	int check() { return b->f(); }
	B* b;
};

class G2
{
public:
	G2(B2Pub& bin) : b(&bin) {}
	int check() { return b->f(); }
	B2Pub* b;
};

class Holder
{
public:
	Holder(int x) : x(x) {}
	int x;
};
class Taker
{
public:
	Taker(int x) : x(x) {}
	virtual ~Taker() {}
	int x;
};
class WrapTaker : public Taker, public boost::python::wrapper<Taker>
//class WrapTaker : public Taker
{
public:
	WrapTaker(Holder& holder) : Taker(holder.x) {}
};


class STI_Device_AdapterPub : public STI_Device_Adapter
{
public:
	STI_Device_AdapterPub(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
		: STI_Device_Adapter(orb.orb_manager, DeviceName, IPAddress, ModuleNumber) {}
	virtual ~STI_Device_AdapterPub() {}
public:
	//STI calls this function if there is no python override:
	virtual void defineChannels() { std::cout << ".......1......." << std::endl; } //{ return STI_Device_Adapter::defineChannels(); }
	
	virtual std::string execute(int argc, char* argv[]) { return ""; };

//	using STI_Device_Adapter::addOutputChannel;
	void addOutputChannel(unsigned short Channel, TValue OutputType, std::string defaultName)
	{
		STI_Device_Adapter::addOutputChannel(Channel, OutputType, defaultName);
	}
	
};

class STI_Device_AdapterWrap : public STI_Device_AdapterPub, public boost::python::wrapper<STI_Device_AdapterPub>
{
public:
	STI_Device_AdapterWrap(ORBManagerPy& orb, std::string DeviceName, std::string IPAddress, unsigned short ModuleNumber)
		: STI_Device_AdapterPub(orb, DeviceName, IPAddress, ModuleNumber) {}

	virtual void defineChannels()
	{
		//STI library calls this if there is a python override
		if (boost::python::override defineChannels = this->get_override("defineChannels"))
		{
			std::cout << "......2........" << std::endl;
			defineChannels(); // *note* // call python function
			return;
		}
		return STI_Device_AdapterPub::defineChannels();
	}
	void default_defineChannels() { std::cout << ".......3......." << std::endl; this->STI_Device_AdapterPub::defineChannels(); }

	virtual std::string execute(int argc, char* argv[])
	{
		//STI library calls this if there is a python override
		if (boost::python::override execute = this->get_override("execute"))
		{
			std::vector<std::string> args;
			STI::Utils::convertArgs(argc, argv, args);

			boost::python::list result;
			// put all the strings inside the python list
			vector<string>::iterator it;
			for (it = args.begin(); it != args.end(); ++it) {
				result.append(*it);
			}

			std::cout << "......2........" << std::endl;
			return execute(result); // *note* // call python function
		}
		return STI_Device_AdapterPub::execute(argc, argv);
	}
	virtual std::string default_execute(int argc, char* argv[]) { std::cout << ".......3......." << std::endl; return this->STI_Device_AdapterPub::execute(argc, argv); }


};

BOOST_PYTHON_MODULE(STIPy)
{
	using namespace boost::python;

	class_<Holder>("Holder", init<int>())
		;
	//class_<Taker>("Taker", init<int>())
	//	;
	//class_<WrapTaker, bases<Taker> >("WrapTaker", init<Holder&>())
	//	;
	class_<WrapTaker, boost::noncopyable>("WrapTaker", init<Holder&>())
//		.def("f", &B2Pub::f, &B2Wrap::default_f)
		;

	class_<ORBManagerPy>("ORBManagerPy")
		.def("run", &ORBManagerPy::run)
		.def("ORBshutdown", &ORBManagerPy::ORBshutdown)
		;

	class_<STIPy_Device_Test>("STIPy_Device_Test", init<MyClass&, std::string, std::string, unsigned short>())
		.def("getMod", &STIPy_Device_Test::getMod)
		.def_readwrite("my", &STIPy_Device_Test::my)
		;

	class_<Base>("Base")
		;

	class_<STIPy_Device_Test2, bases<Base> >("STIPy_Device_Test2", init<ORBManagerPy&, std::string, std::string, unsigned short>())
		.def("getMod", &STIPy_Device_Test2::getMod)
		;



	class_<Attribute>("Attribute")
		.def("value", &Attribute::value)
		.def("setValue", &Attribute::setValue)
		;

	class_<MyClass>("MyClass", init<int>())
		.def_readwrite("x", &MyClass::x)
		;

	
	class_<Derived, bases<Base> >("Derived")
		.def("getMod", &Derived::getMod)
		;



	//class_<STI_Device>("STI_Device")
	//	;

	//class_<A>("A")
	//	;
	//class_<B, bases<A> >("B")
	//	;	
	//class_<C, bases<B> >("C")
	//	;

	class_<BWrap, boost::noncopyable>("B", init<int>())
		.def("f", &B::f, &BWrap::default_f)
		;
	class_<C, bases<B> >("C", init<int>())
		.def("f", &C::f)
		;
	class_<D>("D", init<C&>())
		.def("check", &D::check)
		;
	class_<G>("G", init<B&>())
		.def("check", &G::check)
		;

	class_<B2Wrap, boost::noncopyable>("B2Pub", init<int>())
		.def("f", &B2Pub::f, &B2Wrap::default_f)
		;

	class_<G2>("G2", init<B2Pub&>())
		.def("check", &G2::check)
		;



	////////////////////////////////////////////////////////////


	class_<STI_Device_AdapterWrap, boost::noncopyable>("STI_Device_AdapterPub", init<ORBManagerPy&, std::string, std::string, unsigned short>())
		.def("defineChannels", &STI_Device_AdapterPub::defineChannels, &STI_Device_AdapterWrap::default_defineChannels)
		.def("execute", &STI_Device_AdapterPub::execute, &STI_Device_AdapterWrap::default_execute)
		.def("addOutputChannel", &STI_Device_AdapterPub::addOutputChannel)
		;
	
	enum_<TValue>("TValue")
		.value("ValueNumber", ValueNumber)
		.value("ValueString", ValueString)
		.value("ValueVector", ValueVector)
		.value("ValueNone", ValueNone)
		;

//	class_<STI_DeviceWrap, bases<STI_Device_Adapter>, boost::noncopyable>("STI_Device_Adapter", init<ORBManagerPy&, std::string, std::string, unsigned short>())
////		.def("deviceMain", pure_virtual(&STI_Device_Adapter::deviceMain))
//		.def("deviceMain", &STI_DeviceWrap::deviceMain)
//		;

	//class_<STI_Device_Adapter, bases<STI_Device>, boost::noncopyable>("STI_Device_Adapter", init<ORBManager*, std::string, std::string, unsigned short>())
	//	;
	
	//class_<STIPy_Device, bases<STI_Device_Adapter> >("STIPy_Device", init<ORBManagerPy&, std::string, std::string, unsigned short>())
	//	.def("getMod", &STIPy_Device::getMod)
	//	;

	//class_<STIPy_Device, boost::noncopyable>("STIPy_Device", init<std::string, std::string, unsigned short>())
	//	.def("getMod", &STIPy_Device::getMod)
	//	;
}
