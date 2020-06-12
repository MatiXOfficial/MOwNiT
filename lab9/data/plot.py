from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import json

with open("results.json") as file:
    data = json.load(file)


N = [100, 1000, 10_000, 50_000]

for title, points in data['lorenz'].items():
    x_data = [x for x, _, _ in points]
    y_data = [y for _, y, _ in points]
    z_data = [z for _, _, z in points]
    for n in N:
        curr_title = title + f', n={n}'

        x = x_data[:n]
        y = y_data[:n]
        z = z_data[:n]

        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')

        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_zlabel('z')

        plt.plot(x, y, z, label=curr_title)
        plt.legend()
        plt.tight_layout()

        folder = title.split(',')[0]
        plt.savefig(f'plots/lorenz/{folder}/{curr_title}.png')
        plt.clf()

for title, points in data['task 4'].items():
    if title[:5] == 'exact':
        continue

    x_data = [x for x, _ in points]
    y_data = [y for _, y in points]
    exact_data = [y for _, y in data['task 4'][f'exact solution, n={len(x_data) - 1}']]

    plt.xlabel('x')
    plt.ylabel('y')

    plt.plot(x_data, y_data, label=title)
    plt.plot(x_data, exact_data, label='exact soultion')
    plt.legend()
    plt.tight_layout()

    plt.savefig(f'plots/task4/{title.split(",")[1][1:]}/{title}.png')
    plt.clf()