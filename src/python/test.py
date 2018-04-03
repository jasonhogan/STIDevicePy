#!/usr/bin/env python2.7 
import STIPy
import collections
from os import popen as sh

orb = STIPy.ORBManager()


class TestEvent(STIPy.SynchronousEvent):
    def __init__(self, time, device):
        STIPy.SynchronousEvent.__init__(self, time, device)
        self.localtime=time
        return
    def __deinit__(self):
        print("TestEvent is destroyed: " + str(self.localtime))
        return
    def setupEvent(self):
        print("lsdfjasldkjf")
        return
    def loadEvent(self):
        print("load")
        return
    def playEvent(self):
        print("play")
        return


class SimpleDevice(STIPy.STI_Device):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device.__init__(self, orb, name, ip, module)
        return

class TestDevice(STIPy.STI_Device):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device.__init__(self, orb, name, ip, module)
        return
        
    def defineChannels(self):
        print ("define channels...........5.........................................")
        self.addOutputChannel(0,STIPy.TValue.ValueNumber,"out")
        self.addOutputChannel(1,STIPy.TValue.ValueString,"out2")
        self.addOutputChannel(2, STIPy.TValue.ValueString)
        # self.addInputChannel(3, STIPy.TData.DataDouble)
        # self.addInputChannel(3, STIPy.TData.DataString)
        self.addInputChannel(3, STIPy.TData.DataVector)
        print("Defining this channel...")
        self.addInputChannel(4, STIPy.TData.DataVector,"MassiveSecurityBreach")
        # self.addInputChannel(3, STIPy.TData.DataVector, STIPy.TValue.ValueVector)   # Not working; can't use vector value currently...

        return 
        
    def defineAttributes(self):
        self.addAttribute("x",7)
        self.addAttribute("Y","hello","hello, goodbye, why")
        return
    def updateAttribute(self, key, value):
        # Gets called when the user changes an attribute in the Console.
        # Return True if the change was successful.
        if(key == "x") :
            self.x = int(value)
        return True
    def refreshAttributes(self):
        # Gets called in order to refresh the values of any attributes that are
        # determined by the Device object's state.  If the Device's state changes,
        # its attributes may need to be refreshed using newly available data.
        # For example, this is called after each updateAttribute call, since there
        # could be interdependent attributes.
        if(self.x == 9) :
            self.setAttribute("Y", "why")
        return
    def execute(self, args):
        print ("execute....................." + str(args[1]))
        return "exe!"
    def writeChannel(self, channel, value):
        print("ch: " + str(channel) + " value: " + str(value))
        return True
    def readChannel(self, channel, valueIn, dataOut):
        print("in python")

        # Run command and output device. EXTREMELY UNSAFE; for testing only!
        if channel == 4:
            dataOut.setValue(sh(valueIn).read());
            return True
        #print("ch: " + str(channel) + " value: " + str(valueIn))
        #dataOut.setValue("hello from read channel")
        #dataOut.setValue(3*valueIn)
        dataOut.setValue([2,4,valueIn])
        return True
    def getDeviceHelp(self):
        return "python help!"
    def parseDeviceEvents(self, eventsIn, eventsOut):
        print("Back in python!")

        #od = collections.OrderedDict(sorted(eventsIn.items()))
        #for key in od:
        #    print key, 'corresponds to', od[key][0].time()
        
        for key in eventsIn:
            #print key, 'corresponds to', eventsIn[key][0].time()
            print key
        
        for key in eventsIn:
            #evt = TestEvent(eventsIn[key][0].time(), self)
            #evt = TestEvent(key[1][0].time(), self)
            print(key[0])
            evt = TestEvent(key[0], self)

            #evt.setupEvent()
            #print(evt.localtime)
            eventsOut.append(evt)
            #eventsOut.append(3)  ## this breaks it!

        #evt = STIPy.SynchronousEvent(20, self)
        #evt = TestEvent(20, self)
        #eventsOut.append(evt)
        return


##########

#simpDev = SimpleDevice(orb,"Simple", "localhost", 0)
dev = TestDevice(orb, "Test Device", "localhost", 256)

#dev.setAttribute("a", "b")

mv = STIPy.MixedValue()
mv.setValue("hello")

print(STIPy.TValue.ValueNumber.name)

print (STIPy.STI_Device.__doc__)

orb.run()
