.name "Infant Annihilator"
.comment "Soil the Stillborn"

start:
	st r1, 6

live:
	live %-42
	fork %:live
	add	r10, r10, r10
	zjmp %:live
