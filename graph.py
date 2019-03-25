from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np

style.use('ggplot')

file = open('collisions_summary.txt', 'r')
collisions1 = file.readline()
collisions2 = file.readline()
collisions3 = file.readline()

file.close()

label1 = 'size 1 = 47, Num Collisions = ' + collisions1
label2 = 'size 2 = 100, Num Collisions = ' + collisions2
label3 = 'size 3 = 250, Num Collisions = ' + collisions3

plt.figure(num='Performance of hashtables')

x1,y1 = np.loadtxt('size_1.csv',unpack=True, delimiter=',')
x2,y2 = np.loadtxt('size_2.csv',unpack=True, delimiter=',')
x3,y3 = np.loadtxt('size_3.csv', unpack=True, delimiter=',')


plt.plot(x1,y1, 'g-.', label=label1) 

plt.plot(x2, y2, 'b:', label=label2) 

plt.plot(x3, y3, 'r--', label=label3)

plt.legend(loc='upper left')

plt.title('Chaining & Key Mod Table')
plt.xlabel('Load Factor')
plt.ylabel('Collisions')

plt.show()
