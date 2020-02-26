.name       "Batman"
	.comment    "This city needs me"

loop:
	        sti r1, %:live, %1    # <-- operation 'sti' is pointed to by the label 'loop'
live:
	        live %0               # <-- operation 'live' is pointed to by the label 'live'
	        ld %0, r2             # <-- and this operation is not pointed to by any labels
	        zjmp %:loop
