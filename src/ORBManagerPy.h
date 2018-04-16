#ifndef ORBMANAGERPY_H
#define ORBMANAGERPY_H

#include <ORBManager.h>
#include <memory>

class ORBManagerPy
{
public:

	ORBManagerPy();
	
	void run();
	void ORBshutdown();

//	ORBManager* orb_manager;
	std::shared_ptr<ORBManager> orb_manager;
};


#endif

