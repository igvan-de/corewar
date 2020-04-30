.name       "empty_lines"
	.comment    "multiple empty lines"

	ld	%50, r2
	ld	%100, r3	
	add r2, r3, r4

	add r56, r45, r99
	zjmp	%:sti	
sti:
	sti r99, %23, %2834
	zjmp	%:end
sti:
	sti r2, %23, %2834

	zjmp	%:end
sti:
	sti r3, %23, %2834
