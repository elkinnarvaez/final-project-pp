from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/parallel_running_time.txt", "r")
    lines = f.readlines()
    f.close()
    x_axes = list()
    y_axes = list()
    labels = list()
    colors = ['r', 'g', 'b', 'y']
    i = 0
    while(i < len(lines)):
        line = lines[i]
        if len(line) > 0:
            num_threads, num_iter = list(map(int, line.strip().split()))
            x_axis = list()
            y_axis = list()
            i += 1
            for _ in range(num_iter):
                line = lines[i]
                l = line.strip().split()
                n = int(l[0])
                t = float(l[1])
                x_axis.append(n)
                y_axis.append(t)
                i += 1
            x_axes.append(x_axis)
            y_axes.append(y_axis)
            labels.append(num_threads)
    
            
    fig, ax = plt.subplots()
    for i in range(len(x_axes)):
        x_axis = x_axes[i]
        y_axis = y_axes[i]
        label = labels[i]
        ax.plot(x_axis, y_axis, c=colors[i], label=f"{label} OMP threads")
        ax.scatter(x_axis, y_axis, c=colors[i])
    ax.set_title(f'Parallel running time')
    ax.set_xlabel(f'Degree of polynomial')
    ax.set_ylabel(f'Time (seconds)')
    ax.grid(True)
    ax.legend()

    plt.show()
    return 0

if __name__ == '__main__':
    main()