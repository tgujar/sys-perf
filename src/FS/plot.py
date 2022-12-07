import matplotlib.pyplot as plt
from collections import defaultdict
import math

processes = [3, 4, 5, 6, 7, 8, 9]
mean = [26.8, 50.14, 197.6, 846.7, 1740.9, 3331.5, 3694.4]
median = [13.5, 15.16, 62.4, 169.5, 125.4, 265.7, 346.1]
std_dev = [5.85, 7.6, 15, 37.7, 54, 74.6, 75.2]
plt.xlabel('Number of Processes')
plt.ylabel('Time (in micro secs)')
plt.plot(processes, mean, label='mean')
plt.plot(processes, median, label='meadian')
plt.plot(processes, std_dev, label='std_dev')
plt.legend()
plt.show()