.name "kek"
.comment "top"

live:
	live %42
	ld %123, r5
	xor %5, r5, r4
	and %:live, r4, r6
	sti r6, :live, %123
	fork %:live
	xor %123, r5, r13
	zjmp %:live
