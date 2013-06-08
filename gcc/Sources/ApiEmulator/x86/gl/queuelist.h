
#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#if 0

typedef struct
{
    void *prev;
    void *next;
    //int   body;
}GLQueueListItem __attribute__((aligned(4)));




typedef struct
{
    GLQueueListItem *first,
                    *last;
}GLQueueList;



int glQueueListCreate(GLQueueList *list);
int glQueueListDestroy(GLQueueList *list);
GLQueueListItem *glQueueListPush(GLQueueList *list, void *body, int body_size /* must be aligned by 4! */);
int glQueueListPop(GLQueueList *list, GLQueueListItem *item);

#define queueListItemBody(item, type) (type)(((char *)&item->next) + sizeof(void*))

#endif

#endif

