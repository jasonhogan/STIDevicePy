import STIPy

orb = STIPy.ORBManagerPy()

class SimpleDevice(STIPy.STI_Device_AdapterPub):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device_AdapterPub.__init__(self, orb, name, ip, module)
        return

class TestDevice(STIPy.STI_Device_AdapterPub):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device_AdapterPub.__init__(self, orb, name, ip, module)
        return
        
    def defineChannels(self):
        print ("define channels...........5.........................................")
        self.addOutputChannel(0,STIPy.TValue.ValueNumber,"out")
        self.addOutputChannel(1,STIPy.TValue.ValueString,"out2")
        return
        
    def execute(self, args):
        print ("execute....................." + str(args[1]))
        return "exe!"

##########

#simpDev = SimpleDevice(orb,"Simple", "localhost", 0)
dev = TestDevice(orb, "Test Device", "localhost", 256)

print(STIPy.TValue.ValueNumber.name)

orb.run()

