.name       "add_test3"
	.comment    "50"

ld	%5000, r2
ld	%10000, r3
add r2, r3, r4
sti r4, %500, %0
