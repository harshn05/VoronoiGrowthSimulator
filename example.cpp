#include "Voronoi.hpp"



int main(int argc, char* argv[])
{
    int m = argc > 1 ? std::stoi(argv[1]) : 1000;
    int n = argc > 2 ? std::stoi(argv[2]) : 1000;
    int p = argc > 3 ? std::stoi(argv[3]) : 100;
    Voronoi V(m, n, p);
    V.Nucleate();
    V.Grow();
    std::string A = "Voronoi.csv";
    V.WriteDataToCSV(A);
    return 0;
}