from matplotlib import pyplot as plt
import json

# plt.style.use("ggplot")

# If empty - plots everything from error_data.json, else - plots only data with titles from what_to_plot.
what_to_plot = []

# what_to_plot += ['lagrange: regular']
# what_to_plot += ['lagrange: chebyshev']

# what_to_plot += ['newton: regular']
# what_to_plot += ['newton: chebyshev']

# what_to_plot += ['hermite (one der): regular']
# what_to_plot += ['hermite (one der): chebyshev']

what_to_plot += ['hermite (two ders): regular']
what_to_plot += ['hermite (two ders): chebyshev']

with open('plots/error_data.json') as file:
    data = json.load(file)

if what_to_plot:
    data = dict(filter(lambda elem: elem[0] in what_to_plot, data.items()))


max_y = 0

for title, points in data.items():
    x_points = [x for x, _ in points]
    y_points = [y for _, y in points]
    plt.plot(x_points, y_points, label=title)

    max_y = max(max_y, max(y_points))


plt.title("Errors")

max = min(max_y, 4000)
plt.ylim([-0.05 * max, 1.05 * max])
plt.legend()
plt.tight_layout()
plt.show()