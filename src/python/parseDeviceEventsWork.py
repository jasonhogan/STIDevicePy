

class RawEvent:
    def __init__(self, time):
        self.time = time
        return
    def getTime(self) :
        return self.time


evt = RawEvent(33)



print(eventsIn[3][0].getTime())

print(eventsIn[1][1].getTime())

for key in eventsIn:
    print key, 'corresponds to', eventsIn[key][0].getTime()


class SynchronousEvent:
    def playEvent(self):
        print
        