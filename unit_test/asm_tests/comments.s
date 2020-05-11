.name "invalid_comments"
.comment "testing comments without hastags"

	zjmp%:main
fork:
	lfork%:fork2
	sti r1, %:live, %1                    #fdhsjhfksjhdfksdfks#
	ld %0, r6
	zjmp%:live
main:											# sjsjdfhgsjdfgsjdfs
	lfork %:fork
	sti r1, %:live, %1
	ld %0, r6
	zjmp%:live				#	hsgdjsgdjfsgfs
fork2:
	sti r1, %:live, %1
	ld %0, r6
	zjmp%:live
live:
	live %0
	ld %0, r6
	zjmp%:main
													#fsjdhf######skdfhksjdfs
