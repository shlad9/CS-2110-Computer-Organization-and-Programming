/**
 * @file main.c
 * @author Your TAs
 * @date 2020-10-07
 * 
 * DO NOT MODIFY THIS FILE.
 */
#include "project4.h"

/**
 * @brief Main method, responsible for parsing command line argument and populating expression structs in the global arr
 * 
 * Note: This function/file is provided as the entry point of the program. 
 * All it does is to call your my_main function in project4.c with the command line arguments.
 * 
 * In any C program, there would be only one true "main" function, however, 
 * this is due to the way the local autograder is setup.
 * 
 * Run "make project4" to get the project4 object file and then run the program like:
 * ./project4 
 * 
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int main(int argc, char const *argv[]) {
    return my_main(argc, argv);
}
