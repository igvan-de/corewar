.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r0000101, %:live, %1
		and r0000101, %0, r000101

live:	live %1
		zjmp %:live
