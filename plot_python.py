#import libraries
from matplotlib.pyplot import *
from numpy import *
from scipy import *

#open binary file
f = open("debug013.dat", "rb")

#convert binary file into array
y = fromfile(f, dtype=int16, count=-1)
print(y)

#plot array
plot(y)
xlabel('time (50ms steps)')
ylabel('SensorValue(encoder)')
title('Encoder Value vs. time')
show()
