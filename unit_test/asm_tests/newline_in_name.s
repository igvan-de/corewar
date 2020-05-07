.name "zor
k"
.comment "I'M ALIIIIVE"

l2:		sti r00001, %:live, %1
		and r00001, %0, r0001

live:	live %1
		zjmp %:live
