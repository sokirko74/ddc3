#ifndef  GramInfo_h
#define  GramInfo_h


//! CGramInfo represents one morphological pattern, for example "[SUB pl, sg]"
struct CGramInfo 
{
    //! the language of the pattern 
    MorphLanguageEnum       m_Language;
    //! the part of speech mask  (SUB, ART,ADJ...)
    uint32_t                           m_PartOfSpeechMask;
    //! morphological features (plu, sig, nom...)
    uint64_t                           m_Grammems;

    CGramInfo () {
        m_PartOfSpeechMask = 0;
        m_Grammems = 0;;
        m_Language = morphUnknown;

    };
    CGramInfo (MorphLanguageEnum Language, uint32_t PartOfSpeechMask, uint64_t Grammems)
    { 
        m_PartOfSpeechMask = PartOfSpeechMask;
        m_Grammems = Grammems;
        m_Language = Language;

    };
        

};

#endif
