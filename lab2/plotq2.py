import csv
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

def readData(fileName):
    data=[]
    with open(fileName, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            data.append(row)
    return data

def graphEfficiency():
    data = readData("efficiency_2.csv")
    plt.title("Efficiency in non-persistent CSMA/CD Protocol")
    x = [float(point) for point in data[0]]
    a7 = [float(point) for point in data[1]]
    a10 = [float(point) for point in data[2]]
    a20 = [float(point) for point in data[3]]
    plt.plot(x, a7, '-o', color="black", label="Arrival rate = 7")
    plt.plot(x, a10, '-o', color="blue", label="Arrival rate = 10")
    plt.plot(x, a20, '-o', color="red", label="Arrival rate = 20")
    plt.ylabel("Efficiency")
    plt.xlabel("Number of nodes")
    plt.legend(loc="upper right")
    plt.savefig("efficiency_2.png", bbox_inches="tight")
    plt.close()

def graphThroughput():
    data = readData("throughput_2.csv")
    plt.title("Throughput in non-persistent CSMA/CD Protocol")
    x = [float(point) for point in data[0]]
    a7 = [float(point) for point in data[1]]
    a10 = [float(point) for point in data[2]]
    a20 = [float(point) for point in data[3]]
    plt.plot(x, a7, '-o', color="black", label="Arrival rate = 7")
    plt.plot(x, a10, '-o', color="blue", label="Arrival rate = 10")
    plt.plot(x, a20, '-o', color="red", label="Arrival rate = 20")
    plt.ylabel("Throughput (Mbps)")
    plt.xlabel("Number of nodes")
    plt.legend(loc="lower right")
    plt.savefig("throughput_2.png", bbox_inches="tight")
    plt.close()

graphEfficiency()
graphThroughput()
