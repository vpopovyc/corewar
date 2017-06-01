.name "carry"
.comment "for test carry"

start:	ld	%0, r2
		zjmp %:and1
		live %-1
and1:	or	r1, r1, r3
		st r3, 1
		zjmp %:or2
		live %-1
or2:	or	%-500, %500, r3
		st r3, 1
		zjmp %:or3
		live %-1
or3:	or	%500, %500, r3
		st r3, 1
		zjmp %:or4
		live %-1
or4:	or	500, -50, r3
		st r3, 1
		zjmp %:or5
		live %-1
or5:	or	%500, -50, r3
		st r3, 1
		zjmp %:or6
		live %-1
or6:	or	500, %50, r3
		st r3, 1
		zjmp %:or7
		live %-1
or7:	or	-500, %-50, r3
		st r3, 1
		zjmp %0
		live %-1
