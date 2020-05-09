.name 		"laugh"
.comment	"this is another comment"

hello:
	sti		r1, %:alive, %1
	fork	%:alive
	add		r2, r3, r4
.comment	"this is another comment"

alive:
	live	%0
	zjmp	%:alive
