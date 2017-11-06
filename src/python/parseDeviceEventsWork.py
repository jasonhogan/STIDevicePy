

class RawEvent(object):
    def __init__(self, time):
        self.time = time
        return
    def __del__(self):
        print("RawEvent is destroyed: " + str(self.time))
        return
    def getTime(self) :
        return self.time


evt = RawEvent(33)

eventsIn = {1 : [evt, RawEvent(35), RawEvent(36)], 3:[RawEvent(56)]}

print(eventsIn[3][0].getTime())

print(eventsIn[1][1].getTime())

for key in eventsIn:
    print key, 'corresponds to', eventsIn[key][0].getTime()


        
evt2 = RawEvent(2)



class FooType(object):
    def __init__(self, id):
        self.id = id
        print self.id, 'born'

    def __del__(self):
        print self.id, 'died'


ft = FooType(1)

