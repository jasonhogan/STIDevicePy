import STIPy


orb = STIPy.ORBManager()



class TestPartnerDevice(STIPy.STI_Device):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device.__init__(self, orb, name, ip, module)
        return
    def defineChannels(self):
        self.addInputChannel(0, STIPy.TData.DataDouble)
        self.addInputChannel(1, STIPy.TData.DataString, STIPy.TValue.ValueString)
        self.addOutputChannel(2, STIPy.TValue.ValueString)
        return
    def readChannel(self, channel, valueIn, dataOut):
        #print("in partner")
        print("in partner: " + str(channel) + " value: " + str(valueIn))
        #dataOut.setValue("hello from read channel")
        if (channel == 0) :
            dataOut.setValue(4*valueIn)
        if (channel == 1) :
            dataOut.setValue(str(valueIn) + " partner!")
        #dataOut.setValue([2,4,valueIn])
        #dataOut = 4*valueIn
        return True
    def writeChannel(self, channel, value):
        print("ch: " + str(channel) + " value: " + str(value))
        return True


dev2 = TestPartnerDevice(orb, "Test Partner Device", "localhost", 2)

orb.run()

