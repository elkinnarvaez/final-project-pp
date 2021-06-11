from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/data_incidence.txt", "r")
    lines = f.readlines()
    f.close()
    x_axis_sim = list()
    y_axis_sim = list()
    x_axis = list()
    y_axis_time = list()
    for line in lines:
        if len(line) > 0:
            l = line.strip().split()
            if(l[0] == "---"):
                x_axis_sim.append(x_axis)
                y_axis_sim.append(y_axis_time)
            else:
                n = int(l[0])
                t = float(l[1])
                x_axis.append(n)
                y_axis_time.append(t)
    
    fig, ax = plt.subplots()
    for i in range(len(x_axis_sim)):
        x_axis = x_axis_sim[i]
        y_axis_time = y_axis_sim[i]
        ax.plot(x_axis, y_axis_time, c='g')
        # ax.scatter(x_axis, y_axis_time, c='r', s=25)
    ax.set_title(f'Running time sequential algorithm')
    ax.set_xlabel(f'N')
    ax.set_ylabel(f'Time (seconds)')
    ax.grid(True)
    plt.show()
    return 0

if __name__ == '__main__':
    main()