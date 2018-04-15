#!/usr/bin/env python2.7
import STIPy, threading, time
import gc
# Choose what to thread. Similar/same behavior for all interesting cases.
threadORB = False
threadLocal = True

class MyDevice(STIPy.STI_Device):
    def __init__(self, orb, name, ip, module, lock):
        STIPy.STI_Device.__init__(self, orb, name, ip, module)
        self.lock = lock
        self.counter = 0
        return
  
    def defineChannels(self):
        self.addInputChannel(0, STIPy.TData.DataVector,STIPy.TValue.ValueString, "channel")
        return

    def readChannel(self, channel, valueIn, dataOut):
        self.lock.acquire()
        #print("readChannel")
        if dataOut: # We don't pass a dataOut when calling locally...
            print("%s read from STI/ORB" % (self.counter,))
            dataOut.addValue(self.counter)
        else: # ...so, this must be a local read
            print("%s read from Python" % (self.counter,))
        self.counter += 1
        self.lock.release()
        return True
        
# This is what I want to do locally (eventually will be MIDI, joystick, etc.)
def localStuff(dev):
    while True:
        time.sleep(2); # Don't just hammer STI server...
        dev.counter += 1
        dev.readChannel(0, [], [])
#gc.disable()

orb = STIPy.ORBManager()
readlock = threading.Lock();
dev = MyDevice(orb, "PyThreadMWE", "localhost", 0, readlock)

# Can't use if/else here because we want to make sure to run threads before
# blocking!

myt = threading.Thread(target=localStuff, args=(dev,))
if threadLocal:
	print("Threading off our local stuff.")


if not threadORB:
    orb.run()
    #print("Orb started")
    #raw_input("Paused ...")
    myt.start()
    myt.join()

if threadORB:
	print("Threading off ORB.")
	orbt = threading.Thread(target=orb.run)
	orbt.start()



if not threadLocal:
	localStuff(dev)

raw_input("Paused ...")
myt.join()
orb.run()