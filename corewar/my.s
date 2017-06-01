.name "name"
.comment "comment"

live:	live	%10
		ld		-4, r2
		ld		%15, r3
		st		r2, r4	
		st		r4, 1
		add		r1, r2, r3
		st		r3, 1
		sub		r1, r2, r3
		st		r3, 1
		ld		%0, r3
		zjmp	%:live
