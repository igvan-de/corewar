.name "championes"
.comment "This is a champion mi dolore de cabeza"

init:
	ld %4, r3				# index offset 	
	sti r1, %:live, %1				
	sti r1, %:live2, %1				
	sti r1, %:live3, %1	
	ld %0, r2				# switch the carry				
	ld %4, r3		
	sti r1, %:live, %1				
	sti r1, %:live2, %1				
	sti r1, %:live3, %1	
	ld %0, r2				
	zjmp %:copy
copy:
	ldi %:init, r2, r4
	sti r4, %:dest, r2
	add r4, r10, r4
	zjmp %:lfork
lfork_return:
	ld %0, r4
	add r2, r3, r2
live:
	live %1
live2:
	live %1
live3:
	live %1
	ld %0, r5
	zjmp %:copy
lfork:
	lfork %:dest
	ld %0, r4
	zjmp %:lfork_return
dest:
	live %1
