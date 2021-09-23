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
    data = readData("q6e_n.csv")
    plt.title("Average Packets in Buffer")
    x = [float(row[0]) for row in data]
    k10 = [float(row[1]) for row in data]
    k25 = [float(row[2]) for row in data]
    k50 = [float(row[3]) for row in data]
    plt.plot(x, k10, '-o', color="black", label="k=10")
    plt.plot(x, k25, '-o', color="blue", label="k=25")
    plt.plot(x, k50, '-o', color="red", label="k=50")
    plt.ylabel("Average Number of Packets")
    plt.xlabel("Utilization of Queue (input rate / service rate)")
    plt.legend(loc="upper left")
    plt.savefig("q6_avgPack.png", bbox_inches="tight")
    plt.close()

def graphPacketLoss():
    data = readData("q6p_loss.csv")
    plt.title("Packets Lost")
    x = [float(row[0]) for row in data]
    k10 = [float(row[1]) for row in data]
    k25 = [float(row[2]) for row in data]
    k50 = [float(row[3]) for row in data]
    plt.plot(x, k10, '-o', color="black", label="k=10")
    plt.plot(x, k25, '-o', color="blue", label="k=25")
    plt.plot(x, k50, '-o', color="red", label="k=50")
    plt.ylabel("Packets Lost")
    plt.xlabel("Utilization of Queue (input rate / service rate)")
    plt.legend(loc="upper left")
    plt.savefig("q6_packLoss.png", bbox_inches="tight")
    plt.close()

graphAvPackets()
graphPacketLoss()
