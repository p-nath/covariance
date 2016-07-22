import numpy as np
import argparse
import sys

def parse_args():
  parser = argparse.ArgumentParser(description="Get input filename.")
  parser.add_argument("-i", action="store", dest="input_filename", 
                      default=None, help="Specify input filename.")
  args = parser.parse_args(sys.argv[1:])
  return args

def main():
  args = parse_args()
  input_filename = args.input_filename
  file = open(input_filename, 'r')
  file.readline() #ignoring the first line

  arr = [ map(float,line.split(',')) for line in file ]
  X = np.array(arr) #converting list to numpy array
  covariance =  np.cov(X.T)
  print "Covariance printed on output_py.txt"
  np.savetxt('output_py.txt', covariance, fmt = '%.6f')
  file.close()

if __name__ == '__main__':
  main()