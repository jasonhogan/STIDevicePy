
import os

print (os.getcwd())

import testDLL

print (testDLL.greet())

planet = testDLL.World("Hi")

print (planet.greet())
planet.set("bye")
print (planet.greet())

import STIPy

#at = STIPy.Attribute()

#at.setValue("key")

#print (at.value())

orb = STIPy.ORBManagerPy()

my = STIPy.MyClass(55)
#print (my.x)

dev = STIPy.STIPy_Device_Test(my, "Test Device", "localhost", 5)
print (dev.getMod())
print (dev.my.x)

dev = STIPy.STIPy_Device_Test2(orb, "Test Device", "localhost", 256)
print (dev.getMod())

c = STIPy.C(100)
print(c.f())

#class CChild(STIPy.C):
#    #def __init__(self, x):
#    #    super(x)
#    def g() :
#        return 6
#    def f(self) :
#        print ("In CChild")
#        return 2*super(CChild,self).f()

#print("Test C Child:")
#cc = CChild(512)
#print (cc.f())

d = STIPy.D(c)

print(d.check())

#d2 = STIPy.D(cc)
#print(d2.check())
##orb.run()

class Derived(STIPy.B):
    def f(self):
        return 2*super(Derived,self).f()

print("Testing Derived:")
b2 = STIPy.B(5)
derived = Derived(60)

g = STIPy.G(derived)
print(g.check())


#print(b2.f())

#def printB(b3):
#    print(b3.f())

#printB(b2)
#printB(derived)


class Derived2(STIPy.B2Pub):
    def f(self):
        return 2*super(Derived2,self).f()

print("Testing Derived2:")
b22 = STIPy.B2Pub(18)
derived2 = Derived2(77)

g2 = STIPy.G2(derived2)
print(g2.check())


hold = STIPy.Holder(17)
wt = STIPy.WrapTaker(hold)


dev = STIPy.STI_Device_AdapterPub(orb, "Test Device", "localhost", 256)
#print (dev.getMod())


print(STIPy.TValue.ValueNumber.name)

orb.run()

