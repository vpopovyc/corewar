.name "carry"
.comment "for test carry"

start:	ld	%0, r2
		zjmp %:and1
		live %-1
and1:	and	r1, r1, r3
		zjmp %:and2
		live %-1
and2:	and	%-5, %-5, r3
		zjmp %:and3
		live %-1
and3:	and	%5, 15, r3
		st r3, 1
		zjmp %0
		live %-1
