.name       "sub_test7"
	.comment    "1500"

label:
	ld	%50, r2
	ld	%100, r3
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	sub r2, r3, r4
	sub r4, r3, r2
	sti r2, %500, %0
	ld %0, r5
	zjmp%:label
