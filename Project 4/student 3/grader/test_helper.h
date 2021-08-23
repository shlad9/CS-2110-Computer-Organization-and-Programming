#include "../project4.h"

/**
 * @brief This file is to pass a variable from test_helper.c to the list test suite
 *  
 * You may wonder, why not put this extern variable in test_utils.h?
 *  If I were to put this variable in test_utils.h then when test_helper.c is linked
 *  to the student's project4.c code the test_utils.c helper functions would be
 *  available for student use (which we do NOT want).
 */


/* test_helper.c variable for testing "list()" */
extern uint64_t list_print_vector;
extern int list_errno;
#define LIST_ERROR -1
#define LIST_EMPTY_ERROR -2
