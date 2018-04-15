#ifndef STI_SCOPEDGILRELEASE_H
#define STI_SCOPEDGILRELEASE_H

#include <boost/python.hpp>

//https://wiki.python.org/moin/boost.python/HowTo

class ScopedGILRelease
{
	// C & D -------------------------------------------------------------------------------------------
public:
	inline ScopedGILRelease()
	{
		m_thread_state = PyEval_SaveThread();
	}

	inline ~ScopedGILRelease()
	{
		PyEval_RestoreThread(m_thread_state);
		m_thread_state = NULL;
	}

private:
	PyThreadState * m_thread_state;
};

class AcquireGIL
{
public:
	inline AcquireGIL() {
		state = PyGILState_Ensure();
	}

	inline ~AcquireGIL() {
		PyGILState_Release(state);
	}
private:
	PyGILState_STATE state;
};


#endif
