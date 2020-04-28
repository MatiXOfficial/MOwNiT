from matplotlib import pyplot as plt
import json


n_arr = [6, 8, 10, 15, 20, 30, 50, 70, 100]

plots = []

plots += [['f algebraic approx m=3']]
plots += [['f algebraic approx m=6']]
plots += [['f algebraic approx m=3', 'f algebraic approx m=6']]

plots += [['g algebraic approx m=3']]
plots += [['g algebraic approx m=6']]
plots += [['g algebraic approx m=3', 'g algebraic approx m=6']]

plots += [['f trygonometric approx m=3'], ['f trygonometric approx m=10'], ['f trygonometric approx m=50'], ['f trygonometric approx m=100']]
plots += [['f trygonometric approx m=3', 'f trygonometric approx m=10', 'f trygonometric approx m=50', 'f trygonometric approx m=100']]

plots += [['g trygonometric approx m=3'], ['g trygonometric approx m=10'], ['g trygonometric approx m=50'], ['g trygonometric approx m=100']]
plots += [['g trygonometric approx m=3', 'g trygonometric approx m=10', 'g trygonometric approx m=50', 'g trygonometric approx m=100']]

with open('data/error_data.json') as file:
    data = json.load(file)


for what_to_plot in plots:
    plot_data = dict(filter(lambda elem: elem[0] in what_to_plot, data.items()))
    for i, (title, points) in enumerate(plot_data.items()):
        x_points = [x for x, _ in points]
        y_points = [y for _, y in points]
        plt.plot(x_points, y_points, label=title, color=f'C{i}')

    plt.legend()
    plt.tight_layout()

    if len(what_to_plot) == 1:
        title = what_to_plot[0]
    else:
        title = what_to_plot[0] + ' ' + what_to_plot[1]
    plt.savefig('data/error_plots/' + title + '.png', dpi=400)
    plt.clf()