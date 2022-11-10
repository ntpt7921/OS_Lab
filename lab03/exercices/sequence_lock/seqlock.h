#ifndef SEQLOCK_H
#define SEQLOCK_H

#include <pthread.h>

typedef struct
{
    int seq_count;
    pthread_mutex_t writer_lock;
    pthread_mutex_t reader_lock;
    pthread_cond_t seq_count_even;
} pthread_seqlock_t;

// return 0 on success, other for failure
// the failure case will not be imoplemented, because lazy
int pthread_seqlock_init(pthread_seqlock_t *sl);
int pthread_seqlock_destroy(pthread_seqlock_t *sl);

// reader lock will
// for lock: check even (if not wait signal), store that even value
// for unlock: check even (if not wait signal), store that even value
// return the stored even value in both case, it is the application responsibility to check
// this value before and after the read operation for consistency
int pthread_seqlock_rdlock(pthread_seqlock_t *sl);
int pthread_seqlock_rdunlock(pthread_seqlock_t *sl);

// writer lock will
// for lock: lock writer_lock and increment seq_count
// for unlock: increment seq_count, broadcast seq_count_even signal, unlock writer lock
int pthread_seqlock_wrlock(pthread_seqlock_t *sl);
int pthread_seqlock_wrunlock(pthread_seqlock_t *sl);

#endif
