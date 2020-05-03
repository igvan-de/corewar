.name "invalid_regnumbers"
.comment "testing illogical register numbers"

	zjmp%:main
fork:
	lfork%:fork2
	sti r2d2, %:live, %1   
	ld %0, r6
	zjmp%:live
main:													
	lfork %:fork
	sti r11111, %:live, %1
	ld %0, r6
	zjmp%:live							
fork2:
	sti r-55, %:live, %1
	ld %0, r	6
	zjmp%:live
live:
	live %0
	ld %0, r 6
	zjmp%:main
			