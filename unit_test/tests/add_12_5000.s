.name       "add_test12"
	.comment    "5000"

start:
	ld	%-10, r3
	ld	%10, r2
	add r2, r3, r4
	zjmp%:start
