#include "seqlock.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READER 4
#define NUM_WRITER 1

int global_resource = 0;
pthread_seqlock_t seqlock;
pthread_t reader_list[NUM_READER];
pthread_t writer_list[NUM_WRITER];

void *reader(void *param)
{
    size_t id = (size_t) param;
    while (1)
    {
        int seq_before;
        int seq_current;
        int read_value;

        // read again if seq_before and seq_current is inconsistent
        do
        {
            seq_before = pthread_seqlock_rdlock(&seqlock);
            read_value = global_resource;
            seq_current = pthread_seqlock_rdunlock(&seqlock);
        } while (seq_before != seq_current);

        printf("Reader #%ld reads %d\n", id, read_value);
    }

    pthread_exit(NULL);
}

void *writer(void *param)
{
    size_t id = (size_t) param;

    // change global_resource whenever writer can without waiting for reader
    // of course still have to wait if there is other writer
    while (1)
    {
        pthread_seqlock_wrlock(&seqlock);
        global_resource++;
        printf("Writer #%ld increment to %d\n", id, global_resource);
        pthread_seqlock_wrunlock(&seqlock);
    }

    pthread_exit(NULL);
}

int main(void)
{
    pthread_seqlock_init(&seqlock);

    for (size_t i = 0; i < NUM_READER; i++)
    {
        pthread_create(&reader_list[i], NULL, reader, (void *) i);
    }

    for (size_t i = 0; i < NUM_WRITER; i++)
    {
        pthread_create(&writer_list[i], NULL, writer, (void *) i);
    }

    for (size_t i = 0; i < NUM_READER; i++)
    {
        pthread_join(reader_list[i], NULL);
    }

    for (size_t i = 0; i < NUM_WRITER; i++)
    {
        pthread_join(writer_list[i], NULL);
    }

    return EXIT_SUCCESS;
}
