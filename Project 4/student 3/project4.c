#include "project4.h"

//Array of possible documents
doc_t doc_system[MAX_NUM_DOCS];
//bit vector representing the validity of each doc entry
uint64_t doc_valid_vector;
//command line arguments for each user command
char *arguments[4];
//data array (space pre-allocated for document contents)
char data[MAX_DOCSIZE * MAX_NUM_DOCS];

/**
 * @brief Creates a new document in our system if a document of the same name doesn't exist already.
 * If docname is NULL, a document with the same name already exists, or there is no more space to create documents, do nothing and return -1
 *
 * @param docname the name of the doc to create, including the extension
 * @return the index of the new document, or -1 in case of error
 */
int new_doc(char *docname) {
    // UNUSED(docname);
    // return ERROR;
    if(docname == NULL){
      return -1;
    }

    char name[MAX_NAMESIZE];
    ext_t extension;

    get_name_ext(name, &extension, docname);
    int m = -1;


    for(int i = 0; i < MAX_NUM_DOCS; i++){
      if ((m == -1) && (!GET_DOC_PRESENT(doc_valid_vector, i))) {
        m = i;
      } else {
        if(strcmp(doc_system[i].name, name) == 0) {
          if(doc_system[i].extension == extension) {
            return -1;
      }}}
    }
    if (m == -1) {
      return -1;
    }

    doc_t newDoc;
    strcpy(newDoc.name, name);
    newDoc.extension = extension;
    newDoc.permissions = 0x07;
    newDoc.size = 0;
    newDoc.data = &data[m * MAX_DOCSIZE];
    newDoc.index = m;

    doc_system[m] = newDoc;
    doc_valid_vector = SET_DOC_PRESENT(doc_valid_vector, m);
    return m;

}

/**
 * @brief Find a doc in the doc system array given its name, including the extension
 * If docname is NULL or the document is not present, return -1
 *
 * @param docname the name of the doc to find, including the extension
 * @return index referring to the document in the doc_system, -1 on error
 */
int find_doc(const char *docname) {
    // UNUSED(docname);
    // return ERROR;

    if(docname == NULL){
      return -1;
    }

    char name[MAX_NAMESIZE];
    ext_t extension;

    get_name_ext(name, &extension, docname);
    int m = -1;

    for(int i = 0; i < MAX_NUM_DOCS; i++){
      if(strcmp(doc_system[i].name, name) == 0) {
        if(doc_system[i].extension == extension) {
          m = i;
      }}}


    return m;


}

/**
 * @brief List all doc names in the doc array. Only list those that are marked as
 * valid by the doc valid vector. The helper function print_doc_name will be useful.
 *
 */
void list(void){
  for(int i = 0; i < MAX_NUM_DOCS; i++){
    if ((GET_DOC_PRESENT(doc_valid_vector, i)==1)) {
      print_doc_name(doc_system[i]);
      printf("\n");

    }}
}

/**
 * @brief Append a string to a doc. This operation fails if the string is too large to append to the doc
 * given the length of the string, the current size of the doc, and the max doc size constant. Remember that
 * the data for each document must be zero-terminated. This operation also fails if doc or str is NULL, or if the doc to append to does not have write permissions enabled.
 *
 * @param doc the doc to append to
 * @param str the string to append to the doc
 * @return an int representing the success of the operation. 0 if successful, -1 otherwise.
 */
int append(doc_t *doc, char *str) {
    // UNUSED(doc);
    // UNUSED(str);
    // return ERROR;
    if(doc == NULL){
      return -1;
    }
    if(str == NULL){
      return -1;
    }

    if((doc->permissions & 0x02) != 0x02){
      return -1;
    }

    int theSize = doc->size;
    if((theSize + strlen(str)) > MAX_DOCSIZE - 1) {
      return -1;
    }

    // data[(doc->size)+theSize+1] = *str;
    char temp[strlen(str)];
    strcpy(temp, str);
    strcpy(doc->data + theSize, temp);
    doc->size += strlen(str);
    return 0;
}

/**
 * @brief Import the contents of an external file into this doc system.
 * This function should create a new document to import the contents into.
 * Fails if the contents of the file, with the zero-terminator added at the end, are larger than the max doc size,
 * there is not enough space for a new doc, or if docname or file is NULL.
 *
 * @param docname the name of the new document to create, including the extension
 * @param file the file pointer to read data from
 * @return an int representing the success of the operation. 0 if successful, -1 otherwise.
 */
int import(char *docname, FILE *file) {
    // UNUSED(docname);
    // UNUSED(file);
    // return ERROR;

    if(docname == NULL){
      return -1;
    }
    if(file == NULL) {
      return -1;
    }

    int fileSize = get_file_size(file);

    if(fileSize > MAX_DOCSIZE - 1) {
      return -1;
    }

    int locN = new_doc(docname);

    if (locN == -1) {
      return -1;
    }

    char buffer[MAX_DOCSIZE];
    fread(buffer, fileSize, fileSize, file);

    doc_t * bama = &doc_system[locN];

    append(bama, buffer);

    return 0;


}

/**
 * @brief Prints the internal data of the given doc, followed by a newline.
 * Fails if doc is NULL, or if the doc does not have read permissions enabled.
 *
 * @param doc the doc whose data we print
 * @return an int representing the success of the operation. 0 if successful, -1 otherwise.
 */
int print_doc_data(const doc_t *doc) {
    // UNUSED(doc);
    // return ERROR;

    if(doc == NULL){
      return -1;
    }

    if((doc->permissions & 0x04) != 0x04){
      return -1;
    }

    printf("%s\n", doc->data);
    return 0;

}

/**
 * @brief Export the contents of a doc in our system to an external file.
 * Fails if doc or file is NULL or if the doc does not have read permissions enabled.
 *
 * @param doc the doc whose data we export
 * @param file the file to export to
 * @return an int representing the success of the operation. 0 if successful, -1 otherwise.
 */
int export(const doc_t *doc, FILE *file) {
  if(doc == NULL){
    return -1;
  }
  if(file == NULL) {
    return -1;
  }
  if((doc->permissions & 0x04) != 0x04){
    return -1;
  }

  int m = -1;
  for(int i = 0; i < MAX_NUM_DOCS; i++){
    if(strcmp(doc_system[i].name, doc->name) == 0) {
      if(doc_system[i].extension == doc->extension) {
        m = i;
    }}}
  if(m == -1){
    return -1;
  }

  doc_t * toExport = &doc_system[m];

  fprintf(file, "%s", toExport->data);

  return 0;
}

/**
 * @brief Remove the given doc from the doc system. This doc, if not NULL, is guaranteed to exist in the system.
 * Fails if doc was NULL.
 *
 * @param doc the doc to remove
 * @return an int representing the success of the operation. 0 if successful, -1 otherwise.
 */
int remove_doc(doc_t *doc) {
    // UNUSED(doc);
    // return ERROR;

    if(doc == NULL){
      return -1;
    }

    int m = -1;

    for(int i = 0; i < MAX_NUM_DOCS; i++){
      if ((m == -1) && (GET_DOC_PRESENT(doc_valid_vector, i))) {
        if(strcmp(doc_system[i].name, doc->name) == 0) {
          if(doc_system[i].extension == doc->extension) {
            m = i;
        }}
      }
    }
    doc_valid_vector = CLEAR_DOC_PRESENT(doc_valid_vector, m);
    return 0;
}

/**
 * @brief Change the read, write, execute permissions of a doc
 * Fails if doc or mode_changes is NULL.
 *
 * @param doc the doc to modify the permissions of
 * @param mode_change the string representing the changes to be made (i.e. '+rw' or '-x')
 * @return an int representing the success of the operation. 0 if successful, -1 otherwise.
 */
int change_mode(doc_t *doc, char *mode_changes) {
    // UNUSED(doc);
    // UNUSED(mode_changes);
    // return ERROR;
    if(doc == NULL){
      return -1;
    }
    if(mode_changes == NULL){
      return -1;
    }
    char temp[strlen(mode_changes)];
    strcpy(temp, mode_changes);

    if(strcmp(temp, "+r")==0){
      doc->permissions = doc->permissions | RMASK;
    }
    if(strcmp(temp, "+w")==0){
      doc->permissions = doc->permissions | WMASK;
    }
    if(strcmp(temp, "+x")==0){
      doc->permissions = doc->permissions | XMASK;
    }
    if(strcmp(temp, "+rw")==0){
      doc->permissions = doc->permissions | RMASK;
      doc->permissions = doc->permissions | WMASK;
    }
    if(strcmp(temp, "+rx")==0){
      doc->permissions = doc->permissions | RMASK;
      doc->permissions = doc->permissions | XMASK;
    }
    if(strcmp(temp, "+wx")==0){
      doc->permissions = doc->permissions | WMASK;
      doc->permissions = doc->permissions | XMASK;
    }
    if(strcmp(temp, "+rwx")==0){
      doc->permissions = doc->permissions | RMASK;
      doc->permissions = doc->permissions | WMASK;
      doc->permissions = doc->permissions | XMASK;
    }
    if(strcmp(temp, "-r")==0){
      doc->permissions = doc->permissions & ~RMASK;
    }
    if(strcmp(temp, "-w")==0){
      doc->permissions = doc->permissions & ~WMASK;
    }
    if(strcmp(temp, "-x")==0){
      doc->permissions = doc->permissions & ~XMASK;
    }
    if(strcmp(temp, "-rw")==0){
      doc->permissions = doc->permissions & ~RMASK;
      doc->permissions = doc->permissions & ~WMASK;
    }
    if(strcmp(temp, "-rx")==0){
      doc->permissions = doc->permissions & ~RMASK;
      doc->permissions = doc->permissions & ~XMASK;
    }
    if(strcmp(temp, "-wx")==0){
      doc->permissions = doc->permissions & ~WMASK;
      doc->permissions = doc->permissions & ~XMASK;
    }
    if(strcmp(temp, "-rwx")==0){
      doc->permissions = doc->permissions & ~RMASK;
      doc->permissions = doc->permissions & ~WMASK;
      doc->permissions = doc->permissions & ~XMASK;
    }


    return 0;
}



/**
 * @brief Main method that waits for user input to modify the docsystem. This method starts
 * up a mockup shell and tokenizes each user command using the tokenize helper method.
 *
 * For example, if the user inputs:
 * >> cmd name.doc other.txt
 *
 * The global arguments array will be populated as : {"cmd", "name.doc", "other.txt"}
 * You may use the arguments array to get the arguments for whatever operation needs to be performed.
 *
 * Note: the command to perform (i.e. cp, new, exit...) will always be in arguments[0]
 *
 * @param argc unused int
 * @param argv unused array of strings
 * @return integer representing the success of the main method (0 on exit, 1 otherwise)
 */
int my_main(int argc, char const *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    char *shell_string = ">> ";

    //set up buffer to read in command line input
    char buffer[MAX_CMD_LEN];

    //will loop infinitely unless the user inputs 'exit'
    while(1) {
        printf("%s", shell_string);
        //get user input into buffer and tokenize it using the tokenize method
        fgets(buffer, MAX_CMD_LEN, stdin);
        tokenize(buffer);
        char *cmd = arguments[0];

        //TODO: Add new cases for different commands. You can follow the example given for new.
        if(strncmp(cmd, "new", 3) == 0) {
            char *name = arguments[1];
            new_doc(name);
        }
        else if(strncmp(cmd, "exit", 4) == 0) {
            return 0;
        }
        else if(strncmp(cmd, "ls", 2) == 0) {
            list();
        }
        else if(strncmp(cmd, "import", 6) == 0) {
            FILE *fp;
            fp = fopen(arguments[1], "r");
            char *name = arguments[2];
            import(name, fp);
            fclose(fp);
        }
        else if(strncmp(cmd, "export", 6) == 0) {
            FILE *fp;
            fp = fopen(arguments[2], "w");
            char *name = arguments[1];
            int theDp = find_doc(name);
            doc_t * toExport = &doc_system[theDp];
            export(toExport, fp);
            fclose(fp);
        }
        else if(strncmp(cmd, "print", 5) == 0) {
            char *name = arguments[1];
            int theDp = find_doc(name);
            doc_t * toPrint = &doc_system[theDp];
            print_doc_data(toPrint);
        }
        else if(strncmp(cmd, "append", 6) == 0) {
            char *name = arguments[1];
            int theDp = find_doc(name);
            doc_t * toAppend = &doc_system[theDp];
            char *string = arguments[2];
            append(toAppend, string);
        }
        else if(strncmp(cmd, "chmod", 5) == 0) {
            char *name = arguments[1];
            char *modeChanges = arguments[2];
            int theDp = find_doc(name);
            doc_t * toCH = &doc_system[theDp];
            change_mode(toCH, modeChanges);
        }
        else if(strncmp(cmd, "rm", 2) == 0) {
            char *name = arguments[1];
            int theDp = find_doc(name);
            doc_t * toRemove = &doc_system[theDp];
            remove_doc(toRemove);
        }

    }

    return 1;
}
