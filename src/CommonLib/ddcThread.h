//-*- Mode: C++; c-basic-offset: 4; -*-
//
//  DDC originally by Alexey Sokirko
//  This file by Bryan Jurish, adapted from https://vichargrave.github.io/articles/2012-12/java-style-thread-class-in-cpp
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
#ifndef DDC_THREAD_H
#define DDC_THREAD_H

#include "ddcConfig.h"
#include <pthread.h>
#include <string>

//======================================================================
/** \brief generic lockable object wrapper class */
class ddcLockable
{
public:
    /** mutex for locking */
    mutable pthread_mutex_t m_Mutex;

public:
    /** default constructor initializes mutex */
    ddcLockable()
    { pthread_mutex_init(&m_Mutex,NULL); };

    /** default constructor de-initializes mutex */
    ~ddcLockable()
    { pthread_mutex_destroy(&m_Mutex); };


public:
    /** locks m_Mutex for exclusive access; wraps pthread_mutex_lock() */
    inline int lock() const
    { return pthread_mutex_lock(&m_Mutex); };

    /** unlocks m_Mutex; wraps pthread_mutex_unlock() */
    inline int unlock() const
    { return pthread_mutex_unlock(&m_Mutex); };
};


//======================================================================
/** \brief generic pthread wrapper class */
class ddcThread
{
protected:
    //--------------------------------------------------------------
    //! \name Administrivia
    //@{
    //! underlying thread handle
    pthread_t m_tid;

    //! underlying thread attributes (NULL by default)
    pthread_attr_t* m_attr;

    //! is this thread is currently running?
    int m_running;

    //! is this thread currently detached?
    int m_detached;
    //@}

public:
    //--------------------------------------------------------------
    /// \name Constructors etc.
    //@{

    /** Default constructor */
    ddcThread()
	: m_tid(0), m_attr(NULL), m_running(0), m_detached(0)
    {};

    /** Default destructor
     *  \li detaches thread via pthread_detach() if running and not already detached
     *  \li if thread is flagged as running, it will be cancelled via pthread_cancel()
     */
    virtual ~ddcThread();
    //@}

public:
    //--------------------------------------------------------------
    /// \name Accessors
    //@{
    //! get current thread-id
    inline pthread_t self() const
    { return m_tid; };

    //! get string representation of the current thread
    virtual std::string toString() const;

    //! get current thread attributes (for use by child classes)
    inline pthread_attr_t* attr() const
    { return m_attr; };

    //! get value of \a m_running flag
    inline int running() const
    { return m_running; };

    //! get value of \a m_detached flag
    inline int detached() const
    { return m_detached; };
    //@}

public:
    //--------------------------------------------------------------
    /// \name Generic API
    //@{

    /** called by default start() to initalize \a m_attr.
     *  \li default does nothing
     */
    virtual void init()
    {};

    /** calls pthread_create() to create the thread; sets \a m_running=true
     *  \li default implementation also de-initializes \a m_attr via pthread_attr_destroy() if it is non-NULL
     */
    virtual int start();

    /** attempt to pthread_join() the current thread iff it is running.
     *  \li blocks until thread has completed
     *  \li if successful, thread is marked as detached
     *  \returns ENOTSUP if thread is not running, otherwise as for pthread_join()
     */
    virtual int join();

    /** attempt to pthread_detach() the current thread iff it is running and not detached.
     *  \li call if you don't want to wait for the thread to complete. 
     *  \li on success, thread is flagged as detached.
     *  \param force if true, thread will be flagged as \b not running.
     *         in this case, the underlying pthread may outlive the ddcThread wrapper object,
     *         and its run() method should terminate by calling pthread_exit().
     *  \returns ENOTSUP if thread is not running, otherwise as for pthread_detach()
     */
    virtual int detach(bool force=false);

    /** code to execute inside the newly created thread after start()
     *  \li derived clases \b must override this method
     *  \returns void* as expected by pthread_create routines
     */
    virtual void* run() = 0;
    //@}

};

#endif /* defined(DDC_THREAD_H) */
