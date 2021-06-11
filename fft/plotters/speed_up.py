from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/speed_up.txt", "r")
    lines = f.readlines()
    f.close()
    x_axis = list()
    y_axes = list()
    labels = list()
    sequential_times = list()
    colors = ['r', 'g', 'b', 'y']
    i = 0
    num_iter = int(lines[0])
    i = 1
    for _ in range(num_iter):
        line = lines[i]
        l = line.strip().split()
        x_axis.append(int(l[0]))
        sequential_times.append(float(l[1]))
        i += 1
    while(i < len(lines)):
        line = lines[i]
        if len(line) > 0:
            num_threads, num_iter = list(map(int, line.strip().split()))
            print(num_threads, num_iter)
            y_axis = list()
            i += 1
            k = 0
            for _ in range(num_iter):
                line = lines[i]
                l = line.strip().split()
                t = float(l[1])
                y_axis.append(sequential_times[k]/t)
                i += 1
                k += 1
            y_axes.append(y_axis)
            labels.append(num_threads)
    fig, ax = plt.subplots()
    for i in range(len(y_axes)):
        y_axis = y_axes[i]
        label = labels[i]
        ax.plot(x_axis, y_axis, c=colors[i], label=f"{label} OMP threads")
        # ax.scatter(x_axis, y_axis, c=colors[i])
        
    ax.set_title(f'Speed up')
    ax.set_xlabel(f'Degree of polynomial')
    ax.set_ylabel(f'Speed up')
    ax.grid(True)
    ax.legend()

    plt.show()
    return 0

if __name__ == '__main__':
    main()