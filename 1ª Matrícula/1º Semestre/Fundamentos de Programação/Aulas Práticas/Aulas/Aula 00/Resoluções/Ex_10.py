import numpy as np
import matplotlib.pyplot as plt

plt.figure(1)

t = np.arange(0.0, 5.0, 0.1)

plt.subplot(3, 1, 1)
y1 = np.exp(-t)
plt.plot(t, y1, 'b')

plt.subplot(3, 1, 2)
y2 = np.cos(2*np.pi*t)
plt.plot(t, y2, 'ro-')

plt.subplot(3, 1, 3)
y3 = y1 * y2
plt.plot(t, y3, 'go-')

plt.show()
