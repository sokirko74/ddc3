EXTRA_DIST = \
 AncodePattern.cpp \
 AncodePattern.h \
 BigramsReader.cpp \
 BigramsReader.h \
 bserialize.h \
 cgic.c \
 cgic.cpp \
 cgic.h \
 Chunk.h \
 COMSyntaxHolder.cpp \
 COMSyntaxHolder.h \
 config.h \
 cortege.h \
 DDC_common.h \
 ddcConfigAuto.h \
 ddcConfig.h \
 DDCInternalError.h \
 ddcThreadQueue.h \
 DwdsThesaurus.cpp \
 DwdsThesaurus.h \
 file_off64_windows.c \
 gra_descr.cpp \
 gra_descr.h \
 gra_descr_primitives.h \
 GramInfo.h \
 Graspace.h \
 Homonym.cpp \
 Homonym.h \
 iconv_cpp.cpp \
 iconv_cpp.h \
 imports.h \
 LemWord.cpp \
 LemWord.h \
 MorphologyHolder.cpp \
 MorphologyHolder.h \
 MorphXmlToken.cpp \
 MorphXmlToken.h \
 PlmLine.cpp \
 PlmLine.h \
 ReadQueryFromInternet.cpp \
 RusCorpXml.cpp \
 RusCorpXml.h \
 rus_numerals.cpp \
 rus_numerals.h \
 SortWithTempFiles.h \
 string_tokenizer.h \
 SyntaxHolder.cpp \
 SyntaxHolder.h \
 util_classes.h \
 \
 common_exe_mak common_lib_mak common_mak \
 \
 ddcConfigAuto.h.in \
 ddcIconv.h \
 ddcRandom.h \
 ddcObject.h

# process_flex.sed process_yacc.sed


##-- extra sources
BUILT_SOURCES = \
	 ddcConfigNoAuto.h

##-- extra rules
ddcConfigNoAuto.h: ddcConfigAuto.h
	echo "/* src/common/ddcConfigNoAuto.h. Generated from ddcConfigAuto.h by make */" >ddcConfigNoAuto.h
	sed 's/^#define \([^ ]*\).*$$/#undef \1/;' ddcConfigAuto.h >>ddcConfigNoAuto.h

##-----------------------------------------------------------------------
## Variables: cleanup
##-----------------------------------------------------------------------

## --- mostlyclean: built by 'make' & commonly rebuilt
#MOSTLYCLEANFILES =

## --- clean:  built by 'make'
#CLEANFILES =


## --- distclean: built by 'configure'
DISTCLEANFILES = \
	ddcConfigNoAuto.h

## -- maintainerclean: built by maintainer / by hand
#MAINTAINERCLEANFILES =
