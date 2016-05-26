import numpy as np

file = open("input.txt", 'r')
file.readline() #ignoring the first line

arr = [ map(float,line.split(',')) for line in file ]
X = np.array(arr) #converting list to numpy array
covariance =  np.cov(X.T)
print covariance
np.savetxt('output_py.txt', covariance, fmt = '%.6f')
file.close()