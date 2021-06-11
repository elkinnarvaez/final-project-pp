from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

def main():
    f = open("data/sequential_running_time.txt", "r")
    lines = f.readlines()
    f.close()
    x_axis = list()
    y_axis_time = list()
    y_axis_std = list()
    for line in lines:
        if len(line) > 0:
            l = line.strip().split()
            n = int(l[0])
            t = float(l[1])
            num_iter = int(l[2])
            running_times = list()
            for i in range(num_iter):
                running_times.append(float(l[i + 3]))
            std = np.std(running_times)
            x_axis.append(n)
            y_axis_time.append(t)
            y_axis_std.append(std)
            print(f"{n} & {round(t, 6)} & {round(std, 6)}\\")
            print("\hline")
            
    fig, ax = plt.subplots()
    ax.plot(x_axis, y_axis_time, c='r')
    ax.scatter(x_axis, y_axis_time, c='r', s=25)
    ax.set_title(f'Running time sequential algorithm')
    ax.set_xlabel(f'N')
    ax.set_ylabel(f'Time (seconds)')
    ax.grid(True)

    fig1, ax1 = plt.subplots()
    ax1.plot(x_axis, y_axis_std, c='r')
    ax1.scatter(x_axis, y_axis_std, c='r', s=25)
    ax1.set_title(f'Standard deviation')
    ax1.set_xlabel(f'N')
    ax1.set_ylabel(f'Standard deviation')
    ax1.grid(True)

    plt.show()
    return 0

if __name__ == '__main__':
    main()