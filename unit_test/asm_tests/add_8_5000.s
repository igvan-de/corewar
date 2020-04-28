.name       "add_test8"
	.comment    "50"

ld	%100, r3
add r1, r3, r4
ld	%56, r2
add r4, r2, r1
sti r4, %-500, %0
sti r1, %500, %0
