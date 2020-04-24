#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

FILE=./asm_output
if test -f "$FILE"; then
	echo "$FILE exists"
else
	echo "$FILE does not exist --> creating.."
	mkdir asm_output
fi

FILE=./asm_result
if test -f "$FILE"; then
	echo "$FILE exists"
else
	echo "$FILE does not exist --> creating.."
	mkdir asm_result
fi

FILE=../asm_test_champs
if test -f "$FILE"; then
	echo "$FILE exists"
else
	echo "$FILE does not exist --> creating.."
	mkdir ../asm_test_champs
fi

FILE=../asm
if test -f "$FILE"; then
	echo "$FILE exists"
	make -C ..
else
	echo "$FILE does not exist --> creating.."
	make re -C ..
fi

TESTER=./support/tester/cw_tester
if test -f "$TESTER"; then
	echo "$TESTER exists"
else
	echo "$TESTER does not exist --> creating.."
	make re -C ./support/tester
fi

echo "creating .cor files.."

S_FILES=asm_tests/*.s
for s in $S_FILES
do 
	../asm $s
done

rm -rf asm_tests/*.cor


#CORFILES=asm_tests/*.cor
#for c in $CORFILES
#do
#	../corewar -v 16 -dump 100 c