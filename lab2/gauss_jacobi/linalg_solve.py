import numpy as np

A = np.matrix([[0.0001, -5.0300, 5.8090, 7.8320],
               [2.2660, 1.9950,  1.2120, 8.0080],
               [8.8500, 5.6810,  4.5520, 1.3020],
               [6.7750, -2.253,  2.9080, 3.9700]])

b = np.matrix([9.5740, 7.2190, 5.7300, 6.2910]).transpose()

x = np.linalg.solve(A, b)
print(x, end='\n\n')

A2 = np.matrix([[12, 5, 2, 3],
               [-2, 10, -1, 5],
               [5, 1, 14, -7],
               [3, 2, -8, -16]])

b2 = np.matrix([2, 8, 0, -2]).transpose()

x2 = np.linalg.solve(A2, b2)
print(x2)