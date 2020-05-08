import numpy as np

A = np.matrix([[-37, 9, 22], [2, 14, -9], [1, -3, 5],])

B = np.matrix([5.6, -6.5, 22.37]).transpose()

X= np.linalg.solve(A, B)
print(X)