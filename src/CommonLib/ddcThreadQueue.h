//  This file by Bryan Jurish, adapted from https://vichargrave.github.io/articles/2013-01/multithreaded-work-queue-in-cpp
//

#ifndef DDC_THREAD_QUEUE_H
#define DDC_THREAD_QUEUE_H

#include "ddcConfig.h"
#include <pthread.h>
#include <list>

/* default maximum number of pending items for ddcThreadQueue */
#define DDC_DEFAULT_THREAD_QUEUE_SIZE 256

//======================================================================
/* generic thread-safe queue template class
 *  should use POD or pointer types for message-type T
 *
 */
template<typename T> class ddcThreadQueue
{
public:
    //--------------------------------------------------------------
    //  Types
    //
    // message item type
    typedef T ItemT;
    //

public:
    //--------------------------------------------------------------
    //  Data
    // (all public, because private data is annoying)
    //

    // underlying message queue
    std::list<T>   m_queue;

    // maximum number of enqueued messages (default=DDC_DEFAULT_THREAD_QUEUE_SIZE: unlimited)
    size_t m_max_size;

    // pthread mutex for locking queue access
    pthread_mutex_t m_mutex;
    
    // pthread condition variable for signalling queue insertions
    pthread_cond_t  m_condv_added;
    
    // pthread condition variable for signalling queue removals
    pthread_cond_t  m_condv_removed;
    //

public:
    //--------------------------------------------------------------
    //  API: Constructors etc.
    //
    /* Default constructor */
    ddcThreadQueue(size_t max_size=DDC_DEFAULT_THREAD_QUEUE_SIZE)
        : m_max_size(max_size)
    {
        pthread_mutex_init(&m_mutex, NULL);
        pthread_cond_init(&m_condv_added, NULL);
        pthread_cond_init(&m_condv_removed, NULL);
    };

    /* Default destructor */
    ~ddcThreadQueue()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_condv_added);
        pthread_cond_destroy(&m_condv_removed);
    };
    //

    //--------------------------------------------------------------
    //  API: Queue operations
    //

    /* add an item to the end of the queue
     *  - handles queue locking
     *  - waits on m_condv_removed if queue is already at maximum size
     *  - signals m_condv_added after inserting the new item
     */
    void add(T item)
    {
        pthread_mutex_lock(&m_mutex);
        while (m_queue.size() == m_max_size) {
            //fprintf(stderr, "ddcThreadQueue::add(): max queue size (%zu) reached; waiting...", m_queue.size());
            pthread_cond_wait(&m_condv_removed, &m_mutex);
        }
        //fprintf(stderr, "ddcThreadQueue::add(): appending queue item to queue of size %zu", m_queue.size());
        m_queue.push_back(item);
        pthread_cond_signal(&m_condv_added);
        pthread_mutex_unlock(&m_mutex);
    };

    /* remove an item from the front of the queue
     *  - handles queue locking
     *  - waits on m_condv_added if queue is empty
     *  - signals m_condv_removed after removing an item
     */
    T remove()
    {
        pthread_mutex_lock(&m_mutex);
        while (m_queue.size() == 0) {
            pthread_cond_wait(&m_condv_added, &m_mutex);
        }

        T item = m_queue.front();
        m_queue.pop_front();

        pthread_cond_signal(&m_condv_removed);
        pthread_mutex_unlock(&m_mutex);
        return item;
    };


    /* convenience wrapper for checking current queue size
     *  - handles queue locking
     */
    size_t size() const
    {
        pthread_mutex_lock(&m_mutex);
        size_t sz = m_queue.size();
        pthread_mutex_unlock(&m_mutex);
        return sz;
    };
};

#endif /* DDC_THREAD_QUEUE_H */
