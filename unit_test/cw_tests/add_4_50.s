.name       "add_test4"
	.comment    "50"

ld	%50000, r2
ld	%100000, r3
add r2, r3, r4
sti r4, %500, %0
