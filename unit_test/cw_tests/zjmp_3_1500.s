.name       "zjmp_test3"
	.comment    "1500"

begin:
	sti r1, %:live, %1
	ld %:begin, r2
	sti r2, %400, %0
	sti r2, %400, %1
	sti r2, %400, %2
	sti r2, %400, %3
	sti r2, %400, %4
	zjmp %:begin
	sti r2, %400, %5
	sti r2, %400, %6
	ld	%0, r2
	zjmp %:live
live:
	live %0
set_carry:
	ld	%0, r2
	zjmp %:begin
