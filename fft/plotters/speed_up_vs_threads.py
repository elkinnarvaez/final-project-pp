from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/strong_scaling.txt", "r")
    lines = f.readlines()
    f.close()
    x_axis = list()
    y_axis = list()
    sequential_time = float(lines[0])
    for i in range(1, len(lines)):
        line = lines[i]
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            t = float(l[1])
            x_axis.append(n)
            y_axis.append(sequential_time/t)
            
    fig, ax = plt.subplots()
    ax.plot(x_axis, y_axis, c='r')
    ax.scatter(x_axis, y_axis, c='r', s=25)
    ax.set_title(f'Speed up vs number of threads')
    ax.set_xlabel(f'Number of processors')
    ax.set_ylabel(f'Speed up')
    ax.grid(True)

    plt.show()
    return 0

if __name__ == '__main__':
    main()