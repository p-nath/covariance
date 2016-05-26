import numpy as np
from sklearn import datasets

iris = datasets.load_iris()
X = iris.data
y = iris.target
covariance =  np.cov(X.T)
print covariance

np.savetxt('output_numpy.txt', covariance, fmt = '%.6f')

