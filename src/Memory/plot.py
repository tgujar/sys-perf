import matplotlib.pyplot as plt
from collections import defaultdict
import math

prev_array_size = None
strides = defaultdict(list)
with open('./src/out.txt') as f:
    lines = f.readlines()[2:]
    for line in lines:
        array_size, stride, time = line.split()
        strides[stride].append([array_size, time])

for stride in strides:
    x = [math.log2(int(item[0])) for item in strides[stride]]
    y = [item[1] for item in strides[stride]]
    y = [float(z) / (10**6) for z in y]
    plt.plot(x, y, label=str(stride))
    plt.xticks(x)
plt.axvline(x=15)
plt.text(15.1, 35,'32KB')
plt.axvline(x=20)
plt.text(20.1, 35,'1MB')
plt.axvline(x=25)
plt.text(25.1, 35,'35.1MB')
plt.legend()
plt.show()