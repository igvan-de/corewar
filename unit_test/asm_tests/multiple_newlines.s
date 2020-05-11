.name       "multiple newlines"
	.comment    "test performance when file has multiple newlines at the end of the file"

	ld	%50, r2
	ld	%100, r3	
	add r2, r3, r4
	add r6, r5, r9
	zjmp	%:sti	
sti:
	sti r9, %23, %2834
sti:
	sti r2, %23, %2834
sti:
	sti r3, %23, %2834





