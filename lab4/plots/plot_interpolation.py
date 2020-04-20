from matplotlib import pyplot as plt
import json


# If empty - plots everything from interpolation_data.json, else - plots only data with titles from what_to_plot.
what_to_plot = []
what_to_plot += ['interpolated function']

# what_to_plot += ['lagrange: 59 regular nodes'] 
# # what_to_plot += ['lagrange: 20 chebyshev nodes']

# what_to_plot += ['newton: 59 regular nodes'] 
what_to_plot += ['newton: 5 chebyshev nodes'] 

# what_to_plot += ['hermite (one der): 22 regular nodes'] 
# what_to_plot += ['hermite (one der): 50 chebyshev nodes'] 

# what_to_plot += ['hermite (two ders): 50 regular nodes'] 
# what_to_plot += ['hermite (two ders): 30 chebyshev nodes'] 

with open('plots/interpolation_data.json') as file:
    data = json.load(file)

if what_to_plot:
    data = dict(filter(lambda elem: elem[0] in what_to_plot, data.items()))


for i, (title, [nodes, points]) in enumerate(data.items()):
    x_points = [x for x, _ in points]
    y_points = [y for _, y in points]
    plt.plot(x_points, y_points, label=title, color=f'C{i}')

    if nodes:
        x_nodes = [x for x, _ in nodes]
        y_nodes = [y for _, y in nodes]
        plt.scatter(x_nodes, y_nodes, color=f'C{i}')


plt.title("Interpolation")
plt.legend()
plt.tight_layout()
plt.show()