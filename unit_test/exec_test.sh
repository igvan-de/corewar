#!/bin/bash

FILE=../corewar
if test -f "$FILE"; then
	echo "$FILE exists"
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

S_FILES=tests/*
for s in $S_FILES
do 
	./support/asm $s
done

rm -rf result/*
rm -rf output/*
TEST_FILES=tests/*.cor
SUFFIX=".cor"
for t in $TEST_FILES
do
	TEST_NAME=$(echo $t | cut -c 7-50)
	TEST_NAME=${TEST_NAME%.cor}
	DUMP=${TEST_NAME##*_}
	./../corewar -v 18 -dump $DUMP $t > output/test_my
	./support/real_core -v 18 -d $DUMP $t > output/test_real
	echo "storing test outcome in $TEST_NAME.result"
	./support/tester/cw_tester output/test_my output/test_real > result/$TEST_NAME.result
	mv output/test_real output/$TEST_NAME.real
	mv output/test_my output/$TEST_NAME.my
done

rm -rf ../test_champs/*.cor
for t in $TEST_FILES
do
	mv $t ../test_champs/
done

