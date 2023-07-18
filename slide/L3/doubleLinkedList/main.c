#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

#include "list_head.h"

#if 0

/// @brief A cinema ticket.
typedef struct {
  int  id;          ///< Ticket id. (4)
  char letter;      ///< Row letter. (1)
  int  position;    ///< Column number. (4)
  list_head_t list; ///< List head.
} ticket_t;

int main(int argc, char * argv[]) {
  
  // Initialize the ticket.
  ticket_t t0 = {
    .id       = 42,
    .letter   = 'C',
    .position = 18
  };
  list_head_init(&t0.list); // Init its list_head.

  list_head_t * _ptr = &t0.list;

  // List pointer back to struct.
  ticket_t * lhb = list_entry(_ptr, ticket_t, list);

  // How list_head works exemplified.
  uintptr_t base   = (uintptr_t) &t0;

  uintptr_t list   = (uintptr_t) &t0.list;

  uintptr_t offset = (uintptr_t) &((ticket_t *) NULL)->list;

  uintptr_t back   = (uintptr_t) ((ticket_t *) ((char *) &t0.list - offset));
  
  ticket_t * tb = (ticket_t *) back;

  printf("base       : %p\n", (void *) base);
  printf("list       : %p\n", (void *) list);
  printf("list_entry : %p\n", lhb);
  printf("offest     : %p\n", (void *) offset);
  printf("back       : %p\n", (void *) back);
  printf("\n");
  printf("ticket ID  : %d\n", tb->id);
  printf("ticket LT  : %c\n", tb->letter);
  printf("ticket PS  : %d\n", tb->position);
  printf("\n");

  uintptr_t woffset = sizeof(int) + sizeof(char) + sizeof(int);
  printf("woffest    : %ld\n", woffset);
  printf("\n");

  return 0;
}

#else

/// @brief Example structure.
typedef struct author {
    int id;           ///< Age of the author.
    char name[250];   ///< Name of the author.
    list_head_t list; ///< List head.
} author_t;

int main(void) {
    // == AUTHOR 0 =========
    author_t a0 = {0, "Stone Sour"};
    list_head_init(&a0.list);

    // == AUTHOR 1 =========
    author_t a1 = {1, "Grandpa Elliott"};
    list_head_init(&a1.list);

    // == AUTHOR 2 =========
    author_t a2 = {2, "Headhunterz"};
    list_head_init(&a2.list);

    // == AUTHOR 3 =========
    author_t a3 = {3, "Lazerhawk"};
    list_head_init(&a3.list);

    // == AUTHOR 4 =========
    author_t a4 = {4, "Black Sabbath"};
    list_head_init(&a4.list);
    // =====================

    // Create the head of the list.
    list_head_t author_list_head;
    list_head_init(&author_list_head);

    // Add the authors to the list.
    list_head_add(&a0.list, &author_list_head);
    list_head_add(&a1.list, &author_list_head);
    list_head_add(&a2.list, &author_list_head);
    list_head_add(&a3.list, &author_list_head);
    list_head_add(&a4.list, &author_list_head);

    // Iterate the list.
    list_head_t * it; // Pointer used to iterate.
    list_for_each(it, &author_list_head) {
        // Extract the data.
        author_t * data = list_entry(it, author_t, list);
        // Print the info about the data.
        printf("%3d %-16s (%p)\n", data->id, data->name, &data->list);
    }
    printf("\n");
    // Print the list_head structure.
    print_list_head(&author_list_head);
    return 0;
}

#endif