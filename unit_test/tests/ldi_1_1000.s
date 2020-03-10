.name       "ldi_test1"
	.comment    "1000"

start:
	ldi %:live, %1, r2
	sti r2, %500, %0
live:
	live %42
