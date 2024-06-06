import numpy as np
from numpy import genfromtxt
from matplotlib import pyplot as plt


def show_voronoi():
    """
    Load and display a Voronoi diagram from a CSV file.

    The CSV file should contain the Voronoi diagram data, where each cell represents a region
    and its value represents a property of that region.

    Returns:
        None
    """
    I = genfromtxt('Voronoi.csv', delimiter=',')
    J = I/np.max(I)
    plt.imshow(J)
    plt.show()

show_voronoi()
