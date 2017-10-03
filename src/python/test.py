import STIPy

orb = STIPy.ORBManager()



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
        self.addOutputChannel(2, STIPy.TValue.ValueNumber)
        return
        
    def defineAttributes(self):
        self.addAttribute("x",7)
        self.addAttribute("Y","hello","hello, goodbye, why")
        return
    def updateAttribute(self, key, value):
        if(key == "x") :
            self.x = int(value)
        return True
    def refreshAttributes(self):
        if(self.x == 9) :
            self.setAttribute("Y", "why")
        return
    def execute(self, args):
        print ("execute....................." + str(args[1]))
        return "exe!"
    def writeChannel(self, channel, value):
        print("ch: " + str(channel) + " value: " + str(value))
        return True

##########

#simpDev = SimpleDevice(orb,"Simple", "localhost", 0)
dev = TestDevice(orb, "Test Device", "localhost", 256)

#dev.setAttribute("a", "b")

print(STIPy.TValue.ValueNumber.name)

print (STIPy.STI_Device.__doc__)



orb.run()

