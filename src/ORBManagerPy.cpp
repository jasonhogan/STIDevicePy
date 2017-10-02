
#include "ORBManagerPy.h"

ORBManagerPy::ORBManagerPy()
{
	int argc = 1;
	char* argv[] = { "" };
	orb_manager = new ORBManager(argc, argv);
}

void ORBManagerPy::run() 
{
	orb_manager->run();
}

void ORBManagerPy::ORBshutdown()
{
	orb_manager->ORBshutdown();
}
