

/*! \file  func.cpp
    \brief This file contains the realizations of all the functions used in the project

    The main function for the public use is square_solver, for debug use you can utilize the test_equation function

    \authors VladZ
    \date 26.06.2022
    \todo finish documentation using doxygen
*/

//arcc arcv
#include "func.hpp"

NUM_ROOTS square_solver (S_COEFFS coefficients, double* px1, double* px2) {

    double a = coefficients.a;
    double b = coefficients.b;
    double c = coefficients.c;

    assert ( isfinite(a) && isfinite(b) && isfinite(c));
    assert ( !(px1 == nullptr || px2 == nullptr)      );

    if (double_equal (a, 0)) {           return            linear      (construct_l_coeffs (b, c), px1)      ; }

    if (double_equal (b, 0)) {           return            easy_square (construct_l_coeffs (a, c), px1, px2) ; }

    if (double_equal (c, 0)) { *px1 = 0; return NUM_ROOTS (linear      (construct_l_coeffs (a, b), px2) + 1) ; }

    return square (coefficients, px1, px2);
    
}

NUM_ROOTS linear (L_COEFFS coefficients, double* px) {

    double a = coefficients.a;
    double b = coefficients.b;

    assert (isfinite(a) && isfinite(b));
    assert (!(px == nullptr));

    if (double_equal (a, 0)) {

            if (double_equal (b, 0)) {  return INF_ROOTS ; }
            else                     {  return ZERO_ROOTS; }
        }

    if (double_equal (b, 0)) { *px = 0; return ONE_ROOT  ; }

    *px = -b / a;                       return ONE_ROOT  ;
    
}

NUM_ROOTS square (S_COEFFS coefficients, double* px1, double* px2) {

    double a = coefficients.a;
    double b = coefficients.b;
    double c = coefficients.c;

    assert ( (isfinite(a) && isfinite(b) && isfinite(c)) );
    assert ( (px1 == nullptr || px2 == nullptr) == false );

    double d = b*b - 4*a*c;

    switch ( double_compare(d, 0) ) {

        case MORE:  { *px1 = ( sqrt(d) - b ) / ( 2 * a ); *px2 = ( -sqrt(d) - b ) / ( 2 * a) ; return TWO_ROOTS ; }
        case EQUAL: { *px1 = -b / ( 2 * a );                                                   return ONE_ROOT  ; }
        case LESS:  {                                                                          return ZERO_ROOTS; }
        default  :  {                                                                          return NAN_ROOTS ; }

    }

}

NUM_ROOTS easy_square (L_COEFFS coefficients, double* px1, double* px2) {

    double a = coefficients.a;
    double b = coefficients.b;

    assert (isfinite(a) && isfinite(b));
    assert (!(px1 == nullptr || px2 == nullptr));

    switch (double_compare (b, 0)) {

        case MORE :           return ZERO_ROOTS;
        case EQUAL: *px1 = 0; return ONE_ROOT  ;
        case LESS : {
            double  root = sqrt (-b / a);
            *px1 =  root;
            *px2 = -root;
                              return TWO_ROOTS ; }
        default   :           return NAN_ROOTS ;

    }

}

void greetings(void) {

    printf ("\n\nPlease, enter the coefficients for the equation ax^2 + bx + c = 0 or \"%c\" to exit\n", EXIT_SIMBOL);

}

void get_coeffs (S_COEFFS *p_coefficients) {

    double *pa = &(p_coefficients->a);
    double *pb = &(p_coefficients->b);
    double *pc = &(p_coefficients->c);

    char skip = 0;

    while (scanf ("%lg%lg%lg", pa, pb, pc) != 3) {
        
        char          exit_str ;
        scanf ("%s", &exit_str);
        if           (exit_str == EXIT_SIMBOL) { printf ("Goodbye!\n\n"); exit(0); }

        printf     ("Please, enter 3 real numbers or \"%c\" to exit :/\n\n\n", EXIT_SIMBOL);

        while ((skip = getchar()) != '\n') { continue; }

    }

    while ((skip = getchar()) != '\n') {

        if (skip != ' ' && skip != '\t') {

            while ((skip = getchar()) != '\n') { continue; }
            printf ("Please, enter 3 real numbers or \"%c\" to exit :/\n\n\n", EXIT_SIMBOL);
            get_coeffs (p_coefficients);
            break;
        
        }
    
    }

}

DOUBLE_COMPARE_RESULT double_compare (double first, double second) {

    assert ( (isnan(first) || isnan(second)) == false);

    if      (fabs (first - second) < EPSILON) { return EQUAL; }

    else if (first > second)                  { return MORE ; }

    else  /*(first < second)*/                { return LESS ; }

}

bool double_equal (double first, double second) {

    assert ( (isnan(first) || isnan(second)) == false);

    if (fabs (first - second) < EPSILON) { return true ; }
    else                                 { return false; }

}

bool test_equation (char *file_name) {

    int    num_tests    = 0;
    size_t tests_passed = 0;
    FILE* tests_file = fopen        (file_name, "r");

    if (tests_file == nullptr) {

        printf ("\nCan't find the tests file. Maybe you misspelled it's name?\n\n");
        exit(0);

    }

    num_tests        = get_file_len (file_name)     ;

    S_COEFFS  tests         [num_tests]    {};
    NUM_ROOTS num_solutions [num_tests]    {};
    double    solutions     [num_tests][2] {};

    for (size_t i = 0; i < num_tests; i++) {

        fscanf(tests_file, "%lg%lg%lg%zd", &tests[i].a, &tests[i].b, &tests[i].c, &num_solutions[i]);
        switch (num_solutions[i]) {

            case ZERO_ROOTS: break;
            case ONE_ROOT  : fscanf(tests_file, "%lg",    &solutions[i][0]);                   break;
            case TWO_ROOTS : fscanf(tests_file, "%lg%lg", &solutions[i][0], &solutions[i][1]); break;
            case INF_ROOTS : break;

        }
    
    }

    fclose(tests_file);

    printf ("\n\nWelcome to the test_equation module!\n");
    printf ("Amount of tests: %d\n\n", num_tests)        ;

    for (size_t i = 0; i<num_tests; i++) { tests_passed += one_test (i, tests[i], num_solutions[i], solutions[i]); }

    if (tests_passed == num_tests) { printf (  "All %d tests passed!\n\n",               num_tests); }
    else                           { printf ("%d of %d tests passed.\n\n", tests_passed, num_tests); }

    return tests_passed;
    
}

bool one_test (size_t num_test, S_COEFFS coefficients, NUM_ROOTS num_solutions, double* solutions) {

    double    x1    = NAN         ;
    double    x2    = NAN         ;
    NUM_ROOTS num_x = ZERO_ROOTS  ;

    num_x = square_solver (coefficients, &x1, &x2);

    if (num_x != num_solutions) { error_message (num_test, coefficients, num_solutions, solutions, num_x, x1, x2);                   return false; }

    switch (num_x) {

        case ZERO_ROOTS:

            if (isnan (x1) && isnan (x2)) { success_message (num_test);                                                              return true ; } 
            else                          { error_message   (num_test, coefficients, num_solutions, solutions, num_x, x1, x2);       return false; }
        
        case ONE_ROOT: 
            
            if (x1 == *solutions && isnan (x2)) { success_message (num_test);                                                        return true ; } 
            else                                { error_message   (num_test, coefficients, num_solutions, solutions, num_x, x1, x2); return false; }

        case TWO_ROOTS:
            
            if (x1 == *solutions && x2 == *(solutions+1) || x2 == *solutions && x1 == *(solutions+1)) { success_message (num_test);  return true ; }
            else                                 { error_message (num_test, coefficients, num_solutions, solutions, num_x, x1, x2);  return false; }
        
        case INF_ROOTS:

            if (isnan (x1) && isnan (x2)) { success_message (num_test);                                                              return true ; } 
            else                          { error_message   (num_test, coefficients, num_solutions, solutions, num_x, x1, x2);       return false; }
        
        default: 

            printf ("Test %d: entered incorrect amount of solutions", num_test);                                                     return false;

    }

}

void error_message (size_t num_test, S_COEFFS coefficients, NUM_ROOTS num_solutions, double* solutions, NUM_ROOTS num_x, double x1, double x2) {

    double a = coefficients.a;
    double b = coefficients.b;
    double c = coefficients.c;

    printf ("ERR in test %d while solving equation ", num_test+1);
    if (a == 1) printf("x^2"); else if (a == -1) printf("-x^2");   else printf("%lgx^2",   a);
    if (b == 1) printf("+x");  else if (b == -1) printf("-x");     else printf("%+lgx",    b);
    if (c == 0) printf("=0\n");                                    else printf("%+lg=0\n", c);
    
    switch (num_solutions) {
        case ZERO_ROOTS: printf ("Expected: no solutions and x1 = NAN, x2 = NAN\n");                      break;
        case ONE_ROOT  : printf ("Expected: one solution, %lg and x2 = NAN\n", *solutions);               break;
        case TWO_ROOTS : printf ("Expected: two solutions, %lg and %lg\n", *solutions, *(solutions+1) );  break;
        case INF_ROOTS : printf ("Expected: whole number line as a solution and x1 = NAN, x2 = NAN\n");   break;
    }

    switch (num_x) {
        case ZERO_ROOTS: printf ("Got: no solutions; x1 = %lg, x2 = %lg\n\n"), x1, x2;                    break;
        case ONE_ROOT  : printf ("Got: one solution, %lg; x2 = %lg\n\n", x1, x2);                         break;
        case TWO_ROOTS : printf ("Got: two solutions, %lg and %lg\n\n", x1, x2 );                         break;
        case INF_ROOTS : printf ("Got: whole number line as a solution; x1 = %lg, x2 = %lg\n\n", x1, x2); break;
    }

}

void success_message (size_t num_test) {

    printf ("Test %d - success\n\n", num_test+1);

}

size_t get_file_len (char *file_name) {//убрать переоткрытие

    size_t file_len = 1;

    FILE* file = fopen (file_name, "r");
    fseek (file, 0 , SEEK_END);
    size_t file_size = ftell (file);
    fseek (file, 0 ,SEEK_SET);

    char file_str[file_size] = {};

    fread (file_str, 1, file_size, file);
    
    for (size_t i = 0; file_str[i] != '\0'; i++) { if (file_str[i] == '\n') file_len++; }

    fclose (file);

    return file_len;

}

L_COEFFS construct_l_coeffs (double a, double b) {

    L_COEFFS l = {a, b};
    return l;
    
}

S_COEFFS construct_s_coeffs (double a, double b, double c) {
    
    S_COEFFS s = {a, b, c};
    return s;
    
}