#ifndef DDC_RANDOM_H
#define DDC_RANDOM_H

#include <stdlib.h>
#include "ddcConfig.h"

#if defined(HAVE_ERAND48) || defined(HAVE_JRAND48) || defined(HAVE_NRAND48)
# define DDC_RAND48 1
#else
# undef DDC_RAND48
#endif

//======================================================================
/*!
  \brief
  thread-safe pseudo-random number stream using drand48() & friends
*/
class DDCRandom {
public:
    //! underlying random seed for POSIX.1 random numbers using rand_r() or srand()+rand() hack
    unsigned int m_seed;

#ifdef DDC_RAND48
    //! underlying computation state (defaults to {m_seed,m_seed,m_seed}) for jrand48() & friends
    unsigned short m_state[3];
#endif

public:
    //------------------------------------------------------------
    ///\name Constructors etc.
    //@{
    //! Constructor given state
    DDCRandom(unsigned int seed=0)
    {
        set_seed(seed);
    };

    //! set internal seed
    void set_seed(unsigned int seed=0)
    {
        m_seed = seed;
#ifdef DDC_RAND48
        m_state[0]=seed;
        m_state[1]=seed;
        m_state[2]=seed;
#endif
    };

    //! Default destructor.
    ~DDCRandom(void) {};
    //@}

public:
    //------------------------------------------------------------
    ///\name API
    //@{

    //! returns a pseudo-random double in the range [0,1)
    inline double random_d(void) {
#if defined(HAVE_ERAND48)
        return erand48(m_state);
#elif defined(HAVE_RAND_R)
        return (double)rand_r(&m_seed) / (double)RAND_MAX;
#else
        srand(m_seed++);
        return (double)rand() / (double)RAND_MAX;
#endif
    };

    //! returns a pseudo-random long in the range [-2**31,2**31)
    inline long random_l(void) {
#if defined(HAVE_JRAND48)
        return (long)jrand48(m_state);
#elif defined(HAVE_RAND_R)
        return (long)rand_r(&m_seed);
#else
        srand(m_seed++);
        return (long)rand();
#endif
    };

    //! returns a pseudo-random unsigned long in the range [0,2**31)
    inline long random_n(void) {
        //return (unsigned long)random_l();
#if defined(HAVE_NRAND48)
        return (long)nrand48(m_state);
#else
        return random_l();
#endif
    };
    //@}
};

#endif /* DDC_RANDOM_H */
