

/*! \file  main.cpp
    \brief This file contains the main function

    The main function is used to start debug and publick builds of the program

    \authors VladZ
    \date 26.06.2022
    \todo finish documentation using doxygen
*/

#include "func.hpp"

//условная компиляция
#define DEBU

int main (void) {

    #if defined DEBUG
        
        test_equation();
        
    #else 

        NUM_ROOTS num_roots = ZERO_ROOTS ;
        double  a,  b,  c,  x1,  x2      ;
                a = b = c = x1 = x2 = NAN;
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

    

    return 0; }


