#include "llist.h"

void Curl_llist_init(struct curl_llist *l, curl_llist_dtor dtor)
{
    l->size = 0;
    l->dtor = dtor;
    l->head = NULL;
    l->tail = NULL;
    return;
}

void Curl_llist_insert_next(struct curl_llist *list, struct curl_llist_element *e,
                                const void *ptr, struct curl_llist_element *ne)
{
    if (NULL == list || NULL == ne)
        return;
   
    ne->ptr = (void*)ptr;
    if (0 == list->size)
    {
        // llist为NULL
        list->head = ne;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = ne;
    }
    else {
        ne->next = e?e->next:list->head;
        ne->prev = e;
        if (!e) {
            // e为NULL, 插入header
           list->head->prev = ne;
           list->head = ne;
        }
        else if (e->next) {
            e->next->prev = ne;
        }
        else {
            // 插入e的尾部
            e->next = ne;
            list->tail = ne;
        }
    }
    ++list->size;

    return;
}

void Curl_llist_remove(struct curl_llist *list, struct curl_llist_element *e,
                        void *user)
{
    void *ptr;
    if (NULL == list || 0 == list->size)
        return;

    if (list->head == e){
        list->head = e->next;
        if (NULL == list->head)
            list->tail = NULL;
        else
            e->next->prev = NULL;
    }
    else {
        // e的next处理
        if (NULL == e->prev) 
           list->head = e->next; 
        else 
            e->prev->next = e->next;
        // e的prev处理
        if (NULL == e->next) 
            list->tail = e->prev;
        else 
            e->next->prev = e->prev;
    }
    ptr = e->ptr;

    e->ptr = NULL;
    e->next = NULL;
    e->prev = NULL;

    --list->size;

    if (list->dtor)
        list->dtor(user, ptr);
    
    return;
}

ssize_t Curl_llist_count(struct curl_llist *list)
{
    return list->size;
}

void Curl_llist_destroy(struct curl_llist *list, void *user)
{
    while (list->size > 0)
        Curl_llist_remove(list, list->tail, user);
        
    return;
}

void Curl_llist_move(struct curl_llist *list, struct curl_llist_element *e,
                     struct curl_llist *to_list, struct curl_llist_element *to_e)
{
    if (NULL == list || NULL == to_list || list->size < 0)
        return;
    
    // 移除list
    if (list->head == e) {
       list->head = e->next;
       if (NULL == e->next) 
           list->tail = list->head;
       else
           list->head->prev = NULL;
    }
    else {
        if (NULL == e->prev)
            list->head = e->next;
        else
            e->prev->next = e->next;

        if (NULL == e->next)
            list->tail = e->prev;
        else
            e->next->prev = e->prev;
    }
    --list->size;

    e->prev = NULL;
    e->next = NULL;
    // 添加到to_list
    if (0 == to_list->size) { 
        to_list->head = e;
        to_list->tail = e;
    }
    else {
        if (NULL == to_e)
        {
            // 添加到to_list的head
            e->next = to_list->head;
            e->next->prev = e;
            to_list->head = e;
        }
        else {
            // 插入到to_e后面
            if (NULL == to_e->next) {
                // to_e为tail
                to_e->next = e; 
                e->prev = to_e;
                to_list->tail = e;
            }
            else {
                // to_e在mid
                e->prev = to_e;
                e->next = to_e->next;
                to_e->next->prev = e;
                to_e->next = e;
            }
        }
    }
    ++to_list->size;

    return;
}
