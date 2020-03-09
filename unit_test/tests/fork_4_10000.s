.name "terminator"
.comment "Hasta la vista, baby!"

	zjmp%:main
fork:
	fork%:fork2
	sti r1, %:live, %1
	ld %0, r6
	zjmp%:live
main:
	fork %:fork
	sti r1, %:live, %1
	ld %0, r6
	zjmp%:live
fork2:
	sti r1, %:live, %1
	ld %0, r6
	zjmp%:live
live:
	live %0
	ld %0, r6
	zjmp%:main
