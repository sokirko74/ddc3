//-*- Mode: C++; c-basic-offset: 4; -*-
//
//  DDC originally by Alexey Sokirko
//  This file by Bryan Jurish, adapted from https://vichargrave.github.io/articles/2013-01/multithreaded-work-queue-in-cpp
//
//  This file is part of DDC.
// 
//  DDC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  DDC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with DDC.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef DDC_THREAD_QUEUE_H
#define DDC_THREAD_QUEUE_H

#include "ddcConfig.h"
#include <pthread.h>
#include <list>

/** default maximum number of pending items for ddcThreadQueue */
#define DDC_DEFAULT_THREAD_QUEUE_SIZE 256

//======================================================================
/** \brief generic thread-safe queue template class
 *  \detail should use POD or pointer types for message-type T
 *
 */
template<typename T> class ddcThreadQueue
{
public:
    //--------------------------------------------------------------
    //! \name Types
    //@{
    //! message item type
    typedef T ItemT;
    //@}

public:
    //--------------------------------------------------------------
    //! \name Data
    // (all public, because private data is annoying)
    //@{

    //! underlying message queue
    std::list<T>   m_queue;

    //! maximum number of enqueued messages (default=DDC_DEFAULT_THREAD_QUEUE_SIZE: unlimited)
    size_t m_max_size;

    //! pthread mutex for locking queue access
    pthread_mutex_t m_mutex;
    
    //! pthread condition variable for signalling queue insertions
    pthread_cond_t  m_condv_added;
    
    //! pthread condition variable for signalling queue removals
    pthread_cond_t  m_condv_removed;
    //@}

public:
    //--------------------------------------------------------------
    //! \name API: Constructors etc.
    //@{
    /** Default constructor */
    ddcThreadQueue(size_t max_size=DDC_DEFAULT_THREAD_QUEUE_SIZE)
	: m_max_size(max_size)
    {
        pthread_mutex_init(&m_mutex, NULL);
        pthread_cond_init(&m_condv_added, NULL);
	pthread_cond_init(&m_condv_removed, NULL);
    };

    /** Default destructor */
    ~ddcThreadQueue()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_condv_added);
	pthread_cond_destroy(&m_condv_removed);
    };
    //@}

    //--------------------------------------------------------------
    //! \name API: Queue operations
    //@{

    /** add an item to the end of the queue
     *  \li handles queue locking
     *  \li waits on m_condv_removed if queue is already at maximum size
     *  \li signals m_condv_added after inserting the new item
     */
    void add(T item)
    {
        pthread_mutex_lock(&m_mutex);
	while (m_queue.size() == m_max_size) {
	    //fprintf(stderr, "ddcThreadQueue::add(): max queue size (%zu) reached; waiting...\n", m_queue.size());
            pthread_cond_wait(&m_condv_removed, &m_mutex);
        }
	//fprintf(stderr, "ddcThreadQueue::add(): appending queue item to queue of size %zu\n", m_queue.size());
        m_queue.push_back(item);
        pthread_cond_signal(&m_condv_added);
        pthread_mutex_unlock(&m_mutex);
    };

    /** remove an item from the front of the queue
     *  \li handles queue locking
     *  \li waits on m_condv_added if queue is empty
     *  \li signals m_condv_removed after removing an item
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


    /** convenience wrapper for checking current queue size
     *  \li handles queue locking
     */
    size_t size() const
    {
        pthread_mutex_lock(&m_mutex);
        size_t size = m_queue.size();
        pthread_mutex_unlock(&m_mutex);
        return size;
    };
};

#endif /* DDC_THREAD_QUEUE_H */
