from matplotlib import pyplot as plt
import json


n_arr = [6, 8, 10, 15, 20, 30, 50, 70, 100]

plots = [['true f', 'f'], ['true g', 'g']]

plots += [['true f', 'f algebraic approx m=3, n=' + str(n)] for n in n_arr]
plots += [['true f', 'f algebraic approx m=6, n=' + str(n)] for n in n_arr]

plots += [['true g', 'g algebraic approx m=3, n=' + str(n)] for n in n_arr]
plots += [['true g', 'g algebraic approx m=6, n=' + str(n)] for n in n_arr]

new_n_arr = [(3, [10, 20, 50, 100]), (10, [50, 100]), (50, [150, 300]), (100, [250, 500])]

plots += [['true f', 'f trygonometric approx m=' + str(m) + ', n=' + str(n)] for (m, N) in new_n_arr for n in N]
plots += [['true g', 'g trygonometric approx m=' + str(m) + ', n=' + str(n)] for (m, N) in new_n_arr for n in N]


with open('data/approximation_data.json') as file:
    data = json.load(file)


for what_to_plot in plots:
    plot_data = dict(filter(lambda elem: elem[0] in what_to_plot, data.items()))
    for i, (title, [nodes, points]) in enumerate(plot_data.items()):
        x_points = [x for x, _ in points]
        y_points = [y for _, y in points]
        plt.plot(x_points, y_points, label=title, color=f'C{i}')
        
        if len(nodes) <= 20:
            x_nodes = [x for x, _ in nodes]
            y_nodes = [y for _, y in nodes]
            plt.scatter(x_nodes, y_nodes, color=f'C{i}')

    plt.legend()
    plt.tight_layout()
    # plt.show()
    plt.savefig('data/approximation_plots/' + what_to_plot[1] + '.png', dpi=400)
    plt.clf()