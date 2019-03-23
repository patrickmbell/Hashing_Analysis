from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np


style.use('ggplot')

plt.figure(num='Performance of hashtables')

x1,y1 = np.loadtxt('size_1.csv',unpack=True, delimiter=',')
x2,y2 = np.loadtxt('size_2.csv',unpack=True, delimiter=',')
x3,y3 = np.loadtxt('size_3.csv', unpack=True, delimiter=',')

plt.plot(x1,y1, 'g-.', label='size 1 = <size>') 

plt.plot(x2, y2, 'b:', label='size 2 = <size>') 

plt.plot(x3, y3, 'r--', label='size 3 = <size>')

plt.legend(loc='upper left')

plt.title('Chaining & Key Mod Table')
plt.xlabel('Load Factor')
plt.ylabel('Collisions')

plt.show()
