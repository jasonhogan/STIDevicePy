import STIPy

# Mimimum working device. This doesn't do anything interesting but
# it will connect to the STI server.

class SimpleDevice(STIPy.STI_Device):
    def __init__(self, orb, name, ip, module):
        STIPy.STI_Device.__init__(self, orb, name, ip, module)
        return


orb = STIPy.ORBManager()

simpleDevice = SimpleDevice(orb, "Simple", "localhost", 0)

orb.run()
