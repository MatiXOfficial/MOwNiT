from matplotlib import pyplot as plt
import json


plots = [[f"eq no {i}, jacobi", f"eq no {i}, gauss_seidel", f"eq no {i}, sor"] for i in range(1, 7)]


with open('data.json') as file:
    data = json.load(file)


for what_to_plot in plots:
    plot_data = dict(filter(lambda elem: elem[0] in what_to_plot, data.items()))
    for i, (title, points) in enumerate(plot_data.items()):
        x_points = [x for x, _ in points]
        y_points = [y for _, y in points]
        plt.plot(x_points, y_points, label=title, color=f'C{i}')

    plt.legend()
    plt.tight_layout()
    # plt.show()
    plt.savefig('plots/' + what_to_plot[0][:7] + '.png', dpi=400)
    plt.clf()