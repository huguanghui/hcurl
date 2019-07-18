#ifndef HCURL_LLIST_H
#define HCURL_LLIST_H

#include <stddef.h>
#include <sys/types.h>

typedef void (*curl_llist_dtor)(void *, void *);

struct curl_llist_element {
    void *ptr;
    struct curl_llist_element *prev;
    struct curl_llist_element *next;
};

struct curl_llist {
    struct curl_llist_element *head;
    struct curl_llist_element *tail;
    curl_llist_dtor dtor;
    size_t size;
};

void Curl_llist_init(struct curl_llist *, curl_llist_dtor);
void Curl_llist_insert_next(struct curl_llist *, struct curl_llist_element *,
                                const void *, struct curl_llist_element *node);
void Curl_llist_remove(struct curl_llist *, struct curl_llist_element *,
                        void *);
ssize_t Curl_llist_count(struct curl_llist *);
void Curl_llist_destroy(struct curl_llist *, void *);
void Curl_llist_move(struct curl_llist *, struct curl_llist_element *,
                     struct curl_llist *, struct curl_llist_element *);

#endif

