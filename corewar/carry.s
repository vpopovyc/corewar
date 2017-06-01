.name "carry"
.comment "for test carry"

and3:	and	%-5, -5, r3
		zjmp %:and4
		live %-1
and4:	and	%5, 0, r3
		st r3, 1
		zjmp %0
		live %-1
