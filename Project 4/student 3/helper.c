/**
 * @brief DO NOT EDIT THIS FILE!!!!!
 */
#include "project4.h"

/**
 * @brief Tokenize shell command into array of strings.
 * DO NOT MODIFY
 *
 * @param line A null-terminated C string
 */
void tokenize(char *line) {
    int len = strlen(line);
    line[len - 1] = ' ';
    arguments[0] = strtok(line, " ");
    for(int i = 1; i < 4; i++) {
        arguments[i] = strtok(NULL, " ");
    }
    // printf("%s, %s, %s, %s", arguments[0], arguments[1], arguments[2], arguments[3]);
}

/**
 * @brief Get the name and extension of a doc name string.
 * DO NOT MODIFY
 *
 * @param name Pointer to a string to populate
 * @param ext Pointer to an extension enum type to populate
 * @param docname C string that is the name of a doc
 */
void get_name_ext(char *name, ext_t *ext, const char* docname){
    char temp[MAX_NAMESIZE]; //max namesize + .ascii
    strcpy(temp, docname);
    char test[MAX_NAMESIZE];
    memset(test, 0, MAX_NAMESIZE);
    strcpy(test, strtok(temp, "."));
    test[strlen(test)] = '\0';
    strncpy(name, test, strlen(test) + 1);
    char *name_ext = strtok(NULL, ".");
    *ext = DOC;
    if(strcmp(name_ext, "ascii") == 0) {
        *ext = ASCII;
    }
}

/**
 * @brief Returns the length of the given file
 * DO NOT MODIFY
 *
 * @param file the file to check the length of
 */
int get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    return size;
}

/**
 * @brief Prints the name and permissions of a given doc.
 * DO NOT MODIFY
 *
 * @param doc the doc to print the information of.
 */
void print_doc_name(doc_t doc) {
    printf("%s", doc.name);
    if(doc.extension == DOC) {
        printf(".doc");
    } else {
        printf(".ascii");
    }

    char perm[4];
    int i = 0;
    if((doc.permissions & RMASK) == RMASK) {
        perm[i] = 'r';
        i++;
    }
    if((doc.permissions & WMASK) == WMASK) {
        perm[i] = 'w';
        i++;
    }
    if((doc.permissions & XMASK) == XMASK) {
        perm[i] = 'x';
        i++;
    }
    perm[i] = '\0';
    printf(" - %s\n", perm);
}
