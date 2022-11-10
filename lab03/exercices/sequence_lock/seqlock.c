#include "seqlock.h"

int pthread_seqlock_init(pthread_seqlock_t *sl)
{
    sl->seq_count = 0;
    pthread_mutex_init(&sl->writer_lock, NULL);
    pthread_mutex_init(&sl->reader_lock, NULL);
    pthread_cond_init(&sl->seq_count_even, NULL);

    return 0;
}

int pthread_seqlock_destroy(pthread_seqlock_t *sl)
{
    pthread_mutex_destroy(&sl->writer_lock);
    pthread_mutex_destroy(&sl->reader_lock);
    pthread_cond_destroy(&sl->seq_count_even);

    return 0;
}

int pthread_seqlock_rdlock(pthread_seqlock_t *sl)
{
    pthread_mutex_lock(&sl->reader_lock);
    int store_seq_count;
    while (1)
    {
        store_seq_count = sl->seq_count;
        if (store_seq_count % 2 == 0)
            break;
        pthread_cond_wait(&sl->seq_count_even, &sl->reader_lock);
    }
    pthread_mutex_unlock(&sl->reader_lock);

    return store_seq_count;
}

int pthread_seqlock_rdunlock(pthread_seqlock_t *sl)
{
    return pthread_seqlock_rdlock(sl);
}

int pthread_seqlock_wrlock(pthread_seqlock_t *sl)
{
    pthread_mutex_lock(&sl->writer_lock);
    sl->seq_count++;

    return 0;
}

int pthread_seqlock_wrunlock(pthread_seqlock_t *sl)
{
    sl->seq_count++;
    pthread_cond_broadcast(&sl->seq_count_even);
    pthread_mutex_unlock(&sl->writer_lock);

    return 0;
}

