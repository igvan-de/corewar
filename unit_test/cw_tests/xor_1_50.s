.name       "xor_test1"
	.comment    "50"

ld	%50, r2
ld	%100, r3
xor r2, r3, r4
sti r4, %500, %0
