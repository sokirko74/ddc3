#!/bin/sh
# Compiling Dialing/DWDS Concordance
# written by Alexey Sokirko 2003, sokirko@yandex.ru

halt() {
	echo  "======================"
	echo  "Error: $errorstr"
	echo
	exit  1
}


if [ -z $RML ]; then
	errorstr="you should first register variable \$RML"
	halt;
fi;

if [ -x /usr/bin/gmake ]; then
	make_tool=gmake
else
    make_tool=make
fi


echo "================ Compiling ConcordIndex ==================="
$make_tool -C $RML/Source/ConcordIndex mode=release

if [ "$?" -ne "0" ]; then
	errorstr="cannot compile ConcordIndex"
	halt;
fi

echo "================ Compiling ConcordSimple ==================="
$make_tool -C $RML/Source/ConcordSimple mode=release

if [ "$?" -ne "0" ]; then
	errorstr="cannot compile ConcordSimple"
	halt;
fi

echo "================ Compiling ConcordConsole ==================="
$make_tool -C $RML/Source/ConcordConsole mode=release

if [ "$?" -ne "0" ]; then
	errorstr="cannot compile ConcordConsole"
	halt;
fi

echo "================ Compiling ConcordDaemon ==================="
$make_tool -C $RML/Source/ConcordDaemon mode=release_thread

if [ "$?" -ne "0" ]; then
	errorstr="cannot compile ConcordDaemon"
	halt;
fi


echo "================ Compiling CGI Script 'Search' ==================="
$make_tool -C $RML/Source/Search mode=release_thread

if [ "$?" -ne "0" ]; then
	errorstr="cannot compile Search"
	halt;
fi


echo "================ Compiling 'ddc_xml' ==================="
$make_tool -C $RML/Source/ddc_xml mode=release_thread

if [ "$?" -ne "0" ]; then
	errorstr="cannot compile ddc_xml"
	halt;
fi

#./gen_graphan_bin.sh Russian
#if [ "$?" -ne "0" ]; then
#	errorstr="cannot compile graphematical dictionaries for Russian"
#	halt;
#fi

./gen_graphan_bin.sh German
if [ "$?" -ne "0" ]; then
	errorstr="cannot compile graphematical dictionaries for German"
	halt;
fi

echo "Compilation was successful. Use check_concord.sh  to run test suite"
