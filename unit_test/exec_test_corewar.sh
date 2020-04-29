#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

FILE=../corewar
if test -f "$FILE"; then
	echo "$FILE exists"
	make -C ..
else
	echo "$FILE does not exist --> creating.."
	make re -C ..
fi

FILE=./cw_output
if test -f "$FILE"; then
	echo "$FILE exists"
else
	echo "$FILE does not exist --> creating.."
	mkdir cw_output
fi

FILE=./cw_result
if test -f "$FILE"; then
	echo "$FILE exists"
else
	echo "$FILE does not exist --> creating.."
	mkdir cw_result
fi

FILE=../cw_test_champs
if test -f "$FILE"; then
	echo "$FILE exists"
else
	echo "$FILE does not exist --> creating.."
	mkdir ../cw_test_champs
fi

TESTER=./support/tester/cw_tester
if test -f "$TESTER"; then
	echo "$TESTER exists"
else
	echo "$TESTER does not exist --> creating.."
	make re -C ./support/tester
fi

echo "creating .cor files.."

S_FILES=cw_tests/*.s
for s in $S_FILES
do 
	./support/real_asm $s
done

echo "testing corewar.."

rm -rf cw_result/*
rm -rf cw_output/*
TEST_FILES=cw_tests/*.cor
SUFFIX=".cor"
for t in $TEST_FILES
do
	TEST_NAME=$(echo $t | cut -c 10-50)
	TEST_NAME=${TEST_NAME%.cor}
	DUMP=${TEST_NAME##*_}
	./../corewar -v 16 -dump $DUMP $t > cw_output/test_my
	./support/real_core -v 16 -d $DUMP $t > cw_output/test_real
	./support/tester/cw_tester cw_output/test_my cw_output/test_real > cw_result/$TEST_NAME.result
	mv cw_output/test_real cw_output/$TEST_NAME.real
	mv cw_output/test_my cw_output/$TEST_NAME.my
done

echo "moving .cor files.."

rm -rf ../cw_test_champs/*.cor
for t in $TEST_FILES
do
	mv $t ../cw_test_champs/
done

echo "collecting results.."

RESULTS=cw_result/*
SUCCESS="test passed!"
for r in $RESULTS
do
	OUTPUT=$(cat $r)
	TEST=$(echo $r | cut -c 10-50)
	TEST=${TEST%.result}
	if [ "$OUTPUT" = "$SUCCESS" ]; then
		rm $r
		rm cw_output/$TEST.my
		rm cw_output/$TEST.real
		echo -e "${green}$TEST test passed${reset}"
	else
		exit -1;
    	echo "${red}$TEST faaaaaaaaaaaaill${reset}"
	fi
done
exit 0;



