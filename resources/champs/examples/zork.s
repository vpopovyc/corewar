.name "AAAA"
.comment "I'M ALIIIIVE"

load:	sti r2, %:live_3, %100
		zjmp %:live_1

l1:		sti r1, %:live_2, %1

l2:		sti r1, %:live_1, %1
		and r1, r2, r2
		zjmp %:load

live_1:	live %1
		zjmp %:live_2

live_2: live %1
		zjmp %:l2

live_3: 
