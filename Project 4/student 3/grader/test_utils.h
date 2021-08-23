
#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h> // Used to catch seg faults
#include <time.h> // Generate Random Numbers with Time
#include "test_helper.h" // Used to map helper.c code to autograder version - for list() testing
#include "../project4.h"
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/* Test Case Strings - Function Input Args, Expected Output */
#define TEST_MSG(in, exp) "Input: " #in ", Expected Result: " #exp
#define TEST_CMP(in, exp, act) "Input: " #in ", Expected: " #exp ", Actual: " #act

/**
 * @brief Create Test Case and Add Test Case to Suite
 * 
 * @note setup/teardown fixture functions are run before and after each unit test inside the address space of the test
 * @note TCase *tc = tcase_create("func") : Creates test case to be added to the suite
 * 
 * 
 * @param suite             - Create suite variable in some function and pass it in here
 * @param setup_fixture     - Setup function
 * @param teardown_fixture  - Teardown function : NULL if none
 * @param func              - Name of test being added to the test case
 * 
 */
#define tcase_hack(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(s, tc); \
}


/* TEST SUITES */
extern Suite *remove_doc_suite(void);
extern Suite *append_suite(void);
extern Suite *change_mode_suite(void);
extern Suite *list_doc_suite(void);
extern Suite *macro_suite(void);
extern Suite *new_doc_suite(void);
extern Suite *import_suite(void);
extern Suite *find_doc_suite(void);
extern Suite *export_suite(void);

/******* Helper Methods When Autograding *******/
int AUTO_get_first_document_from_vector(uint64_t vector);
uint64_t AUTO_get_old_valid_vector_state(void);
uint64_t AUTO_doc_clear_bit(uint64_t vector, int remove_bit);
uint64_t AUTO_doc_set_bit(uint64_t vector, int insert_bit);
uint64_t AUTO_doc_check_bit(uint64_t vector, int check_bit);
void AUTO_print_all_doc_names(doc_t* ds);
void AUTO_clear_doc_system(doc_t* ds);
char *AUTO_correct_data_pointer(int index);
doc_t* AUTO_insert_at_index(doc_t* ds, char* doc_content_array, uint64_t* state_vector, doc_t* a, int index, int size);

int AUTO_compare_documents(doc_t* a, doc_t* b);
void AUTO_save_system_state(doc_t* ds, char* doc_content, uint64_t valid_vector);
uint64_t AUTO_create_system_difference_vector(doc_t* current_state);

char* AUTO_fill_doc_contents_with_data(char* doc_data, uint64_t* state_vector, int index, int value);
void AUTO_print_doc_contents(char* doc_data, int index);

/* Catch student seg faults and give advice on what to do. */
void AUTO_catch_segv(int signal);
int AUTO_get_doc_index_at_random(void);
