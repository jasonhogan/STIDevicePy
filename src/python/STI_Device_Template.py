import STIPy

# Template device.

class MyDevice(STIPy.STI_Device):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device.__init__(self, orb, name, ip, module)
        return
        
    def defineChannels(self):
        # Called during device initialization
        self.addOutputChannel(0, STIPy.TValue.ValueNumber, "my channel name")
        self.addInputChannel(1, STIPy.TData.DataString, STIPy.TValue.ValueString)
        return
    def definePartnerDevices(self):
        # Called during device initialization
        partnerModule = 0
        self.addPartnerDevice("partner alias", "Partner IP", partnerModule, "Partner Name")
        return
    def defineAttributes(self):
        # Called during device initialization
        # addAttribute(<name>, <initial value>, <List of allowed values>)
        self.addAttribute("x", 7)
        self.addAttribute("y", "red", "red, blue, green")
        return
    def updateAttribute(self, key, value):
        # Gets called when the user changes an attribute in the Console.
        # Return True if the change was successful.
        if(key == "x") :
            self.x = int(value)
        return True
    def refreshAttributes(self):
        # Gets called in order to refresh the values of any attributes (i.e, shown in the Console) 
        # that are determined by the Device object's state.  If the Device's state changes,
        # its attributes may need to be refreshed using the newly available data.
        # For example, this is called after each updateAttribute call, since there
        # could be interdependent attributes.
        if(self.x == 9) :
            self.setAttribute("y", "blue")
        return
    def execute(self, args):
        # args is a list of strings. By convention, arg[0] is the device's name
        print ("execute: " + str(args[1]))
        return "success"
    def writeChannel(self, channel, value):
        print("ch: " + str(channel) + " value: " + str(value))
        if(channel == 1):
            #self.partnerDevice("multipler").write(2, value.getValue())
            #tmp = self.partnerDevice("multipler").read(2, value)
            partner=self.partnerDevice("multipler")
            #partner.write(1, value) #works
            temp = partner.read(1, value)
            print("read2: " + str(temp))
        return True
    def readChannel(self, channel, valueIn, dataOut):
        print("in python" + str(channel))
        #print("ch: " + str(channel) + " value: " + str(valueIn))
        #dataOut.setValue("hello from read channel")
        #dataOut.setValue(3*valueIn)
        if(channel == 3) :
            dataOut.setValue([2,4,valueIn])
        if (channel==2):
            partner=self.partnerDevice("multipler")
            partner.read(1, valueIn, dataOut)
            #self.partnerDevice("multipler").read(1, valueIn, dataOut)        
        if(channel == 4) :
            print("In channel==4: "+str(valueIn))
            #mvIn = STIPy.MixedValue()
            #mvIn.setValue(valueIn)
            #mvOut = STIPy.MixedValue()

            ##This works:
            #partner=self.partnerDevice("multipler")
            #partner.read(0, valueIn, dataOut)

            ##This works:
            self.partnerDevice("multipler").read(0, valueIn, dataOut)

            ##This works:
            #mvOut = STIPy.MixedValue()
            #self.partnerDevice("multipler").read(0, valueIn, mvOut)
            #dataOut.setValue(mvOut.getValue())  #this works
            #dataOut.setValue(mvOut)    #this works too

            ##This works:
            #tmp = self.partnerDevice("multipler").read(0, valueIn)
            #print("read2: " + str(tmp))
            #dataOut.setValue(tmp)


        return True
    def getDeviceHelp(self):
        return "This string will display in the Console when the Help button is pressed in this devices pane."
    def parseDeviceEvents(self, eventsIn, eventsOut):
        # This function is called during parsing of a timing file.
        # eventsIn: the list of raw events to this device from the server
        # eventsOut: the derived list of device-specific synchronous events 
        # This function must convert eventsIn->eventsOut by inspecting each event
        # from the server and using the data to generate the appropriate synchronous events.
        # This function also must check that the incoming eventsIn are valid and physically possible.

        for key in eventsIn:
            evt = MyDeviceEvent(key[0], self)   # Using device-specific custom event class, defined below
            eventsOut.append(evt)

        return


#Device-specific event class
class MyDeviceEvent(STIPy.SynchronousEvent):
    def __init__(self, time, device):
        STIPy.SynchronousEvent.__init__(self, time, device)
        self.localtime=time
        return
    def setupEvent(self):
        # Called once, after events have been parsed
        return
    def loadEvent(self):
        # Called evey time before play
        return
    def playEvent(self):
        # Place the actual behavior of the event here. This should "run the hardware."
        return



###############################################################################
# End definitions, begin instantiations


# The ORBManager connects the device to the server.
# It is able to locate the server using the server's IP address and port information stored
# in one of the following place: OS environmental variable, registry key, or *.cfg file.
orb = STIPy.ORBManager()


######### Device instance creation ##########
#
# Syntax: MyDevice(orb, <Device Name>, <Device IP>, <Device Module>)
# <Device IP> is just a string identifier here; it has nothing to do with the
# actual network connection, which is handled by the orb. The IP field can be
# a host name or and ip address or any other string; it is intended to be human readable.
# <Device Module> is a number that is used to distinguish devices on the same IP. It 
# is also arbitary and is analogous to a port number on a computer.

dev = MyDevice(orb, "My Device", "localhost", 0)


 # Start the orb and connect to the server. 
 # This command blocks while the device is alive.
 # This is typically the last command in the file.
orb.run()
