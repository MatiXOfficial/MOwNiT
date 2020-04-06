import matplotlib.pyplot as plt
import numpy as np

def f1(x):
    return np.cos(x) * np.cosh(x) - 1

x_set = np.arange(-20, 20, 0.1)

plt.plot(x_set, f1(x_set))
plt.ylim(-20, 20)

plt.show()