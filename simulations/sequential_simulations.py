from google_images_download import google_images_download
from sys import stdin
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import time

response = google_images_download.googleimagesdownload()   #class instantiation

def multiple_example_running_time():
    queries = list()
    
    q1 = {"keywords": "art", "limit": None, "silent_mode": True}   #creating list of arguments

    queries.append(q1)

    for args in queries:
        for limit in range(20, 100 + 1, 20):
            args["limit"] = limit
            running_times = list()
            sum_time = 0
            num_iter = 5
            for _ in range(num_iter):
                start = time.time()
                paths = response.download(args)   #passing the arguments to the function
                end = time.time()
                elapsed = end - start
                running_times.append(elapsed)
                sum_time += elapsed
            overall_time = sum_time/num_iter
            print(f"{limit} {overall_time} {np.std(running_times)}")

def single_example_running_time():    
    args = {"keywords": "art", "limit": None, "silent_mode": True}   #creating list of arguments

    args["limit"] = 100
    running_times = list()
    sum_time = 0
    num_iter = 1
    for _ in range(num_iter):
        start = time.time()
        paths = response.download(args)   #passing the arguments to the function
        end = time.time()
        elapsed = end - start
        running_times.append(elapsed)
        sum_time += elapsed
    overall_time = sum_time/num_iter
    print(f"{100} {overall_time} {np.std(running_times)}")


def main():
    single_example_running_time()
    return 0

if __name__ == '__main__':
    main()