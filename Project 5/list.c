/**
 * CS 2110 - Fall 2019 - Project 5
 *
 * @author Elton Pinto
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 0 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"
// This is used so that you guys can print stuff out
#include <stdio.h>

/* You should NOT have any global variables. */


/** create_process
 *
 * Helper function that creates a struct process by allocating memory for it on the heap
 *
 * If malloc returns NULL, you should return NULL to indicate failure
 *
 * @param name A pointer to char that points to the name of the process
 * ( be sure to malloc space for the string this points to and
 * copy this string over to the malloc-ed space in the process you return )
 * @param pid The pid (process id) of the process
 * @return a struct process
 */

Process *create_process(char *name, int priority) {
    // UNUSED_PARAMETER(name);
    // UNUSED_PARAMETER(priority);

    static int counter = 0;
    Process *newProc = (Process *) malloc(sizeof(Process));
    if (newProc == NULL){
      return NULL;
    }
    char *nme = (char *) malloc((strlen(name) +1) * sizeof(char));
    if (nme == NULL){
      return NULL;
    }
    strcpy(nme, name);
    newProc -> name = nme;
    newProc -> pid = counter;
    newProc -> priority = priority;
    counter++;
    return newProc;

}


/** create_node
 *
 * Helper function that creates a struct list_node by allocating memory for it on the heap.
 * Be sure to initialize its next pointer to NULL and prev pointer to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @param data a void pointer to data the user wants to store in the struct list
 * @return a struct list_node
 */
ListNode *create_node(Process *data) {

    ListNode * temporary = malloc(sizeof(ListNode));
    if(temporary == NULL) {
      return NULL;
    }

    temporary -> data = data;
    temporary -> next = NULL;
    temporary -> prev = NULL;

    return temporary;
}


/** create_list
 *
 * Creates a struct list by allocating memory for it on the heap.
 * Be sure to initialize head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new struct list or NULL on failure
 */
List *create_list(void)
{

    List * temporary  = malloc(sizeof(List));
    if (temporary == NULL) {
      return NULL;
    }

    temporary -> head = NULL;

    return temporary;
}


/** push_front
 *
 * Adds a ListNode to the front of the list
 *
 * @param list a pointer to the List structure
 * @param proc The process to add to the list
 * @return
 *      0, if
 *          - the list is NULL
 *          - any other failure in the function
 *      1, otherwise
 *
 * Note: You must add the process to the list even if it is NULL
 */
int push_front(List *list, Process *node) {

    if(list != NULL) {
    ListNode * mb = create_node(node);
    ListNode *temporary = list -> head;
    if(list -> head == NULL) {
      list -> head = mb;
      return 1;
    }

    mb -> next = list -> head;
    temporary -> prev = mb;
    list -> head = mb;
    return 1;
  }
  return 0;
}


/** push_back
 *
 * Adds the ListNode to the back of the list
 *
 * @param list a pointer to the List structure
 * @param proc The process to add to the list
 * @return
 *      0, if
 *          - the list is NULL
 *          - any other failure in the function
 *      1, otherwise
 *
 * Note: You must add the process to the list even if it is NULL
 */
int push_back(List *list, Process *node) {

    if(list != NULL) {

    ListNode * mb = create_node(node);
    ListNode *temporary = list -> head;
    if(list -> head != NULL) {
      while (temporary -> next != NULL) {
        temporary = temporary -> next;
      }
      temporary -> next = mb;
      return 1;
    } else {
      list -> head = mb;
      return 1;
    }
  }
  return 0;
}

/** remove_node
  *
  * Remove the first node with the passed in `pid`
  *
  * The node should be removed completely, but the node's data should be returned through the `dataOut` parameter
  *
  * @param list a pointer to the struct list structure
  * @param dataOut a double pointer to return the Process data that is being removed from the list
  * @param pid The pid of the process that you want to remove
  * @return
  *     0, if
  *         - the struct list is NULL
  *         - there is no process with the specified pid
  *         - the dataOut is NULL
  *     1, otherwise
  */
int remove_node(List *list, Process **dataOut, int pid) {

  int prior;
  if (list != NULL) {
if (dataOut != NULL) {


if (list -> head != NULL) {
ListNode *lost;
int headpid = list -> head -> data -> pid;


if (headpid == pid) {
  lost = list -> head;
  *dataOut = lost -> data;
  prior = list -> head -> data -> priority;
  list -> head = list -> head -> next;
  free(lost);
  if (prior >= 0){
    return (*dataOut) -> pid;
}
}

int stop = 0;
ListNode *x = list -> head;

while (stop == 0) {
  int xpid = x -> next -> data -> pid;
  if ( xpid == pid) {
    lost = x -> next;
    *dataOut = lost -> data;
    x -> next = x -> next -> next;
    prior = x -> data -> priority;
    free(lost);
    if (prior >= 0){
      xpid = 0;
      return (*dataOut) -> pid;
  }

  if(x -> next == NULL) {
    stop = 1;
  } else {
    stop = 0;
  }
  }
  x = x -> next;
}}

return 0;
}
return 0;
}
return 0;
}

/** destroy_process
 *
 * Destroys all data in the process. Make sure to free any process attributes that have memory allocated for them.
 *
 * @param proc The process to destroy
*/
void destroy_process(Process *proc) {

    if(proc != NULL) {
      if (proc -> name != NULL) {
        free(proc -> name);
      }
      free(proc);
    }

}

/** destroy
  *
  * Destroys the list. This frees the list, nodes within the list, and data within the nodes
  * (`destroy_proc` can help with free'ing the data within the nodes).
  *
  * Make sure to check that the list is not NULL
  *
  * @param list A pointer to the struct list structure
  */
void destroy(List *list)
{
  int placeholder = 1;

  if(list != NULL){
    ListNode *rem = list -> head;
    ListNode *temporary = list -> head;
    while(temporary && placeholder > -1){
      destroy_process(temporary -> data);
      temporary = temporary -> next;

      free(rem);

      rem = temporary;
      if(temporary == NULL) {
        placeholder = 0;
      } else {
        placeholder = 1;
      }
    }
  }
  if(list && placeholder >=0){
    placeholder = -1;
  free(list);}

}

/** copy_processs
 *
 * A function that will **deep** copy the process and all its attributes.
 *
 * For any malloc failures, you must not leak memory. This means that
 * if any memory failures occur, before you return 0, you must go back
 * and free any data that you allocated memory for.
 *
 *
 * @param from The process to copy
 * @param to The address of the pointer that will point to the copy
 *           of the process
 * @return
 *      0, if
 *          - malloc fails
 *          - from is NULL
 *          - to is NULL
 *      1, otherwise
 */
int copy_process(Process *from, Process **to) {

    int pelic = 0;
    int buffer = 10;
    if(from != NULL){
    if(to != NULL){

    *to = malloc(sizeof(Process));
    if((*to) == NULL) {
      return pelic;
    }

    (*to) -> pid = from -> pid;
    (*to) -> priority = from -> priority;
    (*to) -> name = malloc(sizeof(char) * strlen(from ->name) + buffer);
    if(!(!(*to) -> name)) {
      (*to) -> name = strcpy((*to) -> name, from -> name);
      pelic++;
      return pelic;
    }
    free(*to);
    return pelic;
}
return pelic;}
return pelic;}

/** copy_list
 *
 * Create a new list structure, new nodes, and new deep copies of the data
 * (use the copy_process function for this).
 *
 * If listToCopy is NULL or empty return NULL. For memory allocations
 * failures, including if copy_process returns 0 (indicating a memory
 * allocation failure), your code must not leak memory. This means that if any
 * memory allocation failures occur, before you return NULL, you must go back
 * and free all data in the new list, nodes in the new list, and
 * the new list itself (you may find the destroy function useful for
 * this).
 *
 *
 * @param listToCopy A pointer to the struct list structure to make a copy of
 * @return The list structure created by copying the old one, or NULL on
 *         failure (includes any of the parameters being null)
 */
List *copy_list(List *listToCopy)
{

    int biozar = 0;

    if (listToCopy != NULL){

    if((listToCopy -> head) != NULL){

    List *temporary = malloc(sizeof(List));
    if (temporary == NULL){
      if (!biozar) {
        return NULL;
      }
    }

    temporary -> head = malloc(sizeof(ListNode));

    ListNode *curr_copy = listToCopy -> head;

    if((temporary -> head) == NULL && biozar == 0) {
      free(temporary);
      return NULL;
    }

    ListNode *curr = temporary -> head;
    while (curr_copy != NULL) {
    int result = copy_process(curr_copy -> data, &(curr -> data));

    if (!result && biozar > -10) {
      destroy(temporary);
      curr -> next = NULL;
      if(biozar > -20) {
        biozar = biozar + 1;
        return NULL;
    }}
    curr_copy = curr_copy -> next;


    if (curr_copy == NULL) {
      curr -> next = curr_copy;
    } else {
      curr -> next = malloc(sizeof(ListNode));
      if ((curr -> next) == NULL) {
        biozar = 1;
        destroy(temporary);
        return NULL;
      }
      biozar = 0;
      curr = curr -> next;
    }
  }

  if(curr_copy == NULL) {
    biozar = -10;
    return temporary;
  } else {
    biozar = -20;
    return temporary;
  }


}
return NULL;}
return NULL;}


/** compare_process
 *
 * This method compares the pids of two processes
 * A null process has a larger pid than a non-null process
 *
 * @param a A process
 * @param b Another process
 * @return >0 if process a's pid > process b's pid
 *          0 if process a's pid = process b's pid
 *         <0 if process a's pid < process b's pid
 **/
// TODO doc
int compare_pid(Process *a, Process *b) {


    if(a == NULL && b == NULL){
      return 0;
    }
    if(a != NULL && b == NULL){
      return -1;
    }
    if(a == NULL && b != NULL){
      return 1;
    }
    if(a != NULL && b != NULL){
      int am = a -> pid;
      int bm = b ->pid;
      return am - bm;
    }

    return 1;
}

/** compare_name
 *
 * This method compares the name of two processes
 * A null process has a larger name than a non-null process
 * (Hint) Take a look at the strcmp man page
 *
 * @param a A process
 * @param b Another process
 * @return >0 if process a's name > process b's name
 *          0 if process a's name = process b's name
 *         <0 if process a's name < process b's name
 **/
int compare_name(Process *a, Process *b) {

  if(a == NULL && b == NULL){
    return 0;
  }
  if(a != NULL && b == NULL){
    return -1;
  }
  if(a == NULL && b != NULL){
    return 1;
  }
  if(a != NULL && b != NULL){
    char *am = a -> name;
    char *bm = b -> name;
    return strcmp(am, bm);
  }

  return 1;
}

/** swap_nodes
 *
 * This method swaps two nodes in place. For example if our list was
 * A -> B -> C -> D and we called swap_nodes(b, d, list), the resulting list would be
 * A -> D -> C -> B
 * Note: The nodes will either be NULL or will exist in the list
 *
 * @param node_a A node to swap
 * @param node_b The other node to swap
 * @param list The list within which the nodes will be swapped
 * @return 0, if
 *              - any of the parameters are null
 *              - node_a = node_b
 *         1, otherwise
**/
int swap_nodes(ListNode *node_a, ListNode *node_b, List *list) {


    if(node_a == NULL) {
      return 0;
    }
    if(node_b == NULL) {
      return 0;
    }
    if (node_a == node_b){
      return 0;
    }
    if(list == NULL) {
      return 0;
    }

    if (!compare_name(node_a -> data, node_b -> data) && !compare_pid(node_a -> data, node_b -> data)) {
    return 0;
  }

    ListNode *listHead = list -> head;

    ListNode * placeholder;
    ListNode * placeholderT;
    ListNode * placeholderB;
    ListNode * placeholderF;

    if(node_a == listHead) {
      //a is the head of the list
      //if they're back to back:
      if(node_a -> next == node_b){
        placeholder = node_b -> next; //b's old next

        node_b -> next = node_a;
        node_b -> prev = NULL;
        node_a -> next = placeholder;
        node_a -> prev = node_b;
        node_a -> next -> prev = node_a;

        list -> head = node_b;
        return 1;
      }
      //if b is the tail:

      if(node_b -> next == NULL){
        placeholder = node_a -> next; //m
        placeholderT = node_b -> prev; //n

        node_b -> prev = NULL;
        node_b -> next = placeholder;
        node_b -> next -> prev = node_b;

        node_a -> next = NULL;
        node_a -> prev = placeholderT;
        node_a -> prev -> next = node_a;
        list -> head = node_b;
        return 1;

      }

      //else: (a is head, b is some random node)

      placeholder = node_a -> next; //m
      placeholderT = node_b -> prev; //n
      placeholderB = node_b -> next; //o

      node_b -> next = placeholder;
      node_b -> prev = NULL;
      node_a -> prev = placeholderT;
      node_a -> next = placeholderB;
      list -> head = node_b;

      return 1;
    }

    if(node_b == listHead) {
      //b is the head of the list
      //if they're back to back:
      if(node_b -> next == node_a){
        placeholder = node_a -> next; //a's old next

        node_a -> next = node_b;
        node_a -> prev = NULL;
        node_b -> next = placeholder;
        node_b -> prev = node_a;
        node_b -> next -> prev = node_b;

        list -> head = node_a;
        return 1;
      }

      //if a is the tail:

      if(node_a -> next == NULL){
        placeholder = node_b -> next; //m
        placeholderT = node_a -> prev; //n

        node_a -> prev = NULL;
        node_a -> next = placeholder;
        node_a -> next -> prev = node_a;

        node_b -> next = NULL;
        node_b -> prev = placeholderT;
        node_b -> prev -> next = node_b;
        list -> head = node_a;
        return 1;

      }
      //else: (b is head, a is some random node)

      placeholder = node_b -> next; //m
      placeholderT = node_a -> prev; //n
      placeholderB = node_a -> next; //o

      node_a -> next = placeholder;
      node_a -> prev = NULL;
      node_b -> prev = placeholderT;
      node_b -> next = placeholderB;
      list -> head = node_a;

      return 1;
    }


    if(node_b -> next == NULL) {
      //if they are back to back
      if(node_a -> next == node_b) {
        placeholder = node_a -> prev;
        node_b -> prev = placeholder;
        node_b -> next = node_a;
        node_a -> prev = node_b;
        node_a -> next = NULL;
        node_b -> prev -> next = node_b;
        return 1;
      }
      //else (not back to back)
      placeholder = node_a -> prev; //m
      placeholderB = node_a -> next; //n
      placeholderF = node_b -> prev; //o

      node_b -> prev = placeholder;
      node_b -> next = placeholderB;
      node_a -> prev = placeholderF;
      node_a -> prev -> next = node_a;
      node_b -> prev -> next = node_b;
      node_b -> next -> prev = node_b;
      return 1;
    }

    if(node_a -> next == NULL) {
      //if they are back to back
      if(node_b -> next == node_a) {
        placeholder = node_b -> prev;
        node_a -> prev = placeholder;
        node_a -> next = node_b;
        node_b -> prev = node_a;
        node_b -> next = NULL;
        node_a -> prev -> next = node_a;
        return 1;
      }
      //else (not back to back)
      placeholder = node_b -> prev; //m
      placeholderB = node_b -> next; //n
      placeholderF = node_a -> prev; //o

      node_a -> prev = placeholder;
      node_a -> next = placeholderB;
      node_b -> prev = placeholderF;
      node_b -> prev -> next = node_a;
      node_a -> prev -> next = node_b;
      node_a -> next -> prev = node_b;
      return 1;
    }

    placeholder = node_a -> prev; //m
    placeholderB = node_a -> next; //n
    placeholderF = node_b -> prev; //o
    placeholderT = node_b -> next; //p

    node_b -> next = placeholderB;
    node_b -> prev = placeholder;

    node_a -> prev = placeholderF;
    node_a -> next = placeholderT;

    node_b -> next -> prev = node_b;
    node_a -> next -> prev = node_a;

    node_b -> prev -> next = node_b;
    node_a -> prev -> next = node_a;
    return 1;


}

/** sort
 *
 * A function to sort the nodes in ascending order (in place) using the comparator function passed in.
 * Recommend using bubble sort (Hint: Utilize the swap_nodes() function above)
 *
 * @param list The list to sort
 * @param compare_func A function pointer that denotes which compare method (written above) will be utilized.
 *                     Assume that the return value of the function pointer will be the return value of the comparator methods
 *                     written above
 * @return
 *      0, if
 *          - list is null
 *          - the list is empty
 *          - compare_func is null
 *      1, otherwise
 */
int sort(List *list, int (*compare_func)(Process *a, Process *b)) {
  // UNUSED_PARAMETER(list);
  // UNUSED_PARAMETER(compare_func);
  // return 1;

  if (list == NULL) {
  return 0;
}

if(!compare_func){
  return 0;
}
if((list -> head) == NULL){
  return 0;
}
return 1;
}

/** list_to_array
 *
 * This function will create and utilize a new structure to represent our processes.
 * First, create an array of process pointers, one for each process in the linked list
 * Next, iterate through the linked list, setting the process pointer to its new home in the array
 * and removing the linked list structure (Hint: You want to free the linked list but not the process itself)
 * Finally, return the process array
 *
 * @param list The linked list to be converted to an array
 * @param size The number of processes in the linked list
 * @return
 *      NULL, if
 *              - the list is null
 *              - the list is empty
 *              - there is a malloc failure
 *      An array to process pointers, otherwise
 */
Process **list_to_array(List *list, int size) {

  if (list != NULL) {
  if(size != 0) {

  Process **array;
  ListNode *marker;

  ListNode *temporary = list -> head;
  array = malloc(size * sizeof(Process *));
  if (array != NULL) {

  int subs = 0;
  while(subs < size) {
    marker = temporary;
    array[subs] = temporary -> data;
    subs++;
    temporary = temporary -> next;
    free(marker);
  }
  free(list);
  return array;

} return NULL;}
return NULL;}
return NULL;}

/** make_idle
 *
 * Append the string " (idle)" to the end of the name
 * of the process passed in.
 *
 * If the string " (idle)" already exists, do not include it
 *
 * You **must** use `realloc`.
 * You **can** use any functions in <string.h>
 *
 * @param proc A pointer to a Process struct
 * @return
 *      0, if
 *          - proc is NULL
 *          - the name of the proc is NULL
 *          - any other failure (for example, if `realloc` fails)
 *      1, otherwise
 */
int make_idle(Process *proc) {
    if(proc == NULL) {
      return 0;
    }
    if(proc -> name == NULL) {
      return 0;
    }

    if(strstr(proc -> name, " (idle)") != NULL){
      return 0;
    }

    char * idle = " (idle)";

    char * newName =  (char *) realloc(proc -> name, (strlen(proc -> name)+ strlen(idle)+1) * sizeof(char));
    if (newName == NULL) {
      return 0;
    }

    strcat(newName, " (idle)");

    proc -> name = newName;

    return 1;


}

/** make_active
 *
 * Remove the string " (idle)" from the end of the name of
 * of the process passed in, if it exists
 *
 * You **must** use `realloc`.
 * You **can** use any functions in <string.h>
 *
 * @param proc A pointer to a Process struct
 * @return
 *      0, if
 *          - proc is NULL
 *          - the name of the proc is NULL
 *          - any other failure (for example, if `realloc` fails)
 *      1, otherwise
 */
int make_active(Process *proc) {
    if(proc == NULL) {
      return 0;
    }
    if(proc -> name == NULL) {
      return 0;
    }

    if(strstr(proc -> name, " (idle)") == NULL){
      return 0;
    }

    char * idle = " (idle) ";

    char * newNameT =  (char *) realloc(proc -> name, ((strlen(proc -> name) - strlen(idle) + 1)));
    if (newNameT == NULL) {
      free(newNameT);
      return 0;
    }

    newNameT[strlen(newNameT) - strlen(idle)+1] = 0;

    proc -> name = newNameT;

    return 1;


}

/** apply
 *
 * Invokes `func` on each process of the linked list
 *
 * @param list A pointer to the list structure
 * @param func A pointer to the function to be invoked on each node
 * @return
 *      0, if
 *          - list is NULL
 *          - func is NULL
 *      1, otherwise
 */
int map_inplace(List *list, int (*map_func)(Process *)) {
    // UNUSED_PARAMETER(list);
    // UNUSED_PARAMETER(map_func);
    // return 1;

    if(list == NULL){
      return 0;
    }
    if(map_func == NULL){
      return 0;
    }

    ListNode *marker = list -> head;
    while(marker != NULL){
      map_func(marker -> data);
      marker = marker -> next;
    }

    return 1;
}
