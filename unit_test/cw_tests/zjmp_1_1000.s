.name       "zjmp_test1"
	.comment    "1000"

begin:
	sti r1, %:live, %1
live:
	live %0
set_carry:
	ld	%0, r2
zjmp %:begin
