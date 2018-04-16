C = gcc
CPP = g++
CFLAGS = -Wall
# These CPP flags may need adjustment, especially hardcoded paths...
CPPFLAGS = -fPIC -I/usr/include/python2.7 -I../../sti/device/include
ALL = MixedValuePy.o ORBManagerPy.o PartnerDevicePy.o RawEventPy.o STI_Device_Adapter_Pub.o STI_Device_Adapter_Wrapper.o SynchronousEventAdapterPub.o SynchronousEventAdapterPy.o STIDevicePy.o STIPy.so python/STIPy.so

all: $(ALL) 

MixedValuePy.o: MixedValuePy.cpp
	$(CPP) $(CPPFLAGS) -c MixedValuePy.cpp

ORBManagerPy.o: ORBManagerPy.cpp
	$(CPP) $(CPPFLAGS) -c ORBManagerPy.cpp

PartnerDevicePy.o: PartnerDevicePy.cpp
	$(CPP) $(CPPFLAGS) -c PartnerDevicePy.cpp

RawEventPy.o: RawEventPy.cpp
	$(CPP) $(CPPFLAGS) -c RawEventPy.cpp

STI_Device_Adapter_Pub.o: STI_Device_Adapter_Pub.cpp
	$(CPP) $(CPPFLAGS) -c STI_Device_Adapter_Pub.cpp

STI_Device_Adapter_Wrapper.o: STI_Device_Adapter_Wrapper.cpp
	$(CPP) $(CPPFLAGS) -c STI_Device_Adapter_Wrapper.cpp

SynchronousEventAdapterPub.o: SynchronousEventAdapterPub.cpp
	$(CPP) $(CPPFLAGS) -c SynchronousEventAdapterPub.cpp

SynchronousEventAdapterPy.o: SynchronousEventAdapterPy.cpp
	$(CPP) $(CPPFLAGS) -c SynchronousEventAdapterPy.cpp

STIDevicePy.o: STIDevicePy.cpp
	$(CPP) $(CPPFLAGS) -c STIDevicePy.cpp

STIPy.so: MixedValuePy.o ORBManagerPy.o PartnerDevicePy.o RawEventPy.o STI_Device_Adapter_Pub.o STI_Device_Adapter_Wrapper.o SynchronousEventAdapterPub.o SynchronousEventAdapterPy.o STIDevicePy.o
	$(CPP) -shared *.o ../../sti/device/src/libcorba.a -lboost_python -lxerces-c -lomniORB4 -lboost_thread -lboost_filesystem -o STIPy.so

python/STIPy.so:
	(cd python; ln -s ../STIPy.so ./)
	
clean:
	rm $(ALL)


