from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/isoefficiency.txt", "r")
    lines = f.readlines()
    f.close()
    x_axes = list()
    y_axes = list()
    labels = list()
    colors = ["r", "g", "y", "b"]
    i = 0
    while(i < len(lines)):
        x_axis = list()
        y_axis = list()
        line = lines[i]
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            ts = float(l[1])
            num_iter = int(l[2])
            i += 1
            for _ in range(num_iter):
                line = lines[i]
                l = line.strip().split()
                np = int(l[0])
                tp = float(l[1])
                x_axis.append(np)
                y_axis.append((ts/tp)/np)
                i += 1
            labels.append(n)
            x_axes.append(x_axis)
            y_axes.append(y_axis)

    fig, ax = plt.subplots()
    for i in range(len(x_axes)):
        x_axis = x_axes[i]
        y_axis = y_axes[i]
        label = labels[i]
        ax.plot(x_axis, y_axis, c=colors[i], label=f"{label} degree polynomial")
        ax.scatter(x_axis, y_axis, c=colors[i])
    ax.set_title(f'Isoefficiency')
    ax.set_xlabel(f'Number of processors')
    ax.set_ylabel(f'Efficiency')
    ax.grid(True)
    ax.legend()

    plt.show()
    return 0

if __name__ == '__main__':
    main()