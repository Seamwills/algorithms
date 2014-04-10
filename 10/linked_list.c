struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode, *list;

/* initialize a list with sentinel, sen->next points to the first node */
list
list_init(void)
{
    listNode *sen;

    sen = malloc(sizeof(listNode));
    sen->prev = sen->next = NULL;

    return sen;
}

/* prepend an node in front of the list, return the list if succeed */
list
list_prepend(list sen, void *value)
{
    listNode *node;

    /* if failed, return NULL */
    node = malloc(sizeof(listNode));
    node->value = value;
    
    node->next = sen->next;
    sen->next->prev = node;
    sen->next = node;
    node->prev = sen;

    return sen;
}

/* search node with specific value */
listNode *
list_search(list sen, void *value)
{
    listNode *x;

    x = sen->next;
    while (x != sen && x->value != value)
        x = x->next;

    /* if x != sen, node found */
    return x;
}

/* delete an node from the list */
void
list_delete(list sen, listNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    /* free the deleted node */
}
