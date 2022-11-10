
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>

/* Remember to initilize the queue before using it */
void initialize_queue(struct pqueue_t * q) {
	q->head = q->tail = NULL;
	pthread_mutex_init(&q->lock, NULL);
}

/* Return non-zero if the queue is empty */
int empty(struct pqueue_t * q) {
	return (q->head == NULL);
}

/* Get PCB of a process from the queue (q).
 * Return NULL if the queue is empty */
struct pcb_t * de_queue(struct pqueue_t * q) {
	struct pcb_t * proc = NULL;
	// TODO: return q->head->data and remember to update the queue's head
	// and tail if necessary. Remember to use 'lock' to avoid race
	// condition

	// YOUR CODE HERE
    pthread_mutex_lock(&q->lock);
    {
        if (q->head != NULL)
        {
            proc = q->head->data;
            struct qitem_t *new_head = q->head->next;
            free(q->head);
            q->head = new_head;
        }
    }
    pthread_mutex_unlock(&q->lock);

	return proc;
}

/* Put PCB of a process to the queue. */
void en_queue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update q->tail.
	// Remember to use 'lock' to avoid race condition

	// YOUR CODE HERE
    pthread_mutex_lock(&q->lock);
    {
        struct qitem_t *new_item =
            (struct qitem_t*) malloc(1 * sizeof(struct qitem_t));
        new_item->data = proc;
        new_item->next = NULL;

        if (q->head == NULL)
        {
            q->head = q->tail = new_item;
        }
        else
        {
            q->tail->next = new_item;
            q->tail = new_item;
        }
    }
    pthread_mutex_unlock(&q->lock);
}


