

/*! \file  main.cpp
    \brief This file contains the main function

    The main function is used to start debug and public builds of the program
    For debug build, use the file_name argument in the command line which leads to the file with you tests

    \authors VladZ
    \date 26.06.2022
    \todo finish documentation using doxygen
*/

#include "func.hpp"
#define DEBUG

int main (int argc, char *argv[]) {

    #if defined DEBUG
        
        if (argc < 2) {

            printf ("\nPlease enter the test's file name when starting the program\n\n");
            exit(0);

        }

        else {
            
            test_equation(argv[1]);

        }
        
    #else 

        NUM_ROOTS num_roots = ZERO_ROOTS ;
        double  a = NAN,  b = NAN,  c = NAN,  x1 = NAN,  x2 = NAN;

        S_COEFFS coefficients = {a, b, c};

        while (true) {
            greetings ();
            get_coeffs (&coefficients);

            num_roots = square_solver (coefficients, &x1, &x2);

            if (num_roots == ZERO_ROOTS)   { printf ("The equation has no roots !\n")                                      ; }
            if (num_roots == ONE_ROOT  )   { printf ("The equation has one root, which is number %lf\n", x1)               ; }
            if (num_roots == TWO_ROOTS )   { printf ("The equation has two roots, which are numbers %lf and %lf\n", x1, x2); }
            if (num_roots == INF_ROOTS )   { printf ("All real numbers are the solutions to the equation.\n")              ; }

        }

    #endif

    return 0;
    
}


