import matplotlib.pyplot
import csv
import numpy as np

with open('build/output/r2.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    data = list(reader)

header = data[0]
data = data[1:]

timeSteps = [int(row[0]) for row in data]
r2Values = [float(row[1]) for row in data]
deltaTs = [float(row[2]) for row in data]

matplotlib.pyplot.plot(timeSteps, r2Values)
matplotlib.pyplot.xlabel('Time Step')
matplotlib.pyplot.ylabel('r2 Value')
matplotlib.pyplot.show()
