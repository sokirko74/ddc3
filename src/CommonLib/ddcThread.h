//  This file by Bryan Jurish, adapted from https://vichargrave.github.io/articles/2012-12/java-style-thread-class-in-cpp
//

#ifndef DDC_THREAD_H
#define DDC_THREAD_H

#include "ddcConfig.h"
#include <pthread.h>
#include <string>

//======================================================================
/* generic lockable object wrapper class */
class ddcLockable
{
public:
    /* mutex for locking */
    mutable pthread_mutex_t m_Mutex;

public:
    /* default constructor initializes mutex */
    ddcLockable()
    { pthread_mutex_init(&m_Mutex,NULL); };

    /* default constructor de-initializes mutex */
    virtual ~ddcLockable()
    { pthread_mutex_destroy(&m_Mutex); };


public:
    /* locks m_Mutex for exclusive access; wraps pthread_mutex_lock() */
    inline int lock() const
    { return pthread_mutex_lock(&m_Mutex); };

    /* unlocks m_Mutex; wraps pthread_mutex_unlock() */
    inline int unlock() const
    { return pthread_mutex_unlock(&m_Mutex); };
};


//======================================================================
/* generic pthread wrapper class */
class ddcThread
{
protected:
    //--------------------------------------------------------------
    //  Administrivia
    //
    // underlying thread handle
    pthread_t m_tid;

    // underlying thread attributes (NULL by default)
    pthread_attr_t* m_attr;

    // is this thread is currently running?
    int m_running;

    // is this thread currently detached?
    int m_detached;
    //

public:
    //--------------------------------------------------------------
    //  Constructors etc.
    //

    /* Default constructor */
    ddcThread()
        : m_tid(0), m_attr(NULL), m_running(0), m_detached(0)
    {};

    /* Default destructor
     *  - detaches thread via pthread_detach() if running and not already detached
     *  - if thread is flagged as running, it will be cancelled via pthread_cancel()
     */
    virtual ~ddcThread();
    //

public:
    //--------------------------------------------------------------
    //  Accessors
    //
    // get current thread-id
    inline pthread_t self() const
    { return m_tid; };

    // get string representation of the current thread
    virtual std::string toString() const;

    // get current thread attributes (for use by child classes)
    inline pthread_attr_t* attr() const
    { return m_attr; };

    // get value of m_running flag
    inline int running() const
    { return m_running; };

    // get value of m_detached flag
    inline int detached() const
    { return m_detached; };
    //

public:
    //--------------------------------------------------------------
    //  Generic API
    //

    /* called by default start() to initalize m_attr.
     *  - default does nothing
     */
    virtual void init()
    {};

    /* calls pthread_create() to create the thread; sets m_running=true
     *  - default implementation also de-initializes m_attr via pthread_attr_destroy() if it is non-NULL
     */
    virtual int start();

    /* attempt to pthread_join() the current thread iff it is running.
     *  - blocks until thread has completed
     *  - if successful, thread is marked as detached
     *  returns ENOTSUP if thread is not running, otherwise as for pthread_join()
     */
    virtual int join();

    /* attempt to pthread_detach() the current thread iff it is running and not detached.
     *  - call if you don't want to wait for the thread to complete. 
     *  - on success, thread is flagged as detached.
     *  force: if true, thread will be flagged as not running.
     *         in this case, the underlying pthread may outlive the ddcThread wrapper object,
     *         and its run() method should terminate by calling pthread_exit().
     *  returns ENOTSUP if thread is not running, otherwise as for pthread_detach()
     */
    virtual int detach(bool force=false);

    /* code to execute inside the newly created thread after start()
     *  - derived clases must override this method
     *  returns void* as expected by pthread_create routines
     */
    virtual void* run() = 0;
    //

};

#endif /* defined(DDC_THREAD_H) */
