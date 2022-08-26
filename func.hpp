

/*! \file  func.hpp
    \brief A headers file.

    This file contains #incude's, #define's, typedef's,
    declarations of the constant variables and declarations of all the functions used in the project

    \authors VladZ
    \date 26.06.2022
    \todo finish documentation using doxygen
*/

/*! \def file_name
    \brief definition of a name of the file that contain all the tests data
*/

/*! \var typedef struct S_COEFFICIENTS S_COEFFS
    \brief A type definition for a S_COEFFS shortname
*/

/*! \var typedef struct L_COEFFICIENTS L_COEFFS
    \brief A type definition for a L_COEFFS shortname
*/

/*! \var double EPSILON
    \brief Describes the allowed inaccurasy while comparing double type variables
*/

/*! \var char EXIT_SIMBOL
    \brief Contains the simbol used to end the product version of the programm
*/

/*! \fn S_COEFFS construct_s_coeffs (double a, double b, double c)

    \brief used to create and initialize S_COEFS structures
 
    \param[in] a a value for the first field in the structure
    \param[in] b a value for the second field in the structure
    \param[in] c a value for the third field in the structure
    \return a costructed structure of the S_COEFFS type, that contains a, b and c as it's fields
*/

/*! \fn L_COEFFS construct_l_coeffs (double a, double b)

    \brief used to create and initialize L_COEFS structures
 
    \param[in] a a value for the first field in the structure
    \param[in] b a value for the second field in the structure
    \return a costructed structure of the L_COEFFS type, that contains a and b as it's fields
*/

/*! \fn NUM_ROOTS square_solver (S_COEFFS coefficients, double* px1, double* px2)

    \brief the main function that solves the quadratic.
 
    \param[in] coefficients coefficients for the equation
    \param[out] px1 a pointer to the slot for the first solution
    \param[out] px2 a pointer to the slot for the second solution
    \return amount of roots of the equation
*/

/*! \fn NUM_ROOTS linear (L_COEFFS coefficients, double* px)

    \brief a fuction that solves all the linear equations
 
    \param[in] coefficients coefficients for the equation
    \param[out] px a pointer to the slot for the solution
    \return amount of roots of the equation
*/

/*! \fn NUM_ROOTS square (S_COEFFS coefficients, double* px1, double* px2);

    \brief a function that solves all the square equations with a non-zero leader coefficient
 
    \param[in] coefficients coefficients for the equation
    \param[out] px1 a pointer to the slot for the first solution
    \param[out] px2 a pointer to the slot for the second solution
    \return amount of roots of the equation
*/

/*! \fn NUM_ROOTS easy_square (L_COEFFS coefficients, double* px1, double* px2)

    \brief a function that solves square equations with a non-zero leader coefficient and a zero linear coefficient
 
    \param[in] coefficients coefficients for the equation
    \param[out] px1 a pointer to the slot for the first solution
    \param[out] px2 a pointer to the slot for the second solution
    \return amount of roots of the equation
*/

/*! \fn void greetings (void);

    \brief a function that welcomes user and suggests to enter the equation's coefficients
*/

/*! \fn void get_coeffs (S_COEFFS* p_coefficients);

    \brief a functions that reads the coefficients entered by user

    this function will check if the user entered three real numbers and if not, will ask him to re-enter correct values or offer to exit the program 
 
    \param[out] p_coefficients a pointer to the structure that stores the coefficients
*/

/*! \fn DOUBLE_COMPARE_RESULT double_compare (double first, double second);

    \brief a function used to compare the variables of type double
 
    \param[in] first a first varibales you are willing to compare
    \param[in] second a second varibale you are willing to compare
    \param[out] result of comparing the variables as a value of DOUBLE_COMPARE_RESULT type
*/

/*! \fn bool double_equal (double first, double second);

    \brief a function that checks if two variables of type double are equal with an inaccurasy of value EPSILON
 
    \param[in] first a first varibale you are willing to compare
    \param[in] second a second varibale you are willing to compare
    \param[out] result of comparing the variables
*/

/*! \fn void error_message (size_t num_test, S_COEFFS coefficients, NUM_ROOTS num_solutions, double* solutions, NUM_ROOTS num_x, double x1, double x2)

    \brief a function that displays the error message if the test has gone wrong
 
    \param[in] num_test test's number
    \param[in] coefficients coefficients of the equation in the test
    \param[in] num_solutions expected number of solutions
    \param[in] solutions expected solutions
    \param[in] num_x received number of solutions
    \param[in] x1 received first solution
    \param[in] x2 received second solution
*/

/*! \fn void success_message (size_t num_test)

    \brief a function that displays the success message if the test has been passed
 
    \param[in] num_test test's number
*/

/*! \fn bool one_test (size_t num_test, S_COEFFS coefficients, NUM_ROOTS num_solutions, double* solutions)

    \brief a function that performs a test of one equation
 
    \param[in] num_test test's number
    \param[in] coefficients coefficients of the testing equation
    \param[in] num_solutions expected number of solutions
    \param[in] solutions expected solutions
    \return the result of the test in the form of the variable of the bool type
*/

/*! \fn bool test_equation (void);

    \brief a function that tests all the equations in the file_name file
    \return the amount of tests passed
*/

/*! \fn size_t get_file_len ();

    \brief a function that counts lines in the file_name file
    \return amount of the lines in the file_name file
*/


#include <assert.h>
#include  <stdio.h>
#include   <math.h>

const double EPSILON     = 0.001;
const char   EXIT_SIMBOL = 'e'  ;

#define file_name "tests.txt"
typedef struct S_COEFFICIENTS S_COEFFS;
typedef struct L_COEFFICIENTS L_COEFFS;

// doxigen(documentation)


///amount of roots of quadratic and linear equations
enum NUM_ROOTS {

    ZERO_ROOTS = 0, /**< enum value for zero roots */
    ONE_ROOT   = 1, /**< enum value for one root */
    TWO_ROOTS  = 2, /**< enum value for two roots */
    INF_ROOTS  = 3, /**< enum value for infinite amount of roots */
    NAN_ROOTS  = 4, /**< enum value that is used to describe that something went wrong while finding the amount of roots */

};

///results of comparing two double variables
enum DOUBLE_COMPARE_RESULT {

    LESS  = 0, /**< enum value LESS */
    EQUAL = 1, /**< enum value EQUAL */
    MORE  = 2, /**< enum value MORE */

};
    

/** \brief used to store coefficients for the quadratic equation

*/
struct S_COEFFICIENTS {
    
    double a; ///< coefficient before the x^2 term
    double b; ///< coefficient before the x term
    double c; ///< constant coefficient

};

/** \brief used to store coefficients for the linear equation

*/

struct L_COEFFICIENTS {
    
    double a; ///< coefficient before the x term
    double b; ///< constant coefficient

};

S_COEFFS              construct_s_coeffs (double a, double b, double c);

L_COEFFS              construct_l_coeffs (double a, double b);

NUM_ROOTS             square_solver      (S_COEFFS coefficients, double* px1, double* px2);

NUM_ROOTS             linear             (L_COEFFS coefficients, double* px);

NUM_ROOTS             square             (S_COEFFS coefficients, double* px1, double* px2);

NUM_ROOTS             easy_square        (L_COEFFS coefficients, double* px1, double* px2);

void                  greetings          (void);

void                  get_coeffs         (S_COEFFS* p_coefficients);

DOUBLE_COMPARE_RESULT double_compare     (double first, double second);

bool                  double_equal       (double first, double second);

void                  error_message      (size_t num_test, S_COEFFS coefficients, NUM_ROOTS num_solutions, double* solutions, NUM_ROOTS num_x, double x1, double x2);

void                  success_message    (size_t num_test);

bool                  one_test           (size_t num_test, S_COEFFS coefficients, NUM_ROOTS num_solutions, double* solutions);

bool                  test_equation      (void);

size_t                get_file_len       ();

