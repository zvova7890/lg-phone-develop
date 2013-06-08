

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gl.h>




int glQueueListCreate(GLQueueList *list)
{
    list->first = list->last = 0;
    return 0;
}


int glQueueListDestroy(GLQueueList *list)
{
    ((void)list);
    return 0;
}


static inline void copy_body(GLQueueListItem *item, void *body, int size)
{
    unsigned int *in = (unsigned int *)item;
    unsigned int *out = (unsigned int *)body;

    //printf("body_size: %d\n", sizeof(GLQueueListItem)+body_size+4);

    in += 2;
    size /= 4;

    while(--size > -1)
        *in++ = *out++;
}


GLQueueListItem *glQueueListPush(GLQueueList *list, void *body, int body_size)
{
    GLQueueListItem *item = calloc(1, sizeof(GLQueueListItem) + body_size);

    copy_body(item, body, body_size);

    //memcpy(lol, body, body_size);

    if(list->last) {
        item->prev = list->last;
        item->next = 0;

        list->last->next = item;
        list->last = item;
    } else {
        item->next = 0;
        item->prev = 0;
        list->first = list->last = item;
    }

    return item;
}


GLQueueListItem *glQueueListPushFront(GLQueueList *list, void *body, int body_size)
{
    GLQueueListItem *item = calloc(1, sizeof(GLQueueListItem) + body_size);

    copy_body(item, body, body_size);

    if(list->first) {
        item->next = list->first;
        item->prev = 0;

        list->first->prev = item;
        list->first = item;
    } else {
        item->next = 0;
        item->prev = 0;
        list->first = list->last = item;
    }

    return item;
}


GLQueueListItem *glQueueListInsert(GLQueueList *list, void *body, int body_size, int at)
{
    // если имеем какие-то итемы
    if(list->last) {
        GLQueueListItem *it = list->first;

        // итерируем итемы
        int i;
        for(i = 0; it; it = it->next, ++i)
        {
            // есть такой итем
            if(i == at) {

                // выделяем память
                GLQueueListItem *item = calloc(1, sizeof(GLQueueListItem) + body_size);

                // копируем тело
                copy_body(item, body, body_size);

                // делаем вставку
                GLQueueListItem *prev = it->prev;
                prev->next = item;
                item->prev = prev;

                item->next = it;
                it->prev = item;

                return item;
            }
        }

        // если нне хватило одного итема, тоесть вставка производится в конец списка
        if(i == at-1) {
            return glQueueListPush(list, body, body_size);
        }

    // нету итемов вставка в начало списка
    } else if( at == 0 ) {
        return glQueueListPush(list, body, body_size);
    }

    return 0;
}


GLQueueListItem *glQueueListItem(GLQueueList *list, int at)
{
    GLQueueListItem *it = list->first;

    // итерируем итемы
    int i;
    for(i = 0; it; it = it->next, ++i)
    {
        // есть такой итем
        if(i == at) {
            return it;
        }
    }

    return 0;
}


int glQueueListPop(GLQueueList *list, GLQueueListItem *item)
{
    if(!list->last || !item)
        return -1;

    GLQueueListItem *prev = item->prev;

    if(prev) {

        /*
                   +>----2-->+
               +<--|--1--<+  |
               |   |      |  |
        <-prev->   <-item->  <-next->
        */

        GLQueueListItem *next = item->next;
        prev->next = next;

        if(next)
            next->prev = prev;
        else
            list->last = prev;

    } else {
        // firts item?
        list->first = item->next;
        if(list->first)
            list->first->prev = 0;
        else
            list->last = 0;
    }


    free(item);
    return 0;
}

