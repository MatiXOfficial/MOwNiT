from matplotlib import pyplot as plt
import matplotlib.dates
import json
import numpy as np

# task 3
with open('results.json') as file:
    data = json.load(file)

x_all = []
y_all = []

for title, times_data in data['times'].items():
    x_data = [x for x, _ in data['times'][title]]
    x_all += [x_data]
    y_data = [y for _, y in data['times'][title]]
    y_all += [y_data]
    plt.plot(x_data, y_data, marker='o')

    plt.xlabel('size')
    plt.ylabel('time [s]')
    plt.title(title)

    plt.savefig(f'plots/task3/{title}')
    plt.clf()

plt.plot(x_all[0], y_all[0], label='DFT')
plt.plot(x_all[1], y_all[1], label='FFT')

plt.xlabel('size')
plt.ylabel('time [s]')
plt.title(title)
plt.legend()

plt.savefig(f'plots/task3/both')
plt.clf()

# task 4
x_data = [x for x, _ in data['summer']]
y_data = [y for _, y in data['summer']]
plt.plot(x_data, y_data)

plt.xlabel('frequency [1/(1 year)]')
plt.ylabel('magnitude')
plt.savefig(f'plots/task4/summer')

plt.xlim(0, 3)
plt.ylim(-40, 4000)
plt.savefig(f'plots/task4/summer_close')
plt.clf()