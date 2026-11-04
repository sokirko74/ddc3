#ifndef  DDCLessOperators_h
#define  DDCLessOperators_h



//! LessIndexString1 is a template  operator "less" for an \ref index_set_def "index set" (the first version)
//! This less operator provides quite "normal" less and equal operators for stings. The only 
//! difference is that the first compared item is obtained not by a pointer, but by an offset to 
//! LessIndexString1::m_pBuffer.
template <class IndexType, typename VectorType=std::vector<char> >
class LessIndexString1 : public std::binary_function<bool, const IndexType&, const char&> 
{
    const VectorType* m_pBuffer;

public:

    LessIndexString1(const VectorType* pBuffer)
    {
        m_pBuffer = pBuffer;
    }  
    //! operator less for strings
    bool  operator()(const IndexType& Ref, const char* S2) const
    {
        const char*  S1 = &((*m_pBuffer)[0]) + Ref.GetIndexItemOffset();
        return strcmp(S1, S2) < 0;
    }
    bool  operator()(const char* S1, const IndexType& Ref) const
    {
        const char*  S2 = &((*m_pBuffer)[0]) + Ref.GetIndexItemOffset();
        return strcmp(S1, S2) < 0;
    }
    bool  operator()(const IndexType& Ref1, const IndexType& Ref2) const
    {
        const char*  S1 = &((*m_pBuffer)[0]) + Ref1.GetIndexItemOffset();
        const char*  S2 = &((*m_pBuffer)[0]) + Ref2.GetIndexItemOffset();
        return strcmp(S1, S2) < 0;
    }

    //! operator == for strings
    bool  are_equal(const IndexType& Ref, const char* S2) const
    {
        const char*  S1 = &((*m_pBuffer)[0]) + Ref.GetIndexItemOffset();
        return strcmp(S1, S2) == 0;             
    };

};



//! LessIndexString2 is a template  operator "less" for an \ref index_set_def "index set"(the second  version)
//! This less operator provides quite "normal" less and greater operators for stings. The only 
//! difference is that the compared items are obtained not by a pointer, but by an offset to 
//! LessIndexString2::m_pBuffer1 and  LessIndexString2::m_pBuffer2 accordingly.
template <class IndexType, typename VectorType=std::vector<char> >
class LessIndexString2 : public std::binary_function<bool, const IndexType&, const IndexType&>
{
    const VectorType* m_pBuffer1;
    const VectorType* m_pBuffer2;
public:  

    LessIndexString2(const VectorType* pBuffer1, const VectorType* pBuffer2 = 0) 
    {
        m_pBuffer1 = pBuffer1;
        m_pBuffer2 = (pBuffer2 != 0) ? pBuffer2 : pBuffer1;
    }  

    //! operator less for strings
    bool  operator()(const IndexType& W1, const IndexType& W2) const
    {
        const char*  S1 = &((*m_pBuffer1)[0]) + W1.GetIndexItemOffset();
        const char*  S2 = &((*m_pBuffer2)[0]) + W2.GetIndexItemOffset();
        return strcmp(S1, S2) < 0;
    }

    //! operator greater for strings
    bool  Greater(const IndexType& W1, const IndexType& W2) const
    {
        const char*  S1 = &((*m_pBuffer1)[0]) + W1.GetIndexItemOffset();
        const char*  S2 = &((*m_pBuffer2)[0]) + W2.GetIndexItemOffset();
        return strcmp(S1, S2) > 0;
    }
};

#endif
