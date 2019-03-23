from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np

#style.use('ggplot')

x,y = np.loadtxt('size_1.csv',unpack=True, delimiter=',')



plt.plot(x,y)


plt.title('Load Factor versus Collisions')
plt.xlabel('Load Factor')
plt.ylabel('Collisions')

plt.show()
