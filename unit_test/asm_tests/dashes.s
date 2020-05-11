.name "dashes"
.comment "testing for dashes in labels"

hel-lo:
	sti		r1, %:alive, %1
	fork	%:alive
	add		r2, r3, r4

al-ive:
	live	%0
	zjmp	%:alive
