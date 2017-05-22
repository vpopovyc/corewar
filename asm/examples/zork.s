.name "zork"
.comment "I'M ALIIIIVE"
	xor 4, r2, r3
	sti r1,        :live,%1


l2:	sti r1, %:live, %1
	and r1, %0, r1

l2:	live %1
	zjmp %:live

l3:
live:	live %1
           