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
void push (t_pq *q, t_request req)
{
    t_node *n;
    //t_node *prev;
    t_node *curr;

    n = malloc(sizeof(t_node));
    if (!n)
        return ;
    n->req =req;
    n->next =NULL;
    n->prev = NULL;
    curr =  q->head;
    while( curr && q->cmp(&curr->req,&req) < 0)
    {
        n->prev = curr;
        curr = curr->next;
    }
    n->next = curr;
    if (!n->prev) 
        q->head = n;
    else
        n->prev->next = n;
    q->size++;
}
//
t_node *pop(t_pq *q)
{
    t_node	*temp;

	if (!q || q -> size == 0)
		return (NULL);
	temp = q -> head;
	q -> head = q -> head -> next;
	if (q -> head)
		q -> head -> prev = NULL;
	else
		q -> head = NULL;
	temp -> next = NULL;
	temp -> prev = NULL;
	q -> size--;
	return (temp);
}
