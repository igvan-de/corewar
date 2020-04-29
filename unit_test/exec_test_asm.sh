#!/bin/bash

red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

FILE=../asm
if test -f "$FILE"; then
	echo "$FILE exists"
	make -C ..
else
	echo "$FILE does not exist --> creating.."
	make re -C ..
fi

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

TESTER=./support/tester/cw_tester
if test -f "$TESTER"; then
	echo "$TESTER exists"
else
	echo "$TESTER does not exist --> creating.."
	make re -C ./support/tester
fi

###################################################

echo "creating .cor files.."

S_FILES=asm_tests/*.s
for s in $S_FILES
do 
	../asm $s
done

mv asm_tests/*.cor asm_output

COR_FILES=asm_output/*.cor
for file in $COR_FILES
do
	mv "$file" "$(basename "$file" .cor).my"
done

mv *.my asm_output


################################################

for s in $S_FILES
do 
	support/real_asm $s
done

mv asm_tests/*.cor asm_output

COR_FILES=asm_output/*.cor
for file in $COR_FILES
do
	mv "$file" "$(basename "$file" .cor).real"
done

mv *.real asm_output

TEST_FILES=asm_output/*.my
for file in $TEST_FILES
do
	hexdump $file > my_output
	hexdump asm_output/"$(basename "$file" .my).real" > real_output
	./support/tester/cw_tester my_output real_output > asm_result/"$(basename "$file" .my).result"
	rm my_output
	rm real_output
done

#######################################################

echo "moving .cor files.."

rm -rf ../asm_test_champs/*.my
for t in $TEST_FILES
do
	mv $t ../asm_test_champs/"$(basename "$t" .my).cor"
done

echo "collecting results.."

RESULTS=asm_result/*.result
SUCCESS="test passed!"
for r in $RESULTS
do
	OUTPUT=$(cat $r)
	TEST=$(echo $r | cut -c 12-50)
	TEST=${TEST%.result}
	if [ "$OUTPUT" = "$SUCCESS" ]; then
		rm $r
		rm asm_output/$TEST.real
		echo -e "${green}$TEST test passed${reset}"
	else
		echo "${red}$TEST faaaaaaaaaaaaill${reset}"
		exit -1;
	fi
done
exit 0;
