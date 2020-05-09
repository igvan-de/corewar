.name 		"laugh" .name "laugh"
.comment	"aff, just kidding" .comment	"aff, just kidding" #this is a test

hello:
	sti		r1, %:alive, %1
	fork	%:alive
	add		r2, r3, r4

alive:
	live	%0
	zjmp	%:alive
