
#include "ORBManagerPy.h"
#include "ScopedGILRelease.h"

#include <memory>

ORBManagerPy::ORBManagerPy()
{
	int argc = 1;
	char* argv[] = { "" };
//	orb_manager = new ORBManager(argc, argv);

	orb_manager = std::make_shared<ORBManager>(argc, argv);
}

void ORBManagerPy::run() 
{
	ScopedGILRelease gil;
	orb_manager->run(false);
}

void ORBManagerPy::ORBshutdown()
{
	orb_manager->ORBshutdown();
}
