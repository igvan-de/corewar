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

###################################################

if [ 1 -eq 0 ]; then

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

fi

TEST_FILES=asm_output/*.my
for file in $TEST_FILES
do
	echo "$(basename "$file" .my).real"
	./support/tester/cw_tester $file "$(basename "$file" .my).real" > asm_result/"$(basename "$file" .my).result"
done
