.name       "ldi_test2"
	.comment    "5000"
	
	ld %0, r5
	zjmp%:start
live1:
	live %-1
live2:
	live %-1
	zjmp%:start
live3:
	live %-1
live4:
	live %-1
live5:
	live %-1	
live6:
	live %-1
start:
	ldi %:live1, %1, r2
	ldi r2, r1, r3
	sti r3, %-500, %0
	ldi %:live1, %1, r2
	sti r2, %-500, %0
	ldi %:live1, r3, r2
	sti r2, %-500, %0
	ldi %:live1, %1, r2
	sti r2, %-500, %0
	ldi %:live1, %1, r2
	zjmp%:live2
	sti r2, %-500, %0
	ldi %:live1, %1, r2
	sti r2, %-500, %0
	ldi %:live1, %1, r2
	sti r2, %-500, %0
	ldi %:live1, %1, r2
	sti r2, %-500, %0
	ldi %:live1, %1, r2
	sti r2, %-500, %0
	zjmp%:start
live7:
	live %-1
live8:
	live %-1
live9:
	live %-1
live10:
	live %-1
live11:
	live %-1
live12:
	live %-1
live13:
	live %-1
live14:
	live %-1
live15:
	live %-1
live16:
	live %-1
