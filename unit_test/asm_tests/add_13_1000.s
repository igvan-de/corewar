.name       "add_test10"
	.comment    "50"

	ld	%50, r2
	ld	%100, r3	
	add r2, r3, r4
	add r6, r5, r9
	zjmp	%:sti	
sti:
	sti r9, %23, %2834
	zjmp	%:end
sti:
	sti r2, %23, %2834
	zjmp	%:end
sti:
	sti r3, %23, %2834
	zjmp	%:end
end:

