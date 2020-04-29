.name       "zjmp_test2"
	.comment    "1000"

begin:
	ld	%-2352, r2
	sti r1, %:live, %1
live:
	live %234242
set_carry:
	ld	%0, r2
zjmp %:begin
