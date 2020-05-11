.name "lldi carry"
.comment "testing lldi operation effect on cursor carry flag"

live:
	live %0
lldi %1, %:live, r2
zjmp %:live
sti r2, %600, %600
