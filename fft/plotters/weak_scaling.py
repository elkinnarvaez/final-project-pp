from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/weak_scaling.txt", "r")
    lines = f.readlines()
    f.close()
    x_axis = list()
    y_axis = list()
    for i in range(0, len(lines)):
        line = lines[i]
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            p = int(l[1])
            tp = float(l[2])
            ts = float(l[3])
            x_axis.append(f"({n}, {p})")
            y_axis.append(ts/tp)
            
    fig, ax = plt.subplots()
    ax.plot(x_axis, y_axis, c='r')
    ax.scatter(x_axis, y_axis, c='r', s=25)
    ax.set_title(f'Weak scaling')
    ax.set_xlabel(f'(N, P)')
    ax.set_ylabel(f'Speed up')
    ax.grid(True)

    plt.show()
    return 0

if __name__ == '__main__':
    main()