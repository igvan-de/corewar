.name       "zjmp_test5"
	.comment    "1600"

one:
	ld	%0, r2
	zjmp%:two
two:
	sti r1, %:three, %1
	zjmp%:three
eleven:
	zjmp%:twelve
three:
	live %0
	zjmp%:four
four:
	zjmp%:five
five:
	zjmp%:six
twelve:
	zjmp%:thirteen
six:
	zjmp%:seven
seven:
	zjmp%:eight
eight:
	zjmp%:nine
nine:
	zjmp%:ten
ten:
	ld	%-5, r2
	sti r2, %-500, %0
	sti r2, %-500, %1
	sti r2, %-500, %2
	sti r2, %-500, %3
	ld	%-10, r3
	sti r3, %-500, %0
	ld	%-15, r3
	sti r3, %-500, %0
	ld	%-5, r2
	sti r2, %500, %0
	sti r2, %500, %1
	sti r2, %500, %2
	sti r2, %500, %3
	ld	%-10, r3
	sti r3, %500, %0
	ld	%-15, r3
	sti r3, %500, %0
	ld	%0, r2
	zjmp%:eleven
thirteen:
	zjmp%:fourteen
fourteen:
	zjmp%:fifteen
fifteen:
	zjmp%:sixteen
sixteen:
	zjmp%:seventeen
seventeen:
	zjmp%:eighteen
eighteen:
	zjmp%:nineteen
nineteen:
	zjmp%:twenty
twenty:
	zjmp%:twentyone
twentyone:
	zjmp%:twentytwo
twentytwo:
	zjmp%:twentythree
twentythree:
	zjmp%:one
