.name "NEW"
.comment "TESTING"

live:
ld %123, r5
sti r5, %259, %1
ldi %130, r5, r4
xor r4, r5, r13
live %1
zjmp %:live
