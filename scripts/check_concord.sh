#!/bin/sh
# Checking Dialing DWDS Concordance by a language
# written by Alexey Sokirko 2003, sokirko@yandex.ru

halt() {
	echo  "======================"
	echo  "Error: $errorstr"
	echo
	exit  1
}

bad_arguments() {
  errorstr="the first argument should be a language: Russian, English or German"
  halt;
}



if [ $# != 1 ]; then
	bad_arguments;
fi


for i in Russian English German; do
	if [ $i = $1 ]; then
		#Language=`expr substr $i 1 3`
		Language=`echo $i | awk "{print substr(\\$0,1,3);}"`
		break;
	fi
done

if [ -z $Language ]; then
	bad_arguments;
fi


if [ -z $RML ]; then
	errorstr="you should first register variable \$RML"
	halt;
fi;


if [ $1 = "Russian" ]; then

	if [ ! -e $RML/Dicts/Obor/cortege.bin ] ; then
		echo "Error: no Russian graphematical dictionaries are available (DDC compilation is incomplete)"
		exit 1
	fi

	if [ ! -e $RML/Dicts/Morph/Rus/morph.bases ] ; then
		if [ ! -e $RML/Dicts/SrcMorph/Rus.mwz ] ; then
			echo "Error: you should first install Russian morphological dicitonary (http://sf.net/projects/morph-lexicon/)"
			exit 1
		fi
		echo "Error: you should first run \"generate_morph_bin.sh Russian\""
		exit 1
	fi

elif [ $1 = "German" ]; then

	if [ ! -e $RML/Dicts/GerObor/cortege.bin ] ; then
		echo "Error: no German graphematical dictionaries are available (DDC compilation is incomplete)"
		exit 1
	fi

	if [ ! -e $RML/Dicts/Morph/Ger/morph.bases ] ; then
		if [ ! -e $RML/Dicts/SrcMorph/Ger.mwz ] ; then
			echo "Error: you should first install German morphological dicitonary (http://sf.net/projects/morph-lexicon/)"
			exit 1
		fi
		echo "Error: you should first run \"generate_morph_bin.sh German\""
		exit 1
	fi

elif [ $1 = "English" ]; then

	if [ ! -e $RML/Dicts/Morph/Eng/morph.bases ] ; then
		if [ ! -e $RML/Dicts/SrcMorph/Eng.mwz ] ; then
			echo "Error: you should first install English morphological dicitonary (http://sf.net/projects/morph-lexicon/)"
			exit 1
		fi
		echo "Error: you should first run \"generate_morph_bin.sh English\""
		exit 1
	fi

		
fi


echo "======== Indexing example corpus for $1 ========"
Bin/ConcordIndex Test/Concord/$Language/corpus.con

if [ "$?" -ne "0" ]; then
	errorstr="Cannot start indexing!"
	halt;
fi


echo "======== Querying corpus for $1 ========"
QueryStr=$(cat Test/Concord/$Language/query.txt)
echo "Query = $QueryStr"
echo "Bin/ConcordSimple Test/Concord/$Language/corpus.con $QueryStr temp.html"
Bin/ConcordSimple Test/Concord/$Language/corpus.con $QueryStr temp.html

rm Test/Concord/$Language/*._*;

tr -d '\r' < Test/Concord/$Language/result.html >Test/Concord/$Language/result.html_u

cmp temp.html Test/Concord/$Language/result.html_u

if [ "$?" -ne "0" ]; then
	#rm temp.html
	errorstr="The basic search test failed!"
	halt;
fi

rm temp.html


echo
echo "The check is passed. See Docs\DDCReadme.pdf to get information how to use DDC."
