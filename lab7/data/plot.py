from matplotlib import pyplot as plt
import json


with open('results_data.json') as file:
    data = json.load(file)

for title, f_data in data.items():
    for approx_data in f_data:
        if approx_data['title'] == 'monte carlo':
            continue
        x_points = [x for x, _ in approx_data['errors']]
        y_points = [y for _, y in approx_data['errors']]
        plt.plot(x_points, y_points, label=approx_data['title'])

    plt.xlabel(f_data[0]['x_title'])
    plt.ylabel('error')
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.savefig('plots/' + title + '.png', dpi=300)
    plt.clf()

    for approx_data in f_data:
        if approx_data['title'] == 'monte carlo':
            continue
        x_points = [x for x, _ in approx_data['errors']]
        y_points = [y for _, y in approx_data['errors']]
        plt.plot(x_points, y_points, label=approx_data['title'])


    plt.ylim(-f_data[0]['errors'][4][1] / 10, f_data[0]['errors'][4][1])
    plt.xlabel(f_data[0]['x_title'])
    plt.ylabel('error')
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.savefig('plots/' + title + '2.png', dpi=300)
    plt.clf()


    x_points = [x for x, _ in f_data[3]['errors']]
    y_points = [y for _, y in f_data[3]['errors']]
    plt.plot(x_points, y_points, label=f_data[3]['title'])

    plt.xlabel(f_data[3]['x_title'])
    plt.ylabel('error')
    plt.title(title + ' monte carlo')
    plt.tight_layout()
    plt.savefig('plots/' + title + ' monte carlo.png', dpi=300)
    plt.clf()