//source code by Harsh Kumar Narula, harsh.narula@iitbombay.org
#pragma once
#include <vector>
#include "MTEngine/MTEngine.hpp"
#include "PrintUtils/PrintUtils.hpp"

enum StageOfLife { NotYetBorn = -1, Grown, Growing };

struct color
/**
 * @brief Represents a color with red, green, and blue components.
 */
{
    double r; /**< The red component of the color. */
    double g; /**< The green component of the color. */
    double b; /**< The blue component of the color. */
};

/**
 * @class Voronoi
 * @brief Represents a Voronoi diagram.
 * 
 * The Voronoi class is used to create and manipulate Voronoi diagrams.
 * It provides methods for nucleation, growth, and color assignment.
 */
class Voronoi
{
private:
    std::vector<double> X; /**< The x-coordinates of the Voronoi diagram points. */
    std::vector<double> Y; /**< The y-coordinates of the Voronoi diagram points. */
    std::vector<StageOfLife> a; /**< The stage of life of each Voronoi diagram point. */
    int m = 1000; /**< The width of the Voronoi diagram. */
    int n = 1000; /**< The height of the Voronoi diagram. */
    int p = 100; /**< The number of Voronoi diagram points. */
    int r = 1; /**< The growth radius for the Voronoi diagram. */
    bool nucleated = false; /**< Flag indicating if the Voronoi diagram has been nucleated. */

    /**
     * @brief Nucleates the Voronoi diagram.
     * @param M A pointer to the MTEngine object used for nucleation.
     */
    void nucleate(MTEngine* M);

public:
    std::vector<int> I; /**< The index of the Voronoi diagram point each pixel belongs to. */
    bool allgrown = false; /**< Flag indicating if all points in the Voronoi diagram have grown. */
    std::vector<color> colors; /**< The colors assigned to each Voronoi diagram point. */

    /**
     * @brief Constructs a Voronoi object with the specified dimensions and number of points.
     * @param m The width of the Voronoi diagram.
     * @param n The height of the Voronoi diagram.
     * @param p The number of Voronoi diagram points.
     */
    Voronoi(int m, int n, int p);

    /**
     * @brief Nucleates the Voronoi diagram with the specified seed.
     * @param myseed The seed used for nucleation.
     */
    void Nucleate(long long myseed);

    /**
     * @brief Nucleates the Voronoi diagram with a random seed.
     */
    void Nucleate();

    /**
     * @brief Grows the Voronoi diagram.
     */
    void grow();

    /**
     * @brief Grows the Voronoi diagram.
     * @deprecated Use the grow() method instead.
     */
    void Grow();


    void WriteDataToCSV(std::string& filename);

    /**
     * @brief Destroys the Voronoi object.
     */
    ~Voronoi();
};

//std::vector<int> Voronoi(int m, int n, int p, long long seed);
//std::vector<int> Voronoi(int m, int n, int p);
//bool Grow(std::vector<int>& I, int& r, int m, int n, int p, std::vector<double>& X, std::vector<double>& Y, std::vector<StageOfLife>& a);
