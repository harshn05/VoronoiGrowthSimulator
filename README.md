# VoronoiGrowthSimulator

## Voronoi.cpp

This project simulates a Voronoi diagram. A Voronoi diagram is a partitioning of a plane into regions based on distance to points in a specific subset of the plane. In this context, it uses circular growth of nuclei. The Voronoi class represents the diagram itself, with methods for nucleating the seed points followed by their growth in a circular fashion.

## example.cpp

This C++ code is a main function that creates a Voronoi diagram, performs some operations on it, and then writes the data to a CSV file. The program starts by checking the command-line arguments. If there are enough arguments, it converts them to integers and assigns them to the variables `m`, `n`, and `p`. If there aren't enough arguments, it assigns default values of 1000, 1000, and 100 respectively. Next, it creates an instance of a `Voronoi` class, `V`, using `m`, `n`, and `p` as parameters. The `Voronoi` class represents a Voronoi diagram, which is a partitioning of a plane into regions based on distance to points in a specific subset of the plane. Then, it calls the `Nucleate` and `Grow` methods on the `Voronoi` instance. These methods involve initializing and then expanding or populating the Voronoi diagram in isotropic manner. After that, it creates a `std::string` named `A` and assigns it the value "Voronoi.csv". This is the name of the file that the program will write data to. The `WriteDataToCSV` method is then called on the `Voronoi` instance, with `A` as the argument. This method writes the pixelated Voronoi diagram to a CSV file named "Voronoi.csv".

## showvoronoi.py


showvoronoi.py requires the following Python packages:

numpy: This package is used for numerical computations in Python. It is imported at the beginning of the script and used to load data from a CSV file and perform a calculation.

matplotlib: This package is used for creating static, animated, and interactive visualizations in Python. It is imported at the beginning of the script and used to display the Voronoi diagram.

These packages can be installed using pip, Python's package installer. Open the terminal and type the following commands:

```
pip install numpy
pip install matplotlib
```

This Python script, showvoronoi.py, is designed to load and display a Voronoi diagram from a CSV file using the numpy and matplotlib libraries. The script starts by importing the necessary libraries: numpy for numerical operations and data manipulation, and matplotlib.pyplot for data visualization. The function show_voronoi() is defined to load and display the Voronoi diagram. Inside this function, the genfromtxt function from numpy is used to load data from the 'Voronoi.csv' file, with comma as the delimiter. The loaded data is stored in the variable I. Next, the data in I is normalized by dividing it by the maximum value in I. This is done to scale the values between 0 and 1. The normalized data is stored in the variable J. The imshow function from matplotlib.pyplot is then used to display an image of the normalized data. The show function is called to display the plot.

## How to run the program ?

Got to the build directory and run the following:
VoronoiGrowthSimulator.exe 2000 2000 10 & python showvoronoi.py

Harsh Kumar Narula
<harsh.narula@iitbombay.org>
