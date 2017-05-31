.name "zork"
.comment "I'M ALIIIIVE"
	xor	r1,r2,r3
	sti	r1,%15,%1
	and	r1,%0,r1
	live	%1
	zjmp	%-5
