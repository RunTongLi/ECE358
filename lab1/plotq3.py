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

def graphAvPackets():
    data = readData("q3e_n.csv")
    plt.title("Average Packets in Buffer")
    y = [float(dat[0]) for dat in data]
    x = [float(dat[1]) for dat in data]
    plt.ylabel("Number of Packets")
    plt.xlabel("Utilization of Queue (input rate / service rate)")
    plt.plot(x, y, "-o", color="black")
    plt.savefig("q3_avgPack.png", bbox_inches="tight")
    plt.close()

def graphIdleProportion():
    data = readData("q3p_idle.csv")
    plt.title("Proportion of time System is idle")
    y = [float(dat[0]) for dat in data]
    x = [float(dat[1]) for dat in data]
    plt.ylabel("Proportion Idle (out of 1)")
    plt.xlabel("Utilization of Queue (input rate / service rate)")
    plt.plot(x, y, "-o", color="black")
    plt.savefig("q3_idleProportion.png", bbox_inches="tight")
    plt.close()

graphAvPackets()
graphIdleProportion()
