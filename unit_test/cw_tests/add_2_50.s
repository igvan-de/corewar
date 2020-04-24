.name       "add_test2"
	.comment    "50"

ld	%500, r2
ld	%1000, r3
add r2, r3, r4
sti r4, %500, %0
