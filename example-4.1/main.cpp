#include <iostream>
#include <cmath>
#include <armadillo>
#include <vector>
#include <array>

/*
    The governing equation is
    d/dx (k d/dx[phi]) + S = 0
    This problem is no external source, so S = 0
    A and B are the left and right boundaries of the rod respectively
*/

// Define global variables
// Defining variables related to the rod
const double areaCrossSec{std::pow(10, -2)};
const double lengthRod{0.5};
const double T_A{100};
const double T_B{500};
const double k{1000};

int main()
{
    // define number of nodes and find spacing of nodes
    int nNodes{5};
    double deltaX = lengthRod / nNodes;

    /*
        The final set of equations will be of the form Ax = B;
        A => Coefficients of temps at each node
        x => Column vector of temps
        B => The RHS vector of the syst of eqns
    */
    // Define equation matrices
    arma::mat A(nNodes, nNodes, arma::fill::zeros);
    arma::vec T(nNodes, arma::fill::zeros);
    arma::vec B(nNodes, arma::fill::zeros);

    // This variable will appear a lot in the final discretised equation
    double coeff{(k * areaCrossSec) / deltaX};

    // Treat interior points first
    for (int i = 1; i < nNodes - 1; i++)
    {
        /*
            The equations are as follows
            a_P*T_P = a_E*T_E + a_W*T_W
            The matrix is has a pattern for T_2, T_3, T_4, ... T_N-1
            {{boundary node},
            {i-1, i ,i+1, 0s},
            {0, i-1, i, i+1, 0s},
            {0, 0,   i-1, i, i+1, 0s..}
            ...
            {boundary node}}

            Now, a_E = a_W = coeff; a_p = 2*coeff; These things have b[i] = 0, since they are not
            at boundary
        */
        A.at(i, i - 1) = -coeff;
        A.at(i, i) = 2 * coeff;
        A.at(i, i + 1) = -coeff;
        B.at(i) = 0;
    }

    // Treating boundary nodes
    // Left boundary
    A.at(0, 0) = 3 * coeff;
    A.at(0, 1) = -coeff;
    B.at(0) = 200 * T_A;

    // Right boundary
    A.at(A.n_rows - 1, A.n_cols - 1) = 3 * coeff;
    A.at(A.n_rows - 1, A.n_cols - 2) = -coeff;
    B.at(B.n_rows - 1) = 200 * T_B;

    /* With the above statements, we have defined A (in the eqn AT = B) and B
        The T vector is our solution vector, which we get with the solve
    */
    T = arma::solve(A, B);

    // Use these 2 lines to verify A and B matrix
    // std::cout << "The A matrix is - " << A << std::endl;
    // std::cout << "The B amtrix is are - " << B << std::endl;
    std::cout << "The temperatures are - " << T << std::endl;

    // Write out values of T and x coords for plotting
    std::ofstream out("results.csv");

    // Left boundary
    out << 0.0 << "," << T_A << "\n";

    // Interior nodes
    for (int i = 0; i < T.n_elem; i++)
    {
        double x = (i + 0.5) * deltaX;
        out << x << "," << T(i) << "\n";
    }

    // Right boundary
    out << lengthRod << "," << T_B << "\n";
}