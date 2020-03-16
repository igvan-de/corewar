.name       "zjmp_test4"
	.comment    "1500"

one:
	ld	%0, r2
	zjmp%:two
two:
	sti r1, %:three, %1
	zjmp%:three
three:
	live %0
	zjmp%:four
four:
	zjmp%:five
five:
	zjmp%:one
