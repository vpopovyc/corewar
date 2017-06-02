.name "name"
.comment "comment"

live:	ld %2, r2
		ld %3, r3
		ld %4, r4
		ld %5, r5
		ld %6, r6
		ld %7, r7
		ld %8, r8
		ld %9, r9
		ld %10, r10
		ld %11, r11
		ld %12, r12
		ld %13, r13
		ld %14, r14
		ld %0, r15
		fork %4
		zjmp %0
		st r2, 1
		st r3, 1
		st r4, 1
		st r5, 1
		st r6, 1
		st r7, 1
		st r8, 1
		st r9, 1
		st r10, 1
		st r11, 1
		ld %0, r15
