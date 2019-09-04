#!/usr/bin/env python

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from math import pi
# Data for plotting
A, B, a, b = map(float,list(input().split()))
phi = np.arange(A*pi/180, B*pi/180, 0.01)
x = a*phi - b*np.sin(phi)
y = a - b*np.cos(phi)
fig = plt.figure()
plt.plot(x,y)
# 1 + np.sin(2 * np.pi * t)

# fig, ax = plt.subplots()
# ax.plot(phi, s)
#
# ax.set(xlabel='time (s)', ylabel='voltage (mV)',
#        title='About as simple as it gets, folks')
# ax.grid()
#
# fig.savefig("test.png")
plt.show()
