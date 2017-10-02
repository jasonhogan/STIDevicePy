#ifndef ORBMANAGERPY_H
#define ORBMANAGERPY_H

#include <ORBManager.h>

class ORBManagerPy
{
public:

	ORBManagerPy();
	
	void run();
	void ORBshutdown();

	ORBManager* orb_manager;
};


#endif

