.name "st_test2"
	.comment "1500"

start:
	ld %-23, r2
	st r2, r3
	st r3, r4
	st r5, r6
	st r6, -50
	ld %-25, r2
	st r2, r3
	st r3, r4
	st r5, r6
	st r6, -50
	ld %-26, r2
	st r2, r3
	st r3, r4
	st r5, r6
	st r6, -50
	ld %-27, r2
	st r2, r3
	st r3, r4
	st r5, r6
	st r6, -50
	ld %-28, r2
	st r2, r3
	st r3, r4
	st r5, r6
	st r6, -50
	ld %-29, r2
	st r2, r3
	st r3, r4
	st r5, r6
	st r6, -50
	sti r1, %:live, %1
live:
	live %0
	ld %0, r7
zjmp %:start
