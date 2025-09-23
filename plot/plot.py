import matplotlib.pyplot
import csv
import numpy as np
import os

FILE_NAME_EXPLICIT = 'r2_explicit.csv'
FILE_NAME_MONTECARLO = 'r2.csv'

filedir = os.path.dirname(__file__)
parentdir = os.path.dirname(filedir)
csvexplicitdir = os.path.join(parentdir, 'build', 'output', FILE_NAME_EXPLICIT)
csvmontecarlodir = os.path.join(parentdir, 'build', 'output', FILE_NAME_MONTECARLO)

print(csvexplicitdir)

with open(csvexplicitdir, 'r') as csvfile:
    reader = csv.reader(csvfile)
    data_explicit = list(reader)

with open(csvmontecarlodir, 'r') as csvfile:
    reader = csv.reader(csvfile)
    data_montecarlo = list(reader)

data_explicit = data_explicit[1:]

data_montecarlo = data_montecarlo[1:]

timeSteps_explicit = [int(row[0]) for row in data_explicit]
r2Values_explicit = [float(row[1]) for row in data_explicit]

timeSteps_montecarlo = [int(row[0]) for row in data_montecarlo]
r2Values_montecarlo = [float(row[1]) for row in data_montecarlo]

matplotlib.pyplot.plot(timeSteps_explicit, r2Values_explicit)
matplotlib.pyplot.plot(timeSteps_montecarlo, r2Values_montecarlo)
matplotlib.pyplot.xlabel('Time Step')
matplotlib.pyplot.ylabel('r2 Value')
matplotlib.pyplot.show()
