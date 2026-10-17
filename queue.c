#include "codexion.h"

void    init_queue(t_pq *q,  int (*cmp)(t_request *, t_request *))
{
    q->head = NULL;
    q->size = 0;
    q->cmp = cmp;
}

t_request peek(t_pq *q)
{
    return (q->head->req);
}

void swap(t_request *a, t_request *b)
{
    t_request temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

t_node *get_node(t_node *node , int n)
{
    t_node	*found;
    
    if (!node)
        return (NULL);
    if (node->index == n)
        return (node);
    found = get_node(node->left, n);
    if (found)
        return (found);
    return (get_node(node->right, n));
}

void shift_up(t_pq *q, t_node *node)
{
    while(node->parent  && q->cmp(&node->req, &node->parent->req) < 0)
    {
        swap(&node->req, &node->parent->req);
        node=node->parent;
    }
}
void insert (t_pq *q, t_request req)
{
    t_node *node;
    t_node *parent;
    int n;

    node = malloc(sizeof(t_node));
    if (!node)
        return ;
    node->req =req;
    node->left =NULL;
    node->right = NULL;
    node->parent = NULL;
    n = q->size + 1;
    node->index = n;
    
    if (q->size==0)
        q->head=node;
    else
    {
        parent=get_node(q->head, n / 2);
        node->parent = parent;
		if (n % 2 == 0)               /* even → left child */
			parent->left = node;
		else                          /* odd  → right child */
			parent->right = node;
    }
        q->size++;
        shift_up(q, node);
        return;
}
void shift_down(t_pq *q, t_node *node)
{
    t_node *best;
    while(1)
    {
        best = node;
        if (node->left && q->cmp(&node->left->req, &best->req) < 0)
            best = node->left;
        if (node->right && q->cmp(&node->right->req, &best->req) < 0)
            best = node->right;
        if (best == node)
            break;
        swap(&node->req,&best->req);
        node = best;
    }
}

int extract(t_pq *q, t_request *req)
{
    t_node *last;
    if (!q || !q->head || q->size == 0)
        return (0);
    *req = q->head->req;
    if (q->size ==1)
    {
        free(q->head);
        q->head = NULL;
        q->size = 0;
        return(1);
    }
    last = get_node(q->head, q->size);
    swap(&last->req,&q->head->req);
    if (last->parent)
    {
        if (last->parent->left == last)
            last->parent->left = NULL;
        else
            last->parent->right = NULL;
    }
    free(last);
    shift_down(q, q->head);
    q->size--;
    return (1);
}
