#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

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

echo "creating .cor files.."

S_FILES=tests/*
for s in $S_FILES
do 
	./support/asm $s
done

echo "testing corewar.."

rm -rf result/*
rm -rf output/*
TEST_FILES=tests/*.cor
SUFFIX=".cor"
for t in $TEST_FILES
do
	TEST_NAME=$(echo $t | cut -c 7-50)
	TEST_NAME=${TEST_NAME%.cor}
	DUMP=${TEST_NAME##*_}
	./../corewar -v 16 -dump $DUMP $t > output/test_my
	./support/real_core -v 16 -d $DUMP $t > output/test_real
	./support/tester/cw_tester output/test_my output/test_real > result/$TEST_NAME.result
	mv output/test_real output/$TEST_NAME.real
	mv output/test_my output/$TEST_NAME.my
done

echo "moving .cor files.."

rm -rf ../test_champs/*.cor
for t in $TEST_FILES
do
	mv $t ../test_champs/
done

echo "collecting results.."

RESULTS=result/*
SUCCESS="test passed!"
for r in $RESULTS
do
	OUTPUT=$(cat $r)
	TEST=$(echo $r | cut -c 8-50)
	TEST=${TEST%.result}
	if [ "$OUTPUT" = "$SUCCESS" ]; then
		rm $r
		rm output/$TEST.my
		rm output/$TEST.real
		echo -e "${green}$TEST test passed${reset}"
	else
    	echo "${red}$TEST faaaaaaaaaaaaill${reset}"
	fi

done


